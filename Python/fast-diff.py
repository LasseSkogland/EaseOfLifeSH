#!/usr/bin/python
from getopt import getopt
import sys, os
from sys import stdout
global FILE1, FILE2
FILE1 = 0
FILE2 = 0

if __name__ == '__main__':
	opts, args = getopt(sys.argv[1:], '1:2:', ['file1=', 'file2='])
	for o, a in opts:
		if o in ('-1', '--file1'):
			if os.path.isfile(a):
				FILE1 = open(a, 'rb')
			else:
				print 'Error: File does not exist (%s %s)' % (o, a)
		elif o in ('-2', '--file2'):
			if os.path.isfile(a):
				FILE2 = open(a, 'rb')
			else:
				print 'Error: File does not exist (%s %s)' % (o, a)
	tmp1 = FILE1.read()
	size1 = len(tmp1)
	tmp2 = FILE2.read()
	FILE1.close()
	FILE2.close()
	for c in range(size1):
		if tmp1[c] == tmp2[c]:
			stdout.write('\r%i of %i verified' % (c, size1))
		else:
			print '\nComparison failed at %i of %i' % (c, size1)
			sys.exit(1)
	print '\nBytes 0 - %i of %s is identical to bytes 0 - %i of %s' % (size1, FILE1.name, size1, FILE2.name)