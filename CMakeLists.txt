#---------------------------------------------------------------------------------
# CMake version
#---------------------------------------------------------------------------------

cmake_minimum_required(VERSION 3.25.0 FATAL_ERROR)

#---------------------------------------------------------------------------------
# Project directories
#---------------------------------------------------------------------------------

set(MODULE_RMS_ROOT_DIR "${CMAKE_CURRENT_SOURCE_DIR}")
set(MODULE_RMS_LIST_DIR "${CMAKE_CURRENT_LIST_DIR}")
set(MODULE_RMS_CMAKE_DIR "${MODULE_RMS_ROOT_DIR}/submodules/sway.module_core/cmake_modules")
set(MODULE_RMS_LIB_DIR "${MODULE_RMS_ROOT_DIR}/lib")
set(MODULE_RMS_BIN_DIR "${CMAKE_SOURCE_DIR}/bin")

#---------------------------------------------------------------------------------
# Include CMake modules
#---------------------------------------------------------------------------------

include("${MODULE_RMS_CMAKE_DIR}/options.cmake")
include("${MODULE_RMS_CMAKE_DIR}/set_output_dir.cmake")
include("${MODULE_RMS_CMAKE_DIR}/project_metadata.cmake")
include("${MODULE_RMS_CMAKE_DIR}/add_submodule.cmake")
include("${MODULE_RMS_CMAKE_DIR}/enable_cxx17.cmake")
include("${MODULE_RMS_CMAKE_DIR}/enable_coverage.cmake")
include("${MODULE_RMS_CMAKE_DIR}/modules/create_object_library.cmake")
include("${MODULE_RMS_CMAKE_DIR}/modules/create_interface.cmake")
include("${MODULE_RMS_CMAKE_DIR}/modules/logger.cmake")
include("${MODULE_RMS_CMAKE_DIR}/modules/compiler/clang/create_library.cmake")
include("${MODULE_RMS_CMAKE_DIR}/modules/compiler/emscripten/setup.cmake")
include("${MODULE_RMS_CMAKE_DIR}/modules/compiler/emscripten/create_library.cmake")
include("${MODULE_RMS_CMAKE_DIR}/modules/compiler/emscripten/gen_target_name.cmake")
include("${MODULE_RMS_CMAKE_DIR}/modules/compiler/emscripten/set_optimization.cmake")
include("${MODULE_RMS_CMAKE_DIR}/modules/compiler/emscripten/set_environment.cmake")
include("${MODULE_RMS_CMAKE_DIR}/modules/compiler/emscripten/set_compilation.cmake")
include("${MODULE_RMS_CMAKE_DIR}/modules/compiler/emscripten/set_modularize.cmake")

#---------------------------------------------------------------------------------
# Опции сборки
#---------------------------------------------------------------------------------

set_glob_options()

option(MODULE_RMS_LIB_TYPE "Build type library" OFF)
option(MODULE_RMS_ENABLE_COVERAGE "Enable coverage builds" OFF)
option(MODULE_RMS_ENABLE_TESTS "Enable test builds" OFF)

#---------------------------------------------------------------------------------
# [EMSCRIPTEN]: Setup
#---------------------------------------------------------------------------------

if(GLOB_EMSCRIPTEN_PLATFORM)
  emscripten_setup()
endif()

#---------------------------------------------------------------------------------
# Project
#---------------------------------------------------------------------------------

project_metadata("rms" 0.1.0)
project(${MODULE_RMS_PROJ_NAME} VERSION ${MODULE_RMS_VERSION} LANGUAGES CXX)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -fvisibility=hidden -fPIE")

#---------------------------------------------------------------------------------
# Common variables
#---------------------------------------------------------------------------------

set(MODULE_RMS_DEPENDENCY_LIST "module_rms_dependences")

#---------------------------------------------------------------------------------
# Submodules
#---------------------------------------------------------------------------------

set(MODULE_CORE_LIB_TYPE object CACHE STRING "" FORCE)
set(MODULE_CORE_ENVIRONMENT ${MODULE_RMS_ENVIRONMENT} CACHE STRING "" FORCE)
set(MODULE_CORE_COMPILATION ${MODULE_RMS_COMPILATION} CACHE STRING "" FORCE)
add_submodule("module_core" submodules/sway.module_core)

#---------------------------------------------------------------------------------
# Coverage
#---------------------------------------------------------------------------------

if(MODULE_RMS_ENABLE_COVERAGE)
  enable_coverage()
endif()

#---------------------------------------------------------------------------------
# Executable output path
#---------------------------------------------------------------------------------

set_output_dir(${MODULE_RMS_BIN_DIR})

set(SYSTEM_X11_INCLUDE_DIRS "/opt/X11/include")
set(SYSTEM_X11_LIBRARY_DIRS "/opt/X11/lib")

# Добавляем пути для поиска хедеров
include_directories("${SYSTEM_X11_INCLUDE_DIRS}")
include_directories("${GLOB_THIRD_PARTY_DIR}/json/include")
include_directories("${MODULE_RMS_LIST_DIR}/lib/cxx/include")
include_directories("${MODULE_RMS_LIST_DIR}/submodules/sway.module_loader/api/cxx/include")
include_directories("${MODULE_RMS_LIST_DIR}/submodules/sway.module_core/lib/cxx/include")
include_directories("${MODULE_RMS_LIST_DIR}/submodules/sway.module_math/lib/cxx/include")

link_directories("${SYSTEM_X11_LIBRARY_DIRS}")

# Получаем пути ко всем хедерам и исходникам библиотеки
file(GLOB_RECURSE MODULE_RMS_HEADERS "${MODULE_RMS_LIST_DIR}/lib/cxx/include/*.*")
file(GLOB_RECURSE MODULE_RMS_SOURCES "${MODULE_RMS_LIST_DIR}/lib/cxx/src/*.*")

#---------------------------------------------------------------------------------
# Library
#---------------------------------------------------------------------------------

add_subdirectory(lib/cxx)

#---------------------------------------------------------------------------------
# Tests
#---------------------------------------------------------------------------------

if(MODULE_RMS_ENABLE_TESTS)
  message(STATUS "Tests have been enabled")

  add_subdirectory(lib/cxx/tests/google)
endif()
