import RPi.GPIO as GPIO
import time
import serial
import cv2

    
#define GPIO pins
GPIO.setmode(GPIO.BCM)
GPIO.setup(18, GPIO.OUT)
GPIO.output(18, 1)
time.sleep(1)

ser = serial.Serial ("/dev/ttyAMA0", 9600)    #Open port with baud rate
# call the function, pass the arguments
while True:
    #time.sleep(0.75)
    #ser.write('p'.encode())    # Gira paleta
    cv2.namedWindow("Hola")
    k = cv2.waitKey(10) & 0xFF
    if k == ord('x'):
        #ser.write('p'.encode())    # Gira paleta       
        ser.write('x'.encode())    # Gris
    if k == ord('1'):
        #ser.write('p'.encode())    # Gira paleta       
        ser.write('1'.encode())    # Gris
    if k == ord('2'):
        #ser.write('p'.encode())    # Gira paleta       
        ser.write('2'.encode())    # Gris
    if k == ord('4'):
        #ser.write('p'.encode())    # Gira paleta       
        ser.write('4'.encode())    # Gris
    if k == ord('5'):
        #ser.write('p'.encode())    # Gira paleta       
        ser.write('5'.encode())    # Gris
    if k == ord('7'):
        #ser.write('p'.encode())    # Gira paleta       
        ser.write('7'.encode())    # Gris
    if k == ord('8'):
        #ser.write('p'.encode())    # Gira paleta       
        ser.write('8'.encode())    # Gris
    if k == ord('x'):
    #ser.write('p'.encode())    # Gira paleta       
        ser.write('x'.encode())    # Gris
    if k == ord('p'):
    #ser.write('p'.encode())    # Gira paleta       
        ser.write('p'.encode())    # Gris
    if k == ord('r'):
    #ser.write('p'.encode())    # Gira paleta       
        ser.write('r'.encode())    # Gris
    if k == ord('g'):
    #ser.write('p'.encode())    # Gira paleta       
        ser.write('g'.encode())    # Gris
    if k == ord('a'):
    #ser.write('p'.encode())    # Gira paleta       
        ser.write('a'.encode())    # Gris
    if k == ord('v'):
    #ser.write('p'.encode())    # Gira paleta       
        ser.write('v'.encode())    # Gris
    if k == ord('n'):
    #ser.write('p'.encode())    # Gira paleta       
        ser.write('n'.encode())    # Gris
    if k == ord('y'):
    #ser.write('p'.encode())    # Gira paleta       
        ser.write('y'.encode())    # Gris
    if k == ord('r'):
    #ser.write('p'.encode())    # Gira paleta       
        ser.write('r'.encode())    # Gris
    if k == ord('k'):
    #ser.write('p'.encode())    # Gira paleta       
        ser.write('k'.encode())    # Gris
    if k == ord('q'):
        break
   
ser.close()