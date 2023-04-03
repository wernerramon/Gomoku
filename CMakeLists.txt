cmake_minimum_required(VERSION 3.6)
project(gomoku)

set(GOMOKU_HPP ./src/Components/Button.hpp 
                ./src/Encapsulation/Event.hpp
                ./src/Encapsulation/GraphicDataTypes.hpp
                ./src/Encapsulation/IFont.hpp
                ./src/Encapsulation/IGraphic.hpp
                ./src/Encapsulation/IGraphicLoader.hpp
                ./src/Encapsulation/IMouse.hpp
                ./src/Encapsulation/IRectangleShape.hpp
                ./src/Encapsulation/IRenderWindow.hpp
                ./src/Encapsulation/ISprite.hpp
                ./src/Encapsulation/IText.hpp
                ./src/Encapsulation/ITexture.hpp
                ./src/Encapsulation/SFML/Font.hpp
                ./src/Encapsulation/SFML/GraphicLoader.hpp
                ./src/Encapsulation/SFML/Mouse.hpp
                ./src/Encapsulation/SFML/RectangleShape.hpp
                ./src/Encapsulation/SFML/RenderWindow.hpp
                ./src/Encapsulation/SFML/Sprite.hpp
                ./src/Encapsulation/SFML/Text.hpp
                ./src/Encapsulation/SFML/Texture.hpp
                ./src/StateMachine/Core.hpp
                ./src/StateMachine/State.hpp
                ./src/StateMachine/StateMachine.hpp
                ./src/States/GameState.hpp
                ./src/States/MainState.hpp
                ./src/States/ModeSelectLocal.hpp)

set(GOMOKU_CPP ./src/Components/Button.cpp 
                ./src/Encapsulation/SFML/Font.cpp
                ./src/Encapsulation/SFML/GraphicLoader.cpp
                ./src/Encapsulation/SFML/Mouse.cpp
                ./src/Encapsulation/SFML/RectangleShape.cpp
                ./src/Encapsulation/SFML/RenderWindow.cpp
                ./src/Encapsulation/SFML/Sprite.cpp
                ./src/Encapsulation/SFML/Text.cpp
                ./src/Encapsulation/SFML/Texture.cpp
                ./src/StateMachine/Core.cpp
                ./src/StateMachine/State.cpp
                ./src/StateMachine/StateMachine.cpp
                ./src/States/GameState.cpp
                ./src/States/MainState.cpp
                ./src/States/ModeSelectLocal.cpp
                ./src/main.cpp)

include(FetchContent)
FetchContent_Declare(SFML
        GIT_REPOSITORY https://github.com/SFML/SFML.git
        GIT_TAG 2.6.x)
FetchContent_MakeAvailable(SFML)

find_package(Boost 1.69.0 COMPONENTS chrono system thread REQUIRED)

find_package(OpenGL REQUIRED OPTIONAL_COMPONENTS OpenGL)
include_directories(${OPENGL_INCLUDE_DIR})
add_executable(gomoku ${GOMOKU_CPP} ${GOMOKU_HPP})

target_link_libraries(gomoku sfml-graphics sfml-audio
        ${OPENGL_LIBRARIES} ${Boost_SYSTEM_LIBRARY} ${Boost_THREAD_LIBRARY} ${Boost_CHRONO_LIBRARY})
target_link_directories(gomoku PUBLIC ${Boost_LIBRARY_DIRS})

target_compile_features(gomoku PRIVATE cxx_std_17)
if (WIN32 AND BUILD_SHARED_LIBS)
    add_custom_command(TARGET gomoku POST_BUILD
            COMMAND ${CMAKE_COMMAND} -E copy $<TARGET_RUNTIME_DLLS:gomoku> $<TARGET_FILE_DIR:gomoku> COMMAND_EXPAND_LISTS)
endif()

install(TARGETS gomoku)