package expressions;

import java.io.IOException;

import runner.Runner;

public class Output extends PrimitiveExpression {
    public Output(int count) { super(".", count); }
    public Output() { super("."); }

    @Override
    public void execute(Runner runner) throws Exception {
        int value = runner.memoryIterator.getNext();
        for (int i = 0; i < count; i++) {
            try {
                runner.charWriter.write(value);
            }
            catch (IOException e) {
                throw e;
            }
        }
    }
}
