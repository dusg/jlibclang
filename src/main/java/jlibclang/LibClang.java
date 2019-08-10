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

    public static void main(String[] args) {
        ClangTest clangTest = new ClangTest();
        clangTest.testCreateIndex();
    }
}