import cv2
import numpy as np

video = cv2.VideoCapture(0)
frame_height = np.uint16( video.get(cv2.CAP_PROP_FRAME_HEIGHT))
frame_width = np.uint16(video.get(cv2.CAP_PROP_FRAME_WIDTH))
fps = video.get(cv2.CAP_PROP_FPS)

out = cv2.VideoWriter('/home/pi/Desktop/outpy.avi', cv2.VideoWriter_fourcc('M','J','P','G'), fps, (frame_width,frame_height), True)
while True:
	_, frame = video.read()
	if frame is None:
		break
	cv2.imshow("Frame", frame)
	out.write(frame)
	k = cv2.waitKey(1) & 0xFF
	if k == ord('q'):
		break
video.release()
out.release()
cv2.destroyAllWindows()

