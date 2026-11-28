
#include "Microphone.hpp"

Microphone::Microphone(int pinSCK, int pinWS, int pinSD, uint32_t sampleRate)
    : PIN_SCK(pinSCK),
      PIN_WS(pinWS),
      PIN_SD(pinSD),
      SAMPLE_RATE(sampleRate)
{}

bool Microphone::begin()
{
    Serial.println("\n[MIC] Initializing I2S...");

    // Configure the I2S channel
    i2s_chan_config_t channelConfig =
        I2S_CHANNEL_DEFAULT_CONFIG(I2S_NUM_0, I2S_ROLE_MASTER);

    // Create a receive channel
    esp_err_t result = i2s_new_channel(
        &channelConfig,
        nullptr,
        &rxHandle
    );

    if(result != ESP_OK)
    {
        Serial.printf("[MIC] Channel creation failed: %d\n", result);
        return false;
    }

    // Configure I2S standard mode
    i2s_std_config_t stdConfig = {
        .clk_cfg = I2S_STD_CLK_DEFAULT_CONFIG(SAMPLE_RATE),

        .slot_cfg = I2S_STD_PHILIPS_SLOT_DEFAULT_CONFIG(
            I2S_DATA_BIT_WIDTH_32BIT,
            I2S_SLOT_MODE_MONO
        ),

        .gpio_cfg = {
            .mclk = I2S_GPIO_UNUSED,
            .bclk = (gpio_num_t)PIN_SCK,
            .ws = (gpio_num_t)PIN_WS,
            .dout = I2S_GPIO_UNUSED,
            .din = (gpio_num_t)PIN_SD,
            .invert_flags = {
                .mclk_inv = false,
                .bclk_inv = false,
                .ws_inv = false
            }
        }
    };

    // Select the left microphone channel
    stdConfig.slot_cfg.slot_mask = I2S_STD_SLOT_LEFT;

    // Initialize the I2S peripheral
    result = i2s_channel_init_std_mode(rxHandle, &stdConfig);

    if(result != ESP_OK)
    {
        Serial.printf("[MIC] I2S configuration failed: %d\n", result);
        return false;
    }

    // Start receiving audio
    result = i2s_channel_enable(rxHandle);

    if(result != ESP_OK)
    {
        Serial.printf("[MIC] Channel activation failed: %d\n", result);
        return false;
    }

    Serial.println("[MIC] I2S initialized successfully!");

    return true;
}

bool Microphone::read(int32_t* buffer, size_t sampleCount, size_t& samplesRead)
{
    samplesRead = 0;

    if(rxHandle == nullptr || buffer == nullptr)
        return false;

    size_t bytesRead = 0;

    esp_err_t result = i2s_channel_read(
        rxHandle,
        buffer,
        sampleCount * sizeof(int32_t),
        &bytesRead,
        pdMS_TO_TICKS(100)
    );

    if(result != ESP_OK)
        return false;

    samplesRead = bytesRead / sizeof(int32_t);

    return samplesRead > 0;
}

bool Microphone::readPCM16(int16_t* buffer, size_t sampleCount, size_t& samplesRead)
{
    samplesRead = 0;

    if(rxHandle == nullptr || buffer == nullptr)
        return false;

    if(sampleCount == 0 || sampleCount > BUFFER_SIZE)
        return false;

    static int32_t rawBuffer[BUFFER_SIZE];

    size_t rawSamplesRead = 0;

    if(!read(rawBuffer, sampleCount, rawSamplesRead))
        return false;

    for(size_t i = 0; i < rawSamplesRead; i++)
    {
        buffer[i] = (int16_t)(rawBuffer[i] >> 16);
    }

    samplesRead = rawSamplesRead;

    return true;
}