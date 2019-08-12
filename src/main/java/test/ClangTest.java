package test;

import jlibclang.*;
import org.junit.Assert;

import java.util.ArrayList;

public class ClangTest extends ClangTestBase {
    public void testCreateIndex() {
        CXIndex index = createCxIndex();
        Assert.assertTrue(index.get_handler() != 0);
    }

    public void testParseTranslationUnit() {
        CXTranslationUnit unit = getCxTranslationUnit();

        Assert.assertTrue(unit.get_handler() != 0);
    }

    public void testCursor() {
        CXCursor cursor = getCursor();
        Assert.assertTrue(cursor.get_handler() != 0);
    }

    private CXCursor getCursor() {
        CXTranslationUnit unit = getCxTranslationUnit();
        return unit.getUnitCursor();
    }

    private CXTranslationUnit getCxTranslationUnit() {
        CXIndex index = createCxIndex();
        CXTranslationUnit_Flags[] options = {CXTranslationUnit_Flags.CXTranslationUnit_None};

        return index.parseTranslationUnit("/Users/desg/ClionProjects/LearnLibclang/test.cpp",
                null, null, options);
    }

    private CXIndex createCxIndex() {
        LibClang libClang = new LibClang();
        return libClang.createIndex();
    }
}
