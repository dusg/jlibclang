//
// Created by Du Carl on 2019-08-04.
//
#include <iostream>
#include <clang-c/Index.h>  // This is libclang.
#include <boost/format.hpp>
#include <boost/algorithm/string.hpp>
#include <fstream>

using namespace std;

ostream &operator<<(ostream &stream, const CXString &str) {
    stream << clang_getCString(str);
    clang_disposeString(str);
    return stream;
}

std::string &operator<<(std::string &str, CXString cxString) {
    str = clang_getCString(cxString);
    clang_disposeString(cxString);
    return str;
}


int main() {
    ofstream ofs("cursor_kinds.java");
    ofs << "package jlibclang;\n";
    ofs << "public enum CXCursorKind {\n";
    for (int i = 0; i <= CXCursorKind::CXCursor_OverloadCandidate; ++i) {
        std::string text;
        text << clang_getCursorKindSpelling(static_cast<CXCursorKind>(i));
        if ((text == "FunctionDecl") && i != CXCursorKind::CXCursor_FunctionDecl) {
            text.clear();
        }
        if (text.length()) {
            boost::replace_all(text, " ", "_");
            boost::replace_all(text, "(", "_");
            boost::replace_all(text, ")", "_");
            boost::replace_all(text, "+", "p");
            if (text.back() == '_') {
                text.pop_back();
            }
            text = (boost::format("%s(%d),\n") % text % i).str();
            if (i == CXCursorKind::CXCursor_OverloadCandidate) {
                boost::replace_last(text, ",", ";");
            }
            ofs << text ;
            cout << text;
//            cout << boost::format("%s(%d),") % text % i << endl;
        }
    }
    ofs << "    public CXCursorKind(int code) { _code = code; }\n";
    ofs << "    private int _code = 0;\n";
    ofs << "}\n";
}
