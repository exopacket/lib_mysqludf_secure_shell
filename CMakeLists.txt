cmake_minimum_required(VERSION 3.21)
project(lib_mysqludf_exec)

set(CMAKE_C_STANDARD 90)
set(CMAKE_CXX_STANDARD 14)

include_directories(/usr/include/mysql)
link_directories(/usr/lib/mysql)

find_library(MySQL mysql PATHS /usr)

add_library(lib_mysqludf_exec SHARED lib_mysqludf_exec.cc)

target_compile_options(lib_mysqludf_exec PRIVATE -DMYSQL_DYNAMIC_PLUGIN)
set_target_properties(lib_mysqludf_exec PROPERTIES PREFIX "")

install(TARGETS lib_mysqludf_exec LIBRARY DESTINATION /usr/lib/mysql/plugins)