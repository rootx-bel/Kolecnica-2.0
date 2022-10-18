#include <DHT.h>
#include <DHT_U.h>
#include <TinyGPS++.h>
#include "MeOrion.h"
//#include "I2Cdev.h"
//#include "MPU6050.h"
//#include <SoftwareSerial.h>
#include <Wire.h>
//#include "GyverFilters.h"
//#include "HMC5883L.h"
//#include <TroykaIMU.h>
#include <LSM303.h>

LSM303 compass;
#define TO_DEG 57.29577951308232087679815481410517033
#define T_OUT 20
#define DHTPIN 2
#define DHTTYPE DHT11

static const uint32_t GPSBaud = 9600;
TinyGPSPlus gps;
DHT dht(DHTPIN, DHTTYPE);
//double laat[10]={50.549868,50.549762,50.549703,50.549711,50.549778,50.549863,50.549737},lnng[10]={36.575287,36.575299,36.575170,36.574990,36.574948,36.574845,36.574786};
//double laat[10]={50.529181},lnng[10]={36.538318};
double laat[10]={},lnng[10]={};
String buf = "";
bool ready =false;
int now=0;
int n=0;
float gx, gy, gz, ax, ay, az, mx, my, mz;
float yaw, pitch, roll;
float sampleRate = 100;
const float compassCalibrationBias[3] = { 567.893, -825.35, 1061.436 };
const float compassCalibrationMatrix[3][3] = { { 1.909, 0.082, 0.004 },
                                               { 0.049, 1.942, -0.235 },
                                               { -0.003, 0.008, 1.944} };
float headingDegrees=0;
MeEncoderNew motor0(0x09, SLOT1);
MeEncoderNew motor1(0x09, SLOT2);
MeEncoderNew motor2(0x0A, SLOT1);
MeEncoderNew motor3(0x0A, SLOT2);
void sendinf(){
  float t = dht.readTemperature();
  Serial1.println(t+';'+gps.location.lat()+';'+gps.location.lng());
  }

void forward(int power){
    motor0.runSpeed(power);
    motor1.runSpeed(-power);
    motor2.runSpeed(-power);
    motor3.runSpeed(power);
  }
  void backward(int power){
    motor0.runSpeed(-power);
    motor1.runSpeed(power);
    motor2.runSpeed(power);
    motor3.runSpeed(-power);
  }
  void right(int power){
    motor0.runSpeed(-power);//Переднее правое вперед
    motor1.runSpeed(-power);//Переднее левое назад
    motor2.runSpeed(-power);//Заднее левое назад
    motor3.runSpeed(-power);//Заднее правое вперед
  }
  void left(int power){
    motor0.runSpeed(power);
    motor1.runSpeed(power);
    motor2.runSpeed(power);
    motor3.runSpeed(power);
  }
void setup()
{
  Serial.begin(9600);
  Serial1.begin(9600);
  motor0.begin();
  motor1.begin();
  motor2.begin();
  motor3.begin();
  Wire.begin();
  compass.init();
  compass.enableDefault();
  compass.m_min = (LSM303::vector<int16_t>){-32767, -32767, -32767};
  compass.m_max = (LSM303::vector<int16_t>){+32767, +32767, +32767};
  while (true) if (Serial1.available())
  {
    char c = Serial1.read();
    if(c=='o'){
      forward(150);
      while(1==1){
        delay(1);
      }
    }
    //Serial.println(c);
    if ((c == '\n') && (buf != "")) break;
    else buf.concat(c);
  }
  String s = ""; 
  //Serial.println(buf);
  for (int i = 1;buf[i] != '$';i++) s.concat(buf[i]);
  //Serial.println(s);
  n = s.toInt();
  int idx = s.length() + 2;
  //Serial.println(idx);
  for (int i = 0; i<n;i++)
  {
    s = "";
    while (buf[idx] != '$') s.concat(buf[idx++]);
    //Serial.println(s);
    s.replace(',','.');
    //Serial.println(s);
    laat[i] = s.substring(0,s.indexOf('&')).toDouble();
    //Serial.println(idx);
    lnng[i] = s.substring(s.indexOf('&')+1).toDouble();
    Serial.print("point(lat = ");
    Serial.print(laat[i], 16);
    Serial.print(",      lng = ");
    Serial.print(lnng[i], 16);
    Serial.println(")");
    //Serial1.println(0);
    idx++;
  }
  /*for(int i =0; i<n;i++){
    Serial.print(laat[i].toDouble(),16);
    Serial.print(' ');
    Serial.println(lnng[i].toDouble(),16);
  }*/
  //Serial.println("aaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaa");
  Serial2.begin(9600);
  //Serial.println(0);
  
  dht.begin();
  //Serial.println(laat[now]);
  //Serial.println(lnng[now]);
}

void loop()
{
  while (Serial2.available() > 0){
    if (gps.encode(Serial2.read())){
  if (gps.location.isValid())
  {delay(10);
    //Serial.print(gps.location.lat(), 6);
    //Serial.print(F(","));
    //Serial.println(gps.location.lng(), 6);
    //Serial1.println(gps.courseTo(gps.location.lat(),gps.location.lng(),laat[now],lnng[now]));
  compass.read();
  headingDegrees= compass.heading();
  //Serial.println(gps.courseTo(gps.location.lat(),gps.location.lng(),laat[now],lnng[now]));
  if(gps.courseTo(gps.location.lat(),gps.location.lng(),laat[now],lnng[now])+20<headingDegrees){
    //Serial.println("1");
    left(90);
  }
  else if(gps.courseTo(gps.location.lat(),gps.location.lng(),laat[now],lnng[now])-20>headingDegrees){
    //Serial.println("2");
    right(90);
  }else {
    forward(0);
  if (gps.distanceBetween(gps.location.lat(),gps.location.lng(),laat[now],lnng[now])>17){
    forward(180);
    //Serial.println("ahtung");
  }else{
    forward(0);
    delay(3000);
    float t = dht.readTemperature();
    Serial1.print(t);
    Serial1.print(";");
    Serial1.print(laat[now], 8);
    Serial1.print(";");
    Serial1.println(lnng[now], 8);
    delay(15000);
    now++;
    if(n==now){
      forward(0);
      delay(999999);
      }
 }
 }
  }}}
  
}
