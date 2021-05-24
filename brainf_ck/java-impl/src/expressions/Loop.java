package expressions;

import java.util.ListIterator;

import runner.Enviroment;

public class Loop extends ExprSequence {
    @Override
    public String toString() {
        return "[" + super.toString() + "]";
    }

    @Override
    public void execute(Enviroment env) throws Exception {
        while (env.memoryIterator().getNext() != 0) {
            ListIterator<Expression> expr_iter = sequence.listIterator();
            while (expr_iter.hasNext()) {
                Expression expr = expr_iter.next();
                try {
                    expr.execute(env);
                }
                catch (Exception e) {
                    throw e;
                }
            }
        }
    }
}
