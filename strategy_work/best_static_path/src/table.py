"""Data (in mm) about shapes of the table and other components."""

HEIGHT = 2000
WIDTH = 3000
ROBOT_RADIUS = 270//2
POT_RADIUS = 100


def scale(value: int, resolution: int) -> int:
    """Rescale a value according to the chosen resolution.

    Parameters
    ----------
    value: a length in mm
    resolution: the number of pixel to represent the height of the table
    """
    return int(resolution*value/HEIGHT)
