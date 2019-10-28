import struct
def double_to_hex(f):
    return hex(struct.unpack('<Q', struct.pack('<d', f))[0])
 
double_to_hex(0.1)