//
// Created by Du Carl on 2019-08-04.
//

#ifndef LEARNLIBCLANG_JNI_INDEX_H
#define LEARNLIBCLANG_JNI_INDEX_H

#include <vector>
#include <jni.h>
#include <clang-c/Index.h>
#include <string>

namespace index_libclang
{
    class Index {
        std::string _handlerName = "_handler";
        std::string _newName = "()V";
        std::string _className = "jlibclang/CXIndex";
    public:
        CXIndex handler = nullptr;

        Index(JNIEnv *env, jobject obj);
        explicit Index(CXIndex handler);

        jobject toJavaObj(JNIEnv *env);

    };
    extern std::vector<JNINativeMethod> methods;
}
#endif //LEARNLIBCLANG_JNI_INDEX_H
