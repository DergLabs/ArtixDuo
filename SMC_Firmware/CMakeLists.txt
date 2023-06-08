# Set minimum required version of CMake
cmake_minimum_required(VERSION 3.12)

# Include build functions from Pico SDK
include($ENV{PICO_SDK_PATH}/external/pico_sdk_import.cmake)
include($ENV{PICO_SDK_PATH}/tools/CMakeLists.txt)

# Set name of project (as PROJECT_NAME) and C/C   standards
project(SMCFW C CXX ASM)
set(CMAKE_C_STANDARD 11)
set(CMAKE_CXX_STANDARD 17)

# Creates a pico-sdk subdirectory in our project for the libraries
pico_sdk_init()

link_directories(${CMAKE_SOURCE_DIR}/lib)

# Tell CMake where to find the executable source file
add_executable(${PROJECT_NAME} 
    ${CMAKE_CURRENT_LIST_DIR}/main.c
)

AUX_SOURCE_DIRECTORY(lib SUB_SOURCES)

target_sources(
    ${PROJECT_NAME}
    PUBLIC
    ${SUB_SOURCES}
)


target_include_directories(${PROJECT_NAME} PUBLIC
    ${CMAKE_CURRENT_LIST_DIR}
    ${CMAKE_CURRENT_LIST_DIR}/lib
)


# Create map/bin/hex/uf2 files
pico_add_extra_outputs(${PROJECT_NAME})

# Link to pico_stdlib (gpio, time, etc. functions)
target_link_libraries(${PROJECT_NAME} 
    pico_stdlib
    hardware_i2c
    hardware_irq
    hardware_pwm
)

# Enable usb output, disable uart output
pico_enable_stdio_usb(${PROJECT_NAME} 1)
pico_enable_stdio_uart(${PROJECT_NAME} 0)