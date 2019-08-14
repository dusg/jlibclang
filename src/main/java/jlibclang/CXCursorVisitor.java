package jlibclang;

public interface CXCursorVisitor {
    void Visit(CXCursor cursor, CXCursor parent, CXClientData client_data);
}
