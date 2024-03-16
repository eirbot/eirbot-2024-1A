import cv2 as cv
from cv2 import aruco
import numpy as np

#a list of aruco tag to compare with => get aruco tag id
dict_aruco = aruco.getPredefinedDictionary(cv.aruco.DICT_4X4_250)
parameters =  aruco.DetectorParameters()
detector = aruco.ArucoDetector(dict_aruco, parameters)


window_name = "background"
font = cv.FONT_HERSHEY_SIMPLEX
fontScale = 0.5
color = (0, 0, 255)
#in px
thickness = 4
   
class MarkSearch :
    def __init__(self, cameraID):
        self.cap = cv.VideoCapture(cameraID)

    def get_markID(self):
        
        #check ret if you want to be sure to have source from camera
        ret, frame = self.cap.read()

        #corners : list     each coordinate of aruco tag corner
        corners, ids, rejectedImgPoints = detector.detectMarkers(frame)

        list_ids = np.ravel(ids)
        aruco_tag_found = []
        image = frame

        for num_id in list_ids:
            if num_id != None:
                index = np.where(ids == num_id)[0][0]

                #get coordinates of interesting points
                cornerUL = corners[index][0][0]   #corner Up left
                cornerUR = corners[index][0][1]   #corner Up right
                cornerBR = corners[index][0][2]   #corner Bottom right
                cornerBL = corners[index][0][3]   #corner Bottom left
                center = [ int((cornerUL[0]+cornerBR[0])//2) , int((cornerUL[1]+cornerBR[1])//2) ]  #center of aruco tag

                aruco_tag_found.append((num_id, center))

                #display position of 2 corners
                #cv.putText(image, 'c1', (int(cornerUL[0]), int(cornerUL[1])), font, fontScale, color, thickness, cv.LINE_AA)
                #cv.putText(image, 'c2', (int(cornerUR[0]), int(cornerUR[1])), font, fontScale, color, thickness, cv.LINE_AA) 
           
                #cv.putText(image, 'SP',end_arrow, font , fontScale, color, thickness, cv.LINE_AA)

                #aruco tag id 
                #cv.putText(image, str(num_id), center, font, fontScale, color, thickness, cv.LINE_AA)

                end_arrow = [int((cornerUL[0] + cornerUR[0])/2) ,int((cornerUL[1] + cornerUR[1])/2)]
                image = cv.arrowedLine(image, center,  end_arrow, color, thickness) 

            cv.imshow("video",  image)
            cv.setWindowProperty("video", cv.WND_PROP_TOPMOST, 1)

        return aruco_tag_found



if __name__ == "__main__" :
    cameraID = 0   #camera principale
    cam0_aruco_search = MarkSearch(cameraID)

    while True:
        cam0_aruco_search.get_markID()

        #possibility of implementing an other exit condition 
        if cv.waitKey(25) & 0xFF == ord('q'):
            cam0_aruco_search.cap.release()
        
        

