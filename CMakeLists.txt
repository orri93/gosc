cmake_minimum_required(VERSION 3.8.2)

project(GosC
  VERSION 1.0.0
  DESCRIPTION "Geirmundur Orri Sigurdsson C Library"
  LANGUAGES C CXX)

# Build Options
option(BUILD_TESTS "Build tests" OFF)
option(BUILD_EXAMPLES "Build examples" OFF)
option(BUILD_SHARED_LIBS "Build using shared libraries" OFF)
option(GOS_C_EMSCRIPTEN_BUILD "Build a Web Assembly Library with emscripten" OFF)

# Tidy Options
option(CLANG_TIDY_FIX_ERRORS
  "Perform fixes with Clang-Tidy even if compilation errors were found" OFF)
option(CLANG_TIDY_FIX "Perform fixes with Clang-Tidy" OFF)
option(CLANG_TIDY "Perform Clang-Tidy check" OFF)

# GOS Options
option(GOS_PERLIN "Perlin noise" OFF)
option(GOS_EM_ASSERTIONS "EMCC ASSERTIONS" OFF)

option(GOS_NEAREST_NEIGHBOR_TIME "Time Nearest Neighbor" OFF)

# GOS Test Options
option(GOS_USE_GTEST_DISCOVER
  "Use CMake Google Test descovery for unit tests" OFF)
option(GOS_USE_GTEST_PACKAGE
  "Use CMake GTest Package for unit tests" OFF)

set(GOS_BUILD_NUMBER "0" CACHE STRING "The build number")
set(GOS_WASM_OUTPUT "libgosc.bc" CACHE STRING "The Web Assembly Output")

set(gos_c_library_target gosc)

include(CheckLibraryExists)
CHECK_LIBRARY_EXISTS(m sin "" HAVE_LIB_M)

if (GOS_C_EMSCRIPTEN_BUILD)
  if (DEFINED ENV{EMSDK})
    set(GOS_C_EMSCRIPTEN_ROOT $ENV{EMSDK}/upstream/emscripten)
  else ()
    set(GOS_C_EMSCRIPTEN_ROOT "emsdk/upstream/emscripten" CACHE PATH "Emscripten path")
  endif ()
  set(CMAKE_TOOLCHAIN_FILE
    ${GOS_C_EMSCRIPTEN_ROOT}/cmake/Modules/Platform/Emscripten.cmake)
endif ()

set(TIDY_ARGUMENTS "-checks=*,-clang-analyzer-alpha.* "
  CACHE STRING "Arguments for Clang-Tidy check")
set(TIDY_FIX_ARGUMENTS "-list-checks=*,-clang-analyzer-alpha.* "
  CACHE STRING "Arguments for Clang-Tidy fix")
set(TIDY_FIX_ERRORS_ARGUMENTS "-checks=*,-clang-analyzer-alpha.* "
  CACHE STRING "Arguments for Clang-Tidy fix errors")

configure_file(
  "${CMAKE_CURRENT_SOURCE_DIR}/include/gos/version.h.in"
  "include/gos/version.h"
  @ONLY)

set(gos_c_source_include "${CMAKE_CURRENT_SOURCE_DIR}/include")
set(gos_c_binary_include "${CMAKE_CURRENT_BINARY_DIR}/include")

list(APPEND gos_c_include
  ${gos_c_source_include}
  ${gos_c_binary_include})
  
set(CMAKE_PLATFORM_INDEPENDENT_CODE ON)

string(TIMESTAMP GOS_CURRENT_YEAR "%Y" UTC)
set(GOS_COMPANYNAME "Geirmundur Orri Sigurdsson")
set(GOS_LEGALCOPYRIGHT "Copyright (C) ${GOS_CURRENT_YEAR} ${GOS_COMPANYNAME}")

list(APPEND gos_c_library_public_header
  "${CMAKE_CURRENT_BINARY_DIR}/include/gos/version.h")
list(APPEND gos_c_library_public_header
  "${CMAKE_CURRENT_SOURCE_DIR}/include/gos/data.h"
  "${CMAKE_CURRENT_SOURCE_DIR}/include/gos/text.h"
  "${CMAKE_CURRENT_SOURCE_DIR}/include/gos/line.h"
  "${CMAKE_CURRENT_SOURCE_DIR}/include/gos/types.h"
  "${CMAKE_CURRENT_SOURCE_DIR}/include/gos/scale.h"
  "${CMAKE_CURRENT_SOURCE_DIR}/include/gos/color.h"
  "${CMAKE_CURRENT_SOURCE_DIR}/include/gos/noise.h"
# "${CMAKE_CURRENT_SOURCE_DIR}/include/gos/perlin.h"
  "${CMAKE_CURRENT_SOURCE_DIR}/include/gos/signal.h"
  "${CMAKE_CURRENT_SOURCE_DIR}/include/gos/screen.h"
  "${CMAKE_CURRENT_SOURCE_DIR}/include/gos/mapping.h"
  "${CMAKE_CURRENT_SOURCE_DIR}/include/gos/nearest.h"
  "${CMAKE_CURRENT_SOURCE_DIR}/include/gos/dynamic.h"
  "${CMAKE_CURRENT_SOURCE_DIR}/include/gos/geometry.h"
  "${CMAKE_CURRENT_SOURCE_DIR}/include/gos/statistics.h"
  "${CMAKE_CURRENT_SOURCE_DIR}/include/gos/interpolate.h")

if(CLANG_TIDY)
  find_program(CLANG_TIDY_EXE
    NAMES "clang-tidy"
    DOC "Path to clang-tidy executable")
  if(CLANG_TIDY_EXE)
    if(CLANG_TIDY_FIX_ERRORS)
      set(CMAKE_CXX_CLANG_TIDY
        "${CLANG_TIDY_EXE}" "${TIDY_FIX_ERRORS_ARGUMENTS}-fix-errors")
      message(STATUS "Using clang-tidy with fix")
      message(STATUS "  ${CLANG_TIDY_EXE} ${TIDY_FIX_ERRORS_ARGUMENTS}-fix-errors")
    elseif(CLANG_TIDY_FIX)
      set(CMAKE_CXX_CLANG_TIDY "${CLANG_TIDY_EXE}" "${TIDY_FIX_ARGUMENTS}-fix")
      message(STATUS "Using clang-tidy with fix")
      message(STATUS "  ${CLANG_TIDY_EXE} ${TIDY_FIX_ARGUMENTS}-fix")
    else()
      set(CMAKE_CXX_CLANG_TIDY
        "${CLANG_TIDY_EXE}" "${TIDY_ARGUMENTS}")
      message(STATUS "Using clang-tidy")
      message(STATUS "  ${CLANG_TIDY_EXE} ${TIDY_ARGUMENTS}")
    endif()
  endif()
endif()

#set(Boost_USE_MULTITHREADED        ON)
#set(Boost_USE_STATIC_RUNTIME      OFF)
#if (BUILD_SHARED_LIBS)
#  set(Boost_USE_STATIC_LIBS       OFF)    
#else ()
#  set(Boost_USE_STATIC_LIBS        ON)
#endif ()

#list(APPEND needed_boost_package
#  program_options
#  filesystem
#  date_time
#  system
#  regex)
#list(APPEND needed_boost_libraries
#  Boost::program_options
#  Boost::filesystem
#  Boost::date_time
#  Boost::regex)

#if (GOS_USE_BOOST_LOG)
#  list(APPEND needed_boost_package
#    log_setup
#    log)
#  list(APPEND needed_boost_libraries
#    Boost::log_setup
#    Boost::log)
#endif ()

#find_package(Boost 1.70.0 COMPONENTS REQUIRED
#  ${needed_boost_package})

#list(APPEND gos_c_include
#  ${Boost_INCLUDE_DIRS})
 
add_subdirectory(src)

if (BUILD_TESTS)
  enable_testing()
# set(gos_unit_testing_xml_output_dir )
  if(GOS_USE_GTEST_PACKAGE)
    find_package(GTest REQUIRED)
  else ()
    if (MSVC)
      #if (GOS_FORCE_SHARED_CRT)
        set(gtest_force_shared_crt ON CACHE BOOL "Use Shared CRT")
      #endif ()
    endif (MSVC)
    if (GOS_C_INSTRUCT_GOOGLE_TEST_PATH)
      set(GOS_C_GOOGLE_TEST_PATH
        "${GOS_C_INSTRUCT_GOOGLE_TEST_PATH}")
    else ()
      set(GOS_C_GOOGLE_TEST_PATH
        "${CMAKE_CURRENT_SOURCE_DIR}/extern/googletest")
      add_subdirectory(extern/googletest)
    endif ()
    set(gos_c_unit_testing_dir
      "${CMAKE_CURRENT_SOURCE_DIR}/tests")
    set(gos_c_unit_testing_gmock_include_dir
      "${GOS_C_GOOGLE_TEST_PATH}/googlemock/include")
    set(gos_c_unit_testing_gtest_include_dir
      "${GOS_C_GOOGLE_TEST_PATH}/googletest/include")
    list(APPEND gos_c_gtest_include
      ${gos_c_unit_testing_gmock_include_dir}
      ${gos_c_unit_testing_gtest_include_dir})
    list(APPEND gos_c_gtest_libraries
      gtest
      gmock
      gmock_main)
  endif ()
  add_subdirectory(tests)
endif (BUILD_TESTS)

if (BUILD_EXAMPLES)
  set(gos_c_xopt_dir "${CMAKE_CURRENT_SOURCE_DIR}/extern/xopt")
  set(gos_c_xopt_src "${gos_c_xopt_dir}/xopt.c")
  list(APPEND gos_c_xopt_include ${gos_c_xopt_dir})
  add_subdirectory(examples)
endif (BUILD_EXAMPLES)


message(STATUS "")
message(STATUS "Geirmundur Orri Sigurdsson C Library ${PROJECT_VERSION} BUILD SUMMARY")
message(STATUS "  Install prefix            : ${CMAKE_INSTALL_PREFIX}")

message(STATUS "  CMAKE_GENERATOR           : ${CMAKE_GENERATOR}")
message(STATUS "  CMAKE_SOURCE_DIR          : ${CMAKE_SOURCE_DIR}")
message(STATUS "  CMAKE_CURRENT_SOURCE_DIR  : ${CMAKE_CURRENT_SOURCE_DIR}")

message(STATUS "  BUILD_SHARED_LIBS         : ${BUILD_SHARED_LIBS}")

message(STATUS "  C   Compiler ID           : ${CMAKE_C_COMPILER_ID}")
message(STATUS "  C   Compiler Version      : ${CMAKE_C_COMPILER_VERSION}")
message(STATUS "  C   Compiler flags        : ${CMAKE_C_FLAGS}")
message(STATUS "  C++ Compiler ID           : ${CMAKE_CXX_COMPILER_ID}")
message(STATUS "  C++ Compiler Version      : ${CMAKE_CXX_COMPILER_VERSION}")
message(STATUS "  C++ Compiler flags        : ${CMAKE_CXX_FLAGS}")

if (MSVC_VERSION)
message(STATUS "  MSVC Version              : ${MSVC_VERSION}")
endif (MSVC_VERSION)

#if (NOV_USE_BOOST_LOG)
#message(STATUS "Using Boost log")
#endif ()
#message(STATUS "  Boost version             : ${Boost_VERSION}")
#message(STATUS "  Boost include dir         : ${Boost_INCLUDE_DIRS}")
#message(STATUS "  Boost debug library dir   : ${Boost_LIBRARY_DIR_DEBUG}")
#message(STATUS "  Boost release library dir : ${Boost_LIBRARY_DIR_RELEASE}")

if (BUILD_TESTS)
message(STATUS "Building Tests")
if (MSVC_VERSION)
message(STATUS "  GTest Force Shared CRT    : ${gtest_force_shared_crt}")
endif ()
endif ()

if (BUILD_EXAMPLES)
message(STATUS "Building Examples")
endif ()
