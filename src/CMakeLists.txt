list(APPEND gos_c_library_source
  interpolate.c
  statistics.c
  geometry.c
  dynamic.c
  signal.c
  noise.c
  color.c
  data.c)

list(APPEND gos_c_library_definitions
# _CRT_SECURE_NO_WARNINGS
  _USE_MATH_DEFINES)

if (GOS_PERLIN)
  list(APPEND gos_c_library_source perlin.c)
  list(APPEND gos_c_library_definitions
    GOS_PERLIN_FLOAT
    GOS_PERLIN_DOUBLE
    GOS_PERLIN_LERP_FUNCTION)
endif (GOS_PERLIN)

list(APPEND gos_c_library_include
  ${gos_c_include})

add_library(${gos_c_library_target}
  ${gos_c_library_source})

if (gos_c_library_definitions)
  target_compile_definitions(${gos_c_library_target} PUBLIC
    ${gos_c_library_definitions})
endif ()

target_include_directories(${gos_c_library_target} PUBLIC
  ${gos_c_library_include})

if (gos_c_library_public_header)
  set_target_properties(${gos_c_library_target}
    PROPERTIES PUBLIC_HEADER
    "${gos_c_library_public_header}")
endif ()

if (GOS_C_EMSCRIPTEN_BUILD)
  if (GOS_EM_ASSERTIONS)
    set(em_assertions 1)
  else ()
    set(em_assertions 0)
  endif ()
  set(EMCC_ARGS
    -I${gos_c_source_include} -I${gos_c_binary_include}
    -s ASSERTIONS=${em_assertions}
    -O3)
  list(APPEND gos_c_wasm_library_source ${gos_c_library_source})
  list(TRANSFORM gos_c_wasm_library_source PREPEND "${CMAKE_CURRENT_SOURCE_DIR}/")
  add_custom_command(
    TARGET ${gos_c_library_target} POST_BUILD
    COMMAND emcc ${gos_c_wasm_library_source} ${EMCC_ARGS} -o ${GOS_WASM_OUTPUT}
    DEPENDS ${gos_c_library_source} ${gos_c_library_public_header}
    COMMENT "Building GOS C Web Assembly Library"
    VERBATIM)
  set_target_properties(${gos_c_library_target} PROPERTIES
    RESOURCE "${CMAKE_CURRENT_BINARY_DIR}/${GOS_WASM_OUTPUT}")
endif ()

install(TARGETS ${gos_c_library_target}
  LIBRARY DESTINATION lib
  PUBLIC_HEADER DESTINATION include/gos
  ARCHIVE DESTINATION lib
  RESOURCE DESTINATION lib)

export(TARGETS ${gos_c_library_target} FILE gosc-targets.cmake)
