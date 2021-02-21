package expressions;

import java.io.IOException;

import runner.Runner;

public class Input extends PrimitiveExpression {
    public Input(int count) { super(",", count); }
    public Input() { super(","); }

    @Override
    public void execute(Runner runner) throws Exception {
        for (int i = 0; i < count; i++) {
            int value;
            try {
                value = runner.charReader.read();
            }
            catch (IOException e) {
                throw e;
                //throw new Exception("exception while executing command ',': error on reading a character");
            }
            runner.memoryIterator.set(value);
        }
    }
}
