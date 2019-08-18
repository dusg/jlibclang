//
// Created by Du Carl on 2019-08-04.
//
#include <clang-c/Index.h>
#include <jni.h>
#include <map>
#include <vector>
#include "jni_index.h"
#include "jni_cursor.h"
#include "jni_translate_unit.h"
#include "jni_utils.h"

static int registerNatives(JNIEnv *pEnv);

namespace jni_lib_clang
{
    jobject createIndex(JNIEnv *env, jobject thisObj,
                        jboolean excludeDeclarationsFromPCH, jboolean displayDiagnostics) {
        using namespace jni_lib_clang;
        CXIndex cxIndex = clang_createIndex(excludeDeclarationsFromPCH, displayDiagnostics);
        Index index(cxIndex);
        return index.toJavaObj(env);
    }

    jstring getCursorKindSpelling(JNIEnv *env, jobject thisObj, jint kind) {
        using namespace jni_util;
        CXCursorKind cursorKind = static_cast<CXCursorKind>(kind);
        String jString = clang_getCursorKindSpelling(cursorKind);
        return JString(jString.toStdString()).toJaveObj(env);
    }

    std::vector<JNINativeMethod> getMethods() {
        std::vector<JNINativeMethod> methods; //=
        return {
                {(char *) "createIndex",           (char *) "(ZZ)Ljlibclang/CXIndex;", (void *) createIndex},
                {(char *) "getCursorKindSpelling", (char *) "(I)Ljava/lang/String;", (void *) getCursorKindSpelling},
        };
    };

};

static std::map<const char *, std::vector<JNINativeMethod>> getAllMethods() {

    std::map<const char *, std::vector<JNINativeMethod>> methods = {
            {"jlibclang/LibClang",          jni_lib_clang::getMethods()},
            {"jlibclang/CXIndex",           jni_lib_clang::Index::getMethods()},
            {"jlibclang/CXTranslationUnit", jni_lib_clang::TranslationUnit::getMethods()},
            {"jlibclang/CXCursor",          jni_lib_clang::Cursor::getMethods()},
    };
    return methods;
}

static int registerNatives(JNIEnv *pEnv) {
    auto allMethods = getAllMethods();
    for (auto item : allMethods) {
        jclass clazz = pEnv->FindClass(item.first);
        if (clazz == nullptr)
            return JNI_FALSE;

        auto methods = item.second;
        if (pEnv->RegisterNatives(clazz, methods.data(), methods.size()) < 0)
            return JNI_FALSE;
    }
    return JNI_TRUE;
}

extern "C" {
JNIEXPORT jint JNICALL JNI_OnLoad(JavaVM *vm, void *reserved) {

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
