# Code is modified from CSC 413/513 tutorial on teachable machine code 

import cv2
import numpy as np
import tensorflow as tf
import serial
import time


# Load TFLite model and allocate tensors
interpreter = tf.lite.Interpreter(model_path="model_unquant.tflite")
interpreter.allocate_tensors()


# Get input and output details
input_details = interpreter.get_input_details()
output_details = interpreter.get_output_details()


# Setup Serial Communication
arduino = serial.Serial('/dev/cu.usbmodem11401', 9600)  # Update with your Arduino's port
time.sleep(2)  # Allow time for Arduino to initialize


# Setup Webcam
cap = cv2.VideoCapture(1)

previousPrediction = 0

while True:
    ret, frame = cap.read()
    if not ret:
        break


    # Preprocess frame to fit model input
    input_image = cv2.resize(frame, (224, 224))  # Adjust size as per your model
    input_image = np.expand_dims(input_image, axis=0)
    input_image = input_image.astype(np.float32) / 255.0


    # Run inference
    interpreter.set_tensor(input_details[0]['index'], input_image)
    interpreter.invoke()
    predictions = interpreter.get_tensor(output_details[0]['index'])


    # Determine which class has the highest confidence
    predicted_class = np.argmax(predictions)
    confidence = np.max(predictions)

    if previousPrediction == 0:
        if predicted_class == 3 and confidence > 0.9:
            print("Bored")
            previousPrediction = 3
            arduino.write(b"bored\n") 
        elif predicted_class == 2 and confidence > 0.9:
            print("Frustrated")
            previousPrediction = 2
            arduino.write(b"frustrated\n")  
        elif predicted_class == 1 and confidence > 0.9:
            print("Happy")
            previousPrediction = 1
            arduino.write(b"happy\n")  
        elif predicted_class == 4 and confidence > 0.9:
            print("Anxious")
            previousPrediction = 4
            arduino.write(b"anxious\n")  
    elif predicted_class == 0 and confidence > 0.9:
        previousPrediction = 0
 
    # Display the frame
    cv2.imshow("Webcam", frame)
    if cv2.waitKey(1) & 0xFF == ord("q"):
        break


# Cleanup
cap.release()
cv2.destroyAllWindows()
arduino.close()
