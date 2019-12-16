import cv2
import numpy as np

video = cv2.VideoCapture(0)
frame_height = np.uint16( video.get(cv2.CAP_PROP_FRAME_HEIGHT))
frame_width = np.uint16(video.get(cv2.CAP_PROP_FRAME_WIDTH))
fps = video.get(cv2.CAP_PROP_FPS)
cv2.namedWindow("hola")
while True:
    _, frame = video.read()
    k = cv2.waitKey(1) & 0xFF
    if k == ord('q'):
        break;
_, frame = video.read()
cv2.imwrite("/home/pi/Desktop/imagen.jpg", frame)

video.release()
cv2.destroyAllWindows()

