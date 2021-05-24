package app;

import java.io.BufferedReader;
import java.io.File;
import java.io.FileReader;

import expressions.Program;
import runner.Runner;

public class App {
    public static void main(String[] args) throws Exception {
        String script = "";
        {
            File input_file = new File(args[0]);
            BufferedReader reader = new BufferedReader(new FileReader(input_file));
            for (String str = reader.readLine(); str != null; str = reader.readLine()) {
                script += str;
            }
            reader.close();
        }

        Runner runner = new Runner();
        Program program = Program.parse(script);
        //System.out.println(program.toString());
        runner.accept(program);
    }
}
