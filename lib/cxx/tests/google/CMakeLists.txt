set(META_RMS_PRJNAME_TESTS "module_rms_tests")
set(META_RMS_EXENAME_TESTS "${META_RMS_PRJNAME_TESTS}")

project(${META_RMS_PRJNAME_TESTS} CXX)

enable_testing()

set(GTEST_ROOT "${GLOB_GTEST_ROOT_DIR}")
set(GTEST_INC_DIR "${GTEST_ROOT}/include")
set(GTEST_SRC_DIR "${GTEST_ROOT}/src")

set(GMOCK_ROOT "${GLOB_GMOCK_ROOT_DIR}")
set(GMOCK_INC_DIR "${GMOCK_ROOT}/include")

# find_package(Threads REQUIRED)

include_directories(${GTEST_INC_DIR} ${GMOCK_INC_DIR})

file(GLOB MODULE_RMS_SOURCE_TESTS "${PROJECT_SOURCE_DIR}/*.spec.cpp")

add_executable(${META_RMS_EXENAME_TESTS} ${MODULE_RMS_SOURCE_TESTS} "${GTEST_SRC_DIR}/gtest_main.cc")
target_link_libraries(${META_RMS_EXENAME_TESTS} module_rms module_core ${GLOB_GTEST_LIB_DIR}/libgtest.a ${GLOB_GMOCK_LIB_DIR}/libgmock.a)
enable_cxx17(${META_RMS_EXENAME_TESTS})

add_test(NAME ${META_RMS_EXENAME_TESTS} COMMAND ${META_RMS_EXENAME_TESTS})
