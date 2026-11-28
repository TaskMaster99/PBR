add_executable(main.exe)

target_sources(main.exe PRIVATE main.cpp)

target_compile_options(main.exe PUBLIC -O3 -march=native)