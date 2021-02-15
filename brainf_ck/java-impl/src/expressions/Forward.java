package expressions;

public class Forward extends PrimitiveExpression {
    Forward(int count) { super(">", count); }
    Forward() { super(">"); }
}
