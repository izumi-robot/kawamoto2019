package expressions;

import memory.MemoryIterator;
import runner.Runner;

public class Backward extends PrimitiveExpression {
    public Backward(int count) { super("<", count); }
    public Backward() { super("<"); }

    @Override
    public void execute(Runner runner) throws Exception {
        MemoryIterator iter = runner.memoryIterator;
        for (int i = 0; i < count; i++) {
            if (!iter.hasPrevious()) {
                throw new Exception("exception while executing command '<': reached to the first point");
            }
            iter.previous();
        }
    }
}
