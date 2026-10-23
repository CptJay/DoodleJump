add_library(utils STATIC
        Logger.cpp)

target_include_directories(utils PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/include)