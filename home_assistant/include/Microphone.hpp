
#ifndef MICROPHONE_HPP
#define MICROPHONE_HPP

#include <Arduino.h>
#include "driver/i2s_std.h"

class Microphone
{
    public:

        // Constructor
        Microphone(int pinSCK, int pinWS, int pinSD, uint32_t sampleRate);

        // Initializes the I2S peripheral
        bool begin();

        // Reads audio samples into the provided buffer
        bool read(int32_t* buffer, size_t sampleCount, size_t& samplesRead);

    private:

        const int PIN_SCK;
        const int PIN_WS;
        const int PIN_SD;

        const uint32_t SAMPLE_RATE;

        // I2S receive channel
        i2s_chan_handle_t rxHandle = nullptr;
};

#endif
