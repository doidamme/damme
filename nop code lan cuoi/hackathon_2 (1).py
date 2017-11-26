import urllib3
import serial
port = "/dev/ttyACM0"
serialFromArduino = serial.Serial(port,9600)
serialFromArduino.flushInput()
start1=0
start2=0
start3=0
start4=0
start5=0
while True:
    while True:
        while True:
            if(serialFromArduino.inWaiting()>0):
                input = serialFromArduino.read(1)
                input=chr(ord(input))
                if(input=='a'):
                    start1=1
                    nhietdo=''
                elif(start1==1):
                    if(input!='b'):
                        nhietdo=nhietdo+input
                    elif(input=='b'):
                        break
        print(nhietdo)
        http = urllib3.PoolManager()
        r = http.request('GET', 'http://smarthome.bbqsoft.com/input/post.json?node=1&json={Nhiet_do:' + nhietdo + '}&apikey=ba565f4333872b4e7202d03253732248')
        nhietdo=''
        break
    while True:
        while True:
            if(serialFromArduino.inWaiting()>0):
                input = serialFromArduino.read(1)
                input=chr(ord(input))
                if(input=='b'):
                    start2=1
                    anhsang=''
                elif(start2==1):
                    if(input!='c'):
                        anhsang=anhsang+input
                    elif(input=='c'):
                        break
        print(anhsang)
        http = urllib3.PoolManager()
        r = http.request('GET', 'http://smarthome.bbqsoft.com/input/post.json?node=1&json={Cuong_do_anh_sang:' + anhsang + '}&apikey=ba565f4333872b4e7202d03253732248')
        anhsang=''
        break
    while True:
        while True:
            if(serialFromArduino.inWaiting()>0):
                input = serialFromArduino.read(1)
                input=chr(ord(input))
                if(input=='c'):
                    start3=1
                    dopH=''
                elif(start3==1):
                    if(input!='d'):
                        dopH=dopH+input
                    elif(input=='d'):
                        break
        print(dopH)
        http = urllib3.PoolManager()
        r = http.request('GET', 'http://smarthome.bbqsoft.com/input/post.json?node=1&json={Do_pH:' + dopH + '}&apikey=ba565f4333872b4e7202d03253732248')
        dopH=''
        break
    while True:
        while True:
            if(serialFromArduino.inWaiting()>0):
                input = serialFromArduino.read(1)
                input=chr(ord(input))
                if(input=='d'):
                    start4=1
                    dienappin=''
                elif(start4==1):
                    if(input!='e'):
                        dienappin=dienappin+input
                    elif(input=='e'):
                        break
        print(dienappin)
        http = urllib3.PoolManager()
        r = http.request('GET', 'http://smarthome.bbqsoft.com/input/post.json?node=1&json={Dien_ap_PIN:' + dienappin + '}&apikey=ba565f4333872b4e7202d03253732248')
        dienappin=''
        break
    while True:
        while True:
            if(serialFromArduino.inWaiting()>0):
                input = serialFromArduino.read(1)
                input=chr(ord(input))
                if(input=='e'):
                    start5=1
                    dungluongacqui=''
                elif(start5==1):
                    if(input!='f'):
                        dungluongacqui=dungluongacqui+input
                    elif(input=='f'):
                        break
        print(dungluongacqui)
        http = urllib3.PoolManager()
        r = http.request('GET', 'http://smarthome.bbqsoft.com/input/post.json?node=1&json={Dung_luong_acqui:' + dungluongacqui + '}&apikey=ba565f4333872b4e7202d03253732248')
        dungluongacqui=''
        break
