package expressions;

import java.util.List;
import java.util.ListIterator;
import java.util.ArrayList;

public abstract class ExprSequence implements Expression {
    protected List<Expression> sequence;

    public ExprSequence(List<Expression> seq) {
        sequence = seq;
    }

    public ExprSequence() {
        sequence = new ArrayList<>();
    }

    public void addExpr(Expression expr) {
        sequence.add(expr);
    }

    public List<Expression> getExprs() {
        return sequence;
    }

    public ListIterator<Expression> exprIterator() {
        return sequence.listIterator();
    }

    @Override
    public String toString() {
        String str = "";
        for (Expression e : sequence) {
            str += e.toString();
        }
        return str;
    }
}
