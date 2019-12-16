from picamera.array import PiRGBArray
from picamera import PiCamera
import numpy as np
import time
import cv2
import serial

ser = serial.Serial(
               port='/dev/ttyAMA0',
               baudrate = 115200,
               parity=serial.PARITY_NONE,
               stopbits=serial.STOPBITS_ONE,
               bytesize=serial.EIGHTBITS,
               timeout=1
           )
#ser = serial.Serial ("/dev/ttyAMA0")    #Open named port 
#ser.baudrate = 115200                     #Set baud rate to 115200
#data = ser.read(10)                     #Read ten characters from serial port to data
#ser.write(data)                         #Send back the received data

# initialize the camera and grab a reference to the raw camera capture
camera = PiCamera()
camera.resolution = (640, 480)
camera.framerate = 24
camera.brightness = 51
camera.contrast = -15
camera.saturation = 15
camera.sharpness = -100
camera.ISO = 500
rawCapture = PiRGBArray(camera, size=(640, 480))

def nothing(x):
	pass
	
def actualiza_rangos():
	global hLow
	global sLow
	global vLow
	global hUpper
	global sUpper
	global vUpper
	global gray_lower
	global gray_upper
	'''
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
	'''
	hLow = cv2.getTrackbarPos('H low','Trackbar')
	sLow = cv2.getTrackbarPos('S low','Trackbar')
	vLow = cv2.getTrackbarPos('V low','Trackbar')
	hUpper = cv2.getTrackbarPos('H high','Trackbar')
	sUpper = cv2.getTrackbarPos('S high','Trackbar')
	vUpper = cv2.getTrackbarPos('V high','Trackbar')
	gray_lower = np.array([hLow, sLow, vLow])
	gray_upper = np.array([hUpper, sUpper, vUpper])
	
        contrast = cv2.getTrackbarPos('Contrast','Trackbar')
        bright = cv2.getTrackbarPos('Bright','Trackbar')
        sat = cv2.getTrackbarPos('Sat','Trackbar')
        camera.saturation = sat
        camera.brightness = bright
        #camera.contrast = contrast
        

gray_lower = np.array([0, 30, 109])
gray_upper = np.array([179, 80, 203])

#"definitivos"
blue_lower = np.array([100, 180, 45])
blue_upper = np.array([125, 255, 255])
orange_lower = np.array([6, 150, 93])
orange_upper = np.array([16, 255, 255])
yellow_lower = np.array([25, 111, 123])
yellow_upper = np.array([41, 255, 255])
green_lower = np.array([54, 153, 55])
green_upper = np.array([72, 255, 215])
red_lower1 = np.array([0, 110, 93])
red_upper1 = np.array([6, 255, 255])
red_lower2 = np.array([169, 90, 93])
red_upper2 = np.array([180, 255, 255])

cv2.namedWindow('Trackbar')
'''
cv2.createTrackbar('H low1','Trackbar',	red_lower1[0],180,nothing)
cv2.createTrackbar('H low2','Trackbar',	red_lower2[0],180,nothing)
cv2.createTrackbar('S low','Trackbar',	red_lower1[1],255,nothing)
cv2.createTrackbar('V low','Trackbar',	red_lower1[2],255,nothing)
cv2.createTrackbar('H high1','Trackbar', red_upper1[0],180,nothing)
cv2.createTrackbar('H high2','Trackbar', red_upper2[0],180,nothing)
cv2.createTrackbar('S high','Trackbar',	red_upper1[1],255,nothing)
cv2.createTrackbar('V high','Trackbar',	red_upper1[2],255,nothing)
'''
cv2.createTrackbar('H low','Trackbar',	gray_lower[0],180,nothing)
cv2.createTrackbar('S low','Trackbar',	gray_lower[1],255,nothing)
cv2.createTrackbar('V low','Trackbar',	gray_lower[2],255,nothing)
cv2.createTrackbar('H high','Trackbar', gray_upper[0],180,nothing)
cv2.createTrackbar('S high','Trackbar',	gray_upper[1],255,nothing)
cv2.createTrackbar('V high','Trackbar',	gray_upper[2],255,nothing)
cv2.createTrackbar('Sat','Trackbar',	50,100,nothing)
cv2.createTrackbar('Bright','Trackbar',	50,100,nothing)
cv2.createTrackbar('Contrast','Trackbar',	13,100,nothing)

pause = 0
init = 1
cap = "Undefined"
cap_yellow = 0
cap_red = 0
cap_blue = 0
cap_green = 0
cap_orange = 0
cap_gray = 0
kernel = np.ones((9, 9), np.uint8)
time.sleep(2)

image = np.empty((640 * 480 * 3,), dtype=np.uint8)
camera.capture(image, 'bgr')
#image = image.reshape((240, 320, 3))
#if init == 1:
r = cv2.selectROI(image)
#init = 0
#print("ROI")
gray_mask = np.empty((int(r[3]), int(r[2])), np.uint8) #creo que esto no se usa
#print(gray_mask.shape)
#print(raw_frame.shape)
raw_frame = image[int(r[1]):int(r[1]+r[3]), int(r[0]):int(r[0]+r[2])]
raw_frame_bgr = image
received = ord('e')

while True:
	for i in range(1,5):
		try:
			ser.write(ord('p'))	#aviso que gire las paletas y espera respuesta
			received = ser.readline()	
			print(state)
			if received != ord('e'):
				break
		except:
			pass
		time.sleep(0.01)
		
	if received == ord('k'):	#si recibi que termino de girar paletas:
		received = ord('e')		#"vacio" la variable de recepcion
		time.sleep(0.1)			#espero para sacar la foto
		
		image = np.empty((640 * 480 * 3,), dtype=np.uint8)
		camera.capture(image, 'bgr')
		raw_frame = image[int(r[1]):int(r[1]+r[3]), int(r[0]):int(r[0]+r[2])]
		
		####### DETECCION DE COLOR #######
		#Blue caps:
        _, blue_contours, _ = cv2.findContours(blue_mask, cv2.RETR_TREE, cv2.CHAIN_APPROX_SIMPLE)
        if len(blue_contours) != 0:
            for i in range(len(blue_contours)):
                if cv2.contourArea(blue_contours[i]) >= 10000:
                    print(cv2.contourArea(blue_contours[i]))
                    cap_blue = 1
                    break
                
        #yellow caps:
        _, yellow_contours, _ = cv2.findContours(yellow_mask, cv2.RETR_TREE, cv2.CHAIN_APPROX_SIMPLE)
        if len(yellow_contours) != 0:
            for i in range(len(yellow_contours)):
                if cv2.contourArea(yellow_contours[i]) >= 10000:
                    print(cv2.contourArea(yellow_contours[i]))
                    cap_yellow = 1
                    break
                         
        #red caps:
        _, red_contours, _ = cv2.findContours(red_mask, cv2.RETR_TREE, cv2.CHAIN_APPROX_SIMPLE)
        if len(red_contours) != 0:
            for i in range(len(red_contours)):
                if cv2.contourArea(red_contours[i]) >= 10000:
                    print(cv2.contourArea(red_contours[i]))
                    cap_red = 1
                    break
                
        #green caps:
        _, green_contours, _ = cv2.findContours(green_mask, cv2.RETR_TREE, cv2.CHAIN_APPROX_SIMPLE)
        if len(green_contours) != 0:
            for i in range(len(green_contours)):
                if cv2.contourArea(green_contours[i]) >= 10000:
                    print(cv2.contourArea(green_contours[i]))
                    cap_green = 1
                    break
        
        #orange caps:
        _, orange_contours, _ = cv2.findContours(orange_mask, cv2.RETR_TREE, cv2.CHAIN_APPROX_SIMPLE)
        if len(orange_contours) != 0:
            for i in range(len(orange_contours)):
                if cv2.contourArea(orange_contours[i]) >= 10000:
                    print(cv2.contourArea(orange_contours[i]))
                    cap_orange = 1
                break
        #gray caps:
        _, gray_contours, _ = cv2.findContours(gray_mask, cv2.RETR_TREE, cv2.CHAIN_APPROX_SIMPLE)
        if len(gray_contours) != 0:
            for i in range(len(gray_contours)):
                if cv2.contourArea(gray_contours[i]) >= 10000:
                    print(cv2.contourArea(gray_contours[i]))
                    cap_gray = 1
                    break
        
        if cap_yellow == 1 and cap_red == 0 and cap_green == 0 and cap_orange == 0 and cap_blue == 0 and cap_gray == 0:
            cap = ord('y')
        elif cap_yellow == 0 and cap_red == 1 and cap_green == 0 and cap_orange == 0 and cap_blue == 0 and cap_gray == 0:
            cap = ord('r')
        elif cap_yellow == 0 and cap_red == 0 and cap_green == 1 and cap_orange == 0 and cap_blue == 0 and cap_gray == 0:
            cap = ord('v')
        elif cap_yellow == 0 and cap_red == 0 and cap_green == 0 and cap_orange == 1 and cap_blue == 0 and cap_gray == 0:
            cap = ord('n')
        elif cap_yellow == 0 and cap_red == 0 and cap_green == 0 and cap_orange == 0 and cap_blue == 1 and cap_gray == 0:
            cap = ord('a')
        elif cap_yellow == 0 and cap_red == 0 and cap_green == 0 and cap_orange == 0 and cap_blue == 0 and cap_gray == 1:
            cap = ord('g')
        else:
            cap = ord('u')
		
		if cap != ord('u'):	
			for i in range(1,5):	#envio el color y espero por la respuesta
				try:
					ser.write(cap.encode())
					time.sleep(0.02)
					received = ser.readline()
					print(received)
					if received != ord('e'):
						break
				except:
					pass
				#time.sleep(0.01)
		if received == ord('o'): 
		
			
			
		
		
	


for frame in camera.capture_continuous(rawCapture, format="bgr", use_video_port=True):

    if pause == 0:
        raw_frame = frame.array
    
    if init == 1:
        r = cv2.selectROI(raw_frame)
        init = 0
        print("ROI")
        gray_mask = np.empty((int(r[3]), int(r[2])), np.uint8)
        print(gray_mask.shape)
        print(raw_frame.shape)
        #cv2.destroyWindow("ROI Selector")
    # Crop image
    raw_frame = raw_frame[int(r[1]):int(r[1]+r[3]), int(r[0]):int(r[0]+r[2])]
    raw_frame_bgr = raw_frame
    actualiza_rangos()

    raw_frame_hsv = cv2.cvtColor(raw_frame, cv2.COLOR_BGR2HSV)	
    blurred = cv2.GaussianBlur(raw_frame, (15,15), 0)
    blurred = cv2.bilateralFilter(blurred, 8, 150, 150)
    blurred = cv2.cvtColor(blurred, cv2.COLOR_BGR2HSV)

    green_mask = cv2.inRange(blurred, green_lower, green_upper)
    yellow_mask = cv2.inRange(blurred, yellow_lower, yellow_upper)
    blue_mask = cv2.inRange(blurred, blue_lower, blue_upper)
    orange_mask = cv2.inRange(blurred, orange_lower, orange_upper)
    gray_mask = cv2.inRange(blurred, gray_lower, gray_upper)
    red_mask1 = cv2.inRange(blurred, red_lower1, red_upper1)
    red_mask2 = cv2.inRange(blurred, red_lower2, red_upper2)
    red_mask = cv2.bitwise_or(red_mask1, red_mask2)
    
    bg = raw_frame_bgr[:,:,0] == raw_frame_bgr[:,:,1] # B == G
    gr = raw_frame_bgr[:,:,1] == raw_frame_bgr[:,:,2] # G == R
    slices = np.bitwise_and(bg, gr, dtype= np.uint8) * 255
    
    cv2.imshow("Slices", slices)
            
    green_mask = cv2.morphologyEx(green_mask, cv2.MORPH_CLOSE, kernel) #dilate and erode
    red_mask = cv2.morphologyEx(red_mask, cv2.MORPH_CLOSE, kernel) #dilate and erode
    blue_mask = cv2.morphologyEx(blue_mask, cv2.MORPH_CLOSE, kernel) #dilate and erode
    orange_mask = cv2.morphologyEx(orange_mask, cv2.MORPH_CLOSE, kernel) #dilate and erode
    yellow_mask = cv2.morphologyEx(yellow_mask, cv2.MORPH_CLOSE, kernel) #dilate and erode
    gray_mask = cv2.morphologyEx(gray_mask, cv2.MORPH_CLOSE, kernel) #dilate and erode

    #yellow_mask_bgr = np.stack((yellow_mask, yellow_mask, yellow_mask), axis=2)
    #blue_mask_bgr = np.stack((blue_mask, blue_mask, blue_mask), axis=2)
    #orange_mask_bgr = np.stack((orange_mask, orange_mask, orange_mask), axis=2)
    #green_mask_bgr = np.stack((green_mask, green_mask, green_mask), axis=2)

    #cv2.imshow("Raw Frame", np.hstack([raw_frame, green_mask_bgr]))
    cv2.imshow("Blurred", cv2.cvtColor(blurred, cv2.COLOR_HSV2BGR))
    cv2.imshow("Gray mask", gray_mask)
    cv2.imshow("Blue mask", blue_mask)
    cv2.imshow("Green mask", green_mask)
    cv2.imshow("Yellow mask", yellow_mask)
    cv2.imshow("Red mask", red_mask)
    cv2.imshow("Red mask1", red_mask1)
    cv2.imshow("Red mask2", red_mask2)
    cv2.imshow("Orange mask", orange_mask)
    cv2.imshow("Raw frame", raw_frame)
    k = cv2.waitKey(10) & 0xFF
    
    rawCapture.truncate(0)
    if k == ord('t'):
                    
        #Blue caps:
        _, blue_contours, _ = cv2.findContours(blue_mask, cv2.RETR_TREE, cv2.CHAIN_APPROX_SIMPLE)
        if len(blue_contours) != 0:
            for i in range(len(blue_contours)):
                if cv2.contourArea(blue_contours[i]) >= 10000:
                    print(cv2.contourArea(blue_contours[i]))
                    cap_blue = 1
                    break
                
        #yellow caps:
        _, yellow_contours, _ = cv2.findContours(yellow_mask, cv2.RETR_TREE, cv2.CHAIN_APPROX_SIMPLE)
        if len(yellow_contours) != 0:
            for i in range(len(yellow_contours)):
                if cv2.contourArea(yellow_contours[i]) >= 10000:
                    print(cv2.contourArea(yellow_contours[i]))
                    cap_yellow = 1
                    break
                         
        #red caps:
        _, red_contours, _ = cv2.findContours(red_mask, cv2.RETR_TREE, cv2.CHAIN_APPROX_SIMPLE)
        if len(red_contours) != 0:
            for i in range(len(red_contours)):
                if cv2.contourArea(red_contours[i]) >= 10000:
                    print(cv2.contourArea(red_contours[i]))
                    cap_red = 1
                    break
                
        #green caps:
        _, green_contours, _ = cv2.findContours(green_mask, cv2.RETR_TREE, cv2.CHAIN_APPROX_SIMPLE)
        if len(green_contours) != 0:
            for i in range(len(green_contours)):
                if cv2.contourArea(green_contours[i]) >= 10000:
                    print(cv2.contourArea(green_contours[i]))
                    cap_green = 1
                    break
        
        #orange caps:
        _, orange_contours, _ = cv2.findContours(orange_mask, cv2.RETR_TREE, cv2.CHAIN_APPROX_SIMPLE)
        if len(orange_contours) != 0:
            for i in range(len(orange_contours)):
                if cv2.contourArea(orange_contours[i]) >= 10000:
                    print(cv2.contourArea(orange_contours[i]))
                    cap_orange = 1
                break
        #gray caps:
        _, gray_contours, _ = cv2.findContours(gray_mask, cv2.RETR_TREE, cv2.CHAIN_APPROX_SIMPLE)
        if len(gray_contours) != 0:
            for i in range(len(gray_contours)):
                if cv2.contourArea(gray_contours[i]) >= 10000:
                    print(cv2.contourArea(gray_contours[i]))
                    cap_gray = 1
                    break
        
        if cap_yellow == 1 and cap_red == 0 and cap_green == 0 and cap_orange == 0 and cap_blue == 0 and cap_gray == 0:
            cap = "Yellow"
        elif cap_yellow == 0 and cap_red == 1 and cap_green == 0 and cap_orange == 0 and cap_blue == 0 and cap_gray == 0:
            cap = "Red"
        elif cap_yellow == 0 and cap_red == 0 and cap_green == 1 and cap_orange == 0 and cap_blue == 0 and cap_gray == 0:
            cap = "Green"
        elif cap_yellow == 0 and cap_red == 0 and cap_green == 0 and cap_orange == 1 and cap_blue == 0 and cap_gray == 0:
            cap = "Orange"
        elif cap_yellow == 0 and cap_red == 0 and cap_green == 0 and cap_orange == 0 and cap_blue == 1 and cap_gray == 0:
            cap = "Blue"
        elif cap_yellow == 0 and cap_red == 0 and cap_green == 0 and cap_orange == 0 and cap_blue == 0 and cap_gray == 1:
            cap = "Gray"            
        else:
            cap = "Undefined"
            '''
        elif cap_yellow == 0 and cap_red == 0 and cap_green == 0 and cap_orange == 0:
            cap = "Yellow"
            '''
        #ser.write('1')
        print "cap_yellow: ", cap_yellow
        print "cap_blue: ", cap_blue
        print "cap_orange:" , cap_orange
        print "cap_red: ", cap_red
        print "cap_green: ", cap_green
        print "cap_gray: ", cap_gray
        print(cap)
        cap_yellow = 0
        cap_red = 0
        cap_blue = 0
        cap_green = 0
        cap_orange = 0
        cap_gray = 0
        cap = "Undefined"
    if k == ord('q'):
       break
    if k == ord('p'):
        pause = not pause
        print(pause)
    #out.write(frame)

#video.release()
#out.release()
cv2.destroyAllWindows()
ser.close() 
