package test;

import junit.framework.TestCase;
import org.jetbrains.annotations.NotNull;

import java.io.File;

public abstract class ClangTestBase extends TestCase {
    @Override
    protected void setUp() throws Exception {
        super.setUp();
        String path = String.format("%s/dll", System.getProperty("user.dir"));
        System.setProperty("jni.library.path", path);
    }

    @Override
    protected void tearDown() throws Exception {
        super.tearDown();
    }

    @NotNull
    protected static File getTestDataDir() {
        return new File("testData/");
    }
}
