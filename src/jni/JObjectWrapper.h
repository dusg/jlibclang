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

        template<typename T>
        void SetObjField(const std::string &fieldName, NativeWrapper<T> &fieldValue, const std::string &sig) {
            auto fieldId = _env->GetFieldID(_cls, fieldName.c_str(), sig.c_str());
            _env->SetObjectField(_obj, fieldId, fieldValue.toJavaObj(_env));
        }
        void SetObjField(const std::string &fieldName, jobject fieldValue, const std::string &sig) {
            auto fieldId = _env->GetFieldID(_cls, fieldName.c_str(), sig.c_str());
            _env->SetObjectField(_obj, fieldId, fieldValue);
        }
        JString GetStringField(const std::string &fieldName);
        void SetStringField(const std::string &fieldName, std::string str);

        void CallVoid(std::string name, std::string sig, ...);

        template <typename ReturnType>
        ReturnType Call(std::string name, std::string sig, ...) {
            auto methodId = _env->GetMethodID(_cls, name.c_str(), sig.c_str());
            va_list args;
            va_start(args,sig);
            ReleaseArgs tmp(args);
            if (typeid(jobject) == typeid(ReturnType)) {
                return _env->CallObjectMethodV(_obj, methodId, args);
            } else if (typeid(jboolean) == typeid(ReturnType)) {
                return _env->CallBooleanMethodV(_obj, methodId, args);
            } else if (typeid(jbyte) == typeid(ReturnType)) {
                return _env->CallByteMethodV(_obj, methodId, args);
            } else if (typeid(jchar) == typeid(ReturnType)) {
                return _env->CallCharMethodV(_obj, methodId, args);
            } else if (typeid(jshort) == typeid(ReturnType)) {
                return _env->CallShortMethodV(_obj, methodId, args);
            } else if (typeid(jint) == typeid(ReturnType)) {
                return _env->CallIntMethodV(_obj, methodId, args);
            } else if (typeid(jlong) == typeid(ReturnType)) {
                return _env->CallLongMethodV(_obj, methodId, args);
            } else if (typeid(jfloat) == typeid(ReturnType)) {
                return _env->CallFloatMethodV(_obj, methodId, args);
            } else if (typeid(jdouble) == typeid(ReturnType)) {
                return _env->CallDoubleMethodV(_obj, methodId, args);
            }
        }
    private:
        struct ReleaseArgs {
                ReleaseArgs(va_list& args):args(args){}
                ~ReleaseArgs(){ va_end(args); }
                va_list & args;
            };
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
        JString(std::string str):_stdString(str) {
        }
        virtual ~JString();

        const char *operator()();

        const char *c_str() { return operator()(); }

        std::string toStdString() { return c_str(); }
        jstring toJaveObj(JNIEnv* env) {
            return env->NewStringUTF(_stdString.c_str());
        }

    private:
        JNIEnv *_env = nullptr;
        jstring _str = nullptr;
        std::string _stdString;
    };

    template<typename ElementType>
    class JArray : public std::vector<typename ElementType::NativeType>
    {
    public:
        JArray(JNIEnv *env, jobjectArray jarr) {
            _env = env;
            _jarr = jarr;
            if (jarr == nullptr) {
                return;
            }
            auto size = env->GetArrayLength(jarr);
            for (int i = 0; i < size; ++i) {
                jobject obj = env->GetObjectArrayElement(jarr, i);
                ElementType element(env, obj);
                this->push_back(element.toNative());
            }
        }
        typename ElementType::NativeType * toNative() {
            if (this->empty()) {
                return nullptr;
            }
            return this->data();
        }
    private:
        JNIEnv *_env = nullptr;
        jobjectArray _jarr;
    };

    class JStrArray
    {
    public:
        JStrArray(JNIEnv *env, jobjectArray jarr);

        virtual ~JStrArray();

        const char *const *toNative();

        size_t size() { return _nativeArr.size(); }

    private:
        JNIEnv *_env = nullptr;
        jobjectArray _jarr;
        std::vector<JString> _strArr;
        std::vector<const char *> _nativeArr;
    };

}

#endif //LEARNLIBCLANG_JOBJECTWRAPPER_H
