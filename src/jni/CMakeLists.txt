cmake_minimum_required(VERSION 3.8)
project(LearnLibclang)

set(CMAKE_CXX_STANDARD 14)
if (APPLE)
    set(LLVMPath /usr/local/Cellar/llvm/8.0.0_1/Toolchains/LLVM8.0.0.xctoolchain/usr)
    set(boostPath /usr/local/Cellar/boost/1.69.0_2)
    set(boostLibPath /usr/local/Cellar/boost/1.69.0_2/lib)
    set(javaPath /Library/Java/JavaVirtualMachines/jdk1.8.0_144.jdk/Contents/Home)
    include_directories(
            ${javaPath}/include/darwin
    )
elseif(${WIN32})
    set(LLVMPath "C:/Program Files/LLVM")
    set(boostPath ":D:/Program Files/boost_1_70_0")
    set(boostLibPath ":D:/Program Files/boost_1_70_0/lib32-msvc-14.1")
    set(javaPath "D:/Program Files/Java/jdk1.8.0_101")
    include_directories(
            ${javaPath}/include/win32
    )
endif()

set(jlibclangDir /Users/desg/Documents/workspace/intellij_idea_workspace/jlibclang)

include_directories(
        ${LLVMPath}/include
        ${boostPath}/include
        ${boostPath}
        ${javaPath}/include
        )
link_directories(
        ${LLVMPath}/lib
        ${boostLibPath}
)
if (APPLE)
link_libraries(
        libclang.dylib
#        libboost_filesystem.dylib
        )
elseif(${WIN32})
    link_libraries(
            libclang
    )
endif()


add_executable(LearnLibclang main.cpp)

add_library(clang-jni SHARED
        jni_libclang.cpp
        jni_index.cpp
        JObjectWrapper.cpp
        jni_translate_unit.cpp jni_translate_unit.h jni_cursor.cpp jni_cursor.h jni_utils.cpp jni_utils.h)

add_executable(gen_enums gen_enums.cpp)

add_custom_command(TARGET clang-jni
        POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy
        $<TARGET_FILE:clang-jni>
        ${jlibclangDir}/dll
        )
