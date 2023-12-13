# Мета-информация о проекте
set(META_RMS_PRJNAME_TESTS "module_rms_tests")
set(META_RMS_EXENAME_TESTS "${META_RMS_PRJNAME_TESTS}")

project(${META_RMS_PRJNAME_TESTS} CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED on)

set(GTEST_ROOT "${GLOB_GTEST_ROOT_DIR}")
set(GTEST_INC_DIR "${GTEST_ROOT}/include")
set(GTEST_SRC_DIR "${GTEST_ROOT}/src")

find_package(Threads REQUIRED)

include_directories(${GTEST_INC_DIR})

# Получаем пути ко всем исходникам с тестами
file(GLOB MODULE_RMS_SOURCE_TESTS "${PROJECT_SOURCE_DIR}/*.spec.cpp")

add_executable(${META_RMS_EXENAME_TESTS} ${MODULE_RMS_SOURCE_TESTS} "${GTEST_SRC_DIR}/gtest_main.cc")
target_link_libraries(${META_RMS_EXENAME_TESTS} module_rms module_core ${GLOB_GTEST_LIB_DIR}/libgtest.a ${CMAKE_DL_LIBS})

add_custom_command(TARGET ${META_RMS_EXENAME_TESTS} POST_BUILD COMMAND ${META_RMS_EXENAME_TESTS})
