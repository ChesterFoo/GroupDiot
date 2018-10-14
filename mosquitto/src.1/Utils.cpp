#include <stdio.h>
#include <arduino.h>

class Utils{
    public:
    String toString(double value){
        String str;
        char buffer[32];

        snprintf(buffer, sizeof(buffer), "%g", value);
        str.concat(buffer);
        return str;
    }
};
