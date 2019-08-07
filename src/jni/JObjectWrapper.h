//
// Created by Du Carl on 2019-08-04.
//

#ifndef LEARNLIBCLANG_JOBJECTWRAPPER_H
#define LEARNLIBCLANG_JOBJECTWRAPPER_H

#include <jni.h>
#include <string>
#include <vector>

namespace jni_util
{
    class JString;

    class JObjectWrapper
    {
    public:
        JObjectWrapper(JNIEnv *env, jobject obj);

        JObjectWrapper(JNIEnv *env, const std::string &className, const std::string &constructor);

        void SetLongField(const std::string &fieldName, jlong fieldValue);

        jobject GetJavaObj() { return _obj; }

        jlong GetLongField(const std::string &fieldName);

        template<typename T>
        T GetObjField(const std::string &fieldName, const std::string &sig) {
            auto fieldId = _env->GetFieldID(_cls, fieldName.c_str(), sig.c_str());
            auto obj = _env->GetObjectField(_obj, fieldId);
            return T(_env, obj);
        }

        JString GetStringField(const std::string &fieldName);

    private:
        JNIEnv *_env = nullptr;
        jobject _obj = nullptr;
        std::string _className;
        jclass _cls;
    };

    class JString
    {
    public:
        typedef const char *NativeType;
    public:
        JString(JNIEnv *env, jstring str);

        void Init(JNIEnv *env, jstring str);

        JString(JNIEnv *env, jobject obj);

        virtual ~JString();

        const char *operator()();

        const char *c_str() { return operator()(); }

        std::string toStdString() { return c_str(); }

    private:
        JNIEnv *_env = nullptr;
        jstring _str = nullptr;
        std::string _stdString;
    };

    template<typename ElementType>
    class JArray : public std::vector<ElementType>
    {
    public:
        JArray(JNIEnv *env, jobjectArray jarr) {
            _env = env;
            _jarr = jarr;
            auto size = env->GetArrayLength(jarr);
            for (int i = 0; i < size; ++i) {
                jobject obj = env->GetObjectArrayElement(jarr, i);
                ElementType element(env, obj);
                this->push_back(element);
            }
        }

    private:
        JNIEnv *_env = nullptr;
        jobjectArray _jarr;
    };

    class JStrArray : public JArray<JString>
    {
    public:
        JStrArray(JNIEnv *env, jobjectArray jarr);

        virtual ~JStrArray();

        const char *const *toNative();

    private:
        JNIEnv *_env = nullptr;
        jobjectArray _jarr;
        std::vector<JString> _strArr;
        std::vector<const char *> _nativeArr;
    };

    template<typename T>
    class NativeWrapper
    {
    public:
        typedef T NativeType;

        NativeWrapper(NativeType native) {
            _native = native;
            _isNativeReady = true;
        }

        NativeWrapper(JNIEnv *env, jobject obj) {
            _env = env;
            _obj = obj;
        }

        NativeType &toNative() {
            if (!_isNativeReady) {
                DoMakeNative(_native, _env, _obj);
                _isNativeReady = true;
            }
            return _native;
        }

        jobject toJavaObj(JNIEnv *env) {
            return DoMakeJavaObj(env, _native);
        }

    protected:
        virtual void DoMakeNative(NativeType &native, JNIEnv *env, jobject obj) = 0;

        virtual jobject DoMakeJavaObj(JNIEnv *env, NativeType &native) = 0;

    private:
        JNIEnv *_env = nullptr;
        jobject _obj = nullptr;
        NativeType _native;
        bool _isNativeReady = false;
    };
}

#endif //LEARNLIBCLANG_JOBJECTWRAPPER_H
