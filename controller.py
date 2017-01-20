import serial
import sys
import time
import struct


uno = serial.Serial('/dev/cu.usbmodem14221',57600)
mega= serial.Serial('/dev/tty.usbmodem14241',76800)

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

def breakCmd(value):
    sendMega(18,value)

def steerCmd(value):
    sendMega(19,value)

def main():
    breakValue = 0
    dists = [1e4,1e4,1e4]
    pDist = 0
    threshold = 1000
    steerValue = -130
    while True:
        dist = getDist()
        dists[pDist] = dist
        pDist = (pDist+1)%3
        average = sum(dists)/len(dists)
        print average, breakValue
        if dist<threshold:
            breakValue = 1
        breakCmd(breakValue)
        steerCmd(steerValue)


if __name__ == "__main__":
    main()
