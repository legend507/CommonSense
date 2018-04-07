# a TCP Server Program
#   ATTENTION:  server has 2 sockets, first one is "welcome socket (serverSocket)", 
#                   this socket do 3 way handshake and generate connectionSocket
#               the second one is connectionSocket (cliend address is bind to it)
#                   this socket receives and sends data

from socket import *

serverPort = 50000
serverSocket = socket(AF_INET, SOCK_STREAM)     # why stream?

serverSocket.bind(('', serverPort))   

serverSocket.listen(1)      # what is this?
print('Server Ready')
while 1:
    connectionSocket, addr = serverSocket.accept()  # serverSocket returns connectionSocket
    recvMessage = connectionSocket.recv(1024)       # connectionSocket receive data
    reply = recvMessage.upper()
    # print received and reply
    connectionSocket.send(reply)        # unlike UDP, do NOT need to set client address, because the address is remembered in connectionSocket
    connectionSocket.close()
