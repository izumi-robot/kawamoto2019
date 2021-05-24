package runner;

import java.io.InputStream;
import java.io.PrintStream;

import expressions.Expression;
import memory.MemoryIterator;

public interface Enviroment {
    public InputStream inputStream();
    public PrintStream printStream();
    public MemoryIterator memoryIterator();
    public void accept(Expression expr) throws Exception;
}
