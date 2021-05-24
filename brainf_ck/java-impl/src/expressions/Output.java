package expressions;

import java.io.IOException;

import runner.Enviroment;

public class Output extends PrimitiveExpression {
    public Output(int count) { super(".", count); }
    public Output() { super("."); }

    @Override
    public void execute(Enviroment env) throws IOException {
        int value = env.memoryIterator().getNext();
        for (int i = 0; i < count; i++) {
            env.printStream().print((char)value);
        }
    }
}
