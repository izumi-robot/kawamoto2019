package memory;

import java.util.ArrayList;
import java.util.ListIterator;

//import memory.MemoryIterator;

public class Memory extends ArrayList<Integer> {
    /**
     *
     */
    private static final long serialVersionUID = 1L;

    @Override
    public ListIterator<Integer> listIterator() {
        return new MemoryIterator(this);
    }

    @Override
    public ListIterator<Integer> listIterator(int index) {
        return new MemoryIterator(this, index);
    }
}
