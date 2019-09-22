#!/usr/bin/python3
from psutil import virtual_memory
import sys

def sufix(num, SI : bool= False):
	multipler = 1024
	if SI:
		multipler = 1000
	if num >= multipler**6:
		return str(num/(multipler**6)) + " EB"
	elif num >= multipler**5:
		return str(num/(multipler**5)) + " PB"
	elif num >= multipler**4: 
		return str(num/(multipler**4))+" TB"
	elif num >= multipler**3:
		return str(num/(multipler**3))+" GB"
	elif num >= multipler**2:
		return str(num/(multipler**2))+" MB"
	elif num >= multipler:
		return str(num/multipler)+" KB"
	else:
		return str(num)+" B"

if len(sys.argv) == 1:
	print(virtual_memory().total)
elif "-h" in sys.argv:
	print(sufix(virtual_memory().total))
elif "--si" in sys.argv:
	print(sufix(virtual_memory().total, True))