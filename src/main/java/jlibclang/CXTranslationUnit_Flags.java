package jlibclang;

public enum CXTranslationUnit_Flags {
    CXTranslationUnit_None(0x0);

    CXTranslationUnit_Flags(int code) {
        _code = code;
    }

    int _code;
    public int getCode() {
        return _code;
    }

}
