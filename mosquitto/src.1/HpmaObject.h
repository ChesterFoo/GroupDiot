
#include <arduino.h>
#ifndef HPMAOBJECT_H
#define HPMAOBJECT_H
class HpmaObject{
    double  reading_temp;
    double  reading_humidity;
    double  reading_light;
    double  reading_audio;
    double  reading_battery_volts;
    double  reading_CO2;
    double  reading_VOC;
    public: 

        HpmaObject();
        
        double  getReading_temp();
        void setReading_temp(int res);

        double getReading_humidity();
        void setReading_humidity(int reading_humidity);

        double getReading_light();
        void setReading_light(int reading_light);

        double getReading_audio();
        void setReading_audio(int reading_audio);

        double getReading_battery_volts();
        void setReading_battery_volts(int reading_battery_volts);

        double getReading_co2();
        void setReading_co2(int reading_CO2);

        double getReading_voc();
        void setReading_voc(int reading_VOC);
};

#endif