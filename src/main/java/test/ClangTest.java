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

    public void testAST() {
        final CXCursor cxCursor = getCursor();
        try {
            cxCursor.visitChildren(new CXCursorVisitor() {
                public void Visit(CXCursor cursor, CXCursor parent, CXClientData client_data) throws Exception {
                    String msg = String.format("Cursor %s of kind %s", cursor, cursor.getKind());
                    System.out.println(msg);
                }
            }, null);
        } catch (Exception e) {
            e.printStackTrace();
            assertTrue(false);
        }
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
