//
// Created by Du Carl on 2019-08-11.
//

#ifndef LEARNLIBCLANG_JNI_CURSOR_H
#define LEARNLIBCLANG_JNI_CURSOR_H

#include <clang-c/Index.h>
#include "JObjectWrapper.h"

namespace jni_lib_clang
{
    class Cursor : public jni_util::NativeWrapper<CXCursor *>
    {
    public:
        static std::vector<JNINativeMethod> getMethods();

        explicit Cursor(CXCursor native) : NativeWrapper(new CXCursor(native)) {
        }

        Cursor(JNIEnv *env, jobject obj) : NativeWrapper(env, obj) {
        }

    protected:
        void DoMakeNative(NativeType &native, JNIEnv *env, jobject obj) override;

        jobject DoMakeJavaObj(JNIEnv *env, NativeType &native) override;

    private:

    };
}

#endif //LEARNLIBCLANG_JNI_CURSOR_H
