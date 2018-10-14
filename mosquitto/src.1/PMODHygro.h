
#include <arduino.h>
#ifndef PMODHYGRO_H
#define PMODHYGRO_H


class PMODHygro{

    //private variables
    double temperature;
    double humidity;

    uint16_t reading_temp;
    uint16_t reading_hum;

    private:

    double tempCalculation(uint16_t temp);
    double humidityCalculation(uint16_t upper);

    public :
    //public functions
    double getTemperature();

	double getHumidity();

    void init();

    void collectTempHumidity();
};

#endif 
