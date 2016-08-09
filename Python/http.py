import httplib
import collections
import os

def doExit(arg):
	global Alive
	Alive = False

def showHelp(arg):
	print 'Available Commands'
	for key in sorted(cmdHelp):
		print '{0} - {1}'.format(key, cmdHelp[key]);

def doConnect(arg):
	global curHost
	if(len(arg) > 0):
		curHost = arg[0]
	else:
		curHost = raw_input('Hostname/Address: ')
	curHTTP = httplib.HTTPConnection(curHost)
	try:
		curHTTP.request('GET', '/')
		print 'Connected'
	except:
		print 'Error Connecting to host'
		curHost = '[NULL]'
		
def doGet(arg):
	global data
	if (arg == None):
		print 'Syntax : get [PAGE PATH] {ARGUMENTS}'
		print 'Example: get /page.php p=1&option=Name'
		return
	if (curHost == '[NONE]'):
		print 'You need to connect to a host first.'
	if (len(arg) > 0):
		con = httplib.HTTPConnection(curHost)
		con.request('GET', arg[0] + (arg[1] if len(arg) == 2 else ''));
		res = con.getresponse()
		print res.status, res.reason
		print res.msg
		data = res.read();
	else:
		print 'Syntax : get [PAGE PATH] {ARGUMENTS}'
		print 'Example: get /page.php p=1&option=Name'
		return

def doPost(arg):
	global data
	if (arg == None):
		print 'Syntax : post [PAGE PATH] [ARGUMENTS]'
		print 'Example: post /page.php p=1&option=Name'
		return
	if (len(arg) == 2):
		con = httplib.HTTPConnection(curHost)
		con.request('POST', arg[0], arg[1], {"Content-type": "application/x-www-form-urlencoded", "Accept": "text/plain"});
		res = con.getresponse()
		print res.status, res.reason
		print res.msg
		data = res.read();
	else:
		print 'Syntax : post [PAGE PATH] [ARGUMENTS]'
		print 'Example: post /page.php p=1&option=Name'
		return

def doGets(arg):
	global data
	if (arg == None):
		print 'Syntax : gets [PAGE PATH] {ARGUMENTS}'
		print 'Example: gets /page.php p=1&option=Name'
		return
	if (len(arg) > 0):
		con = httplib.HTTPSConnection(curHost)
		con.request('GET', arg[0] + (arg[1] if len(arg) == 2 else ''));
		res = con.getresponse()
		print res.status, res.reason
		print res.msg
		data = res.read();
	else:
		print 'Syntax : gets [PAGE PATH] {ARGUMENTS}'
		print 'Example: gets /page.php p=1&option=Name'
		return

def doPosts(arg):
	global data
	if (arg == None):
		print 'Syntax : posts [PAGE PATH] [ARGUMENTS]'
		print 'Example: posts /page.php p=1&option=Name'
		return
	if (len(arg) == 2):
		con = httplib.HTTPSConnection(curHost)
		con.request('POST', arg[0], arg[1], {"Content-type": "application/x-www-form-urlencoded", "Accept": "text/plain"});
		res = con.getresponse()
		print res.status, res.reason
		print res.msg
		data = res.read();
	else:
		print 'Syntax : posts [PAGE PATH] [ARGUMENTS]'
		print 'Example: posts /page.php p=1&option=Name'
		return

def doDump(arg):
	print data
	
def doFileDump(arg):
	f = open(arg[0], 'wb')
	f.write(data)
	f.close()
		
def main():
	while (Alive):
		command = raw_input('{0}>'.format(curHost)).split(' ');
		cmd = command[0];
		arg = None
		if(len(command) > 1):
			arg = command[1:]
		try:
			if (cmd == 'clear'):
				os.system('cls')
			else:
				commands[cmd](arg)
		except KeyError:
			print 'Command not found'
	

if __name__ == '__main__':
	global curHost, Alive, commands, cmdHelp
	curHost = '[NONE]'
	Alive = True
	commands = {
		'help' : showHelp,
		'exit' : doExit,
		'connect' : doConnect,
		'get' : doGet,
		'post' : doPost,
		'gets' : doGets,
		'posts' : doPosts,
		'dumpdata' : doDump,
		'dumpdatafile' : doFileDump,
		'clear' : '',
	}
	cmdHelp = {
		'help                                ' : 'Print the help message',
		'exit                                ' : 'Exits the program',
		'connect      [HOSTNAME/IP]          ' : 'Connect to the host',
		'get          [PAGE PATH] {ARGUMENTS}' : 'Gets the page requested through HTTP',
		'post         [PAGE PATH] [ARGUMENTS]' : 'Posts the page requested through HTTP',
		'gets         [PAGE PATH] {ARGUMENTS}' : 'Gets the page requested through HTTPS',
		'posts        [PAGE PATH] [ARGUMENTS]' : 'Posts the page requested through HTTPS',
		'dumpdata                            ' : 'Dump the data to console',
		'dumpdatafile [FILE]                 ' : 'Dump the data to file',
	}
	try:
		main()
	except KeyboardInterrupt:
		doExit(None)
