import RPi.GPIO as GPIO
import time
import serial

# import the library
from RpiMotorLib import RpiMotorLib
    
#define GPIO pins
GPIO_pins = (26, 19, 13) # Microstep Resolution MS1-MS3 -> GPIO Pin
direction= 12      # Direction -> GPIO Pin
step = 15      # Step -> GPIO Pin
t1=.0001555555
t2=.0002
tw=1
i=0
j=0
# Declare an named instance of class pass GPIO pins numbers
mymotortest = RpiMotorLib.A4988Nema(direction, step, GPIO_pins, "A4988")

time.sleep(1)

ser = serial.Serial ("/dev/ttyAMA0", 9600)    #Open port with baud rate
# call the function, pass the arguments
while True:
    time.sleep(0.75)
    ser.write('p'.encode())    # Gira paleta

#    if j==3:
#        mymotortest.motor_go(False, "1/16" , 533, t2, False, tw)
#    else
#        mymotortest.motor_go(False, "1/16" , 532, t2, False, tw)
#     mymotortest.motor_go(False, "1/16" , 100, t2, False, 0)
#    mymotortest.motor_go(False, "1/16" , 533, t1, False, tw)
#     mymotortest.motor_go(False, "1/16" , 100, t2, False, 0)
#    mymotortest.motor_go(False, "1/16" , 533, t1, False, tw)
#     mymotortest.motor_go(False, "1/16" , 100, t2, False, 0)
#    mymotortest.motor_go(False, "1/16" , 533, t1, False, tw)
#     mymotortest.motor_go(False, "1/16" , 100, t2, False, 0)
#    mymotortest.motor_go(False, "1/16" , 533, t1, False, tw)
#    mymotortest.motor_go(False, "1/16" , 100, t2, False, 0)
#    mymotortest.motor_go(False, "1/16" , 533, t1, False, tw)
#     mymotortest.motor_go(False, "1/16" , 100, t2, False, 0)
    if j==0:
        #ser.write('p'.encode())    # Gira paleta       
        ser.write('g'.encode())    # Gris        
    if j==1:
        #ser.write('p'.encode())    # Gira paleta
        ser.write('v'.encode())    # Verde
    if j==2:
        #ser.write('p'.encode())    # Gira paleta
        ser.write('a'.encode())    # Azul
    if j==3:
        #ser.write('p'.encode())    # Gira paleta
        ser.write('n'.encode())    # Naranja
    if j==4:
        #ser.write('p'.encode())    # Gira paleta
        ser.write('y'.encode())    # Amarillo
    if j==5:
        #ser.write('p'.encode())    # Gira paleta        
        ser.write('r'.encode())    # Rojo
        
        
    i=i+1
    j=j+1
#    if i==10:
#        i=0
#        mymotortest.motor_go(False, "1/16" , 2, t1, False, 0)
        
    if j==6:
        j=0
    
 #   time.sleep(0.075)


# good practise to cleanup GPIO at some point before exit
GPIO.output(step,0)
#GPIO.cleanup()