//
// Created by Du Carl on 2019-08-11.
//

#include "jni_cursor.h"
#include "jni_utils.h"
#include "JObjectWrapper.h"


namespace jni_lib_clang
{
    void disposeNative(JNIEnv *env, jobject thisObj) {
        Cursor cursor(env, thisObj);
        CXCursor *tmp = (cursor.toNative());
        delete (tmp);
    }

    jstring getSpelling(JNIEnv *env, jobject thisObj) {
        using namespace jni_util;
        Cursor cursor(env, thisObj);
        String str = clang_getCursorSpelling(*cursor.toNative());

        return JString(str.toStdString()).toJaveObj(env);
    }
}

std::vector<JNINativeMethod> jni_lib_clang::Cursor::getMethods() {
    return {
            {(char *) "disposeNative", (char *) "()V", (void *) disposeNative},
            {(char *) "getSpelling", (char *) "()Ljava/lang/String;", (void *) getSpelling},
    };
}

void jni_lib_clang::Cursor::DoMakeNative(CXCursor *&native, JNIEnv *env, jobject obj) {
    using namespace jni_util;
    JObjectWrapper wrapper(env, obj);
    native = reinterpret_cast<CXCursor* >(wrapper.GetLongField(FiedlHandler));
}

jobject jni_lib_clang::Cursor::DoMakeJavaObj(JNIEnv *env, CXCursor *&native) {
    using namespace jni_util;
    JObjectWrapper wrapper(env, "jlibclang/CXCursor", "()V");
    wrapper.SetLongField(FiedlHandler, reinterpret_cast<jlong>(native));
    return wrapper.GetJavaObj();
}
