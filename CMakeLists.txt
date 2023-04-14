cmake_minimum_required(VERSION 3.12)
project(gomoku)

# Set C++ standard
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Find Boost.Asio and SFML
find_package(Boost COMPONENTS system thread REQUIRED)
find_package(SFML 2.5 COMPONENTS graphics window system REQUIRED)

# Check if Boost.Asio and SFML were found
if(NOT Boost_FOUND OR NOT SFML_FOUND)
    message(STATUS "Boost.Asio and/or SFML not found. Attempting to install...")
    if(UNIX)
        execute_process(COMMAND sudo apt-get update)
        execute_process(COMMAND sudo apt-get -y install libboost-all-dev libsfml-dev)
    elseif(WIN32)
        # Check if Conan is installed
        find_program(CONAN_BIN NAMES conan)
        if(NOT CONAN_BIN)
            message(STATUS "Conan not found. Attempting to install...")
            execute_process(COMMAND pip install conan)
        endif()
        # Install missing dependencies using Conan
        execute_process(COMMAND conan install ${CMAKE_SOURCE_DIR} --build=missing)
    else()
        message(FATAL_ERROR "Unsupported operating system")
    endif()
    # Attempt to find Boost.Asio and SFML again
    find_package(Boost COMPONENTS system thread REQUIRED)
    find_package(SFML 2.5 COMPONENTS graphics window system REQUIRED)
endif()

set(GOMOKU_HPP ./src/Action/Action.hpp
                ./src/Action/IAction.hpp
                ./src/Components/Button.hpp
                ./src/Components/Textbox.hpp
                ./src/Components/Timer.hpp
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
                ./src/Networking/Client.hpp
                ./src/Networking/Host.hpp
                ./src/Networking/Session.hpp
                ./src/StateMachine/Core.hpp
                ./src/StateMachine/State.hpp
                ./src/StateMachine/StateMachine.hpp
                ./src/States/GameState.hpp
                ./src/States/JoinLobbyState.hpp
                ./src/States/LobbyState.hpp
                ./src/States/MainState.hpp
                ./src/States/ModeSelectLocal.hpp
                ./src/States/SettingsState.hpp)

set(GOMOKU_CPP ./src/Action/Action.cpp
                ./src/Components/Button.cpp
                ./src/Components/Textbox.cpp
                ./src/Components/Timer.cpp
                ./src/Encapsulation/SFML/Font.cpp
                ./src/Encapsulation/SFML/GraphicLoader.cpp
                ./src/Encapsulation/SFML/Mouse.cpp
                ./src/Encapsulation/SFML/RectangleShape.cpp
                ./src/Encapsulation/SFML/RenderWindow.cpp
                ./src/Encapsulation/SFML/Sprite.cpp
                ./src/Encapsulation/SFML/Text.cpp
                ./src/Encapsulation/SFML/Texture.cpp
                ./src/Networking/Client.cpp
                ./src/Networking/Host.cpp
                ./src/Networking/Session.cpp
                ./src/StateMachine/Core.cpp
                ./src/StateMachine/State.cpp
                ./src/StateMachine/StateMachine.cpp
                ./src/States/GameState.cpp
                ./src/States/JoinLobbyState.cpp
                ./src/States/LobbyState.cpp
                ./src/States/MainState.cpp
                ./src/States/ModeSelectLocal.cpp
                ./src/States/SettingsState.cpp
                ./src/main.cpp)

# Add executable target
add_executable(gomoku ${GOMOKU_CPP} ${GOMOKU_HPP})

# Link with Boost.Asio and SFML libraries
target_link_libraries(gomoku Boost::system Boost::thread sfml-graphics sfml-window sfml-system)

# Set output directory based on operating system
if(UNIX)
    set_target_properties(gomoku PROPERTIES RUNTIME_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}")
elseif(WIN32)
    set_target_properties(gomoku PROPERTIES RUNTIME_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}")
    # Set Conan build type
    set(CONAN_BUILD_TYPE "Release")
    # Include Conan-generated files
    include(${CMAKE_BINARY_DIR}/conanbuildinfo.cmake)
    conan_basic_setup(TARGETS)
    # Link with Conan-generated libraries
    target_link_libraries(gomoku CONAN_PKG::boost CONAN_PKG::sfml)
endif()
