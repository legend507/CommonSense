# The following is a client sending UDP to server

from socket import *

serverName = "127.0.0.1"         # Server IP
serverPort = 50000

clientSocket = socket(AF_INET, SOCK_DGRAM)      # config socket type
message = input('Input lower case setence:')    # take user input, input can be string
message_byte = message.encode()                 # convert string obj to byte array, sendto only take byte array

# send
clientSocket.sendto(message_byte, (serverName, serverPort)) # send byte array to server
# receive
recvMessage, serverAddress = clientSocket.recvfrom(2048)    # get server reply

print(recvMessage)
clientSocket.close()
