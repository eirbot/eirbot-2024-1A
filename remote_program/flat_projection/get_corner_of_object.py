import numpy as np
import cv2 as cv
from matplotlib import pyplot as plt
from skimage import transform
from skimage.io import imread, imshow
from homo_transformation import homo_image


MIN_MATCH_COUNT = 10
img1= cv.imread('images/homoclean.jpg', cv.IMREAD_GRAYSCALE)          # queryImage
img2 = cv.imread('images/book_to_point.jpg', cv.IMREAD_GRAYSCALE)   # trained Image

# Initiate SIFT detector
sift = cv.SIFT_create()

# find the keypoints and descriptors with SIFT
kp1, des1 = sift.detectAndCompute(img1,None)
kp2, des2 = sift.detectAndCompute(img2,None)
FLANN_INDEX_KDTREE = 1



index_params = dict(algorithm = FLANN_INDEX_KDTREE, trees = 5)
search_params = dict(checks = 50)
flann = cv.FlannBasedMatcher(index_params, search_params)
matches = flann.knnMatch(des1,des2,k=2)
# store all the good matches as per Lowe's ratio test.
good = []
for m,n in matches:
    if m.distance < 0.7*n.distance:
        good.append(m)


if len(good)>MIN_MATCH_COUNT:

    src_pts = np.float32([ kp1[m.queryIdx].pt for m in good ]).reshape(-1,1,2)
    dst_pts = np.float32([ kp2[m.trainIdx].pt for m in good ]).reshape(-1,1,2)
    M, mask = cv.findHomography(src_pts, dst_pts, cv.RANSAC,5.0)
    matchesMask = mask.ravel().tolist()
    h,w = img1.shape
    pts = np.float32([ [0,0],[0,h-1],[w-1,h-1],[w-1,0] ]).reshape(-1,1,2)
    dst = cv.perspectiveTransform(pts,M)
    img2 = cv.polylines(img2,[np.int32(dst)],True,(30,92,255),3, cv.LINE_AA)

else:
    print( "Not enough matches are found - {}/{}".format(len(good), MIN_MATCH_COUNT) )
    matchesMask = None

draw_params = dict(matchColor = (0,255,0), # draw matches in green color
                   singlePointColor = None,
                   matchesMask = matchesMask, # draw only inliers
                   flags = 2)


new_src = np.array([elem[0] for elem in dst])
new_src = sorted(new_src,key=lambda y: y[1])

pts_haut = sorted(new_src[:2], key=lambda x: x[0])
pts_bas = sorted(new_src[2:],key=lambda x: x[0])
new_src = [pts_haut[0], pts_haut[1], pts_bas[0], pts_bas[1]]

homo_image('images/book_to_point.jpg', new_src)
