package expressions;

import runner.Runner;

public class Increment extends PrimitiveExpression {
    public Increment(int count) { super("+", count); }
    public Increment() { super("+"); }

    @Override
    public void execute(Runner runner) {
        int value = runner.memoryIterator.getNext();
        runner.memoryIterator.set(value + count);
    }
}
