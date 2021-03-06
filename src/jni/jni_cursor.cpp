//
// Created by Du Carl on 2019-08-11.
//

#include "jni_cursor.h"
#include "jni_utils.h"
#include "JObjectWrapper.h"


namespace jni_lib_clang
{
    struct CursorVisit
    {
        jobject visitor;
        jobject client_data;
        JNIEnv *env;

        CursorVisit(jobject visitor, jobject clientData, JNIEnv* env) : visitor(visitor), client_data(clientData), env(env){}

    };

    jboolean visitChildren(JNIEnv *env, jobject thisObj, jobject vistor, jobject client_data) {
        Cursor cursor(env, thisObj);
        CursorVisit cursorVisit(vistor, client_data, env);
        return clang_visitChildren(*(cursor.toNative()),
                                   [](CXCursor cxCursor, CXCursor parent, CXClientData clientData) {
                                       auto *visitPtr = static_cast<CursorVisit *>(clientData);
                                       Cursor jCursor(cxCursor), jParent(parent);
                                       jni_util::JObjectWrapper wrapper(visitPtr->env, visitPtr->visitor);
                                       wrapper.CallVoid("Visit",
                                                          "(Ljlibclang/CXCursor;Ljlibclang/CXCursor;Ljlibclang/CXClientData;)V",
                                                          jCursor.toJavaObj(visitPtr->env),
                                                          jParent.toJavaObj(visitPtr->env), visitPtr->client_data);
                                       return CXChildVisit_Recurse;
                                   }, &cursorVisit);
    }

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
    jint getKindNative(JNIEnv *env, jobject thisObj) {
        using namespace jni_util;
        Cursor cursor(env, thisObj);
        jint kind = cursor.toNative()->kind;
        return kind;
    }
}

std::vector<JNINativeMethod> jni_lib_clang::Cursor::getMethods() {
    return {
            {(char *) "disposeNative", (char *) "()V",                  (void *) disposeNative},
            {(char *) "getSpelling",   (char *) "()Ljava/lang/String;", (void *) getSpelling},
            {(char *) "visitChildren",   (char *) "(Ljlibclang/CXCursorVisitor;Ljlibclang/CXClientData;)Z", (void *) visitChildren},
            {(char *) "getKindNative",   (char *) "()I", (void *) getKindNative},
    };
}

void jni_lib_clang::Cursor::DoMakeNative(CXCursor *&native, JNIEnv *env, jobject obj) {
    using namespace jni_util;
    JObjectWrapper wrapper(env, obj);
    native = reinterpret_cast<CXCursor * >(wrapper.GetLongField(FiedlHandler));
}

jobject jni_lib_clang::Cursor::DoMakeJavaObj(JNIEnv *env, CXCursor *&native) {
    using namespace jni_util;
    JObjectWrapper wrapper(env, "jlibclang/CXCursor", "()V");
    wrapper.SetLongField(FiedlHandler, reinterpret_cast<jlong>(native));
    return wrapper.GetJavaObj();
}
