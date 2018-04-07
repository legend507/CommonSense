#       PSH ACK ->                  | client send data
#               <- ACK              | server ACK
#               <- PSH ACK          | server send data
#               <- FIN ACK          | ?
#               -> ACK              | client ack (for data)
#               -> ACK              | client ack (for FIN ACK)
#       FIN ACK ->                  | ?
#               <- ACK              | server ack (for FIN ACK)
# PSH means that the receiverr should pass the data to upper layer immediately

from socket import *

serverName = '192.168.11.13'         # server IP
serverPort = 50000

clientSocket = socket(AF_INET, SOCK_STREAM)     # STREAM means TCP
clientSocket.bind(('', 50001))                  # bind clientSocket to 50001
clientSocket.connect((serverName, serverPort))  # unlike udp client, need to connect first

message = input('Input lowercase sentence:')
clientSocket.send(message.encode())

recvMessage = clientSocket.recv(1024)
print('From Server:', recvMessage)
clientSocket.close()
