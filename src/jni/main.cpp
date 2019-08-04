#include <iostream>
#include <clang-c/Index.h>  // This is libclang.
#include <boost/filesystem.hpp>
#include <boost/format.hpp>

using namespace std;
using namespace boost;

ostream &operator<<(ostream &stream, const CXString &str) {
    stream << clang_getCString(str);
    clang_disposeString(str);
    return stream;
}

enum CXChildVisitResult CursorVisitor(CXCursor cursor,
                                      CXCursor parent,
                                      CXClientData client_data);

int main() {
    cout << filesystem::current_path() << endl;
    CXIndex index = clang_createIndex(0, 0);
    CXTranslationUnit unit = clang_parseTranslationUnit(
            index,
            "/Users/desg/ClionProjects/LearnLibclang/test.cpp", nullptr, 0,
            nullptr, 0,
            CXTranslationUnit_None);
    if (unit == nullptr) {
        cerr << "Unable to parse translation unit. Quitting." << endl;
        exit(-1);
    }

    CXCursor cursor = clang_getTranslationUnitCursor(unit);
    clang_visitChildren(
            cursor,
            CursorVisitor,
            nullptr);

    clang_disposeTranslationUnit(unit);
    clang_disposeIndex(index);
}

enum CXChildVisitResult CursorVisitor(CXCursor cursor,
                                      CXCursor parent,
                                      CXClientData client_data) {
    cout << "Cursor '" << clang_getCursorSpelling(cursor) << "' of kind '"
         << clang_getCursorKindSpelling(clang_getCursorKind(cursor)) << "'\n";
    if (cursor.kind == CXCursorKind::CXCursor_FunctionDecl) {
        auto num = clang_Cursor_getNumArguments(cursor);
        cout << "  ";
        for (int i = 0; i < num; ++i) {
            auto c = clang_Cursor_getArgument(cursor, i);
            auto type = clang_getCursorType(c);
            cout << boost::format("arg%d:%s %s ") % i % clang_getTypeSpelling(clang_getCursorType(c)) %
                    clang_getCursorSpelling(c);
            if (type.kind != CXTypeKind::CXType_Invalid) {
                cout << endl << "  ";
                int f = 1;
                clang_Type_visitFields(type, [](CXCursor c, CXClientData clientData) {
                    cout << boost::format("field%d:%s ") %(*(int*)(clientData))% clang_getTypeSpelling(clang_getCursorType(c)) ;
                                           return CXVisit_Continue;
                                       },
                                       &f);
            }
        }
        cout << endl;
    }
    return CXChildVisit_Recurse;
}
