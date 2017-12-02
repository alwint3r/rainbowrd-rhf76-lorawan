#ifndef RADIO_SERVICE_RHF76_H
#define RADIO_SERVICE_RHF76_H

#include <Arduino.h>
#include <RHF76.h>
#include <Stream.h>

class RadioService {
public:
    RadioService(Stream* stream);
    ~RadioService();

    void begin(const char* devId, const char* nwkSKey, const char* appSKey);
    bool publishMessage(char* payload, size_t length);

private:
    const char* devId;
    const char* nwkSKey;
    const char* appSKey;
    Stream* stream;
    RHF76* rhf76;
};

#endif