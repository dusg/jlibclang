//
// Created by Du Carl on 2019-08-08.
//

#ifndef LEARNLIBCLANG_JNI_TRANSLATE_UNIT_H
#define LEARNLIBCLANG_JNI_TRANSLATE_UNIT_H

#include <clang-c/Index.h>
#include "JObjectWrapper.h"

namespace jni_lib_clang
{
    class TranslationUnit : public jni_util::NativeWrapper<CXTranslationUnit>
    {
    public:
        TranslationUnit(CXTranslationUnit native);

        TranslationUnit(JNIEnv *env, jobject obj);

    protected:
        void DoMakeNative(NativeType &native, JNIEnv *env, jobject obj) override;

        jobject DoMakeJavaObj(JNIEnv *env, NativeType &native) override;

    private:

    };
}
#endif //LEARNLIBCLANG_JNI_TRANSLATE_UNIT_H
