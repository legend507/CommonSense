#

from socket import *

serverPort = 50000
serverSocket = socket(AF_INET, SOCK_STREAM)     # why stream?

serverSocket.bind(('', serverPort))

serverSocket.listen(1)      # what is this?
print('Server Ready')
while 1:
    connectionSocket, addr = serverSocket.accept()  # serverSocket returns connectionSocket
    recvMessage = connectionSocket.recv(1024)
    reply = recvMessage.upper()
    connectionSocket.send(reply)
    connectionSocket.close()
