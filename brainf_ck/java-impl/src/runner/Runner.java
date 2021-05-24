package runner;

import java.io.InputStream;
import java.io.PrintStream;

import expressions.Expression;
import memory.Memory;
import memory.MemoryIterator;

public class Runner implements Enviroment {
    private InputStream input;
    private PrintStream output;
    private Memory memory;
    private MemoryIterator memIter;

    public Runner(InputStream _input, PrintStream _output) {
        input = _input;
        output = _output;
        memory = new Memory();
        memIter = memory.memoryIterator();
    }

    public Runner() {
        this(System.in, System.out);
    }

    @Override
    public InputStream inputStream() {
        return input;
    }

    @Override
    public PrintStream printStream() {
        return output;
    }

    @Override
    public MemoryIterator memoryIterator() {
        return memIter;
    }

    @Override
    public void accept(Expression expr) throws Exception {
        expr.execute(this);
    }
}