//
// Created by Du Carl on 2019-08-04.
//

#ifndef LEARNLIBCLANG_JOBJECTWRAPPER_H
#define LEARNLIBCLANG_JOBJECTWRAPPER_H

#include <jni.h>
#include <string>
#include <vector>

namespace jni_libclang
{
    class JObjectWrapper
    {
    public:
        JObjectWrapper(JNIEnv *env, jobject obj);
        JObjectWrapper(JNIEnv* env, const std::string& className, const std::string& constructor);

        void SetLongField(const std::string& fieldName, jlong fieldValue);

        jobject GetJavaObj() { return _obj; }

        jlong GetLongField(const std::string& fieldName);

    private:
        JNIEnv* _env = nullptr;
        jobject _obj = nullptr;
        std::string _className;
        jclass _cls;
    };

    class JString
    {
    public:
        JString(JNIEnv* env, jstring str);
        virtual ~JString();

        const char*operator()();
        const char* c_str() { return operator()();}
    private:
        JNIEnv* _env = nullptr;
        const char* _cstr = nullptr;
        jstring _str;
    };

    class JStrArray
    {
    public:
        JStrArray(JNIEnv *env, jobjectArray);
        virtual ~JStrArray();

        const char* const * toNative();

    private:
        JNIEnv* _env = nullptr;
        jobjectArray _jarr;
        std::vector<JString> _strArr;
        std::vector<const char*> _nativeArr;
    };
}

#endif //LEARNLIBCLANG_JOBJECTWRAPPER_H
