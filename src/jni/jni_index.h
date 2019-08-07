//
// Created by Du Carl on 2019-08-04.
//

#ifndef LEARNLIBCLANG_JNI_INDEX_H
#define LEARNLIBCLANG_JNI_INDEX_H

#include <vector>
#include <jni.h>
#include <clang-c/Index.h>
#include <string>
#include "JObjectWrapper.h"

namespace index_libclang
{
    class Index : public jni_util::NativeWrapper<CXIndex>
    {
        std::string _handlerName = "_handler";
        std::string _newName = "()V";
        std::string _className = "jlibclang/CXIndex";
    public:
        Index(JNIEnv *env, jobject obj);
        explicit Index(CXIndex handler);

    protected:
        jobject DoMakeJavaObj(JNIEnv *env, NativeType &native) override;
        void DoMakeNative(NativeType &native, JNIEnv *env, jobject obj) override;
    };


class UnsavedFile : public jni_util::NativeWrapper<CXUnsavedFile>
    {
    public:
        UnsavedFile(JNIEnv *env, jobject obj);
        UnsavedFile(CXUnsavedFile unsavedFile):NativeWrapper(unsavedFile) {}

    protected:
    void DoMakeNative(NativeType &native, JNIEnv *env, jobject obj) override;

    jobject DoMakeJavaObj(JNIEnv *env, NativeType &native) override;

    std::string _FilenameField = "Filename";
    std::string _ContentsField = "Contents";
    std::string _LengthField = "Length";
    };

    extern std::vector<JNINativeMethod> methods;
}
#endif //LEARNLIBCLANG_JNI_INDEX_H
