#---------------------------------------------------------------------------------
# CMake version
#---------------------------------------------------------------------------------

cmake_minimum_required(VERSION 3.25.0 FATAL_ERROR)

enable_testing()

#--------------------------------------------------------------------------------
# Set dependency paths
#--------------------------------------------------------------------------------

set(GTEST_ROOT "${GLOB_GTEST_ROOT_DIR}")
set(GTEST_INC_DIR "${GTEST_ROOT}/include")
set(GTEST_SRC_DIR "${GTEST_ROOT}/src")

set(GMOCK_ROOT "${GLOB_GMOCK_ROOT_DIR}")
set(GMOCK_INC_DIR "${GMOCK_ROOT}/include")

#--------------------------------------------------------------------------------
# Include dependency headers
#--------------------------------------------------------------------------------

include_directories(${GTEST_INC_DIR} ${GMOCK_INC_DIR})

#--------------------------------------------------------------------------------
# Find project test files
#--------------------------------------------------------------------------------

file(GLOB MODULE_RMS_SOURCE_TESTS "${PROJECT_SOURCE_DIR}/*.spec.cpp")

#--------------------------------------------------------------------------------
# Build tests
#--------------------------------------------------------------------------------

add_executable(${MODULE_RMS_TEST_TARGET} ${MODULE_RMS_SOURCE_TESTS} "${GTEST_SRC_DIR}/gtest_main.cc")
target_link_libraries(${MODULE_RMS_TEST_TARGET} ${MODULE_RMS_DEPENDENCY_LIST} ${GLOB_GTEST_LIB_DIR}/libgtest.a ${GLOB_GMOCK_LIB_DIR}/libgmock.a)
enable_cxx17(${MODULE_RMS_TEST_TARGET})

add_test(NAME ${MODULE_RMS_TEST_TARGET} COMMAND ${MODULE_RMS_TEST_TARGET})
