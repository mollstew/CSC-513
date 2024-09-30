# Importing Libraries 
import serial
import time


ser = serial.Serial("/dev/cu.usbmodem1401", 9600)

myPath = "/Users/mollystewart/Library/Mobile Documents/com~apple~TextEdit/Documents/myWordCount.txt"


# ask the user for their goal
input_goal = input("Enter your word count goal: ")

input_wpm = input("Input word goal per minute: ")

# send the goal.
goal = "G" + input_goal

ser.write(goal.encode())
time.sleep(5)

loopCount = 0 
loopCheck = 12 # check wpm = 12 loops since 5 seconds of sleep each loop on average    
number_of_words = 0

while True:

    if loopCount == 0:
        startWordCount = number_of_words # saving number of words at the beggining of time period
    
    number_of_words = 0

    with open(myPath,'r') as file:
        data = file.read()
        lines = data.split()

    for word in lines:
        number_of_words += 1
    file.close()

    ser.write(str(number_of_words).encode())
    print(number_of_words)

    loopCount += 1
    if loopCount > loopCheck:
        time.sleep(2) # adding space so brightness and count don't show up in same serial line
        # compare current word count and start word count
        wordIncrease = number_of_words - startWordCount
        if wordIncrease < int(input_wpm):
            # did not reach goal, send signal to dim lights
            dim = "D"
            ser.write(dim.encode())
            print("dim")
        else:
            # did reach goal, send signal brighten lights
            brighten = "B"
            ser.write(brighten.encode())
            print("brighten")
        loopCount = 0  # reset counter 
        
    time.sleep(2)