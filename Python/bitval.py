# PYTHON
import urllib, urllib2, json, time, sys
from sys import stdout
from datetime import timedelta

ContPrint = lambda x: stdout.write('\r' + str(x) + (' ' * (80 - len(str(x)))))

if __name__ == '__main__':
	try:
		req = urllib2.Request('https://www.bitstamp.net/api/ticker/')
		req.add_header("Content-type", "application/x-www-form-urlencoded")
		while True:
			response = urllib2.urlopen(req)
			data = json.loads(response.read())
			ContPrint(data['last'] + 'USD')
			time.sleep(1)
	except KeyboardInterrupt:
		sys.exit(0)