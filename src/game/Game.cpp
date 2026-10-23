#include "game/Game.h"
#include "game/Constants.h"
#include "utils/Logger.h"

#include <logic/Random.h>
#include <logic/StopWatch.h>

DJGame::Game::Game(const unsigned int& windowWidth, const unsigned int& windowHeight) {
    Logger::getInstance().log(LogLevel::INFO, "Game.cpp: Game constructor called");

    // Get the desktop resolution and set the window position to the center of the screen
    const sf::VideoMode desktopMode = sf::VideoMode::getDesktopMode();
    const unsigned int screenWidth = desktopMode.width;
    const unsigned int screenHeight = desktopMode.height;
    m_window = std::make_shared<sf::RenderWindow>(sf::VideoMode(windowWidth, windowHeight), "Doodle Jump",
                                                  sf::Style::Titlebar | sf::Style::Close | sf::Style::Resize);
    // m_window->setVerticalSyncEnabled(false);
    m_window->setFramerateLimit(Constants::Screen::FPS);
    m_window->setPosition(sf::Vector2i(static_cast<int>((screenWidth - windowWidth) / 2),
                                       static_cast<int>((screenHeight - windowHeight) / 2)));

    // Set the view
    m_view.setSize(static_cast<float>(windowWidth), static_cast<float>(windowHeight));

    // Factory
    m_factory = std::make_unique<ConcreteFactory>(*m_window);

    // Player
    Logger::getInstance().log(LogLevel::INFO, "Game.cpp: Creating player");
    m_player = m_factory->createPlayer((static_cast<float>(windowWidth) / 2) - 150, static_cast<float>(windowHeight),
                                       50, 50, 90);

    // Player View
    m_playerView = std::make_unique<PlayerView>(m_player.get());

    // Platforms
    Logger::getInstance().log(LogLevel::INFO, "Game.cpp: Creating platforms");
    const int amountPlatforms = Random::getInstance().getRandomValue(4, 8);
    for (int i = 0; i < amountPlatforms; ++i) {
        const int x = Random::getInstance().getRandomValue(0, static_cast<int>(windowWidth) - 100);
        const int y = Random::getInstance().getRandomValue(0, static_cast<int>(windowHeight) - 100);
        m_platforms.emplace_back(m_factory->createPlatform(Platform::Type::STATIC, x, y, 100, 20));
    }
    m_platforms.emplace_back(m_factory->createPlatform(Platform::Type::HORIZONTAL, 50, 50, 100, 20));
    m_platforms.emplace_back(m_factory->createPlatform(Platform::Type::VERTICAL, 200, 200, 100, 20));
    m_platforms.emplace_back(m_factory->createPlatform(Platform::Type::TEMPORARY, 300, 300, 100, 20));

    // Platform Views
    Logger::getInstance().log(LogLevel::INFO, "Game.cpp: Creating Platform views");
    for (const auto& platform : m_platforms) {
        m_platformViews.emplace_back(std::make_shared<PlatformView>(platform.get()));
    }

    // Background Tiles & Views
    Logger::getInstance().log(LogLevel::INFO, "Game.cpp: Creating background tiles");
    const int N = 30;
    const int amountTilesX = (windowWidth / N) + 1;
    const int amountTilesY = (windowHeight / N) + 2;
    for (int i = -1; i < amountTilesX; ++i) {
        for (int j = -1; j < amountTilesY - 1; ++j) {
            m_bgTiles.emplace_back(m_factory->createBGTile(i * N, j * N, N, N));
            m_bgTileViews.emplace_back(std::make_shared<BGTileView>(m_bgTiles.back().get()));
        }
    }

    // Bonuses
    Logger::getInstance().log(LogLevel::INFO, "Game.cpp: Creating bonuses");
    constexpr int amountBonuses = 1;
    for (int i = 0; i < amountBonuses; ++i) {
        const int x = Random::getInstance().getRandomValue(0, static_cast<int>(windowWidth) - 100);
        const int y = -1000;
        m_bonuses.emplace_back(m_factory->createBonus(x, y, 20, 20));
        m_bonusViews.emplace_back(std::make_shared<BonusView>(m_bonuses.back().get()));
    }

    // Camera
    m_camera = std::make_unique<Camera>(*m_window, m_player, m_view);

    // Score
    m_score = std::make_unique<Score>(m_player.get());

    // Score text
    if (!m_font.loadFromFile("../assets/fonts/DoodleJump.ttf")) {
        Logger::getInstance().log(LogLevel::ERROR, "Game.cpp: Font not loaded");
        m_window->close();
        exit(1);
    }

    m_scoreText.setFont(m_font);
    m_scoreText.setCharacterSize(24);
    m_scoreText.setFillColor(sf::Color::Magenta);
    m_scoreText.setPosition(10, 10);
    m_scoreText.setString("Score: " + std::to_string(m_score->getScore()));
}
DJGame::Game::~Game() {
    Logger::getInstance().log(LogLevel::INFO, "Game.cpp: Game destructor called");

    // Clear the vectors
    m_platforms.clear();
    m_platformViews.clear();
    m_bgTiles.clear();
    m_bgTileViews.clear();
    m_bonuses.clear();
    m_bonusViews.clear();

    // Close the window
    m_window->close();
}

void DJGame::Game::run() {
    // sf::Clock clock;
    StopWatch::getInstance().start();
    while (m_window->isOpen()) {
        // For debugging purposes, set delta time to 0.0167
        // const float deltaTime = 0.0167;
        // const float deltaTime = clock.restart().asSeconds();
        const auto deltaTime = StopWatch::getInstance().getElapsedTime();
        Logger::getInstance().log(LogLevel::INFO, "Game.cpp: Delta time: " + Logger::toString(deltaTime));
        handleEvents();
        update(deltaTime);
        render();
    }
}

void DJGame::Game::handleEvents() {
    sf::Event event{};

    while (m_window->pollEvent(event)) {
        // Lambda functions to get the new window size
        auto newHeight = [&event]() -> int {
            const auto res =
                (event.size.height < Constants::Screen::MIN_HEIGHT) ? Constants::Screen::MIN_HEIGHT : event.size.height;
            Logger::getInstance().log(LogLevel::DEBUG,
                                      "Game.cpp: Event size width: " + Logger::toString(event.size.width));
            Logger::getInstance().log(LogLevel::DEBUG,
                                      "Game.cpp: Min width: " + Logger::toString(Constants::Screen::MIN_WIDTH));
            Logger::getInstance().log(LogLevel::INFO, "Game.cpp: Resizing window height");
            Logger::getInstance().log(LogLevel::DEBUG, "Game.cpp: Resizing window height to " + Logger::toString(res));
            return res;
        };
        auto newWidth = [&event]() -> int {
            const auto res =
                (event.size.width < Constants::Screen::MIN_WIDTH) ? Constants::Screen::MIN_WIDTH : event.size.width;
            Logger::getInstance().log(LogLevel::INFO, "Game.cpp: Resizing window width");
            Logger::getInstance().log(LogLevel::DEBUG, "Game.cpp: Resizing window width to " + Logger::toString(res));
            return res;
        };

        // Handle events
        switch (event.type) {
        case sf::Event::Closed:
            m_window->close();
            break;

        case sf::Event::Resized:
            // Resize the window but can't make it smaller than min_values.
            // TODO: Crash happening here
            // m_view.setSize({ static_cast<float>(newWidth()), static_cast<float>(newHeight()) });
            Logger::getInstance().log(LogLevel::INFO, "Game.cpp: " + Logger::toString(static_cast<float>(newWidth())));
            Logger::getInstance().log(LogLevel::INFO, "Game.cpp: " + Logger::toString(static_cast<float>(newHeight())));
            break;

        case sf::Event::KeyPressed:
            if (event.key.code == sf::Keyboard::Escape) {
                Logger::getInstance().log(LogLevel::INFO, "Game.cpp: Escape key pressed, closing window");
                m_window->close();
                break;
            }
            if (event.key.code == sf::Keyboard::Left) {
                Logger::getInstance().log(LogLevel::INFO, "Game.cpp: Left key pressed, moving player left");
                m_player->moveLeft();
                m_playerView->left();
                break;
            }
            if (event.key.code == sf::Keyboard::Right) {
                Logger::getInstance().log(LogLevel::INFO, "Game.cpp: Right key pressed, moving player right");
                m_player->moveRight();
                m_playerView->right();
                break;
            }
        default:
            // Not moving the player
            m_player->stopMovement();
            break;
        }
    }
}

void DJGame::Game::update(float deltaTime) {

    if (m_player->getY() > m_camera->getViewBottom()) {
        // TODO: Game over screen
        Logger::getInstance().log(LogLevel::INFO, "Game.cpp: Game over");

        // Show Game Over text
        sf::Font font;
        if (!font.loadFromFile("../assets/fonts/DoodleJump.ttf")) {
            Logger::getInstance().log(LogLevel::ERROR, "Game.cpp: Font not loaded");
            m_window->close();
            exit(1);
        }

        sf::Text text;
        text.setFont(font);
        text.setString("Game Over!\nScore: " + std::to_string(m_score->getScore()));
        text.setCharacterSize(100);
        text.setFillColor(sf::Color::Red);
        text.setPosition(m_camera->getViewLeft() + 75, m_camera->getViewTop() + 100);

        // Draw and display the text
        m_window->draw(text);
        m_window->display();

        // Sleep for 3 seconds
        sf::sleep(sf::seconds(5));

        // Close the window
        m_window->close();
        exit(0);
    }

    // update player logic and view
    m_player->update(deltaTime);
    m_playerView->update();

    // collision detection with platforms
    for (const auto& platform : m_platforms) {
        m_player->interact(*platform, m_score.get());
    }

    m_score->update();

    // update bonuses
    m_camera->updateBonuses(deltaTime, m_bonuses, m_bonusViews);

    // collision detection with bonuses
    for (const auto& bonus : m_bonuses) {
        m_player->interact(*bonus, m_score.get());
    }

    // update platforms
    m_camera->updatePlatforms(deltaTime, m_platforms, m_platformViews);

    // update background tiles
    m_camera->updateBGTiles(m_bgTiles, m_bgTileViews);

    // update score text
    m_camera->updateScoreText(m_scoreText, m_score->getScore());

    // // shake camera
    // if (m_score->getScore() % 1000 == 0) {
    //     m_camera->shake(deltaTime, 2, 100);
    // }

    // update camera
    m_camera->update(deltaTime);
}

void DJGame::Game::render() {
    m_window->clear();

    // render background tiles
    for (auto& m_bgTileView : m_bgTileViews) {
        m_bgTileView->render(*m_window);
    }

    // render platforms
    for (auto& m_platformView : m_platformViews) {
        m_platformView->render(*m_window);
    }

    // render bonuses
    for (auto& m_bonusView : m_bonusViews) {
        m_bonusView->render(*m_window);
    }

    // render score
    m_window->draw(m_scoreText);

    // render player
    m_playerView->render(*m_window);

    m_camera->apply(*m_window);

    m_window->display();
}
