package jlibclang;

public class CXTranslationUnit {
    static {
        LibClang.LoadLibClang();
    }

    public CXTranslationUnit() {
    }

    public long get_handler() {
        return _handler;
    }

    public native CXCursor getUnitCursor();

    @Override
    protected void finalize() throws Throwable {
        super.finalize();
        disposeTranslationUnit();
    }
    private native void disposeTranslationUnit();

    private long _handler = 0;
}
