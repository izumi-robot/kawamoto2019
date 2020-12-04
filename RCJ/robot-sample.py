import abc

class Coordinate(abc.ABC):
    def __init__(self):
        ...


class RectCoordinate(Coordinate):
    pass

class PolarCoordinate(Coordinate):
    pass
