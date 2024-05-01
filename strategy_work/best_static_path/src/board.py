"""Definition of the Board data abstract type."""
import numpy as np
import table
from numpy.typing import NDArray


class Board():
    """Table modelisation as a discrete grid in which the robot can move."""

    def __init__(self, resolution: int):
        """Initiate the board according to a chosen resolution.

        Parameters
        ----------
        resolution: the number of graduations to divide the height of the table
        """
        self.__shape = (table.scale(table.WIDTH, resolution), resolution)
        self.__obstacles: NDArray[np.bool_] = np.zeros(self.__shape, np.bool_)
        self.__robot_radius = table.scale(table.ROBOT_RADIUS, resolution)
        self.__pot_radius = table.scale(table.POT_RADIUS, resolution)
