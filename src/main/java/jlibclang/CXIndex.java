package jlibclang;

import org.jetbrains.annotations.NotNull;

import java.lang.ref.PhantomReference;
import java.lang.ref.WeakReference;

public class CXIndex {
    static {
//        LibClang.LoadLibClang();
    }

    long _handler = 0;

    @Override
    protected void finalize() throws Throwable {
        super.finalize();
        disposeIndex();
    }

    public long get_handler() {
        return _handler;
    }

    public CXTranslationUnit parseTranslationUnit(String source_filename,
                                           String[] command_line_args,
                                           CXUnsavedFile[] unsaved_files,
                                           CXTranslationUnit_Flags[] options) {
        int opt = 0;
        for (CXTranslationUnit_Flags flag : options) {
            opt |= flag.getCode();
        }
        return parseTranslationUnit(source_filename, command_line_args, unsaved_files, opt);
    }

    private native CXTranslationUnit parseTranslationUnit(String source_filename,
                                                  String[] command_line_args,
                                                  CXUnsavedFile[] unsaved_files,
                                                  int options);
    private native void disposeIndex();
}
