//
// Created by Du Carl on 2019-08-08.
//

#include "jni_translate_unit.h"

void jni_lib_clang::TranslationUnit::DoMakeNative(CXTranslationUnitImpl *&native, JNIEnv *env, jobject obj) {
//todo
}

jobject jni_lib_clang::TranslationUnit::DoMakeJavaObj(JNIEnv *env, CXTranslationUnitImpl *&native) {
//    todo
    return nullptr;
}

jni_lib_clang::TranslationUnit::TranslationUnit(JNIEnv *env, jobject obj) : NativeWrapper(env, obj) {}

jni_lib_clang::TranslationUnit::TranslationUnit(CXTranslationUnit native) : NativeWrapper(native) {}
