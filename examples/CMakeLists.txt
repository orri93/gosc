set(gos_c_example_generator_target generator)

list(APPEND gos_c_example_generator_source
  ${gos_c_xopt_src}
  generator.c)

#list(APPEND gos_c_example_generator_definitions
#  _CRT_SECURE_NO_WARNINGS)

list(APPEND gos_c_example_generator_include
  ${gos_c_library_include}
  ${gos_c_xopt_include})

list(APPEND gos_c_example_generator_libraries
  ${gos_c_library_target})

#if (HAVE_LIB_M)
#  list(APPEND gos_c_example_generator_libraries m)
#endif (HAVE_LIB_M)

add_executable(${gos_c_example_generator_target}
  ${gos_c_example_generator_source})

if (gos_c_example_generator_definitions)
  target_compile_definitions(${gos_c_example_generator_target} PUBLIC
    ${gos_c_example_generator_definitions})
endif ()

target_include_directories(${gos_c_example_generator_target} PUBLIC
  ${gos_c_example_generator_include})

target_link_libraries(${gos_c_example_generator_target}
  ${gos_c_example_generator_libraries})

install(TARGETS ${gos_c_example_generator_target}
  RUNTIME DESTINATION bin)
