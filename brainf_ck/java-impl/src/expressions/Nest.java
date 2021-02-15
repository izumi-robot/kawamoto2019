package expressions;

import java.util.List;
import java.util.ArrayList;

public class Nest implements Expression {
    protected List<Expression> exprs;

    Nest(List<Expression> exprs) {
        assert exprs != null;
        this.exprs = exprs;
    }

    Nest() {
        this.exprs = new ArrayList<>();
    }

    @Override
    public String toString() {
        String res = "[";
        for (Expression expr : exprs) {
            res += expr.toString();
        }
        return res + "]";
    }
}
