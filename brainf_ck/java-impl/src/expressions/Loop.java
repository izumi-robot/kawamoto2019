package expressions;

import java.util.List;
import java.util.ArrayList;

import runner.Runner;

public class Loop implements Expression {
    protected List<Expression> exprs;

    public Loop(List<Expression> exprs) {
        assert exprs != null;
        this.exprs = exprs;
    }

    public Loop() {
        this.exprs = new ArrayList<>();
    }

    public void addExpression(Expression expr) {
        exprs.add(expr);
    }

    @Override
    public String toString() {
        String res = "[";
        for (Expression expr : exprs) {
            res += expr.toString();
        }
        return res + "]";
    }

    @Override
    public void execute(Runner runner) throws Exception {
        while (runner.memoryIterator.getNext() != 0) {
            ListIterator<Expression> expr_iter = exprs.listIterator();
            while (expr_iter.hasNext()) {
                Expression expr = expr_iter.next();
                try {
                    expr.execute(runner);
                }
                catch (Exception e) {
                    throw e;
                }
            }
        }
    }
}
