cmake_minimum_required(VERSION 3.25)
project(Pong CXX)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Hint for Homebrew's SFML installation
set(SFML_DIR "/usr/local/opt/sfml/lib/cmake/SFML")
find_package(SFML 3 REQUIRED COMPONENTS Graphics Window System Audio)

# Define our executable using the book's project name
# Will have our unique source files
add_executable(Pong
        source_files/Pong.cpp
        source_files/Bat.cpp
        source_files/Ball.cpp)

# Link the SFML modules
target_link_libraries(Pong PRIVATE
        SFML::Graphics
        SFML::Window
        SFML::System
        SFML::Audio
)

# Tell CMake to look inside the header_files directory
target_include_directories(Pong PRIVATE header_files)

# Automatically copy asset folders to the build directory so SFML can find them
#file(COPY graphics sound fonts DESTINATION ${CMAKE_CURRENT_BINARY_DIR})