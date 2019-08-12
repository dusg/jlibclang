package jlibclang;


public class CXCursor {
    static {
        LibClang.LoadLibClang();
    }
    private CXCursor() {}

    public native boolean visitChildren(CXCursorVisitor visitor, CXClientData data);

    native String getSpelling();

    CXCursorKind getKind() throws Exception {
        return CXCursorKind.fromNative(getKindNative());
    }
    native int getKindNative();
    native void disposeNative();

    @Override
    public String toString() {
        return getSpelling();
    }

    @Override
    protected void finalize() throws Throwable {
        super.finalize();
        disposeNative();
    }

    private long _handler = 0;

    public long get_handler() {
        return _handler;
    }
}
