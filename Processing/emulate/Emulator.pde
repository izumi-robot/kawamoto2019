abstract class Emulator {
    protected Machine _machine;

    public Emulator(Machine machine) {
        _machine = machine;
    }

    public Emulator() {
        _machine = new Machine();
    }

    abstract public void setup();
    abstract public void draw();
    abstract public void keyPressed();
}