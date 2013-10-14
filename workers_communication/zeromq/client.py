import zmq
import random
import sys
import time

port = "5556"
context = zmq.Context()
socket = context.socket(zmq.PAIR)
socket.connect("tcp://localhost:%s" % port)

while True:
	msg = socket.recv()
	print ">>> %s" % msg
	socket.send("Client-sent message to server #1")
	socket.send("Client message to server #2")
	time.sleep(1)
