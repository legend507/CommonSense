# This is a UDP server, with 1 socket binding to 50000 port
#   every time packets are received in 50000 port, 
#   this program change the content to upper case char and reply

from socket import *

serverPort = 50000
serverSocket = socket(AF_INET, SOCK_DGRAM)

serverSocket.bind(('', serverPort))     # this program only react to packets received on 50000 port
print('Server Ready')

# 
while 1:
    message_bytes, clientAddress = serverSocket.recvfrom(2048)  # listen to 50000, do the following if receives a packet
    reply = message_bytes.upper()               # convert received message to Upper case letters
    print('receive  : '+ message_bytes.decode() + '\nreply  : ' + reply.decode())
    serverSocket.sendto(reply, clientAddress)   # send back, need to set clientAddress