#
#	a function to calculate XOR of 2 arrays
#

def calcXOR(para1, para2):
	result = [ ((a) ^ (b)) for (a,b) in zip(para1, para2) ]
	return result
	
