package jlibclang;


public class CXCursor {
    static {
        LibClang.LoadLibClang();
    }

    native boolean visitChildren(CXCursorVisitor visitor, CXClientData data);

    native String getSpelling();

    native CXCursorKind getKind();

    @Override
    public String toString() {
        return getSpelling();
    }
}
