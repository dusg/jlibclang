cmake_minimum_required(VERSION 3.14)
project(LearnLibclang)

set(CMAKE_CXX_STANDARD 14)
if (APPLE)
    set(LLVMPath /usr/local/Cellar/llvm/8.0.0_1/Toolchains/LLVM8.0.0.xctoolchain/usr)
    set(boostPath /usr/local/Cellar/boost/1.69.0_2)
    set(javaPath /Library/Java/JavaVirtualMachines/jdk1.8.0_144.jdk/Contents/Home)
elseif(${WIN32})
    set(LLVMPath "C:/Program Files/LLVM")
    set(boostPath /usr/local/Cellar/boost/1.69.0_2)
    set(javaPath /Library/Java/JavaVirtualMachines/jdk1.8.0_144.jdk/Contents/Home)
endif()

include_directories(
        ${LLVMPath}/include
#        /usr/local/Cellar/llvm/8.0.0_1/Toolchains/LLVM8.0.0.xctoolchain/usr/include
        ${boostPath}/include
#        /usr/local/Cellar/boost/1.69.0_2/include
        ${javaPath}/include
        ${javaPath}/include/darwin
#        /Library/Java/JavaVirtualMachines/jdk1.8.0_144.jdk/Contents/Home/include
#        /Library/Java/JavaVirtualMachines/jdk1.8.0_144.jdk/Contents/Home/include/darwin
#        "/Applications/IntelliJ IDEA CE.app/Contents/jbr/Contents/Home/include/"
#        "/Applications/IntelliJ IDEA CE.app/Contents/jbr/Contents/Home/include/darwin/"
        )
link_directories(
        ${LLVMPath}/lib
#        /usr/local/Cellar/llvm/8.0.0_1/Toolchains/LLVM8.0.0.xctoolchain/usr/lib
        ${boostPath}/lib
#        /usr/local/Cellar/boost/1.69.0_2/lib
)

link_libraries(
        libclang.dylib
#        libboost_filesystem.dylib
        )
add_executable(LearnLibclang main.cpp)

add_library(clang-jni SHARED
        jni_libclang.cpp
        jni_index.cpp
        JObjectWrapper.cpp
        jni_translate_unit.cpp jni_translate_unit.h)

add_executable(gen_enums gen_enums.cpp)