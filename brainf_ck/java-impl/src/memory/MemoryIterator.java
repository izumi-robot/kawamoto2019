package memory;

import java.util.List;
import java.util.ListIterator;

public class MemoryIterator implements ListIterator<Integer> {

    protected List<Integer> list;
    protected int index;

    public MemoryIterator(List<Integer> list, int index) {
        this.list = list;
        this.index = index;
    }

    public MemoryIterator(List<Integer> list) { this(list, 0); }

    @Override
    public boolean hasNext() {
        return index < list.size();
    }

    @Override
    public Integer next() {
        if (!hasNext()) { list.add(0); }
        return list.get(index++);
    }

    @Override
    public boolean hasPrevious() {
        return index > 0;
    }

    @Override
    public Integer previous() {
        if (!hasPrevious()) { return null; }
        return list.get(--index);
    }

    @Override
    public int nextIndex() {
        return index;
    }

    @Override
    public int previousIndex() {
        if (!hasPrevious()) { return -1; }
        return index - 1;
    }

    @Override
    public void remove() {
        list.remove(index);
    }

    @Override
    public void set(Integer e) {
        list.set(index, e);
    }

    @Override
    public void add(Integer e) {
        list.add(index, e);
    }

}