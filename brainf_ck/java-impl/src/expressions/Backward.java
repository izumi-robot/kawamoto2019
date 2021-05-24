package expressions;

import memory.MemoryIterator;
import runner.Enviroment;

public class Backward extends PrimitiveExpression {
    public Backward(int count) { super("<", count); }
    public Backward() { super("<"); }

    @Override
    public void execute(Enviroment env) throws Exception {
        MemoryIterator iter = env.memoryIterator();
        for (int i = 0; i < count; i++) {
            if (!iter.hasPrevious()) {
                throw new Exception("exception while executing command '<': reached to the first point");
            }
            iter.previous();
        }
    }
}
