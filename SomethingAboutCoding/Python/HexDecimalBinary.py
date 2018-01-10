>>> bin(int("1f", base=16))[2:].zfill(8)
'00011111'


#---- utilities
# to deal with NaN problem
def IntConvert(v, param):
    if (v is np.nan):
        return 0
    else:
        return int(v, param)
# s16 converts value into signed 
def s16(value):
    return -(value & 0x8000) | (value & 0x7fff)