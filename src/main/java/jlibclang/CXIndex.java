package jlibclang;

public class CXIndex {
    static {
        LibClang.LoadLibClang();
    }

    long _handler = 0;

    public long get_handler() {
        return _handler;
    }

    native CXTranslationUnit parseTranslationUnit(String source_filename,
                                                  String[] command_line_args,
                                                  CXUnsavedFile unsaved_files,
                                                  CXTranslationUnit_Flags[] options);
}
