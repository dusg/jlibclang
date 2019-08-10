package jlibclang;

public class CXTranslationUnit {
    static {
        LibClang.LoadLibClang();
    }
    public native CXCursor getUnitCursor();

    private long _handler = 0;
}
