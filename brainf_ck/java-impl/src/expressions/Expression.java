package expressions;

import runner.Enviroment;

public interface Expression {
    public String toString();
    public void execute(Enviroment env) throws Exception;
}
