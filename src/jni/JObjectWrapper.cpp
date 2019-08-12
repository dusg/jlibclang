//
// Created by Du Carl on 2019-08-04.
//

#include "JObjectWrapper.h"

jni_util::JObjectWrapper::JObjectWrapper(JNIEnv *env, jobject obj)
        : _env(env), _obj(obj) {
    _cls = env->GetObjectClass(obj);
}

void jni_util::JObjectWrapper::SetLongField(const std::string& fieldName, jlong fieldValue) {
    auto fieldId = _env->GetFieldID(_cls, fieldName.c_str(), "J");
    _env->SetLongField(_obj, fieldId, fieldValue);
}

jni_util::JObjectWrapper::JObjectWrapper(JNIEnv *env, const std::string& className, const std::string& constructor) {
    _env = env;
    _cls = env->FindClass(className.c_str());
    auto newMethod = env->GetMethodID(_cls, "<init>", constructor.c_str());
    _obj = env->NewObject(_cls, newMethod);
}

jlong jni_util::JObjectWrapper::GetLongField(const std::string& fieldName) {
    auto fieldId = _env->GetFieldID(_cls, fieldName.c_str(), "J");

    return _env->GetLongField(_obj, fieldId);
}

jni_util::JString jni_util::JObjectWrapper::GetStringField(const std::string &fieldName) {
    return GetObjField<JString>(fieldName, "java/lang/String");
}

void jni_util::JObjectWrapper::SetStringField(const std::string &fieldName, std::string str) {
    jstring jstring1 = _env->NewStringUTF(str.c_str());
    SetObjField(fieldName, jstring1, "java/lang/String");
}

jni_util::JString::JString(JNIEnv *env, jstring str) {
    Init(env, str);
}

const char *jni_util::JString::operator()() {
    return _stdString.c_str();
}

jni_util::JString::~JString() {
}

jni_util::JString::JString(JNIEnv *env, jobject obj) {
    Init(env, static_cast<jstring>(obj));
}

void jni_util::JString::Init(JNIEnv *env, jstring str) {
    _env = env;
    _str = str;
    auto cstr = env->GetStringUTFChars(str, nullptr);
    _stdString = cstr;
    _env->ReleaseStringUTFChars(_str, cstr);
}

jni_util::JStrArray::JStrArray(JNIEnv *env, jobjectArray jarr) {
    _env = env;
    _jarr = jarr;
    if (jarr == nullptr) {
        return;
    }
    auto size = env->GetArrayLength(jarr);
    for (int i = 0; i < size; ++i) {
        auto str = static_cast<jstring>(env->GetObjectArrayElement(jarr, i));
        JString jString(env, str);
        _strArr.emplace_back(jString);
        _nativeArr.push_back(jString.c_str());
    }
}

const char *const *jni_util::JStrArray::toNative() {
    if (_nativeArr.empty()) {
        return nullptr;
    }

    return _nativeArr.data();
}

jni_util::JStrArray::~JStrArray() = default;
