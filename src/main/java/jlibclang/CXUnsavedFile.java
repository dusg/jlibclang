package jlibclang;

public class CXUnsavedFile {
    public CXUnsavedFile() {
    }

    public String getFilename() {
        return Filename;
    }

    public String getContents() {
        return Contents;
    }

    public long getLength() {
        return Length;
    }

    public void setFilename(String filename) {
        Filename = filename;
    }

    public void setContents(String contents) {
        Contents = contents;
    }

    public void setLength(long length) {
        Length = length;
    }
    /**
     * The file whose contents have not yet been saved.
     * <p>
     * This file must already exist in the file system.
     */
    String Filename = "";

    /**
     * A buffer containing the unsaved contents of this file.
     */
    String Contents = "";

    /**
     * The length of the unsaved contents of this buffer.
     */
    long Length = 0;
}
