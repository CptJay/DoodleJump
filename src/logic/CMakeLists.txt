# Logic library

add_library(logic
        AbstractFactory.cpp
        Bonus.cpp
        Platform.cpp
        Player.cpp
        Random.cpp
        StopWatch.cpp
        World.cpp
        EntityModel.cpp
        Observer.cpp
        Score.cpp
        BGTile.cpp)

target_include_directories(logic PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/include)