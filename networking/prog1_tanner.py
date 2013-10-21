#This can't bind properly unless it's run as root (or with sudo, obviously)

from socket import *
serversocket = socket(AF_INET, SOCK_STREAM)
serversocket.bind(('', 80)) #empty string means all available interfaces, port 80
serversocket.listen(5) #queue up to 5 connect requests

print("Winding up on port 80...")
print()
while True:
	connectionSocket, addr = serversocket.accept() #blocks until we receive a tcp connection
	print("TCP connection received from:"+addr[0]+" at port:"+str(addr[1]))
	print()

	try:
		message = connectionSocket.recv(1024) #Number of bytes to read, I assume
		filename = message.split()[1]
		print(filename+" requested...")
		print()
		f = open(filename)
		outputdata = f.read()
		#Send one HTTP header line into socket
		for i in range(0, len(outputdata)):
			connectionSocket.send(outputdata[i]) #Write the outputdata, one character at a time
		print("...and served")
		print()
		connectionSocket.close()
	except IOError: #File not found
		print("...but not found")
		print()
		#TODO:Send response message for file not found
		connectionSocket.close()
serversocket.close()