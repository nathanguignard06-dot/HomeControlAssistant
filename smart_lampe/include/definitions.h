//pin definitions and led count for neopixel
#define POT_PIN   33
#define LDR_PIN   35
#define RING_PIN  25
#define LED_COUNT 24

//neopixel lamp
Adafruit_NeoPixel ring
(
  LED_COUNT,
  RING_PIN,
  NEO_GRB + NEO_KHZ800
);

//mqtt
const char broker[]       = "192.168.20.121";
int        port           = 1883;

//serial
int baud = 115200;