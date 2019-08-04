package jlibclang;


public class CXTranslationUnit {
    static {
        LibClang.LoadLibClang();
    }
    native CXCursor getUnitCursor();
}
