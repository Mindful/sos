#Python 3

#This can't bind properly unless it's run as root (or with sudo, obviously)
#Also, as intended, this will only serve files in directories below it (excluding all the exploits I'm sure I haven't thought of)


try:
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

		try: #Read, look for file
			message = connectionSocket.recv(1024) #Number of bytes to read, I assume
			filename = message.split()[1].decode('UTF-8').strip('/')
			print(filename+" requested...")
			print()
			f = open(filename)
			outputdata = f.read()
			connectionSocket.send("HTTP/1.1 200 OK \n\n".encode('UTF-8'))
			connectionSocket.send(outputdata.encode('UTF-8')) #Write the outputdata, one character at a time
			print("...and served")
			print()
			connectionSocket.close()
		except IOError: #File not found
			print("...but not found")
			connectionSocket.send("HTTP/1.1 404 Not Found \n\n".encode('UTF-8'))
			print()
			connectionSocket.close()
	serversocket.close()
except Exception as err:
	serversocket.close()
	print("Exception detected, closing socket and reraising...")
	raise err