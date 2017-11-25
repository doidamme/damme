#include <OneWire.h>
#include <DallasTemperature.h>
#define ONE_WIRE_BUS 2
OneWire oneWire(ONE_WIRE_BUS);
DallasTemperature sensors(&oneWire);

#include <Wire.h>
#include <BH1750FVI.h>
BH1750FVI LightSensor;

#define SensorPin 0          
unsigned long int avgValue;  
float b;
int buf[10],temp;

#include <DS3231.h>
DS3231 clock;
RTCDateTime dt;

int n = A2;
int n1 = A1;
 
void setup() {


//=================================THOI GIAN========================
   Serial.begin(9600);
   clock.begin();
   clock.setDateTime(__DATE__, __TIME__);
//==============NHIET DO=======================================
  sensors.begin();
//=============================ANH SANG==========================
  LightSensor.begin(); 
  LightSensor.SetAddress(Device_Address_H);
  LightSensor.SetMode(Continuous_H_resolution_Mode);
  //======================PH===================
   pinMode(13,OUTPUT);    
  //=======================PHAN TRAM PIN======================
   pinMode(n,INPUT);
   pinMode(n1,INPUT);
}

void loop() {
//============================THOI GIAN==============================
  /*dt = clock.getDateTime();
  Serial.print("@");
  Serial.print(clock.dateFormat("d-m-Y H:i:s", dt));
  Serial.print("#");
  //delay(1000);*/
  //====================NHIET DO=================================
 sensors.requestTemperatures();
  Serial.print("@");  
  Serial.print(sensors.getTempCByIndex(0));
  Serial.print("-");
  //delay(1000);
//============================ANH SANG===============================
  uint16_t lux = LightSensor.GetLightIntensity();
  //Serial.print("@");
  Serial.print(lux);
  Serial.print("-");
  //delay(1000);
  //=============================PH====================================
  for(int i=0;i<10;i++)
  { 
    buf[i]=analogRead(SensorPin);
    //delay(10);
  }
  for(int i=0;i<9;i++)       
  {
    for(int j=i+1;j<10;j++)
    {
      if(buf[i]>buf[j])
      {
        temp=buf[i];
        buf[i]=buf[j];
        buf[j]=temp;
      }
    }
  }
  avgValue=0;
  for(int i=2;i<8;i++)                      
    avgValue+=buf[i];
  float phValue=(float)avgValue*5.0/1024/6; 
  phValue=3.5*phValue;
  //Serial.print("@");                      
  Serial.print(phValue,2);
  Serial.print("-");
  digitalWrite(13, HIGH);       
  //delay(800);
  digitalWrite(13, LOW); 

//===================================PHAN TRAM PIN=============================================
  float value = analogRead(n); 
  float volt = (((value / 1023.00 * 5.00)*20.00)/5.00)/20.00*100;
  //Serial.print("@");
  Serial.print(volt);
  Serial.print("-");                                    
  float value1 = analogRead(n1);
  float volt1 = (((value1 / 1023.00 * 5.00)*15.00)/5.00)/15.00*100;
  //Serial.print("@"); 
  Serial.print(volt1 );
  Serial.println("#" );  
 delay(5000);
}
