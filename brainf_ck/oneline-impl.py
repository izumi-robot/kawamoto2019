(lambda fs: [f() for f in fs])((lambda file, parse: parse(parse, [file.read(), file.close()][0], {"count":0, "start":0}))(open("helloworld.bf", "r", encoding="utf-8"), (lambda cmds, make_loop: (lambda parse, source, nest: list(filter(callable, (nest.__setitem__("start", nest["start"] if nest["count"] else i) or nest.__setitem__("count", nest["count"] + 1) if c == '[' else [nest.__setitem__("count", nest["count"] - 1), nest["count"] == 0 and make_loop(parse(parse, source[nest["start"]+1:i], {"count":0, "start":0}))][1] if c == ']' else nest["count"] == 0 and cmds.get(c, bool) for i, c in enumerate(source))))))(*(lambda env: ({'+': (lambda : env["memory"].__setitem__(env["index"], env["memory"][env["index"]] + 1)), '-': (lambda : env["memory"].__setitem__(env["index"], env["memory"][env["index"]] - 1)), '>': (lambda : (env.__setitem__("index", env["index"] + 1) or len(env["memory"]) <= env["index"]) and env["memory"].append(0)), '<': (lambda : env.__setitem__("index", max(0, env["index"] - 1))), ',': (lambda : env["memory"].__setitem__(env["index"], ord(next(env["input"])))), '.': (lambda : print(chr(env["memory"][env["index"]]), end=""))}, (lambda fs: (lambda : [f() for _ in iter((lambda : env["memory"][env["index"]] <= 0), True) for f in fs]))))({"memory": [0], "index": 0, "input": iter("some string...")}))))

"""雛形
env = {
    "memory": [0],
    "index": 0,
    "input": iter("some string...")
}

cmds = {
    '+': (lambda : env["memory"].__setitem__(env["index"], env["memory"][env["index"]] + 1)),
    '-': (lambda : env["memory"].__setitem__(env["index"], env["memory"][env["index"]] - 1)),
    '>': (lambda : (env.__setitem__("index", env["index"] + 1) or len(env["memory"]) <= env["index"]) and env["memory"].append(0)),
    '<': (lambda : env.__setitem__("index", max(0, env["index"] - 1))),
    ',': (lambda : env["memory"].__setitem__(env["index"], ord(next(env["input"])))),
    '.': (lambda : print(chr(env["memory"][env["index"]]), end=""))
}

make_loop = (lambda fs:
    (lambda : [f() for _ in iter((lambda : env["memory"][env["index"]] <= 0), True) for f in fs])
)

parse = (lambda source, nest:
    list(filter(callable, (
        nest.__setitem__("start", nest["start"] if nest["count"] else i) or nest.__setitem__("count", nest["count"] + 1) if c == '['
        else [nest.__setitem__("count", nest["count"] - 1), nest["count"] == 0 and make_loop(parse(source[nest["start"]+1:i], {"count":0, "start":0}))][1] if c == ']'
        else nest["count"] == 0 and cmds.get(c, bool)
        for i, c in enumerate(source)
    )))
)

res = [
    f() for f in parse((lambda f:
        [f.read(), f.close()][0]
    )(open("helloworld.bf", "r", encoding="utf-8")),
    {"count":0, "start":0})
]
"""
"""インデントありのワンライン
(lambda fs: [f() for f in fs])((lambda file, parse:
    parse(parse, [file.read(), file.close()][0], {"count":0, "start":0})
)(open("helloworld.bf", "r", encoding="utf-8"), (lambda cmds, make_loop:
    (lambda parse, source, nest:
    list(filter(callable, (
        nest.__setitem__("start", nest["start"] if nest["count"] else i) or nest.__setitem__("count", nest["count"] + 1) if c == '['
        else [nest.__setitem__("count", nest["count"] - 1), nest["count"] == 0 and make_loop(parse(parse, source[nest["start"]+1:i], {"count":0, "start":0}))][1] if c == ']'
        else nest["count"] == 0 and cmds.get(c, bool)
        for i, c in enumerate(source)
    )))
)
)(
    *(lambda env: ({
        '+': (lambda : env["memory"].__setitem__(env["index"], env["memory"][env["index"]] + 1)),
        '-': (lambda : env["memory"].__setitem__(env["index"], env["memory"][env["index"]] - 1)),
        '>': (lambda : (env.__setitem__("index", env["index"] + 1) or len(env["memory"]) <= env["index"]) and env["memory"].append(0)),
        '<': (lambda : env.__setitem__("index", max(0, env["index"] - 1))),
        ',': (lambda : env["memory"].__setitem__(env["index"], ord(next(env["input"])))),
        '.': (lambda : print(chr(env["memory"][env["index"]]), end=""))
    }, (lambda fs:
        (lambda : [f() for _ in iter((lambda : env["memory"][env["index"]] <= 0), True) for f in fs])
    )))({
        "memory": [0],
        "index": 0,
        "input": iter("some string...")
    })
)))
"""
