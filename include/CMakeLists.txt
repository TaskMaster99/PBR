add_library(pbr INTERFACE)

set(MY_HEADERS
  ${CMAKE_SOURCE_DIR}/include/integrator.hpp
  ${CMAKE_SOURCE_DIR}/include/rng.hpp
  ${CMAKE_SOURCE_DIR}/include/sampler.hpp
  ${CMAKE_SOURCE_DIR}/include/pdf.hpp
  ${CMAKE_SOURCE_DIR}/include/exploit.hpp
  ${CMAKE_SOURCE_DIR}/include/image.hpp
  ${CMAKE_SOURCE_DIR}/include/ray.hpp
  ${CMAKE_SOURCE_DIR}/include/vecmath.hpp
  ${CMAKE_SOURCE_DIR}/include/primitive.hpp

)

set(COMPILE_CONFIG -O3 -Wextra -Wall -Werror -march=native)

target_sources(pbr
  INTERFACE
  FILE_SET HEADERS
  BASE_DIRS ${CMAKE_SOURCE_DIR}/include
  FILES ${MY_HEADERS} 
)

target_compile_options(pbr INTERFACE ${COMPILE_CONFIG})