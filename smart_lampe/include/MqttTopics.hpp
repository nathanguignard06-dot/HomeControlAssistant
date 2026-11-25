#ifndef MQTTTOPICS
#define MQTTTOPICS

namespace MqttTopics
{
    //sending topic
    const char allData[]        = "light/send/data";

    //receiving topics
    const char modeControl[]    = "light/control/mode";
    const char brightness[]     = "light/control/brightness";
    const char autoBrightness[] = "light/control/auto_brightness";
}

#endif