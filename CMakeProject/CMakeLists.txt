# CMakeList.txt: CMakeProject 的 CMake 项目，在此处包括源代码并定义
# 项目特定的逻辑。
#
# 将源代码添加到此项目的可执行文件。
add_executable (CMakeProject "CMakeProject.cpp" "CMakeProject.h" "../src/glad.c")
if (CMAKE_VERSION VERSION_GREATER 3.12)
  set_property(TARGET CMakeProject PROPERTY CXX_STANDARD 20)
endif()
# TODO: 如有需要，请添加测试并安装目标。
target_link_libraries(CMakeProject glfw3 opengl32)
target_include_directories(CMakeProject PUBLIC
                           "${CMAKE_CURRENT_SOURCE_DIR}"
                           )