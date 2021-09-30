cmake_minimum_required(VERSION 3.15)

project(cxx-attribute-visibility LANGUAGES "CXX")

# Commenting out the following line will set visibility to default.
#
# With visibility=default,
# Generator::Next() will be exported as a weak symbol (W)
# Generator::Next()::next will be exported as unique global symbol (u)
# The dynamic linker will de-duplicate and resolve those at runtime.
#
# With visibility=hidden, all Generator symbols become private to libmodule1.so
# and libmodule2.so.
set(CMAKE_CXX_VISIBILITY_PRESET hidden)

add_library(module1 SHARED module1.cc)
add_library(module2 SHARED module2.cc)

add_executable(app_linked app_linked.cc)
target_link_libraries(app_linked PRIVATE module1 module2)

add_executable(app_plugin app_plugin.cc)
target_link_libraries(app_plugin PRIVATE dl)
