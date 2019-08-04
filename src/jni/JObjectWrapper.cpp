//
// Created by Du Carl on 2019-08-04.
//

#include "JObjectWrapper.h"

jni_libclang::JObjectWrapper::JObjectWrapper(JNIEnv *env, jobject obj)
        : _env(env), _obj(obj) {
    _cls = env->GetObjectClass(obj);
}

void jni_libclang::JObjectWrapper::SetLongField(const std::string& fieldName, jlong fieldValue) {
    auto fieldId = _env->GetFieldID(_cls, fieldName.c_str(), "J");
    _env->SetLongField(_obj, fieldId, fieldValue);
}

jni_libclang::JObjectWrapper::JObjectWrapper(JNIEnv *env, const std::string& className, const std::string& constructor) {
    _env = env;
    _cls = env->FindClass(className.c_str());
    auto newMethod = env->GetMethodID(_cls, "<init>", constructor.c_str());
    _obj = env->NewObject(_cls, newMethod);
}

jlong jni_libclang::JObjectWrapper::GetLongField(const std::string& fieldName) {
    auto fieldId = _env->GetFieldID(_cls, fieldName.c_str(), "J");

    return _env->GetLongField(_obj, fieldId);
}
