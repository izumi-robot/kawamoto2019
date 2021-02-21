package expressions;

import runner.Runner;

public class Decrement extends PrimitiveExpression {
    public Decrement(int count) { super("-", count); }
    public Decrement() { super("-"); }

    @Override
    public void execute(Runner runner) {
        int value = runner.memoryIterator.getNext();
        runner.memoryIterator.set(value - count);
    }
}
