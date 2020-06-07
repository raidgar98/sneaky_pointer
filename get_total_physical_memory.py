#!/usr/bin/python3
from psutil import virtual_memory
import sys

def sufix(num, SI : bool = False):
	multipler = 1024
	if SI:
		multipler = 1000
	if num >= multipler**6:
		return "{:.4f}".format(num/(multipler**6)) + " EB"
	elif num >= multipler**5:
		return "{:.4f}".format(num/(multipler**5)) + " PB"
	elif num >= multipler**4: 
		return "{:.4f}".format(num/(multipler**4))+" TB"
	elif num >= multipler**3:
		return "{:.4f}".format(num/(multipler**3))+" GB"
	elif num >= multipler**2:
		return "{:.4f}".format(num/(multipler**2))+" MB"
	elif num >= multipler:
		return "{:.4f}".format(num/multipler)+" KB"
	else:
		return "{:.4f}".format(num)+" B"


mem = virtual_memory().total
_ = True
human = False
SI = False

if "-h" in sys.argv or "--with-sufix" in sys.argv:
	human = True
if "--si" in sys.argv:
	SI = True

if "-e" in sys.argv or "--enumerate" in sys.argv:
	for i in range(64):
		if _ and 2**i >= mem:
			print("Your physical memory: ", sufix(mem, SI) if human or SI else mem)
			_ = False
		print(i,"\t",sufix(2**i, SI) if human or SI else 2**i)
elif "-c" in sys.argv or "--calculate" in sys.argv:
	print("***\nWarning: This result is theoritical\nIf you want to make sure, you should experiment and find of bits bits by yourself\n***")
	for i in range(64):
		if 2**i > mem:
			result = 64 - (i + 1)	# + 1 to make extra safety 1-bit space
			print("max bits: {}".format(result))
			print("unsigned range: < 0  {} >".format((2**result) - 1))
			result -= 1
			print("signed range: < {}  {} >".format((-(2**result)) + 1, (2**result) - 1 ))
			break
else:
	print(mem)