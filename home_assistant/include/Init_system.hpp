#ifndef INIT_SYSTEM
#define INIT_SYSTEM

#include <Arduino.h>
#include "Oled.hpp"

class Init_system
{
    public:

        Init_system(Oled& screen, int baud);

        /**
         * @brief Start system
         */
        void begin();
        
    private:
        
        const int SERIAL_BAUD_R8;
        Oled& oled;

        /**
         * @brief Function to setup Serial communication
         * 
         * @param int baud : Serial monitor baud rate
         */
        void setupSerial(int baud);
};

#endif