package expressions;

import runner.Runer;

public interface Expression {
    public String toString();
    public void execute(Runner) throws Exception;
}
