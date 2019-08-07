//
// Created by Du Carl on 2019-08-04.
//
#include <clang-c/Index.h>
#include <jni.h>
#include <map>
#include <vector>
#include "jni_index.h"

static int registerNatives(JNIEnv *pEnv);

namespace jni_util
{
    jobject createIndex(JNIEnv *env, jobject thisObj,
                        jboolean excludeDeclarationsFromPCH, jboolean displayDiagnostics) {
        using namespace index_libclang;
        CXIndex cxIndex = clang_createIndex(excludeDeclarationsFromPCH, displayDiagnostics);
        Index index(cxIndex);
        return index.toJavaObj(env);
    }


    std::vector<JNINativeMethod> methods = {
            {(char*)"createIndex", (char*)"(ZZ)Ljlibclang/CXIndex;", (void *) createIndex}
    };
}

static std::map<const char *, std::vector<JNINativeMethod>> _methods = {
        { "jlibclang/LibClang", jni_util::methods}
};

static int registerNatives(JNIEnv *pEnv) {

    for (auto item : _methods) {
        jclass clazz = pEnv->FindClass(item.first);
        if (clazz == nullptr)
            return JNI_FALSE;

        auto methods = item.second;
        if (pEnv->RegisterNatives(clazz, methods.data(), methods.size())<0)
            return JNI_FALSE;
    }
    return JNI_TRUE;
}

extern "C" {
jint JNI_OnLoad(JavaVM *vm, void *reserved) {

    jint result = -1;
    JNIEnv *env = nullptr;


    if (vm->GetEnv(reinterpret_cast<void **>(&env), JNI_VERSION_1_8) != JNI_OK) {
        return -1;
    }

    if (registerNatives(env) != JNI_TRUE) {
        return -1;
    }

    result = JNI_VERSION_1_8;

    return result;
}
}
