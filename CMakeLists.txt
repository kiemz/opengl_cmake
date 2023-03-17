# CMakeList.txt: 顶层 CMake 项目文件，在此处执行全局配置
# 并包含子项目。
#
cmake_minimum_required (VERSION 3.24 FATAL_ERROR)

# Enable Hot Reload for MSVC compilers if supported.
if (POLICY CMP0141)
  cmake_policy(SET CMP0141 NEW)
  set(CMAKE_MSVC_DEBUG_INFORMATION_FORMAT "$<IF:$<AND:$<C_COMPILER_ID:MSVC>,$<CXX_COMPILER_ID:MSVC>>,$<$<CONFIG:Debug,RelWithDebInfo>:EditAndContinue>,$<$<CONFIG:Debug,RelWithDebInfo>:ProgramDatabase>>")
endif()

project ("CMakeProject")

configure_file(${PROJECT_NAME}/helpers/RootDir.h.in ${PROJECT_NAME}/helpers/RootDir.h)
include_directories(${CMAKE_SOURCE_DIR}/${PROJECT_NAME})

# Add .lib files
link_directories(${CMAKE_SOURCE_DIR}/lib)

# Add .include files
include_directories(${CMAKE_SOURCE_DIR}/include)


# GLAD
add_library(GLAD "thirdparty/glad.c")

# 包含子项目。
add_subdirectory ("CMakeProject")
