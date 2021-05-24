package expressions;

import runner.Enviroment;

public class Decrement extends PrimitiveExpression {
    public Decrement(int count) { super("-", count); }
    public Decrement() { super("-"); }

    @Override
    public void execute(Enviroment env) {
        int value = env.memoryIterator().getNext();
        env.memoryIterator().set(value - count);
    }
}
