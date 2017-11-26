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

int n = A2;
int n1 = A1;

void setup() {
Serial.begin(9600);
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
//====================NHIET DO=================================
 sensors.requestTemperatures();
  Serial.print("a");  
  Serial.print(sensors.getTempCByIndex(0));
  Serial.print("b");
  //delay(1000);
//============================ANH SANG===============================
  uint16_t lux = LightSensor.GetLightIntensity();
  Serial.print(lux);
  Serial.print("c");
  //=============================PH====================================
   for(int i=0;i<10;i++)       //Get 10 sample value from the sensor for smooth the value
  { 
    buf[i]=analogRead(SensorPin);
    delay(10);
  }
  for(int i=0;i<9;i++)        //sort the analog from small to large
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
  for(int i=2;i<8;i++)                      //take the average value of 6 center sample
    avgValue+=buf[i];
  float phValue=(float)avgValue*5.0/1024/6; //convert the analog into millivolt
  phValue=3.5*phValue;                      //convert the millivolt into pH value
  Serial.print("    pH:");  
  Serial.print(phValue,2);
  Serial.println(" ");
  digitalWrite(13, HIGH);       
  delay(3000);
  digitalWrite(13, LOW);  
//===================================PHAN TRAM PIN=============================================
  float value = analogRead(n); 
  float volt = (((value / 1023.00 * 5.00)*20.00)/5.00)/20.00*100;
  Serial.print(volt);
  Serial.print("e");                                    
  float value1 = analogRead(n1);
  float volt1 = (((value1 / 1023.00 * 5.00)*15.00)/5.00)/15.00*100;
  Serial.print(volt1 );
  Serial.println("f" );  
 delay(2000);
}
