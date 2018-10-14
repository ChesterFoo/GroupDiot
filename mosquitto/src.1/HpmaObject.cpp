
#include <arduino.h>
#include "HpmaObject.h"

       HpmaObject::HpmaObject(){
            reading_temp= 0;
            reading_humidity= 0;
            reading_light= 0;
            reading_audio= 0;
            reading_battery_volts= 0;
            reading_CO2= 0;
            reading_VOC= 0;
        }

        double  HpmaObject::getReading_temp()
            {
                return this->reading_temp;
            }

        void HpmaObject::setReading_temp(int res)
            {
                this->reading_temp = (double) res /10.0;
            }

        double HpmaObject::getReading_humidity()
            {
                return this->reading_humidity;
            }

        void HpmaObject::setReading_humidity(int reading_humidity)
            {
                this->reading_humidity = (double)reading_humidity /10.0;
            }

        double HpmaObject::getReading_light()
            {
                return this->reading_light;
            }

        void HpmaObject::setReading_light(int reading_light)
            {
                this->reading_light = reading_light;
            }

        double HpmaObject::getReading_audio()
            {
                return this->reading_audio;
            }

        void HpmaObject::setReading_audio(int reading_audio)
            {
                this->reading_audio = reading_audio;
            }

        double HpmaObject::getReading_battery_volts()
            {
                return this->reading_battery_volts;
            }

        void HpmaObject::setReading_battery_volts(int reading_battery_volts)
            {
                this->reading_battery_volts = (double)reading_battery_volts / 1024.0 * (3.3/0.33);
            }

        double HpmaObject::getReading_co2()
            {
                return this->reading_CO2;
            }

        void HpmaObject::setReading_co2(int reading_CO2)
            {
                this->reading_CO2 = reading_CO2;
            }

        double HpmaObject::getReading_voc()
            {
                return this->reading_VOC;
            }

        void HpmaObject::setReading_voc(int reading_VOC)
            {
                this->reading_VOC = reading_VOC;
            }
