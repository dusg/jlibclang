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
        using namespace jni_libclang;
        Index idx(env, thisObj);

        JString srcFile(env, source_file);
        CXTranslationUnit unit = clang_parseTranslationUnit(
                idx.handler,
                srcFile.c_str(), nullptr, 0,
                nullptr, 0,
                CXTranslationUnit_None);
    }

    std::vector<JNINativeMethod> methods;

    Index::Index(JNIEnv *env, jobject obj) {
        using namespace jni_libclang;
        JObjectWrapper wrapper(env, obj);
        handler = reinterpret_cast<CXIndex>(wrapper.GetLongField(_handlerName));
    }

    Index::Index(CXIndex handler) {
        handler = handler;
    }

    jobject Index::toJavaObj(JNIEnv *env) {
        using namespace jni_libclang;
        JObjectWrapper wrapper(env, _className, _newName);
        return wrapper.GetJavaObj();
    }

}