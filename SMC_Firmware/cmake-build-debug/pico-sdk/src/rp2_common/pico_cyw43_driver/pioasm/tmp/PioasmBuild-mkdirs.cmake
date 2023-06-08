# Distributed under the OSI-approved BSD 3-Clause License.  See accompanying
# file Copyright.txt or https://cmake.org/licensing for details.

cmake_minimum_required(VERSION 3.5)

file(MAKE_DIRECTORY
  "/Users/john/Desktop/RP2040/pico-sdk/tools/pioasm"
  "/Users/john/Desktop/RP2040/pico-template/cmake-build-debug/pioasm"
  "/Users/john/Desktop/RP2040/pico-template/cmake-build-debug/pico-sdk/src/rp2_common/pico_cyw43_driver/pioasm"
  "/Users/john/Desktop/RP2040/pico-template/cmake-build-debug/pico-sdk/src/rp2_common/pico_cyw43_driver/pioasm/tmp"
  "/Users/john/Desktop/RP2040/pico-template/cmake-build-debug/pico-sdk/src/rp2_common/pico_cyw43_driver/pioasm/src/PioasmBuild-stamp"
  "/Users/john/Desktop/RP2040/pico-template/cmake-build-debug/pico-sdk/src/rp2_common/pico_cyw43_driver/pioasm/src"
  "/Users/john/Desktop/RP2040/pico-template/cmake-build-debug/pico-sdk/src/rp2_common/pico_cyw43_driver/pioasm/src/PioasmBuild-stamp"
)

set(configSubDirs )
foreach(subDir IN LISTS configSubDirs)
    file(MAKE_DIRECTORY "/Users/john/Desktop/RP2040/pico-template/cmake-build-debug/pico-sdk/src/rp2_common/pico_cyw43_driver/pioasm/src/PioasmBuild-stamp/${subDir}")
endforeach()
