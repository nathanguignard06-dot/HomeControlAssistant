#ifndef MICROPHONE_HPP
#define MICROPHONE_HPP

#include <Arduino.h>
#include "driver/i2s_std.h"

class Microphone
{
    public:

        static constexpr size_t BUFFER_SIZE = 1024;

        Microphone(int pinSCK, int pinWS, int pinSD, uint32_t sampleRate);

        bool begin();

        bool read(int32_t* buffer, size_t sampleCount, size_t& samplesRead);

        bool readPCM16(int16_t* buffer, size_t sampleCount, size_t& samplesRead);

    private:

        const int PIN_SCK;
        const int PIN_WS;
        const int PIN_SD;

        const uint32_t SAMPLE_RATE;

        i2s_chan_handle_t rxHandle = nullptr;
};

#endif