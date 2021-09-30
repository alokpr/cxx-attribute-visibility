cmake_minimum_required(VERSION 3.15)

project(cxx-attribute-visibility LANGUAGES "CXX")

# With visibility=default, detail::Next() will be exported (T).
# The dynamic linker will de-duplicate and resolve those at runtime.
# With visibility=hidden, detail::Next() becomes private to libmodule.so.
# Ref: https://gcc.gnu.org/wiki/Visibility
set(CMAKE_CXX_VISIBILITY_PRESET hidden)

add_library(detail STATIC detail.cc)

add_library(module1 SHARED module1.cc)
target_link_libraries(module1 PRIVATE detail)

add_library(module2 SHARED module2.cc)
target_link_libraries(module2 PRIVATE detail)

# app_linked uses standard linking mechanism to use the modules.
add_executable(app_linked app_linked.cc)
target_link_libraries(app_linked PRIVATE module1 module2)

# app_plugin dynamically loads the modules at runtime.
#
# Unlike standard linking, dynamically loaded modules are completely decoupled
# from the underlying application. The dynamic loader does not use them to
# resolve any unbound symbols in the application. Each dynamically loaded module
# gets its own private symbol namespace. So, if a symbol name is defined in more
# than one loadable module, those symbols remain distinct and do not clash
# with each other during execution. Similarly, symbols defined in previously
# loaded modules are not used to resolve symbols in newly loaded modules.
#
# When a static library is linked into a shared module, the relevant parts of
# the static library are simply copied into the resulting shared library object.
# For multiple modules linked in this manner, each module ends up with its own
# private copy of the static library. When these modules load, all private
# library copies remain isolated from each other, owing to the way in which
# symbols are bound in dynamic modules. For instance, changes to global
# variables don’t seem to affect other modules, functions seem to operate on
# different sets of data, and so on.
#
# References:
# https://cseweb.ucsd.edu/~gbournou/CSE131/the_inside_story_on_shared_libraries_and_dynamic_loading.pdf
# https://www.cs.dartmouth.edu/~sergey/cs258/ABI/UlrichDrepper-How-To-Write-Shared-Libraries.pdf
add_executable(app_plugin app_plugin.cc)
target_link_libraries(app_plugin PRIVATE dl)
