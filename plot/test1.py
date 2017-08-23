import time
import random
import plotly
import serial
import collections
from plotly.graph_objs import Scatter, Layout

Points = collections.namedtuple('Points', ['x', 'y']) # Define a point array

BAUD = 57600
CMD_PRESET_DISTANCE = 1
CMD_CUSTOM_DISTANCE = 5
CMD_FIFO = 4

mega = serial.Serial('/dev/tty.usbmodem1421', BAUD)

def sendMega(message):
    message = [message]
    mega.write(message)
    mega.flush()
    return

def readMega():
    line = mega.readline()
    try:
        value = float(line)
    except:
        print "Error readline: ", line
        return readMega()
    return value


def plot(p, auto_open=True, filename="temp-plot.html", title="hello world"):
    plotly.offline.plot({
        "data": [ Scatter(x=p.x, y=p.y, mode='lines') ],
        "layout": Layout( title=title)},
        auto_open=auto_open,
        filename=filename)
    return

def getFifo():
    sendMega(CMD_FIFO)
    length = int(readMega())

    print length

    x = []
    y = []
    for i in xrange(0,length):
        x.extend([i])
        y.extend([readMega()])

    p = Points(x, y)
    return p

def getDist(preset=True):
    if (preset):
        sendMega(CMD_PRESET_DISTANCE)
    else:
        sendMega(CMD_CUSTOM_DISTANCE)
    return readMega()

def main():
    time.sleep(3)

    while 1:
        dist = getDist() 
        print dist
        p = getFifo()
        print p.y

        plot(p, title=str(len(p.y)) + " " + str(dist), auto_open=False)
    return



if __name__ == "__main__":
    main()
