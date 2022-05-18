from flask import Flask, jsonify , request, Response
from flask_cors import CORS
from lane import *
import numpy as np


app = Flask(_name_)
CORS(app)
# for blue color

low=np.array([60,40,40])
high=np.array([150,255,255])
@app.route('/')
def main():
    return "main Page"

@app.route('/DetectAngle', methods=['GET'])
def process():
    # image=plt.imread('6.png')
    # image=np.multiply(image,255)
    # image = image.astype('uint8')
    image=GetImageFromMobile()
    laneLines =LaneDetection(image, low, high)
    laneLinesImage = LinesDisplaying(image, laneLines)
    steeringAngle= SteeringAngle(image, laneLines)
    currentAngle = steeringAngle
    print(currentAngle)
    finalImage = displayHeadingLine(laneLinesImage, currentAngle)


    # if (0<=currentAngle<=30 or 150<=currentAngle<=180):
    #     currentAngle=0 

    if (30<=currentAngle<80):
        currentAngle=45   
    elif (105<=currentAngle<150): 
        currentAngle=135         
    elif (80<=currentAngle<100):
        currentAngle=90
    else:
        currentAngle=0    

        
    resultJSON = {"angle": currentAngle}
    print(resultJSON)
    return jsonify(resultJSON)


if _name_ == '_main_':
    app.run(host='192.168.1.6',port=3000,debug=True)