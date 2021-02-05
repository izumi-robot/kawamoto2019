import sys, io
import enum
import typing as tp


class Command(enum.Enum):
    add = '+'
    sub = '-'

    shift_r = '>'
    shift_l = '<'

    char_in  = ','
    char_out = '.'

    nest_in  = '['
    nest_out = ']'


def parse_program(source):
    result = list()
    nest_count, nest_in_index = 0, 0
    for i, cmd_chr in enumerate(source):
        try:
            cmd = Command(cmd_chr)
        except ValueError:
            continue
        if cmd is Command.nest_in:
            nest_in_index = nest_in_index if nest_count else i
            nest_count += 1
        elif cmd is Command.nest_out:
            if nest_count == 1:
                new_source = source[nest_in_index+1 : i]
                result.append(parse_program(new_source))
            nest_count -= 1
        else:
            nest_count or result.append(cmd)
    return result


class Machine(list):

    __slots__ = ("_ptr", "_mem_len")

    def __init__(self, ptr=0, mem_len=1024):
        super().__init__([0] * mem_len)
        self._ptr = ptr
        self._mem_len = mem_len

    @property
    def val(self):
        return self[self._ptr]

    @val.setter
    def val(self, nvalue):
        assert isinstance(nvalue, int), "val must be int"
        self[self._ptr] = nvalue

    @property
    def ptr(self):
        return self._ptr

    @ptr.getter
    def ptr(self, nptr):
        assert isinstance(nptr, int), "ptr must be int"
        self._ptr = nptr

    @property
    def mem_len(self):
        return self._mem_len

    def inc_val(self):
        self[self._ptr] += 1
        return self[self._ptr]

    def dec_val(self):
        self[self._ptr] -= 1
        return self[self._ptr]

    def inc_ptr(self):
        self._ptr += 1
        if self._ptr >= self._mem_len:
            for _ in range(self._ptr - self._mem_len + 1):
                self.append(0)
            self._mem_len = self._ptr
        return self._ptr

    def dec_ptr(self):
        self._ptr -= 1
        return self._ptr


class Executor(Machine):

    __slots__ = ("_program", "_stdin", "_stdout")

    def __init__(self):
        super().__init__()
        self._program = None
        self._stdin  = None
        self._stdout = None

    def __call__(self, source, stdin=sys.stdin, stdout=sys.stdout):
        self._program = source
        if isinstance(source, str):
            self._program = parse_program(source)
        self._stdin  = stdin
        self._stdout = stdout
        self._execute(self._program)
        self._stdout.write('\n')

    def char_in(self):
        assert isinstance(self._stdin, io.TextIOBase), "stdin must be an instance of io.TextIOBase"
        assert self._stdin.readable(), "stdin must be readable"
        char = self._stdin.read(1) or '\0'
        self.val = ord(char)

    def char_out(self):
        assert isinstance(self._stdout, io.TextIOBase), "stdout must be an instance of io.TextIOBase"
        assert self._stdout.writable(), "stdout must be writable"
        char = chr(self.val)
        self._stdout.write(char)

    def _eval_cmd(self, cmd):
        assert isinstance(cmd, Command)
        if   cmd is Command.add:
            self.inc_val()
        elif cmd is Command.sub:
            self.dec_val()
        elif cmd is Command.shift_r:
            self.inc_ptr()
        elif cmd is Command.shift_l:
            self.dec_ptr()
        elif cmd is Command.char_in:
            self.char_in()
        elif cmd is Command.char_out:
            self.char_out()
        else:
            raise ValueError(f"unsupported command: {cmd}")

    def _execute(self, program):
        if isinstance(program, Command):
            return self._eval_cmd(program)
        for elem in program:
            if isinstance(elem, list):
                while self.val:
                    self._execute(elem)
                continue
            self._eval_cmd(elem)


if __name__ == "__main__":
    executor = Executor()
    _, sourcefile_name, *filenames = sys.argv
    with open(sourcefile_name, "r", encoding="utf-8") as f:
        executor(f.read())
