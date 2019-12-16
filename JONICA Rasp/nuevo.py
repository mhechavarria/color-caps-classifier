import cv2
import numpy as np
import time

def nothing(x):
	pass

def actualiza_rangos():
	global hBlueLow
	global sBlueLow
	global vBlueLow
	global hBlueUpper
	global sBlueUpper
	global vBlueUpper
	global red_lower1
	global red_upper1
	global red_lower2
	global red_upper2
	hLow1 = cv2.getTrackbarPos('H low1','Trackbar')
	hLow2 = cv2.getTrackbarPos('H low2', 'Trackbar')
	sLow = cv2.getTrackbarPos('S low','Trackbar')
	vLow = cv2.getTrackbarPos('V low','Trackbar')
	hUpper1 = cv2.getTrackbarPos('H high1','Trackbar')
	hUpper2 = cv2.getTrackbarPos('H high2', 'Trackbar')
	sUpper = cv2.getTrackbarPos('S high','Trackbar')
	vUpper = cv2.getTrackbarPos('V high','Trackbar')
	red_lower1 = np.array([hLow1, sLow, vLow])
	red_upper1 = np.array([hUpper1, sUpper, vUpper])
	red_lower2 = np.array([hLow2, sLow, vLow])
	red_upper2 = np.array([hUpper2, sUpper, vUpper])

#def muestra_colores():
	#blue


img = cv2.imread('/home/tomas/Desktop/JONICA/tapa_roja.png', 1)

red = np.uint8([[[0, 0, 255]]])
red_hsv = cv2.cvtColor(red, cv2.COLOR_BGR2HSV)
red_hsv = red_hsv[0, 0, 0]

red_lower1 = np.array([red_hsv, 160, 160])
red_upper1 = np.array([red_hsv + 20, 255, 255])
red_lower2 = np.array([red_hsv, 160, 160])
red_upper2 = np.array([red_hsv + 20, 255, 255])

cv2.namedWindow('Trackbar')
cv2.createTrackbar('H low1','Trackbar',	red_lower1[0],180,nothing)
cv2.createTrackbar('H low2','Trackbar',	red_lower2[0],180,nothing)
cv2.createTrackbar('S low','Trackbar',	red_lower1[1],255,nothing)
cv2.createTrackbar('V low','Trackbar',	red_lower1[2],255,nothing)
cv2.createTrackbar('H high1','Trackbar', red_upper1[0],180,nothing)
cv2.createTrackbar('H high2','Trackbar', red_upper2[0],180,nothing)
cv2.createTrackbar('S high','Trackbar',	red_upper1[1],255,nothing)
cv2.createTrackbar('V high','Trackbar',	red_upper1[2],255,nothing)

pause = 0
#print(cv2.selectROI("Imagen", img, showCrosshair=True))
img = img[124: 700, 100:700, :]
while True:

	actualiza_rangos()
	raw_frame = img
	raw_frame_hsv = cv2.cvtColor(raw_frame, cv2.COLOR_BGR2HSV)
	blurred = cv2.GaussianBlur(raw_frame, (15,15), 0)
	blurred = cv2.bilateralFilter(blurred, 8, 75, 75)
	blurred = cv2.cvtColor(blurred, cv2.COLOR_BGR2HSV)

	red_mask1 = cv2.inRange(blurred, red_lower1, red_upper1)
	red_mask2 = cv2.inRange(blurred, red_lower2, red_upper2)

	red_mask = cv2.bitwise_or(red_mask1, red_mask2)
	cv2.imshow("Red mask1", red_mask1)
	cv2.imshow("Red mask2", red_mask2)
	cv2.imshow("Red mask", red_mask)
	cv2.imshow("Raw frame", img)

	k = cv2.waitKey(10) & 0xFF
	if k == ord('q'):
		break
	if k == ord('p'):
		pause = not pause
		print(pause)

cv2.destroyAllWindows()

