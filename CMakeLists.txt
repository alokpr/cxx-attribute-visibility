cmake_minimum_required(VERSION 3.15)

project(cxx-attribute-visibility LANGUAGES "CXX")

# Commenting out the following line will set visibility to default.
#
# With visibility=default, the symbols defined in libcommon.a will be exported
# as global symbols in both - libmodule1.so and libmodule2.so - that will be
# de-duplicated by the dynamic linker at runtime.
#
# With visibility=hidden, the symbols defined in libcommon.a become private to
# libmodule1.so and libmodule2.so.
set(CMAKE_CXX_VISIBILITY_PRESET hidden)

add_library(common STATIC next.cc)

add_library(module1 SHARED module1.cc)
target_link_libraries(module1 PRIVATE common)

add_library(module2 SHARED module2.cc)
target_link_libraries(module2 PRIVATE common)

add_executable(app app.cc)
target_link_libraries(app PRIVATE module1 module2)
