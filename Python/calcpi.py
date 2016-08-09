from sys import stdout, exit, maxint
from time import time
import math, os, gzip
first = True
global Q, R, T, K, M, X, PIOPEN, ALIVE
Q, R, T, K, M, X = 60, -70, 105, 4, 1, 9
PIOPEN = 'wb'
BUFFER = 4096
ALIVE = True

def setConfig(q, r, t, k, m, x):
	global Q, R, T, K, M, X
	Q, R, T, K, M, X = q, r, t, k, m, x

def saveConfig():
	with open('calcpi.cache', 'wb') as f:
		stdout.write('\rSaving Cache 0%')
		f.write(str(Q) + '\n')
		stdout.write('\rSaving Cache 20%')
		f.write(str(R) + '\n')
		stdout.write('\rSaving Cache 36%')
		f.write(str(T) + '\n')
		stdout.write('\rSaving Cache 52%')
		f.write(str(K) + '\n')
		stdout.write('\rSaving Cache 68%')
		f.write(str(M) + '\n')
		stdout.write('\rSaving Cache 84%')
		f.write(str(X) + '\n')
		stdout.write('\rSaving Cache 99%')
		f.flush()
		stdout.write('\rSaving Cache 100%\n')
	
def loadConfig():
	try:
		with open('calcpi.cache', 'rb') as f:
			stdout.write('\rLoading Cache 0%')
			cache = f.read().split('\n')
			stdout.write('\rLoading Cache 4%')
			Q = long(cache[0])
			stdout.write('\rLoading Cache 20%')
			R = long(cache[1])
			stdout.write('\rLoading Cache 36%')
			T = long(cache[2])
			stdout.write('\rLoading Cache 52%')
			K = long(cache[3])
			stdout.write('\rLoading Cache 68%')
			M = long(cache[4])
			stdout.write('\rLoading Cache 84%')
			X = long(cache[5])
			stdout.write('\rLoading Cache 100%\n')
		print 'Continuing generation of PI'
		return Q, R, T, K, M, X
	except:
		print 'Starting generation of PI'
		return 60, -70, 105, 4, 1, 9
	return 60, -70, 105, 4, 1, 9

def make_pi():
	q, r, t, k, m, x = loadConfig()
	while ALIVE:
		if 4 * q + r - t < m * t:
			yield m
			q, r, t, k, m, x = 10*q, 10*(r-m*t), t, k, (10*(3*q+r))//t - 10*m, x
		else:
			q, r, t, k, m, x = q*k, (2*q+r)*x, t*x, k+1, (q*(7*k+2)+r*x)//(t*x), x+2
		setConfig(q, r, t, k, m, x)

def mainLoop():
	f = gzip.open('pi.txt.gz', PIOPEN)
	tmp = ''
	digits = 0
	lastTime = time()
	if not 'ab' in PIOPEN:
		tmp = '3.'
	try:
		for i in make_pi():
			tmp += (str(i))
			if len(tmp) > BUFFER:
				f.write(tmp)
				tmp = ''
			digits += 1
			if time() - lastTime >= 1.0:
				stdout.write('\r{} digits/s'.format(digits) + (' ' * 10))
				digits = 0
				lastTime += 1.0
	except KeyboardInterrupt:
		print '\nKeyboard Interrupt!'
		print 'Saving PI'
		f.write(tmp)
		f.close()
		os.rename('pi.txt.gz', 'pi.txt.gz.tmp')
		new = gzip.open('pi.txt.gz', 'wb')
		old = gzip.open('pi.txt.gz.tmp', 'rb')
		new.write(old.read())
		old.close()
		new.close()
		os.remove('pi.txt.gz.tmp')
		saveConfig()
		print 'Exiting'
		exit(0)
		
if __name__ == '__main__':
	print 'Starting up'
	print 'Checking Cache'
	if os.path.isfile('calcpi.cache'):
		PIOPEN = 'ab'
	mainLoop()