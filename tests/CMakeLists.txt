if (GOS_USE_GTEST_PACKAGE OR GOS_USE_GTEST_DISCOVER)
  include(GoogleTest)
endif ()

set(gos_c_gos_test_target gosctest)
set(gos_c_gos_test_name gosctest)

list(APPEND gos_c_gos_test_source
  interpolate.cpp
  statistics.cpp
  geometry.cpp
  dynamic.cpp
  nearest.cpp
  screen.cpp
  signal.cpp
  noise.cpp
  color.cpp
  scale.cpp
  text.cpp
  data.cpp)

#list(APPEND gos_c_gos_test_definitions
#  _CRT_SECURE_NO_WARNINGS)

list(APPEND gos_c_gos_test_include
  ${gos_c_gtest_include}
  ${gos_c_include})

list(APPEND gos_c_gos_test_libraries
  ${gos_c_gtest_libraries}
  ${gos_c_library_target})

if (HAVE_LIB_M)
  list(APPEND gos_c_gos_test_libraries m)
endif (HAVE_LIB_M)

add_executable(${gos_c_gos_test_target}
  ${gos_c_gos_test_source})

if (gos_c_gos_test_definitions)
  target_compile_definitions(${gos_c_gos_test_target} PUBLIC
    ${gos_c_gos_test_definitions})
endif ()

target_include_directories(${gos_c_gos_test_target} PUBLIC
  ${gos_c_gos_test_include})

target_link_libraries(${gos_c_gos_test_target}
  ${gos_c_gos_test_libraries})

#if(CLANG_TIDY_EXE)
#  set_target_properties(${gos_c_gos_test_target} PROPERTIES
#    CXX_CLANG_TIDY "${CMAKE_CXX_CLANG_TIDY}")
#endif()

if (GOS_USE_GTEST_PACKAGE OR GOS_USE_GTEST_DISCOVER)
  gtest_discover_tests(${gos_c_gos_test_target}
    XML_OUTPUT_DIR ${CMAKE_CURRENT_BINARY_DIR}/xmlout)
else ()
  add_test(NAME ${gos_c_gos_test_name} COMMAND
    ${gos_c_gos_test_target})
endif ()
