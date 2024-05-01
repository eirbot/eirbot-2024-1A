"""Data (in mm) about shapes of the table and other components."""

HEIGHT = 2000
WIDTH = 3000
ROBOT_SHAPE = (306, 192.5)  # robot 2D body without the arm
ROBOT_RADIUS = ROBOT_SHAPE[0]

INITIAL_POSITION_BLUE_TEAM = (3000-300, 750)

SOLAR_PANELS: list[tuple[int, int]] = [
        (275, 2050), (500, 2050), (725, 2050),
        (1275, 2050), (1500, 2050), (1725, 2050),
        (2275, 2050), (2500, 2050), (2725, 2050)
        ]
POT_RADIUS = 55
POT_SPOT_RADIUS = 125
POT_SPOTS: list[tuple[int, int]] = [
        (1000, 1300), (1000, 700), (1500, 1500),
        (1500, 500), (2000, 1300), (2000, 700),
        ]


def scale(value: int, resolution: int) -> int:
    """Rescale a value according to the chosen resolution.

    Parameters
    ----------
    value: a length in mm
    resolution: the number of pixel to represent the height of the table
    """
    return int(resolution*value/HEIGHT)
