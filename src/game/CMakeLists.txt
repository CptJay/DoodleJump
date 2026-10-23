# Game library

add_library(game_component
        Camera.cpp
        ConcreteFactory.cpp
        Game.cpp
        GameView.cpp
        PlatformView.cpp
        PlayerView.cpp
        EntityView.cpp
        BGTileView.cpp
        BonusView.cpp
        )

# Include directories for header files
target_include_directories(game_component PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/include)

# Link the logic library
target_link_libraries(game_component PUBLIC logic)

# Link the SFML libraries
target_link_libraries(game_component PUBLIC sfml-system sfml-graphics sfml-window)