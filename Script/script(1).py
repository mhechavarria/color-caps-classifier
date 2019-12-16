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


img = cv2.imread('/home/tomas/Desktop/JONICA/tapa_verde.png', 1)
#video = cv2.VideoCapture(0)
video = cv2.VideoCapture('/home/tomas/Desktop/JONICA/test90fps.h264', 0)
frame_width = int(video.get(3))
frame_height = int(video.get(4))
fps = video.get(cv2.CAP_PROP_FPS)
fourcc = cv2.VideoWriter_fourcc(*'XVID')
#out = cv2.VideoWriter('outpy.avi',cv2.VideoWriter_fourcc('M','J','P','G'), 1.0, (frame_width,frame_height))
out = cv2.VideoWriter('outpy.avi', fourcc, 30.0, (frame_width,frame_height))

green = np.uint8([[[0, 255, 0]]])
red = np.uint8([[[0, 0, 255]]])
violet = np.uint8([[[211, 0, 148]]])

green_hsv = cv2.cvtColor(green, cv2.COLOR_BGR2HSV)
red_hsv = cv2.cvtColor(red, cv2.COLOR_BGR2HSV)
violet_hsv = cv2.cvtColor(violet, cv2.COLOR_BGR2HSV)

green_hsv = green_hsv[0, 0, 0]
red_hsv = red_hsv[0, 0, 0]
violet_hsv = violet_hsv[0, 0, 0]

white_lower = np.array([0, 0, 100])
white_upper = np.array([179, 50, 255])

#"definitivos"
blue_lower = np.array([100, 195, 96])
blue_upper = np.array([125, 255, 255])
orange_lower = np.array([4, 189, 93])
orange_upper = np.array([16, 255, 255])
yellow_lower = np.array([25, 111, 123])
yellow_upper = np.array([41, 255, 255])
green_lower = np.array([60, 53, 56])
green_upper = np.array([80, 238, 134])
red_lower1 = np.array([0, 200, 93])
red_upper1 = np.array([7, 255, 255])
red_lower2 = np.array([169, 200, 93])
red_upper2 = np.array([180, 255, 255])

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

time.sleep(0.5)

while True:

	if pause == 0:
		ok, raw_frame = video.read()
	if raw_frame is None:
		print("fin")
		break
	
	frame_orig  = raw_frame
	actualiza_rangos()

	raw_frame_hsv = cv2.cvtColor(raw_frame, cv2.COLOR_BGR2HSV)	
	blurred = cv2.GaussianBlur(raw_frame, (15,15), 0)
	blurred = cv2.bilateralFilter(blurred, 8, 75, 75)
	blurred = cv2.cvtColor(blurred, cv2.COLOR_BGR2HSV)

	green_mask = cv2.inRange(blurred, green_lower, green_upper)
	yellow_mask = cv2.inRange(blurred, yellow_lower, yellow_upper)
	blue_mask = cv2.inRange(blurred, blue_lower, blue_upper)
	orange_mask = cv2.inRange(blurred, orange_lower, orange_upper)

	red_mask1 = cv2.inRange(blurred, red_lower1, red_upper1)
	red_mask2 = cv2.inRange(blurred, red_upper2, red_lower2)

	red_mask = cv2.bitwise_and(red_mask1, red_mask2)


	#yellow_mask_bgr = np.stack((yellow_mask, yellow_mask, yellow_mask), axis=2)
	#blue_mask_bgr = np.stack((blue_mask, blue_mask, blue_mask), axis=2)
	#orange_mask_bgr = np.stack((orange_mask, orange_mask, orange_mask), axis=2)
	#green_mask_bgr = np.stack((green_mask, green_mask, green_mask), axis=2)

	#cv2.imshow("Raw Frame", np.hstack([raw_frame, green_mask_bgr]))
	#cv2.imshow("Blurred", cv2.cvtColor(blurred, cv2.COLOR_HSV2BGR))

	cv2.imshow("Green mask", green_mask)
	cv2.imshow("Yellow mask", yellow_mask)
	cv2.imshow("Red mask", red_mask)
	cv2.imshow("Orange mask", orange_mask)
	cv2.imshow("Raw frame", raw_frame)
	k = cv2.waitKey(10) & 0xFF
	if k == ord('q'):
		break
	if k == ord('p'):
		pause = not pause
		print(pause)
	#out.write(frame)

video.release()
out.release()
cv2.destroyAllWindows()

