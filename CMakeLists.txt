# Проверяем версию CMake
cmake_minimum_required(VERSION 3.14.3 FATAL_ERROR)

include("${CMAKE_CURRENT_SOURCE_DIR}/submodules/sway.module_core/cmakehelpers/custom_enable_cxx17.cmake")
include("${CMAKE_CURRENT_SOURCE_DIR}/submodules/sway.module_core/cmakehelpers/custom_add_subdirectory.cmake")

# Мета-информация о проекте
set(META_RMS_PRJNAME "module_rms")
set(META_RMS_LIBNAME "lib${META_RMS_PRJNAME}")
set(META_RMS_VERSION_MAJOR 0)
set(META_RMS_VERSION_MINOR 1)
set(META_RMS_VERSION_PATCH 0)
set(META_RMS_VERSION ${META_RMS_VERSION_MAJOR}.${META_RMS_VERSION_MINOR}.${META_RMS_VERSION_PATCH})

# Опции сборки
option(MODULE_RMS_BUILD_SHARED "Build shared library" OFF)
option(MODULE_RMS_ENABLE_COVERAGE "Enable coverage builds" OFF)
option(MODULE_RMS_ENABLE_TESTS "Enable test builds" OFF)

if (NOT CMAKE_BUILD_TYPE)
  set(CMAKE_BUILD_TYPE "Debug" CACHE STRING "Choose the type of build" FORCE)
endif ()

project(${META_RMS_PRJNAME} CXX)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

if(MODULE_RMS_ENABLE_COVERAGE)
  set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -g ")
  set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -O0")
  set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -fprofile-arcs")
  set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -ftest-coverage")
  set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} --coverage")
endif()

# Определяем каталог вывода по умолчанию
if (CMAKE_BUILD_TYPE MATCHES Debug)
  set(LIBRARY_OUTPUT_PATH ${CMAKE_SOURCE_DIR}/bin/dbg)
  set(EXECUTABLE_OUTPUT_PATH ${CMAKE_SOURCE_DIR}/bin/dbg)
else ()
  set(LIBRARY_OUTPUT_PATH ${CMAKE_SOURCE_DIR}/bin)
  set(EXECUTABLE_OUTPUT_PATH ${CMAKE_SOURCE_DIR}/bin)
endif ()

set(MODULE_RMS_DIR ${CMAKE_CURRENT_LIST_DIR})

set(SYSTEM_X11_INCLUDE_DIRS "/opt/X11/include")
set(SYSTEM_X11_LIBRARY_DIRS "/opt/X11/lib")
set(MODULE_GAPI_GL_DIR ${CMAKE_CURRENT_LIST_DIR})

# Добавляем пути для поиска хедеров
include_directories("${SYSTEM_X11_INCLUDE_DIRS}")
include_directories("${MODULE_RMS_DIR}/lib/include")
include_directories("${MODULE_RMS_DIR}/submodules/sway.module_loader/include")
include_directories("${MODULE_RMS_DIR}/submodules/sway.module_core/lib/include")
include_directories("${MODULE_RMS_DIR}/submodules/sway.module_math/lib/include")

link_directories("${SYSTEM_X11_LIBRARY_DIRS}")

# Получаем пути ко всем хедерам и исходникам библиотеки
file(GLOB_RECURSE MODULE_RMS_HEADERS "${MODULE_RMS_DIR}/lib/include/*.*")
file(GLOB_RECURSE MODULE_RMS_SOURCES "${MODULE_RMS_DIR}/lib/src/*.*")

if (MODULE_RMS_BUILD_SHARED)
  set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -fvisibility=default -fPIE")

  # Добавляем в проект цель для сборки динамической библиотеки
  add_library(${META_RMS_LIBNAME} SHARED ${MODULE_RMS_SOURCES})
  set_target_properties(${META_RMS_LIBNAME} PROPERTIES OUTPUT_NAME ${META_RMS_PRJNAME})
  set_target_properties(${META_RMS_LIBNAME} PROPERTIES PREFIX "")
  set_target_properties(${META_RMS_LIBNAME} PROPERTIES SUFFIX ".so.${META_RMS_VERSION}")
else ()
  # Добавляем в проект цель для сборки статической библиотеки
  add_library(${META_RMS_LIBNAME} STATIC ${MODULE_RMS_SOURCES})
  set_target_properties(${META_RMS_LIBNAME} PROPERTIES OUTPUT_NAME ${META_RMS_PRJNAME})
  set_target_properties(${META_RMS_LIBNAME} PROPERTIES PREFIX "")
  set_target_properties(${META_RMS_LIBNAME} PROPERTIES SUFFIX ".a.${META_RMS_VERSION}")
endif ()

target_link_libraries(${META_RMS_LIBNAME} X11)

custom_enable_cxx17(${META_RMS_LIBNAME})

if (MODULE_RMS_ENABLE_TESTS)
  if (NOT TARGET libmodule_core)
    add_subdirectory("submodules/sway.module_core")
  endif ()
endif ()

# Добавляем построение тестов
if (MODULE_RMS_ENABLE_TESTS)
  message(STATUS "Tests have been enabled")

  add_subdirectory(lib/tests/google)
endif ()