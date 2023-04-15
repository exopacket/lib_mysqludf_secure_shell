cmake_minimum_required(VERSION 3.21)
project(lib_mysqludf_secure_shell)

set(CMAKE_C_STANDARD 90)
set(CMAKE_CXX_STANDARD 14)

include_directories(/usr/include/mysql)
link_directories(/usr/lib/mysql)

find_library(MySQL mysql PATHS /usr)

add_library(lib_mysqludf_secure_shell SHARED lib_mysqludf_secure_shell.cc)

target_compile_options(lib_mysqludf_secure_shell PRIVATE -DMYSQL_DYNAMIC_PLUGIN)
set_target_properties(lib_mysqludf_secure_shell PROPERTIES PREFIX "")

install(TARGETS lib_mysqludf_secure_shell LIBRARY DESTINATION /usr/lib/mysql/plugin)