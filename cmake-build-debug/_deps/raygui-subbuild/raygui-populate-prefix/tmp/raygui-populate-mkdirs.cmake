# Distributed under the OSI-approved BSD 3-Clause License.  See accompanying
# file Copyright.txt or https://cmake.org/licensing for details.

cmake_minimum_required(VERSION 3.5)

file(MAKE_DIRECTORY
  "C:/Users/Jermaine/CLionProjects/2048/cmake-build-debug/_deps/raygui-src"
  "C:/Users/Jermaine/CLionProjects/2048/cmake-build-debug/_deps/raygui-build"
  "C:/Users/Jermaine/CLionProjects/2048/cmake-build-debug/_deps/raygui-subbuild/raygui-populate-prefix"
  "C:/Users/Jermaine/CLionProjects/2048/cmake-build-debug/_deps/raygui-subbuild/raygui-populate-prefix/tmp"
  "C:/Users/Jermaine/CLionProjects/2048/cmake-build-debug/_deps/raygui-subbuild/raygui-populate-prefix/src/raygui-populate-stamp"
  "C:/Users/Jermaine/CLionProjects/2048/cmake-build-debug/_deps/raygui-subbuild/raygui-populate-prefix/src"
  "C:/Users/Jermaine/CLionProjects/2048/cmake-build-debug/_deps/raygui-subbuild/raygui-populate-prefix/src/raygui-populate-stamp"
)

set(configSubDirs )
foreach(subDir IN LISTS configSubDirs)
    file(MAKE_DIRECTORY "C:/Users/Jermaine/CLionProjects/2048/cmake-build-debug/_deps/raygui-subbuild/raygui-populate-prefix/src/raygui-populate-stamp/${subDir}")
endforeach()
if(cfgdir)
  file(MAKE_DIRECTORY "C:/Users/Jermaine/CLionProjects/2048/cmake-build-debug/_deps/raygui-subbuild/raygui-populate-prefix/src/raygui-populate-stamp${cfgdir}") # cfgdir has leading slash
endif()
