# The following is a client sending UDP to server,
#   and wait for server reply

from socket import *

serverName = '192.168.11.13'         # Server IP
serverPort = 50000

clientSocket = socket(AF_INET, SOCK_DGRAM)      # config socket type, DGRAM means UDP
clientSocket.bind(('', 50001))        # optional, this bind client port to 50001; if no this line, client port will be random

message = input('Input lower case setence:')    # take user input, input can be string
message_byte = message.encode()                 # convert string obj to byte array, sendto only take byte array

# send
clientSocket.sendto(message_byte, (serverName, serverPort)) # send byte array to server
# receive
recvMessage, serverAddress = clientSocket.recvfrom(2048)    # get server reply

print(recvMessage)
clientSocket.close()
