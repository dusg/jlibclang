//
// Created by Du Carl on 2019-08-04.
//

#include "jni_index.h"
#include <clang-c/Index.h>
#include <jni.h>
#include <vector>
#include "JObjectWrapper.h"
#include "jni_translate_unit.h"
namespace jni_lib_clang
{

    JNICALL jobject parseTranslationUnit(JNIEnv *env, jobject thisObj, jstring source_file, jobjectArray command_line_args,
                                         jobjectArray unsaved_files, jint options) {
        using namespace jni_util;
        Index idx(env, thisObj);
        JString srcFile(env, source_file);
        JStrArray args(env, command_line_args);
        JArray<UnsavedFile> unsavedFiles(env, unsaved_files);
        CXTranslationUnit unit = clang_parseTranslationUnit(
                idx.toNative(),
                srcFile.c_str(), args.toNative(), args.size(),
                unsavedFiles.data(), unsavedFiles.size(),
                options);

        return TranslationUnit(unit).toJavaObj(env);
    }

    std::vector<JNINativeMethod> Index::methods = {
            {(char*)"parseTranslationUnit", (char*)"(Ljava/lang/String;[Ljava/lang/String;[Ljlibclang/CXUnsavedFile;I)Ljlibclang/CXTranslationUnit;", (void *) parseTranslationUnit}
    };

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
        static std::string temp1 = wrapper.GetStringField(_ContentsField).toStdString();
        native.Contents = temp1.c_str();
        static std::string temp2 = wrapper.GetStringField(_FilenameField).toStdString();
        native.Filename = temp2.c_str();
    }

    jobject UnsavedFile::DoMakeJavaObj(JNIEnv *env, CXUnsavedFile &native) {
        using namespace jni_util;
        JObjectWrapper wrapper(env, "jlibclang/CXUnsavedFile", "()V");
        wrapper.SetLongField(_LengthField, native.Length);
        wrapper.SetStringField(_ContentsField, native.Contents);
        wrapper.SetStringField(_FilenameField, native.Filename);
        return wrapper.GetJavaObj();
    }
}