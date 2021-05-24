package memory;

import java.util.ArrayList;
import java.util.ListIterator;

public class Memory extends ArrayList<Integer> {
    private static final long serialVersionUID = 1L;

    public MemoryIterator memoryIterator() {
        return new MemoryIterator(this);
    }

    public MemoryIterator memoryIterator(int index) {
        return new MemoryIterator(this, index);
    }

    @Override
    public ListIterator<Integer> listIterator() {
        return memoryIterator();
    }

    @Override
    public ListIterator<Integer> listIterator(int index) {
        return memoryIterator(index);
    }
}
