import enum


class Command(enum.Enum):
    add = '+'
    sub = '-'

    shift_r = '>'
    shift_l = '<'

    char_in  = ','
    char_out = '.'

    nest_in  = '['
    nest_out = ']'


class Machine(list):
    __slots__ = ("_ptr", "_mem_len")

    def __init__(self, ptr=0, mem_len=1024):
        self._ptr = ptr
        self._mem_len = mem_len

    @property
    def val(self):
        return self[self._ptr]

    @property
    def ptr(self):
        return self._ptr

    @property
    def mem_len(self):
        return self._mem_len

    def inc_val(self):
        self[self._ptr] += 1
        return self[self._ptr]

    def dec_val(self):
        self[self._ptr] -= 1
        return self[self._ptr]

    def inc_ptt(self):
        self._ptr += 1
        return self._ptr

    def dec_ptr(self):
        self._ptr -= 1
        return self._ptr
