cmake_minimum_required(VERSION 3.2...3.27.8)

project (fp LANGUAGES CXX)
add_executable (fp src/fp.cpp)

project (epsilon-bad LANGUAGES CXX)
add_executable (epsilon-bad src/epsilon-bad.cpp)

project (hexfloat LANGUAGES CXX)
add_executable (hexfloat src/hexfloat.cpp)

project (specials LANGUAGES CXX)
add_executable (specials src/specials.cpp)
