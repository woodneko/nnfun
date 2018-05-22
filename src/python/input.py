from ctypes import *
from sklearn import datasets

#libc = CDLL("libc.so.6")

# generate base data
X, y = datasets.make_moons(200, noise=0.20)

def c_array(ctype, values):
    arr = (ctype*len(values))()
    arr[:] = values
    return arr

class MyStruct(Structure):
     _fields_ = [("a", c_int),
    ("b", c_float),
    ("point_array", POINT * 4)]
