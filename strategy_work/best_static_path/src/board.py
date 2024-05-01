"""Definition of the Board data abstract type."""
import matplotlib.pyplot as plt
import numpy as np
from numpy.typing import NDArray

import table


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

    def plot_board(self):
        """Plot the board with the obstacles."""
        X = np.linspace(0, table.WIDTH, self.__shape[0])
        Y = np.linspace(0, table.HEIGHT, self.__shape[1])
        plt.figure()
        plt.pcolormesh(X, Y, self.__obstacles.T, shading='auto')
        plt.xlabel('x (cm)')
        plt.ylabel('y (cm)')
        plt.show()


if __name__ == "__main__":
    b = Board(500)
    b.plot_board()
