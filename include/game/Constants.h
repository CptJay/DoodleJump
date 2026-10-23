#ifndef CONSTANTS_H
#define CONSTANTS_H

namespace DJGame::Constants {

/**
 * @brief Constants for the game
 */
struct Screen {
    static constexpr unsigned int WIDTH = 600;
    static constexpr unsigned int MIN_WIDTH = 400;
    static constexpr unsigned int HEIGHT = 900;
    static constexpr unsigned int MIN_HEIGHT = 600;
    static constexpr int FPS = 144;
    static constexpr int FRAME_DELAY = 1000 / FPS;
};
} // namespace DJGame::Constants

#endif // CONSTANTS_H
