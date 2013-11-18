#Python 2
#Josh Tanner, Colin Robinson


# UDPPingerServer.py
# We will need the following module to generate randomized lost packets
from socket import *
import time
# Create a UDP socket 
# Notice the use of SOCK_DGRAM for UDP packets
# Server listens on 12001
UDP_IP = "127.0.0.1"
UDP_PORT = 12000
listenSocket = socket(AF_INET, SOCK_DGRAM)
# Assign IP address and port number to socket
listenSocket.bind(('', 12001))
listenSocket.settimeout(1.0)
for x in range (0,10): 
	# Receive the client packet along with the address it is coming from 
	message = "Python is a lovely lady"
	t = time.time()
	print "Sending \""+message+"\""
	listenSocket.sendto(message, (UDP_IP, UDP_PORT))
	try:
		message, address = listenSocket.recvfrom(1024)
		rt = time.time() - t
		print "Received \""+message+"\". Round-trip time:"+str(rt)
	except timeout:
		print "Timed out"
