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
include("${MODULE_RMS_CMAKE_DIR}/modules/logger.cmake")
include("${MODULE_RMS_CMAKE_DIR}/modules/compiler/clang/create_library.cmake")
include("${MODULE_RMS_CMAKE_DIR}/modules/compiler/emscripten/setup.cmake")
include("${MODULE_RMS_CMAKE_DIR}/modules/compiler/emscripten/create_bitcode.cmake")
include("${MODULE_RMS_CMAKE_DIR}/modules/compiler/emscripten/create_library.cmake")
include("${MODULE_RMS_CMAKE_DIR}/modules/compiler/emscripten/gen_target_name.cmake")
include("${MODULE_RMS_CMAKE_DIR}/modules/compiler/emscripten/set_optimization.cmake")
include("${MODULE_RMS_CMAKE_DIR}/modules/compiler/emscripten/set_environment.cmake")
include("${MODULE_RMS_CMAKE_DIR}/modules/compiler/emscripten/set_compilation.cmake")
include("${MODULE_RMS_CMAKE_DIR}/modules/compiler/emscripten/set_modularize.cmake")

#---------------------------------------------------------------------------------
# Опции сборки
#---------------------------------------------------------------------------------

option(MODULE_RMS_SHARED_LIB "Build shared library" OFF)
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

#---------------------------------------------------------------------------------
# Submodules
#---------------------------------------------------------------------------------

add_submodule("module_core" submodules/sway.module_core)

#---------------------------------------------------------------------------------
# Coverage
#---------------------------------------------------------------------------------

if(MODULE_RMS_ENABLE_COVERAGE)
  enable_coverage()
endif()

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -fvisibility=hidden -fPIE")

if(GLOB_EMSCRIPTEN_PLATFORM)
  set(CMAKE_CXX_COMPILER "${GLOB_EMSCRIPTEN_ROOT_DIR}/em++")
  set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} -s WASM=1 -s MODULARIZE=1")
  set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Os -std=c++17")
  set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Wno-unknown-pragmas -Wno-unicode-whitespace \
      -Wno-unused-local-typedef -Wno-invalid-noreturn -Wno-unused-command-line-argument")
  set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -DEMSCRIPTEN_PLATFORM")
  if(GLOB_EMSCRIPTEN_USE_BINDINGS)
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} --bind")
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -DEMSCRIPTEN_PLATFORM_USE_BINDING")
  endif()
endif()

#---------------------------------------------------------------------------------
# Executable output path
#---------------------------------------------------------------------------------

set_output_dir(${MODULE_RMS_BIN_DIR})

set(SYSTEM_X11_INCLUDE_DIRS "/opt/X11/include")
set(SYSTEM_X11_LIBRARY_DIRS "/opt/X11/lib")

# Добавляем пути для поиска хедеров
include_directories("${SYSTEM_X11_INCLUDE_DIRS}")
include_directories("${MODULE_RMS_LIST_DIR}/lib/cxx/include")
include_directories("${MODULE_RMS_LIST_DIR}/submodules/sway.module_loader/include")
include_directories("${MODULE_RMS_LIST_DIR}/submodules/sway.module_core/lib/cxx/include")
include_directories("${MODULE_RMS_LIST_DIR}/submodules/sway.module_math/lib/cxx/include")

link_directories("${SYSTEM_X11_LIBRARY_DIRS}")

# Получаем пути ко всем хедерам и исходникам библиотеки
file(GLOB_RECURSE MODULE_RMS_HEADERS "${MODULE_RMS_LIST_DIR}/lib/cxx/include/*.*")
file(GLOB_RECURSE MODULE_RMS_SOURCES "${MODULE_RMS_LIST_DIR}/lib/cxx/src/*.*")

if(MODULE_RMS_SHARED_LIB)
  # Добавляем в проект цель для сборки динамической библиотеки
  add_library(${MODULE_RMS_TARGET} SHARED ${MODULE_RMS_SOURCES})
  set_target_properties(${MODULE_RMS_TARGET} PROPERTIES OUTPUT_NAME ${MODULE_RMS_PROJ_NAME})
  set_target_properties(${MODULE_RMS_TARGET} PROPERTIES PREFIX "")
  set_target_properties(${MODULE_RMS_TARGET} PROPERTIES SUFFIX ".so.${MODULE_RMS_VERSION}")
else()
  # Добавляем в проект цель для сборки статической библиотеки
  add_library(${MODULE_RMS_TARGET} STATIC ${MODULE_RMS_SOURCES})
  set_target_properties(${MODULE_RMS_TARGET} PROPERTIES OUTPUT_NAME ${MODULE_RMS_PROJ_NAME})
  set_target_properties(${MODULE_RMS_TARGET} PROPERTIES PREFIX "")
  set_target_properties(${MODULE_RMS_TARGET} PROPERTIES SUFFIX ".a.${MODULE_RMS_VERSION}")
endif()

target_link_libraries(${MODULE_RMS_TARGET} module_core X11)

enable_cxx17(${MODULE_RMS_TARGET})

#---------------------------------------------------------------------------------
# Построение тестов
#---------------------------------------------------------------------------------

if(MODULE_RMS_ENABLE_TESTS)
  message(STATUS "Tests have been enabled")

  add_subdirectory(lib/cxx/tests/google)
endif()
