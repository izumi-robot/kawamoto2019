package expressions;

public abstract class PrimitiveExpression implements Expression {
    protected int count;
    protected String expr_str;

    public PrimitiveExpression(String expr_str, int count) {
        assert expr_str != null;
        assert count > 0;
        this.expr_str = expr_str;
        this.count = count;
    }

    public PrimitiveExpression(String expr_str) {
        this(expr_str, 1);
    }

    public String exprString() {
        return expr_str;
    }

    @Override
    public String toString() {
        String res = "";
        for (int i = 0; i < count; i++) {
            res += expr_str;
        }
        return res;
    }

    public boolean setCount(int count) {
        if (count <= 0) { return false; }
        this.count = count;
        return true;
    }

    public boolean changeCountBy(int offset) {
        return setCount(count + offset);
    }
}
