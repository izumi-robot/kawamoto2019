package expressions;

import java.util.List;

import runner.Enviroment;

public class Program extends ExprSequence {
    static public Program parse(String script) {
        Program program = new Program(parseLoop(script, 0, script.length()).getExprs());
        return program;
    }

    static private Loop parseLoop(String script, int begin, int end) {
        Loop loop = new Loop();
        PrimitiveExpression last_expr = null;
        int i = begin, loop_count = 0, loop_start = 0;
        while (i < end) {
            char ch = script.charAt(i);
            switch (ch) {
                case '[':
                    if (last_expr != null) {
                        loop.addExpr(last_expr);
                        last_expr = null;
                    }
                    if (loop_count++ == 0) {
                        loop_start = i + 1;
                    }
                    break;
                case ']':
                    if (--loop_count == 0) {
                        loop.addExpr(parseLoop(script, loop_start, i));
                    }
                    break;
                case '+': case '-': case '>': case '<': case ',': case '.':
                    if (loop_count > 0) { break; }
                    if (last_expr != null) {
                        if (last_expr.exprString().charAt(0) == ch) {
                            last_expr.changeCountBy(1);
                            break;
                        } else {
                            loop.addExpr(last_expr);
                            last_expr = null;
                        }
                    }
                    last_expr = parsePrimitive(ch);
                default: break;
            }
            i++;
        }
        if (last_expr != null) {
            loop.addExpr(last_expr);
        }
        return loop;
    }

    static private PrimitiveExpression parsePrimitive(char chr) {
        switch (chr) {
            case '+': return new Increment();
            case '-': return new Decrement();
            case '>': return new Forward();
            case '<': return new Backward();
            case ',': return new Input();
            case '.': return new Output();
            default: return null;
        }
    }

    public Program(List<Expression> exprs) {
        super(exprs);
    }

    public Program() {
        super();
    }

    @Override
    public void execute(Enviroment env) throws Exception {
        for (Expression expr : sequence) {
            expr.execute(env);
        }
    }
}
