cmake_minimum_required(VERSION 3.16)
project(chain VERSION 0.1.0)

include(CTest)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS ON)

string(APPEND CMAKE_CXX_FLAGS " -Wall -Wextra")
string(APPEND CMAKE_CXX_FLAGS_DEBUG " -fsanitize=address -fno-omit-frame-pointer")
string(APPEND CMAKE_EXE_LINKER_FLAGS_DEBUG " -fsanitize=address -fno-omit-frame-pointer")

find_package(SFML 2.5 COMPONENTS graphics REQUIRED)

add_executable(chain-sfml main.cpp chain.cpp ppstate.cpp)
target_link_libraries(chain-sfml PRIVATE sfml-graphics)

if (BUILD_TESTING)

  add_executable(chain.t chain.test.cpp chain.cpp ppstate.cpp)
  target_link_libraries(chain.t PRIVATE sfml-graphics)
  add_test(NAME chain.t COMMAND chain.t)

endif()
