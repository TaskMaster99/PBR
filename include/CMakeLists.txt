add_library(pbr INTERFACE)

set(MY_HEADERS
  ${CMAKE_CURRENT_SOURCE_DIR}/utils.hpp
  ${CMAKE_CURRENT_SOURCE_DIR}/integrator.hpp
  ${CMAKE_CURRENT_SOURCE_DIR}/rng.hpp
  ${CMAKE_CURRENT_SOURCE_DIR}/sampler.hpp
  ${CMAKE_CURRENT_SOURCE_DIR}/pdf.hpp
  ${CMAKE_CURRENT_SOURCE_DIR}/image.hpp
  ${CMAKE_CURRENT_SOURCE_DIR}/ray.hpp
  ${CMAKE_CURRENT_SOURCE_DIR}/vecmath.hpp
  ${CMAKE_CURRENT_SOURCE_DIR}/primitive.hpp
  ${CMAKE_CURRENT_SOURCE_DIR}/transform.hpp
  ${CMAKE_CURRENT_SOURCE_DIR}/camera.hpp

)

set(COMPILE_CONFIG -O3 -Wextra -Wall -Werror -march=native)

target_sources(pbr
  INTERFACE
  FILE_SET HEADERS
  BASE_DIRS ${CMAKE_CURRENT_SOURCE_DIR}
  FILES ${MY_HEADERS} 
)

target_compile_options(pbr INTERFACE ${COMPILE_CONFIG})