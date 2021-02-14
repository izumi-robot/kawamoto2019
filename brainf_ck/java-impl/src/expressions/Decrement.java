package expressions;

public class Decrement extends PrimitiveExpression {
    Decrement(int count) { super("-", count); }
    Decrement() { super("-"); }
}
