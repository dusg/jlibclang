//
// Created by Du Carl on 2019-08-11.
//

#include "jni_utils.h"

jni_lib_clang::String::~String() {
    clang_disposeString(_cxString);
}

jni_lib_clang::String::String(CXString str) {
    _str = clang_getCString(str);
}
