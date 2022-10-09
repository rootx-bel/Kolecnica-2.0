import requests
import serial
url = 'http://2332453345.ddns.net/send.php'
counter=1
'''
file_path_json = {"1": "1;temp;latt;lngg","2": "1"}
file_path_json1 = {"1": "2;temp;lattt;lnggg","2": "0"}
resp = requests.get(url, file_path_json)
resp = requests.get(url, file_path_json1)
print(resp.text)
'''
a=str(input())
ser = serial.Serial('COM'+a, 9600)
while(True):
                data=ser.readline().decode("utf-8")
                data=data[:-2]
                print(data)
                if(counter==1):
                                file_path_json = {"1":str(counter)+";"+data,"2": "1"}
                                resp = requests.get(url, file_path_json)
                else:
                                file_path_json = {"1":str(counter)+";"+data,"2": "0"}
                                resp = requests.get(url, file_path_json)
                counter+=1