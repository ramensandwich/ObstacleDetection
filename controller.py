import serial
import sys
import time
import struct


uno = serial.Serial('/dev/cu.usbmodem14221',57600)
mega= serial.Serial('/dev/tty.usbmodem14241',76800)

GOAL = 150
P = 1

def getDist():
    line = uno.readline()
    dist = 0
    try:
        dist = float(line)
    except:
        return getDist()
    return dist

def sendMega(message_id,message_data):
    message_buffer = struct.pack(">Bic",
                                 message_id,
                                 message_data,
                                 "\n")
    mega.write(message_buffer)
    mega.flush()

def brakeCmd(value):
    sendMega(18,value)

def steerCmd(value):
    sendMega(19,value)

def main():
    brakeValue = 0
    #dists = [1e4,1e4,1e4]
    pDist = 0
    threshold = 1000
    steerValue = -130
    while True:
        dist = getDist()

        #dists[pDist] = dist
        #pDist = (pDist+1)%3
        #average = sum(dists)/len(dists)
        #print average, brakeValue

        #dist = distance to obstacle in centimeters.  We're looking to keep it around 150

        error = int(GOAL - dist)

        steerCmd(P * error)


        print dist

        #if dist<threshold:
        #    brakeValue = 1
        brakeCmd(brakeValue)


if __name__ == "__main__":
    main()
