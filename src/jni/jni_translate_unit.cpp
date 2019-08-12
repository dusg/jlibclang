//
// Created by Du Carl on 2019-08-08.
//

#include "jni_translate_unit.h"
#include "jni_cursor.h"

static const char *const s_handlerField = "_handler";
namespace jni_lib_clang
{
    JNICALL void disposeTranslationUnit(JNIEnv *env, jobject thisObj) {
        TranslationUnit unit(env, thisObj);
        clang_disposeTranslationUnit(unit.toNative());
    }
    JNICALL jobject getUnitCursor(JNIEnv *env, jobject thisObj) {
        TranslationUnit unit(env, thisObj);
        CXCursor cursor = clang_getTranslationUnitCursor(unit.toNative());
        return Cursor(cursor).toJavaObj(env);
    }
}

std::vector<JNINativeMethod> jni_lib_clang::TranslationUnit::getMethods() {
    return {
            {(char*)"disposeTranslationUnit", (char*)"()V", (void*)disposeTranslationUnit},
            {(char*)"getUnitCursor", (char*)"()Ljlibclang/CXCursor;", (void*)getUnitCursor}
    };
}

void jni_lib_clang::TranslationUnit::DoMakeNative(CXTranslationUnit &native, JNIEnv *env, jobject obj) {
    using namespace jni_util;
    JObjectWrapper wrapper(env, obj);
    native = reinterpret_cast<CXTranslationUnit >(wrapper.GetLongField(s_handlerField));
}

jobject jni_lib_clang::TranslationUnit::DoMakeJavaObj(JNIEnv *env, CXTranslationUnit &native) {
    using namespace jni_util;
    JObjectWrapper wrapper(env, "jlibclang/CXTranslationUnit", "()V");
    wrapper.SetLongField(s_handlerField, reinterpret_cast<jlong>(native));
    return wrapper.GetJavaObj();
}

jni_lib_clang::TranslationUnit::TranslationUnit(JNIEnv *env, jobject obj) : NativeWrapper(env, obj) {}

jni_lib_clang::TranslationUnit::TranslationUnit(CXTranslationUnit native) : NativeWrapper(native) {}

