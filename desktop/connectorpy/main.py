import requests
import serial
import time
#$5$50,6&36,6$50,80333110444795&36,811065673828125$50,801595275627555&36,81724548339844$50,80116130834655&36,81793212890625$50,75817859508892&36,87355041503906$
#http://127.0.0.1/comm?points=50.5987,36.5766&temp=0&idds=3
#50.6097;36.5701;20
url = 'http://entropy31.ru/comm'
flag = True
a=str(input())
try:
    ser = serial.Serial('COM'+a, 9600, timeout=5)
    time.sleep(2)
except serial.SerialException:
    print("Проверьте порт.")
    flag = False

resp = requests.get(url, {"start":""})
ids = resp.text.split('*')[1]
points = resp.text[:-3].split(";")
for i in range(len(points)):
    points[i] = points[i].split("&")
numpoints = len(points)
poi_to_send = "$" + str(numpoints) + "$"
for i in points:
    poi_to_send += i[0][:-2] + '&' + i[1][:-2] + '$'
poi_to_send += "\n"
ser.write(poi_to_send.encode("utf-8"))
time.sleep(1)
while flag:
    if numpoints > 0:
        data=ser.readline().decode("utf-8")
        data=data[:-2]
        coords = data.split(";")
        if len(data)>6:
            print(coords)
            resp = requests.get(url+"?points" + "=" + coords[1] + "," + coords[2] + "&temp" + "=" + coords[0] + "&idds" + "=" + ids)
            numpoints -= 1
    else:
        ser.close()
        flag = False 

# while(True):
#     data=ser.readline().decode("utf-8")
#     data=data[:-2]
#     print(data)
#     if(counter==1):
#                     file_path_json = {"1":str(counter)+";"+data,"2": "1"}
#                     resp = requests.get(url, file_path_json)
#     else:
#                     file_path_json = {"1":str(counter)+";"+data,"2": "0"}
#                     resp = requests.get(url, file_path_json)
#     counter+=1