package expressions;

import runner.Enviroment;

public class Increment extends PrimitiveExpression {
    public Increment(int count) { super("+", count); }
    public Increment() { super("+"); }

    @Override
    public void execute(Enviroment env) {
        int value = env.memoryIterator().getNext();
        env.memoryIterator().set(value + count);
    }
}
