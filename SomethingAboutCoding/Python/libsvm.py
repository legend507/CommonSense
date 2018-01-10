#//
#//   █████▒█    ██  ▄████▄   ██ ▄█▀       ██████╗ ██╗   ██╗ ██████╗
#// ▓██   ▒ ██  ▓██▒▒██▀ ▀█   ██▄█▒        ██╔══██╗██║   ██║██╔════╝
#// ▒████ ░▓██  ▒██░▒▓█    ▄ ▓███▄░        ██████╔╝██║   ██║██║  ███╗
#// ░▓█▒  ░▓▓█  ░██░▒▓▓▄ ▄██▒▓██ █▄        ██╔══██╗██║   ██║██║   ██║
#// ░▒█░   ▒▒█████▓ ▒ ▓███▀ ░▒██▒ █▄       ██████╔╝╚██████╔╝╚██████╔╝
#//  ▒ ░   ░▒▓▒ ▒ ▒ ░ ░▒ ▒  ░▒ ▒▒ ▓▒       ╚═════╝  ╚═════╝  ╚═════╝
#//  ░     ░░▒░ ░ ░   ░  ▒   ░ ░▒ ▒░
#//  ░ ░    ░░░ ░ ░ ░        ░ ░░ ░
#//           ░     ░ ░      ░  ░
#//                 ░
#print('Fuck bug')

import glob
from subprocess import call

def callShell(fileName):
	'''
	When executing this libsvm.py on Ubuntu terminal or Windows cmd, 
	this function calls another .py script and pass fileName as parameter
	'''
	call(["python", "another.py", fileName])


def concatenateAll():
    '''
    This function finds all files in one folder and 
    concatenates all files tail-head into a larger file
    '''
    files = glob.glob('./*')

    fileSummary = 'summary'

    with open(fileSummary, 'wb') as outfile:
        for f in files:
            print(f)
	    callShell(f)
            with open(f) as infile:
                for line in infile:
                    outfile.write(line)
    return


if __name__ == '__main__':
    concatenateAll()
