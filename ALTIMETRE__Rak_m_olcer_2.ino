#include <LiquidCrystal_I2C.h>
 LiquidCrystal_I2C lcd(0x27,16,2);
#include <SFE_BMP180.h>
#include <Wire.h>
#include<SoftwareSerial.h>
SoftwareSerial btBaglan(11,12);
// :
SFE_BMP180 pressure;
#define ALTITUDE 1049.0 // ISPARTA rakımı 1049.0 metre //1 mbar = 100Pa = 0.750062 mmHg. P/ mbar.
void setup()
{
Serial.begin(9600);
btBaglan.begin(9600);

Serial.println("Degerler Olculuyor");


if (pressure.begin())
Serial.println("BMP180 sensoru okuyor");
else
{

Serial.println("BMP180 init fail\n\n");
while(1); // 
}
}
void loop()
{
char status;
double T,P,p0,a;
//
lcd.begin();

status = pressure.startTemperature();
if (status != 0)
{

delay(status);

status = pressure.getTemperature(T);
if (status != 0)
{

Serial.print("Sicaklik: ");
Serial.print(T,2);
Serial.println(" C, ");

lcd.print("Sicaklik: ");
lcd.print(T,2);
lcd.println(" C, ");


status = pressure.startPressure(3);
if (status != 0)
{

delay(status);

status = pressure.getPressure(P,T);
if (status != 0)
{

Serial.print("Mutlak basınc: ");
Serial.print(P,2);
Serial.print(" mb, ");
Serial.print(P*0.0295333727,2);
Serial.println(" inHg");


p0 = pressure.sealevel(P,ALTITUDE);


a = pressure.altitude(P,p0);



int rakim;

rakim = P*1.173;

rakim = map(rakim,0,2098,2098,0);

Serial.println("...............");
Serial.println("...............");
Serial.println("...............");


Serial.print("Rakim :");
Serial.println(rakim);
lcd.setCursor (0 ,1);
lcd.print("Rakim :");
lcd.println(rakim);
lcd.setCursor (11 ,1);
lcd.print(" m");
}
else Serial.println("error retrieving pressure measurement\n");
}
else Serial.println("error starting pressure measurement\n");
}
else Serial.println("error retrieving temperature measurement\n");
}
else Serial.println("error starting temperature measurement\n");
delay(1000); // Pause for 5 seconds.
}
