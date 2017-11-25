import urllib3
import serial
port = "/dev/ttyACM0"
serialFromArduino = serial.Serial(port,9600)
serialFromArduino.flushInput()
nhietdo=''
anhsang=''
dopH=''
dienappin=''
dungluongacqui=''
start=0
dem=0
while True:
    if(serialFromArduino.inWaiting()>0):
        input = serialFromArduino.read(1)
        input=chr(ord(input))
        if(input=='a'):
            start=1
        elif(start==1):
            if(input!='b'):
                dem=dem+1
                nhietdo=nhietdo+input
            elif(input=='b'):
                http = urllib3.PoolManager()
                r = http.request('GET', 'http://smarthome.bbqsoft.com/input/post.json?node=1&json={Nhiet_do:' + nhietdo + '}&apikey=ba565f4333872b4e7202d03253732248')
                break
while True:
    if(serialFromArduino.inWaiting()>0):
        input = serialFromArduino.read(1)
        input=chr(ord(input))
        if(input=='b'):
            start=1
        elif(start==1):
            if(input!='c'):
                dem=dem+1
                anhsang=anhsang+input
            elif(input=='c'):
                http = urllib3.PoolManager()
                r = http.request('GET', 'http://smarthome.bbqsoft.com/input/post.json?node=1&json={Cuong_do_anh_sang:' + anhsang + '}&apikey=ba565f4333872b4e7202d03253732248')
                break
while True:
    if(serialFromArduino.inWaiting()>0):
        input = serialFromArduino.read(1)
        input=chr(ord(input))
        if(input=='c'):
            start=1
        elif(start==1):
            if(input!='d'):
                dem=dem+1
                dopH=dopH+input
            elif(input=='d'):
                http = urllib3.PoolManager()
                r = http.request('GET', 'http://smarthome.bbqsoft.com/input/post.json?node=1&json={Do_pH:' + dopH + '}&apikey=ba565f4333872b4e7202d03253732248')
                break
while True:
    if(serialFromArduino.inWaiting()>0):
        input = serialFromArduino.read(1)
        input=chr(ord(input))
        if(input=='d'):
            start=1
        elif(start==1):
            if(input!='e'):
                dem=dem+1
                dienappin=dienappin+input
            elif(input=='e'):
                break
        print(dienappin)
while True:
    if(serialFromArduino.inWaiting()>0):
        input = serialFromArduino.read(1)
        input=chr(ord(input))
        if(input=='e'):
            start=1
        elif(start==1):
            if(input!='f'):
                dem=dem+1
                dungluongacqui=dungluongacqui+input
            elif(input=='f'):
                break
        print(dungluongacqui)

                


