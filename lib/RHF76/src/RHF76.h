#ifndef RHF76_LORAWAN_H
#define RHF76_LORAWAN_H

#include <Arduino.h>
#include <esp_log.h>

#define BUFFER_MAX_LENGTH 1024
#define DEFAULT_TIMEWAIT 100
#define MAC_COMMAND_FLAG "MACCMD:"

enum rhf76_class_type {
    CLASS_A = 0,
    CLASS_C
};

enum rhf76_physical_type {
    EU434 = 0,
    EU868,
    US915,
    AU920
};

enum rhf76_device_mode {
    LWABP = 0,
    LWOTAA,
    TEST
};

enum rhf76_otaa_join_cmd {
    JOIN = 0,
    FORCE
};

enum rhf76_window_delay {
    RECEIVE_DELAY1 = 0,
    RECEIVE_DELAY2,
    JOIN_ACCEPT_DELAY1,
    JOIN_ACCEPT_DELAY2
};

enum rhf76_band_width {
    BW125 = 125,
    BW250 = 250,
    BW500 = 500
};

enum rhf76_spreading_factor {
    SF12 = 12,
    SF11 = 11,
    SF10 = 10,
    SF9 = 9,
    SF8 = 8,
    SF7 = 7
};

enum rhf76_data_rate {
    DR0 = 0,
    DR1,
    DR2,
    DR3,
    DR4,
    DR5,
    DR6,
    DR7,
    DR8,
    DR9,
    DR10,
    DR11,
    DR12,
    DR13,
    DR14,
    DR15
};

class RHF76 {
public:
    RHF76();
    ~RHF76();

    void begin(Stream* serial);

    // EUIs
    void setDevAddr(const char* devAddr);
    void setDevEUI(const char* devEUI);
    void setAppEUI(const char* appEUI);

    // Keys
    void setNwkSKey(const char* nwkSKey);
    void setAppSKey(const char* appSKey);
    void setAppKey(const char* appKey);

    // Info
    void getId(char* response, int timeout = 500);
    void getVersion(char* response, int timeout = 500);
    void getCurrentPort(char* response, int timeout = 500);

    bool publishMessage(char* message, int timeout = 2 * 8000);
    bool publishHexMessage(char* message, size_t length, int timeout = 2 * 8000);
    bool publishConfirmedMessage(char* message, int timeout = 4 * 8000);
    bool publishConfirmedHexMessage(char* message, size_t length, int timeout = 4 * 8000);

    short receivePacket(char* packet, short length, short* rssi);

    void setPort(int port);
    void setDataRate(rhf76_data_rate dataRate, rhf76_physical_type physicalType);
    void setAdaptiveDataRate(bool enable);
    void setTXPower(int power);
    void setReceiveWindowFirst(bool enable);
    void setReceiveWindowFirst(unsigned char channel, float frequency);
    void setReceiveWindowSecond(float frequency, rhf76_data_rate dataRate);
    void setReceiveWindowSecond(float frequency, rhf76_spreading_factor spreadingFactor, rhf76_band_width bandwidth);
    void setReceiveWindowDelay(rhf76_window_delay windowDelay, unsigned short delayTime);
    void setDeviceMode(rhf76_device_mode deviceMode);
    void setClassType(rhf76_class_type classType);
    void setUnconfirmedMessageRepeatTime(int time);
    void setConfirmedMessageRetryTime(int time);

    // module functionality
    void sleep();
    void wakeup();
    void reset();
    void factoryDefault();
    void startDFU();
private:
    int sendCommand(char* command, char* responseBuffer = NULL, int timeout = 5000);
    int getResponse(char* target, int length, int timeout);
    void clearBuffer();
    char* rxBuffer;
    char* buffer;
    Stream* stream;

    bool isSleeping;

    const char* TAG = "RHF76";
};

#endif