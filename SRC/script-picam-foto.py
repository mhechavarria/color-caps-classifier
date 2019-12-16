from picamera.array import PiRGBArray
from picamera import PiCamera
import RPi.GPIO as GPIO
import numpy as np
import time
import cv2
import serial

#ser = serial.Serial ("/dev/ttyAMA0")    #Open named port 
#ser.baudrate = 115200                     #Set baud rate to 115200
#data = ser.read(10)                     #Read ten characters from serial port to data
#ser.write(data)                         #Send back the rec data
GPIO.setmode(GPIO.BCM)
GPIO.setup(18, GPIO.OUT)
GPIO.output(18, 1)

# initialize the camera and grab a reference to the raw camera capture
camera = PiCamera()
camera.resolution = (640, 480)
camera.framerate = 24
camera.brightness = 51
camera.contrast = -15
camera.saturation = 70
camera.sharpness = -100
camera.ISO = 500
camera.awb_mode = "incandescent"
#camera.start_preview()
time.sleep(2)
rawCapture = PiRGBArray(camera, size=(640, 480))

#buffer = ["", "", ""]

def nothing(x):
    pass
        
def actualiza_rangos():
    global hLow
    global sLow
    global vLow
    global hUpper
    global sUpper
    global vUpper
    global green_lower
    global green_upper
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
    green_lower = np.array([hLow, sLow, vLow])
    green_upper = np.array([hUpper, sUpper, vUpper])
    
    contrast = cv2.getTrackbarPos('Contrast','Trackbar')
    bright = cv2.getTrackbarPos('Bright','Trackbar')
    sat = cv2.getTrackbarPos('Sat','Trackbar')
    camera.saturation = sat
    camera.brightness = bright
    camera.contrast = contrast
        

gray_lower = np.array([0, 0, 88])
gray_upper = np.array([179, 163, 205])

#"definitivos"
blue_lower = np.array([95, 143, 154])
blue_upper = np.array([110, 255, 255])
orange_lower = np.array([7, 150, 45])
orange_upper = np.array([26, 255, 255])
yellow_lower = np.array([25, 111, 123])
yellow_upper = np.array([45, 255, 255])
green_lower = np.array([72, 100, 170])
green_upper = np.array([95, 255, 255])

red_lower1 = np.array([0, 150, 150])
red_upper1 = np.array([15, 255, 255])
red_lower2 = np.array([171, 150, 150])
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
cv2.createTrackbar('H low','Trackbar',	green_lower[0],180,nothing)
cv2.createTrackbar('S low','Trackbar',	green_lower[1],255,nothing)
cv2.createTrackbar('V low','Trackbar',	green_lower[2],255,nothing)
cv2.createTrackbar('H high','Trackbar', green_upper[0],180,nothing)
cv2.createTrackbar('S high','Trackbar',	green_upper[1],255,nothing)
cv2.createTrackbar('V high','Trackbar',	green_upper[2],255,nothing)
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
#time.sleep(2)


image = np.empty((640 * 480 * 3,), dtype=np.uint8)
camera.capture('foto.jpg')
#camera.stop_preview()
imagen = cv2.imread('foto.jpg', 1)
#cv2.imshow("imagen", imagen)

r = cv2.selectROI(imagen)
#cv2.destroyWindow("ROI Selector")
#init = 0
#print("ROI")
#gray_mask = np.empty((int(r[3]), int(r[2])), np.uint8) #creo que esto no se usa
#print(gray_mask.shape)
#print(raw_frame.shape)
#raw_frame = imagen[int(r[1]):int(r[1]+r[3]), int(r[0]):int(r[0]+r[2])]
#raw_frame_bgr = imagen

#ser.write('p'.encode())

#rec = ord('e')
#camera.start_preview()
image = np.empty((640 * 480 * 3), dtype=np.uint8)
ser = serial.Serial ("/dev/ttyAMA0", 9600, timeout=0.1)    #Open port with baud rate
i = 0
init = 1
ser.write('u'.encode())
while True:
    time.sleep(0.05)
    ser.write('p'.encode())
    time.sleep(0.15)
    if init == 1:
        init = 0
    else:
        ser.write('k')
    time.sleep(0.1)
    actualiza_rangos()
    camera.capture('foto.jpg')
    image = cv2.imread('foto.jpg', 1)
    time.sleep(0.05)
    raw_frame = image[int(r[1]):int(r[1]+r[3]), int(r[0]):int(r[0]+r[2])]
    raw_frame_bgr = raw_frame
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
        
    green_mask = cv2.morphologyEx(green_mask, cv2.MORPH_CLOSE, kernel) #dilate and erode
    red_mask = cv2.morphologyEx(red_mask, cv2.MORPH_CLOSE, kernel) #dilate and erode
    blue_mask = cv2.morphologyEx(blue_mask, cv2.MORPH_CLOSE, kernel) #dilate and erode
    orange_mask = cv2.morphologyEx(orange_mask, cv2.MORPH_CLOSE, kernel) #dilate and erode
    yellow_mask = cv2.morphologyEx(yellow_mask, cv2.MORPH_CLOSE, kernel) #dilate and erode
    gray_mask = cv2.morphologyEx(gray_mask, cv2.MORPH_CLOSE, kernel) #dilate and erode
            
            
        
    ####### DETECCION DE COLOR #######
    #Blue caps:
    _, blue_contours, _ = cv2.findContours(blue_mask, cv2.RETR_TREE, cv2.CHAIN_APPROX_SIMPLE)
    if len(blue_contours) != 0:
        for i in range(len(blue_contours)):
            if cv2.contourArea(blue_contours[i]) >= 7500:
                print("Blue")
                print(cv2.contourArea(blue_contours[i]))
                cap_blue = 1
                break
            
    #yellow caps:
    _, yellow_contours, _ = cv2.findContours(yellow_mask, cv2.RETR_TREE, cv2.CHAIN_APPROX_SIMPLE)
    if len(yellow_contours) != 0:
        for i in range(len(yellow_contours)):
            if cv2.contourArea(yellow_contours[i]) >= 7500:
                print("Yellow")
                print(cv2.contourArea(yellow_contours[i]))
                cap_yellow = 1
                break
                     
    #red caps:
    _, red_contours, _ = cv2.findContours(red_mask, cv2.RETR_TREE, cv2.CHAIN_APPROX_SIMPLE)
    if len(red_contours) != 0:
        for i in range(len(red_contours)):
            if cv2.contourArea(red_contours[i]) >= 8000:
                print("Red")
                print(cv2.contourArea(red_contours[i]))
                cap_red = 1
                break
            
    #green caps:
    _, green_contours, _ = cv2.findContours(green_mask, cv2.RETR_TREE, cv2.CHAIN_APPROX_SIMPLE)
    if len(green_contours) != 0:
        for i in range(len(green_contours)):
            if cv2.contourArea(green_contours[i]) >= 7500:
                print("Green")
                print(cv2.contourArea(green_contours[i]))
                cap_green = 1
                break
    
    #orange caps:
    _, orange_contours, _ = cv2.findContours(orange_mask, cv2.RETR_TREE, cv2.CHAIN_APPROX_SIMPLE)
    if len(orange_contours) != 0:
        for i in range(len(orange_contours)):
            if cv2.contourArea(orange_contours[i]) >= 7500:
                print("Orange")
                print(cv2.contourArea(orange_contours[i]))
                cap_orange = 1
                break
    #gray caps:
    _, gray_contours, _ = cv2.findContours(gray_mask, cv2.RETR_TREE, cv2.CHAIN_APPROX_SIMPLE)
    if len(gray_contours) != 0:
        for i in range(len(gray_contours)):
            if cv2.contourArea(gray_contours[i]) >= 9000:
                print("Gray")
                print(cv2.contourArea(gray_contours[i]))
                cap_gray = 1
                break
    
    if cap_yellow == 1 and cap_red == 0 and cap_green == 0 and cap_orange == 0 and cap_blue == 0 and cap_gray == 0:
        cap = 'y'
    elif cap_yellow == 0 and cap_red == 1 and cap_green == 0 and cap_orange == 0 and cap_blue == 0 and cap_gray == 0:
        cap = 'r'
    elif cap_yellow == 0 and cap_red == 0 and cap_green == 1 and cap_orange == 0 and cap_blue == 0 and cap_gray == 0:
        cap = 'v'
    elif cap_yellow == 0 and cap_red == 0 and cap_green == 0 and cap_orange == 1 and cap_blue == 0 and cap_gray == 0:
        cap = 'n'
    elif cap_yellow == 0 and cap_red == 0 and cap_green == 0 and cap_orange == 0 and cap_blue == 1 and cap_gray == 0:
        cap = 'a'
    elif cap_yellow == 0 and cap_red == 0 and cap_green == 0 and cap_orange == 0 and cap_blue == 0 and cap_gray == 1:
        cap = 'g'
    else:
        cap = 'u'
    
    cv2.imshow("Gray mask", gray_mask)
    cv2.imshow("Blue mask", blue_mask)
    cv2.imshow("Green mask", green_mask)
    cv2.imshow("Yellow mask", yellow_mask)
    cv2.imshow("Red mask", red_mask)
    cv2.imshow("Red mask1", red_mask1)
    cv2.imshow("Red mask2", red_mask2)
    cv2.imshow("Orange mask", orange_mask)
    cv2.imshow("raw frame", raw_frame)
    
    ser.write(cap.encode())
    print(cap)
    cap_yellow = 0
    cap_red = 0
    cap_blue = 0
    cap_green = 0
    cap_orange = 0
    cap_gray = 0
    cap = 'u'
    
    k = cv2.waitKey(10) & 0xFF
    if k == ord('q'):
       break

#camera.stop_preview()
cv2.destroyAllWindows()
ser.close() 
GPIO.cleanup()
