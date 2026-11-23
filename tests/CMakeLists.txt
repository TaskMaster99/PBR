include(FetchContent)

FetchContent_Declare(
  Catch2
  GIT_REPOSITORY https://github.com/catchorg/Catch2.git
  GIT_TAG v3.16.1
  GIT_SHALLOW    TRUE
)
FetchContent_MakeAvailable(Catch2)

set(MY_SRC_FILES
  ${CMAKE_CURRENT_SOURCE_DIR}/vecmath_test.cpp
  ${CMAKE_CURRENT_SOURCE_DIR}/rng_test.cpp
  ${CMAKE_CURRENT_SOURCE_DIR}/rgb_test.cpp
  ${CMAKE_CURRENT_SOURCE_DIR}/sphere_test.cpp
  ${CMAKE_CURRENT_SOURCE_DIR}/plane_test.cpp
  ${CMAKE_CURRENT_SOURCE_DIR}/transformation_test.cpp

)

add_executable(pbr_test.exe)

target_sources(pbr_test.exe PRIVATE ${MY_SRC_FILES})

target_link_libraries(pbr_test.exe PRIVATE pbr Catch2::Catch2WithMain)
