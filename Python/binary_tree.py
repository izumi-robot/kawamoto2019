def same_type(x, y):
    return isinstance(x, type(y))


class Node:
    def __init__(self, key, value, left=None, right=None):
        assert hasattr(key, "__lt__")
        f = (lambda x: isinstance(x, Node) or x is None)
        assert f(left)
        assert f(right)
        self._key = key
        self.value = value
        self._left = left
        self._right = right

    @property
    def key(self):
        return self._key

    @key.setter
    def key(self, n_key):
        assert same_type(n_key, self._key)
        self._key = n_key
    
    @property
    def left(self):
        return self._left
    
    @left.setter
    def left(self, n_left):
        assert isinstance(n_left, Node)
        assert same_type(n_left.key, self._key)
        self._left = n_left
    
    @property
    def right(self):
        return self._right
    
    @right.setter
    def right(self, n_right):
        assert isinstance(n_right, Node)
        assert same_type(n_right.key, self._right)


class Tree:
    def __init__(self, **kwargs):
        self._root = None
        for k, v in kwargs.items():
            self[k] = v
    
    def __getitem__(self, key):
        if self._root is None:
            raise KeyError('No key matched')
        assert same_type(key, self._root.key)
        p = self._root
