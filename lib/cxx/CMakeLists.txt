#---------------------------------------------------------------------------------
# CMake version
#---------------------------------------------------------------------------------

cmake_minimum_required(VERSION 3.25.0 FATAL_ERROR)

set(SYSTEM_X11_INCLUDE_DIRS "/opt/X11/include")
set(SYSTEM_X11_LIBRARY_DIRS "/opt/X11/lib")

#--------------------------------------------------------------------------------
# Include project headers
#--------------------------------------------------------------------------------

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

#--------------------------------------------------------------------------------
# Build object library
#--------------------------------------------------------------------------------

if(NOT TARGET ${MODULE_RMS_OBJ_TARGET})
  set(MODULE_RMS_LIB_SOURCES "${MODULE_RMS_ROOT_DIR}/lib/cxx/src/*.*")
  set(MODULE_RMS_ENABLE_FILE_EXPORT TRUE)

  create_object_library(${MODULE_RMS_OBJ_TARGET} ${MODULE_RMS_LIB_SOURCES} ${MODULE_RMS_ENABLE_FILE_EXPORT})
  enable_cxx17(${MODULE_RMS_OBJ_TARGET})
endif()

#---------------------------------------------------------------------------------
# Interface
#---------------------------------------------------------------------------------

set(TARGET_OBJECT_LIST)
set(MODULE_CORE_OBJ_TARGET "module_core_obj")

if(TARGET ${MODULE_CORE_OBJ_TARGET})
  list(APPEND TARGET_OBJECT_LIST $<TARGET_OBJECTS:${MODULE_CORE_OBJ_TARGET}>)
endif()

if(TARGET ${MODULE_RMS_OBJ_TARGET})
  list(APPEND TARGET_OBJECT_LIST $<TARGET_OBJECTS:${MODULE_RMS_OBJ_TARGET}>)
endif()

list(LENGTH TARGET_OBJECT_LIST TARGET_OBJECT_LIST_LENGTH)
if(${TARGET_OBJECT_LIST_LENGTH})
  create_interface(${MODULE_RMS_DEPENDENCY_LIST} ${TARGET_OBJECT_LIST})
endif()
