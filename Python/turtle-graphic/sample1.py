from turtle import *

if __name__ == "__main__":
    color("red", "yellow")
    begin_fill()
    while True:
        forward(200)
        left(170)
        if abs(pos()) < 1:
            break
    end_fill()
    done()
