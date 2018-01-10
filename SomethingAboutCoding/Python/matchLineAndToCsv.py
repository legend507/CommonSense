#
#   █████▒█    ██  ▄████▄   ██ ▄█▀       ██████╗ ██╗   ██╗ ██████╗
# ▓██   ▒ ██  ▓██▒▒██▀ ▀█   ██▄█▒        ██╔══██╗██║   ██║██╔════╝
# ▒████ ░▓██  ▒██░▒▓█    ▄ ▓███▄░        ██████╔╝██║   ██║██║  ███╗
# ░▓█▒  ░▓▓█  ░██░▒▓▓▄ ▄██▒▓██ █▄        ██╔══██╗██║   ██║██║   ██║
# ░▒█░   ▒▒█████▓ ▒ ▓███▀ ░▒██▒ █▄       ██████╔╝╚██████╔╝╚██████╔╝
#  ▒ ░   ░▒▓▒ ▒ ▒ ░ ░▒ ▒  ░▒ ▒▒ ▓▒       ╚═════╝  ╚═════╝  ╚═════╝
#  ░     ░░▒░ ░ ░   ░  ▒   ░ ░▒ ▒░
#  ░ ░    ░░░ ░ ░ ░        ░ ░░ ░
#           ░     ░ ░      ░  ░
#                 ░

import re
import sys
import os.path

if len(sys.argv) != 2:
    print("usage: ./LogConvert.py [filename.asc]")
    sys.exit(0)

#---- open infile
infile_name = sys.argv[1]
infile = open(infile_name, 'r')
print('Converting file: ' + infile_name)

#--- open outfile
outfile_name = infile_name[0:-4] + '.csv'
if os.path.exists(outfile_name):
    print("!file already exists")
    sys.exit(0)
outfile = open(outfile_name, 'w')
outfile.write('時間,CAN Channel,ID,送受信,謎,DLC,Data1,Data2,Data3,Data4,Data5,Data6,Data7,Data8\n')

#---- converting .asc
for line in infile:
    line = line[0:-1]

    if re.match('\s+[0-9]+.[0-9]+\s+[0-9]\s+[a-fA-F0-9]+\s+[TxR]+\s+[d]\s+[0-8]\s+[0-9A-Fa-f\s]+' , line):
        elements = line.split()
        #print(elements) # ['0.002436', '1', '20', 'Rx', 'd', '7', '80', '00', '07', '01', '00', '00', 'AF', 'Length', '=', '219894', 'BitCount', '=', '114', 'ID', '=', '32']
        newline = ''
        for ele in elements:
            if ele != 'Length':
                newline += ele+','
            else:
                newline = newline[0:-1]
                break
        outfile.write(newline + '\n')
infile.close()
outfile.close()