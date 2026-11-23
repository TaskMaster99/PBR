add_executable(generateFrame.exe)

target_sources(generateFrame.exe PRIVATE generateFrame.cpp)

target_link_libraries(generateFrame.exe PRIVATE pbr)

add_executable(plane.exe)

target_sources(plane.exe PRIVATE main.cpp)

target_link_libraries(plane.exe PRIVATE pbr)