package jlibclang;

import com.sun.jna.Platform;
import test.ClangTest;

public class LibClang {
    public static void LoadLibClang() {
        String libPath = "";
        if (Platform.isMac()) {
            libPath = "clang-jni";
        } else if (Platform.isWindows()) {
            libPath = "libclang-jni.dll";
        }
//        String basePath = System.getProperty("jni.library.path");
        //libPath = String.format("%s/%s", basePath, libPath);
//        System.out.println(System.getProperty("user.dir"));
        System.loadLibrary(libPath);
    }

    static {
        LoadLibClang();
    }

    public static final LibClang I = new LibClang();

    native CXIndex createIndex(boolean excludeDeclarationsFromPCH, boolean displayDiagnostics);

    public CXIndex createIndex() {
        return createIndex(false, false);
    }

    String getCursorKindSpelling(CXCursor cursor) throws Exception {
        return getCursorKindSpelling(cursor.getKind());
    }

    String getCursorKindSpelling(CXCursorKind kind) {
        return getCursorKindSpelling(kind.toNative());
    }

    private native String getCursorKindSpelling(int kind);

    public static void main(String[] args) {
        ClangTest clangTest = new ClangTest();
        clangTest.testCreateIndex();
        clangTest.testParseTranslationUnit();
        clangTest.testAST();
    }
}