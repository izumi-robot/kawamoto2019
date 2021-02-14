package expressions;

public class Increment extends PrimitiveExpression {
    Increment(int count) { super("+", count); }
    Increment() { super("+"); }
}
