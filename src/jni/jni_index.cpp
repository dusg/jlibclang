//
// Created by Du Carl on 2019-08-04.
//

#include "jni_index.h"
#include <clang-c/Index.h>
#include <jni.h>
#include <vector>
#include "JObjectWrapper.h"
namespace index_libclang
{

    jobject jni_parseTranslationUnit(JNIEnv *env, jobject thisObj, jstring source_file, jobjectArray command_line_args,
                                     jobjectArray unsaved_files, jint options) {
        using namespace jni_util;
        Index idx(env, thisObj);

        JString srcFile(env, source_file);
        JStrArray args(env, command_line_args);
        CXTranslationUnit unit = clang_parseTranslationUnit(
                idx.toNative(),
                srcFile.c_str(), args.toNative(), args.size(),
                nullptr, 0,
                CXTranslationUnit_None);
    }

    std::vector<JNINativeMethod> methods;

    Index::Index(JNIEnv *env, jobject obj) : NativeWrapper(env, obj) {
    }

    Index::Index(CXIndex handler) : NativeWrapper(handler) {
    }

    void Index::DoMakeNative(void *&native, JNIEnv *env, jobject obj) {
        using namespace jni_util;
        JObjectWrapper wrapper(env, obj);
        native = reinterpret_cast<CXIndex>(wrapper.GetLongField(_handlerName));
    }

    jobject Index::DoMakeJavaObj(JNIEnv *env, void *&native) {
        using namespace jni_util;
        JObjectWrapper wrapper(env, _className, _newName);
        wrapper.SetLongField(_handlerName, reinterpret_cast<jlong>(native));
        return wrapper.GetJavaObj();
    }

    UnsavedFile::UnsavedFile(JNIEnv *env, jobject obj) : NativeWrapper(env, obj) {}

    void UnsavedFile::DoMakeNative(CXUnsavedFile &native, JNIEnv *env, jobject obj) {
        using namespace jni_util;
        JObjectWrapper wrapper(env, obj);
        native.Length = wrapper.GetLongField(_LengthField);
    }

    jobject UnsavedFile::DoMakeJavaObj(JNIEnv *env, CXUnsavedFile &native) {
        return nullptr;
    }
}