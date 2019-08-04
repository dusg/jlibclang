package test;

import jlibclang.CXIndex;
import jlibclang.LibClang;
import org.junit.Assert;

public class ClangTest extends ClangTestBase {
    public void testCreateIndex() {
        LibClang libClang = new LibClang();
        CXIndex index = libClang.createIndex();
        Assert.assertTrue(index.get_handler() != 0);
    }
}
