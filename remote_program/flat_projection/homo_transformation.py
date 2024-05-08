import numpy as np
import matplotlib.pyplot as plt

from skimage import transform
from skimage.io import imread, imshow
import cv2 as cv


def quickly_find_by_hand_corner_coordinate():
    img= plt.imread('images/homo.jpg') 
    img = cv.rotate(img, cv.ROTATE_90_CLOCKWISE)
    plt.imshow(img)
    plt.show()

def homo_image(image, src):
    book = imread(image)
    book = cv.rotate(book, cv.ROTATE_90_CLOCKWISE)
    imshow(book)

    # Convert the image from BGR to RGB for proper visualization with Matplotlib
    book = cv.cvtColor(book, cv.COLOR_BGR2RGB)

    # Define the source points
    src = np.array(src)
    src = src.reshape(4,2)
    plt.scatter(src[:, 0], src[:, 1], color='red', marker='o')


    #possibility of changing those coordinates if you want different size of final object
    dst = np.array([0, 0,
                    1500, 0,
                    0, 2000,
                    1500, 2000,
    ]).reshape((4, 2))
    tform = transform.estimate_transform('projective', src, dst)
    # Plot the image

    tf_img = transform.warp(book, tform.inverse)
    fig, ax = plt.subplots()

    tf_img  = tf_img[0 : 2000, 0 : 1500]

    ax.imshow(tf_img)

    _ = ax.set_title('projective transformation')

    # Show the image with the plotted points
    plt.show()

#if you use "images/homo.jpg" : coordinates of corners are [(699,1587),(2181,1619),(283,3596),(2659,3546)]
#order of coordinates : [up-left, up-right, bottom-left, bottom-right]
#homo_image("images/homo.jpg", [(699,1587),(2181,1619),(283,3596),(2659,3546)])