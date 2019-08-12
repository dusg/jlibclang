//
// Created by Du Carl on 2019-08-11.
//

#ifndef LEARNLIBCLANG_JNI_UTILS_H
#define LEARNLIBCLANG_JNI_UTILS_H

#include <clang-c/CXString.h>
#include <string>
#define FiedlHandler "_handler"

namespace jni_lib_clang
{
    class String{
    public:
        String(CXString str);

        virtual ~String();

        const std::string &toStdString() {
            return _str;
        }

    private:
        CXString _cxString;
        std::string _str;
    };
}
#endif //LEARNLIBCLANG_JNI_UTILS_H
