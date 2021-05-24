package expressions;

import java.io.IOException;

import runner.Enviroment;

public class Input extends PrimitiveExpression {
    public Input(int count) { super(",", count); }
    public Input() { super(","); }

    @Override
    public void execute(Enviroment env) throws IOException {
        for (int i = 0; i < count; i++) {
            int value;
            try {
                value = env.inputStream().read();
            }
            catch (IOException e) {
                throw e;
            }
            env.memoryIterator().set(value);
        }
    }
}
