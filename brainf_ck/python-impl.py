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
    __slots__ = ("_ptr",)

    @property
    def val(self):
        return self[self._ptr]

    @val.setter
    def val(self, nv):
        
