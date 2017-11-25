import urllib3
import serial
port = "/dev/ttyACM0"
serialFromArduino = serial.Serial(port,9600)
serialFromArduino.flushInput()
nhietdo=''
start=0
dem=0
while True:
    if(serialFromArduino.inWaiting()>0):
        input = serialFromArduino.read(1)
        input=chr(ord(input))
        if(input=='@'):
            start=1
        elif(start==1):
            if(input!='#'):
                dem=dem+1
                nhietdo=nhietdo+input
            else:
                break
        
http = urllib3.PoolManager()
r = http.request('GET', 'http://smarthome.bbqsoft.com/input/post.json?node=1&json={Nhiet_do:' + nhietdo+ '}&apikey=ba565f4333872b4e7202d03253732248')
