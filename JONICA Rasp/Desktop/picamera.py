import time
import picamera

with picamera.PiCamera() as picam:
	picam.start_preview()
