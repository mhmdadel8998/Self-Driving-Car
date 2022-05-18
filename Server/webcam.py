from cv2 import imshow
import numpy as np
import cv2
import urllib
from flask import Flask, request, Response
import time


url = 'http://192.168.43.228:8080/shot.jpg'
while True:
    img = urllib.request.urlopen(url)
    im = np.array(bytearray(img.read()), dtype=np.uint8)
    img0 = cv2.imdecode(im, -1)
    #cv2.imshow('Captured Image', img0)
    #  Filename
    filename = 'Outputimage.jpg'
    cv2.imwrite(filename, img0)
    time.sleep(5)


# Using cv2.imwrite() method
# Saving the image
# cv2.imwrite(filename, img0)
# filepath = 'C:\Users\moham\Desktop\IOT\Server'
# onlyfiles = [f for f in listdir(filepath) if isfile(join(filepath))]

    # other things you need to do snipped
    # cv2.imwrite(f'C:\Users\moham\Desktop\IOT\Server/image_{n}.png', img0)


#  im1 = Image.open(r"http://10.10.10.74:8080/shot.jpg")
# # save a image using extension
#  image = im1.save("webcam.jpg")
