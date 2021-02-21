package expressions;

import memory.MemoryIterator;
import runner.Runner;

public class Forward extends PrimitiveExpression {
    public Forward(int count) { super(">", count); }
    public Forward() { super(">"); }

    @Override
    public void execute(Runner runner) {
        for (int i = 0; i < count; i++) {
            runner.memoryIterator.next();
        }
    }
}
