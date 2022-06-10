cmake_minimum_required(VERSION 3.8)

project(cpp_examples)

set (CMAKE_CXX_STANDARD 17)

if (CMAKE_CXX_COMPILER_ID STREQUAL "GNU" OR
    CMAKE_CXX_COMPILER_ID STREQUAL "Clang")
  add_compile_definitions(FUNCTION_SIGNATURE=__PRETTY_FUNCTION__)
elseif (CMAKE_CXX_COMPILER_ID STREQUAL "MSVC")
  add_compile_definitions(FUNCTION_SIGNATURE=__FUNCSIG__)
else()
  message(FATAL_ERROR, "define FUNCTION_SIGNATURE")
endif()

function(build_examples folder)
  file(GLOB files "${folder}/*.cpp")
  
  foreach(file ${files})
    get_filename_component(exe_name ${file} NAME)
    add_executable(${folder}.${exe_name} ${file})
  endforeach()
endfunction()

build_examples("variadic_templates")