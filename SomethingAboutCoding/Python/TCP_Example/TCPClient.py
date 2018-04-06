# 

from socket import *

serverName = '10.229.90.22'         # server IP
serverPort = 50000

clientSocket = socket(AF_INET, SOCK_STREAM)
clientSocket.connect((serverName, serverPort))  # unlike udp client, need to connect first

message = input('Input lowercase sentence:')
clientSocket.send(message.encode())

recvMessage = clientSocket.recv(1024)
print('From Server:', recvMessage)
clientSocket.close()
