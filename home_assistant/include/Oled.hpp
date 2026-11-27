#ifndef OLED
#define OLED

#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

class Oled
{
    public:

        /**
         * @brief Oled class constructor.
         *
         * @param Adafruit_SSD1306 screen   : Oled object initialised with Adafruit_SSD1306 librairie.
         */
        Oled(Adafruit_SSD1306& screen);
        
        /**
         * @brief Initialises the Oled screen.
         *
         * @returns False if unsuccessful, True if successful (bool)
         */
        bool begin();

        /**
         * @brief Clears Oled screen.
         */
        void clearScreen();

        /**
         * @brief Setup Oled parameters.
         *
         * @param int textSize   : Size of text.
         * @param int x          : X axis of Oled (for cursor).
         * @param int y          : Y axis of Oled (for cursor).
         */
        void screenSettings(int txtSize, int xAxis, int yAxis);

        /**
         * @brief Displays everything on Oled screen.
         */
        void displayScreen();


        /**
         * @brief Message to print.
         *
         * @param String    : A string message.
         * @param int       : An integer value.
         * @param float     : A float value.
         * @param double    : A double value.
         */
        void print(String message);
        void print(int value);
        void print(float value, int decimals = 2);
        void print(double value, int decimals = 2);
        
    private:
        
        Adafruit_SSD1306& oled;

        /**
         * @brief Starting screen after initialising.
         */
        void startScreen();
};

#endif