#include <arduino.h>
#include "IntSensors.h"
#include <Wire.h>
#include <stdio.h>
#define DDEControllerAddress 0x2A

String IntSensors::print_hpma_info(){

  char buffer[32];
  snprintf(buffer, sizeof(buffer), "%g", this->reading_temp);
  String str = "\nValues from hpma \n=================\nTemperature: ";
  str.concat(buffer);

  snprintf(buffer, sizeof(buffer), "%g", this->reading_humidity);
  str += "\nHumidity: ";
  str.concat(buffer);

  snprintf(buffer, sizeof(buffer), "%g", this->reading_light);
  str += "\nLight: ";
  str.concat(buffer);

  snprintf(buffer, sizeof(buffer), "%g", this->reading_audio);
  str += "\nBattery Volts: ";
  str.concat(buffer);

  snprintf(buffer, sizeof(buffer), "%g", this->reading_battery_volts);
  str += "\nCO2: ";
  str.concat(buffer);

  snprintf(buffer, sizeof(buffer), "%g", this->reading_CO2);
  str += "\nVOC: ";
  str.concat(buffer);

  snprintf(buffer, sizeof(buffer), "%g", this->reading_VOC);
  str += "\nSound(db): ";
  str.concat(buffer);
  str += "\n";
  Serial.println(str);

  return str;
}

void IntSensors::init_hpma(){
  // config hpma all in one sensor
  //I2C start
  Wire.beginTransmission(DDEControllerAddress);
  Wire.write(0xC0); //Scan Start
  Wire.write(0xFF);  // all init
  if(Wire.endTransmission() == 0)
    Serial.println("Initialized hpma.");
  else
    Serial.println("Didnt Initialized hpma.");
  delay(80); 
}

void IntSensors::collect_hpma(){
  uint16_t reading_temp[7] ={};
  Serial.println("~~~~~~~~~~~~~~~~ Refreshing data ~~~~~~~~~~~~~~~~");
  init_hpma();
  for (int i = 1, j = 0; i <= 14; j++){
    //I2C start
    Wire.beginTransmission(DDEControllerAddress);
    Wire.write(i++);  // IntSensors::set all sensors
    if(Wire.endTransmission() == 0){}
      //Serial.println("Requesting data from hpma."); 

    Wire.requestFrom(DDEControllerAddress,2);

    while (Wire.available()==0);
    reading_temp[j] = Wire.read(); //read data from register
    reading_temp[j] = reading_temp[j] << 8;    // shift high byte to be high 8 bits
    //I2C start
    Wire.beginTransmission(DDEControllerAddress);
    Wire.write(i++);  // get all sensors
    if(Wire.endTransmission() == 0){}
      //Serial.println("Requesting data from hpma."); 

    Wire.requestFrom(DDEControllerAddress,2);

    while (Wire.available()==0);
    reading_temp[j] |= Wire.read(); //read data from register
  }

  //set values
  setReading_temp(reading_temp[0]);
  setReading_humidity(reading_temp[1]);
  setReading_light(reading_temp[2]);
  setReading_audio(reading_temp[3]);
  setReading_battery_volts(reading_temp[4]);
  setReading_co2(reading_temp[5]);
  setReading_voc(reading_temp[6]);
}

   
void IntSensors::setReading_temp(int res)
{
    this->reading_temp = (double) res /10.0;
}

double IntSensors::getReading_humidity()
{
    return this->reading_humidity;
}

void IntSensors::setReading_humidity(int reading_humidity)
{
    this->reading_humidity = (double)reading_humidity /10.0;
}

double IntSensors::getReading_light()
{
    return this->reading_light;
}

void IntSensors::setReading_light(int reading_light)
{
    this->reading_light = reading_light;
}

double IntSensors::getReading_audio()
{
    return this->reading_audio;
}

void IntSensors::setReading_audio(int reading_audio)
{
    this->reading_audio = reading_audio;
}

double IntSensors::getReading_battery_volts()
{
    return this->reading_battery_volts;
}

void IntSensors::setReading_battery_volts(int reading_battery_volts)
{
    this->reading_battery_volts = (double)reading_battery_volts / 1024.0 * (3.3/0.33);
}

double IntSensors::getReading_co2()
{
    return this->reading_CO2;
}

void IntSensors::setReading_co2(int reading_CO2)
{
    this->reading_CO2 = reading_CO2;
}

double IntSensors::getReading_voc()
{
    return this->reading_VOC;
}

void IntSensors::setReading_voc(int reading_VOC)
{
    this->reading_VOC = reading_VOC;
}