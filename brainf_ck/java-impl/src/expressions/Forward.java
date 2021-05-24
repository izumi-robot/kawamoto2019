package expressions;

import runner.Enviroment;

public class Forward extends PrimitiveExpression {
    public Forward(int count) { super(">", count); }
    public Forward() { super(">"); }

    @Override
    public void execute(Enviroment env) {
        for (int i = 0; i < count; i++) {
            env.memoryIterator().next();
        }
    }
}
