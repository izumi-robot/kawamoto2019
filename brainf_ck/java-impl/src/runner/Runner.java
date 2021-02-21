package runner;


import java.io.Reader;
import java.io.Writer;

import expressions.Increment;
import expressions.Decrement;
import expressions.Forward;
import expressions.Backward;
import expressions.Input;
import expressions.Output;
import expressions.Loop;
import expressions.Expression;

import memory.Memory;
import memory.MemoryIterator;

public class Runner {
    public Reader charReader;
    public Writer charWriter;
    private Memory memory;
    public MemoryIterator memoryIterator;

    public Runner(Reader reader, Writer writer) {
        charReader = reader;
        charWriter = writer;
        memory = new Memory();
        memoryIterator = memory.memoryIterator();
    }

    public Runner() { this(System.in, System.out); }

    void accept(Expression expr) {
        expr.execute(this);
    }
}