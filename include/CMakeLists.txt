add_library(pbr INTERFACE)

set(MY_HEADERS
  ${CMAKE_SOURCE_DIR}/include/mce.hpp
  ${CMAKE_SOURCE_DIR}/include/rng.hpp
  ${CMAKE_SOURCE_DIR}/include/sampler.hpp
)

set(COMPILE_CONFIG -O3 -Wextra -Wall -Werror)

target_sources(pbr
  INTERFACE
  FILE_SET HEADERS
  BASE_DIRS ${CMAKE_SOURCE_DIR}/include
  FILES ${MY_HEADERS} 
)

target_compile_options(pbr INTERFACE ${COMPILE_CONFIG})