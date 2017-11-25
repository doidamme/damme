#include <OneWire.h>
#include <DallasTemperature.h>
#define ONE_WIRE_BUS 2
OneWire oneWire(ONE_WIRE_BUS);
DallasTemperature sensors(&oneWire);

#include <Wire.h>
#include <BH1750FVI.h>
BH1750FVI LightSensor;

#define SensorPin 0          //pH meter Analog output to Arduino Analog Input 0
unsigned long int avgValue;  //Store the average value of the sensor feedback
float b;
int buf[10],temp;

#include <DS3231.h>
DS3231 clock;
RTCDateTime dt;

int n = A2;
int n1 = A1;
 
void setup() {


//=================================thoigian========================
   Serial.begin(9600);

  Initialize DS3231
  Serial.println("Initialize DS3231");;
  clock.begin();

  Set sketch compiling time
  clock.setDateTime(__DATE__, __TIME__);

  Set from UNIX timestamp
  clock.setDateTime(1397408400);

  Manual (YYYY, MM, DD, HH, II, SS
  clock.setDateTime(2014, 4, 13, 19, 21, 00);
  //==============nhietdo=======================================
Serial.begin(9600);
  sensors.begin();
//=============================anhsang==========================
  Serial.begin(9600);
  LightSensor.begin(); 
  LightSensor.SetAddress(Device_Address_H);//Address 0x5C
  LightSensor.SetMode(Continuous_H_resolution_Mode);
  
  Serial.println("Running...");
  //======================PH===================
   pinMode(13,OUTPUT);  
  Serial.begin(9600);  
  Serial.println("Ready");    //Test the serial monitor
  //=======================%pin======================
   pinMode(n,INPUT);
  pinMode(n1,INPUT);
  Serial.begin(9600);
}

void loop() {
//============================thoigian==============================
  dt = clock.getDateTime();

  Serial.print("D/M/Y H:I:S : ");
  Serial.println(clock.dateFormat("d-m-Y H:i:s", dt));

  Serial.print("Long format with month name: ");
  Serial.println(clock.dateFormat("d F Y H:i:s",  dt));

  Serial.print("Short format witch 12h mode: ");
  Serial.println(clock.dateFormat("jS M y, h:ia", dt));

  Serial.print("Today is:                    ");
  Serial.print(clock.dateFormat("l, z", dt));
  Serial.println(" days of the year.");

  Serial.print("Actual month has:            ");
  Serial.print(clock.dateFormat("t", dt));
  Serial.println(" days.");

  Serial.print("Unixtime:                    ");
  Serial.println(clock.dateFormat("U", dt));

  Serial.println();

  delay(1000);
  //====================nhietdo=================================
 sensors.requestTemperatures();  
  Serial.print("Nhietdo: ");
  Serial.println(sensors.getTempCByIndex(0)); // vì 1 ic nên dùng 0
 
  chờ 1 s rồi đọc để bạn kiệp thấy sự thay đổi
  delay(1000);
//============================anhsang===============================
  uint16_t lux = LightSensor.GetLightIntensity();// Get Lux value
  Serial.print("Anhsang: ");
  Serial.println(lux);
  Serial.println(" lux");
  delay(1000);
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
  //Serial.print(" pH:");  
  Serial.print( phValue,2);
  Serial.println(" ");
  digitalWrite(13, HIGH);       
  delay(800);
  digitalWrite(13, LOW); 

//===================================%pin=============================================
float value = analogRead(n); 
  float volt = (((value / 1023.00 * 5.00)*20.00)/5.00)/20.00*100;
  Serial.println(volt );                                    
  float value1 = analogRead(n1);
  float volt1 = (((value1 / 1023.00 * 5.00)*15.00)/5.00)/15.00*100; 
  Serial.println(volt1 );                                  
  delay(5000);
}
