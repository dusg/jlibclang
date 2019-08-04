//
// Created by Du Carl on 2019-08-04.
//

#ifndef LEARNLIBCLANG_JOBJECTWRAPPER_H
#define LEARNLIBCLANG_JOBJECTWRAPPER_H

#include <jni.h>
#include <string>

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
}

#endif //LEARNLIBCLANG_JOBJECTWRAPPER_H
