#include <arduino.h>
#ifndef INTSENSORS_H
#define INTSENSORS_H

class IntSensors{
    private:
    double  reading_temp;
    double  reading_humidity;
    double  reading_light;
    double  reading_audio;
    double  reading_battery_volts;
    double  reading_CO2;
    double  reading_VOC;

    void setReading_temp(int res);
    void setReading_humidity(int reading_humidity);
    void setReading_light(int reading_light);
    void setReading_audio(int reading_audio);
    void setReading_battery_volts(int reading_battery_volts);
    void setReading_co2(int reading_CO2);
    void setReading_voc(int reading_VOC);
    
    public :
    IntSensors() : 
        reading_temp(0),reading_humidity(0),reading_light(0),
        reading_audio(0),reading_battery_volts(0),
        reading_CO2(0),reading_VOC(0){
            //default contrstuctor
    }
    double getReading_humidity();
    double getReading_light();
    double getReading_audio();
    double getReading_battery_volts();
    double getReading_co2();
    double getReading_voc();

    String print_hpma_info();    
    void init_hpma();
    void collect_hpma();
};
#endif