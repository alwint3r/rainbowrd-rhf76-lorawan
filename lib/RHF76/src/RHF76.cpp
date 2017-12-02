#include "RHF76.h"

RHF76::RHF76() {
    rxBuffer = (char*)malloc(BUFFER_MAX_LENGTH);
    buffer = (char*)malloc(BUFFER_MAX_LENGTH);
    isSleeping = false;
}

RHF76::~RHF76() {
    delete buffer;
    buffer = NULL;

    delete rxBuffer;
    rxBuffer = NULL;
}

void RHF76::begin(Stream* serial) {
    stream = serial;
    sendCommand("AT+UART=TIMEOUT,0\r\n", NULL, 500);
}

void RHF76::setDevAddr(const char* devAddr) {
    clearBuffer();
    sprintf(buffer, "AT+ID=DevAddr,\"%s\"\r\n", devAddr);
    sendCommand(buffer, NULL, 100);
}

void RHF76::setDevEUI(const char* devEUI) {
    clearBuffer();
    sprintf(buffer, "AT+ID=DevEui,\"%s\"\r\n", devEUI);
    sendCommand(buffer, NULL, 100);
}

void RHF76::setAppEUI(const char* appEUI) {
    clearBuffer();
    sprintf(buffer, "AT+ID=AppEui,\"%s\"\r\n", appEUI);
    sendCommand(buffer, NULL, 100);
}

void RHF76::getId(char* response, int timeout) {
    sendCommand("AT+ID\r\n", response, timeout);
}

void RHF76::getVersion(char* response, int timeout) {
    sendCommand("AT+VER\r\n", response, timeout);
}

void RHF76::setNwkSKey(const char* nwkSKey) {
    clearBuffer();
    sprintf(buffer, "AT+KEY=NWKSKEY,\"%s\"\r\n", nwkSKey);
    sendCommand(buffer, NULL, 500);
}

void RHF76::setAppSKey(const char* appSKey) {
    clearBuffer();
    sprintf(buffer, "AT+KEY=APPSKEY,\"%s\"\r\n", appSKey);
    sendCommand(buffer, NULL, 500);
}

void RHF76::setAppKey(const char* appKey) {
    clearBuffer();
    sprintf(buffer, "AT+KEY=APPKEY,\"%s\"\r\n", appKey);
    sendCommand(buffer, NULL, 500);
}

bool RHF76::publishMessage(char* message, int timeout) {
    char response[BUFFER_MAX_LENGTH] = {0};

    clearBuffer();
    sprintf(buffer, "AT+MSG=\"%s\"\r\n", message);
    sendCommand(buffer, response, timeout);

    return (strstr(response, "+MSG: Done") != NULL);
}

bool RHF76::publishConfirmedMessage(char* message, int timeout) {
    char response[BUFFER_MAX_LENGTH] = {0};
    
    clearBuffer();
    sprintf(buffer, "AT+CMSG=\"%s\"\r\n", message);
    sendCommand(buffer, response, timeout);

    return (strstr(response, "+CMSG: Done"));
}

bool RHF76::publishHexMessage(char* message, size_t length, int timeout) {
    char response[BUFFER_MAX_LENGTH] = {0};
    memset(response, 0, BUFFER_MAX_LENGTH);

    char placeholder[2] = {0};
    String input = "";
    input.reserve(BUFFER_MAX_LENGTH);
    input += "AT+MSGHEX=\"";

    for (size_t i = 0; i < length; i++) {
        if (length - i == 1) {
            sprintf(placeholder, "%02x", message[i]);
        } else {
            sprintf(placeholder, "%02x ", message[i]);
        }
        input += placeholder;
    }

    input += "\"\r\n";

    sendCommand((char*)input.c_str(), response, timeout);
    return (strstr(response, "+MSGHEX: Done") != NULL);
}

bool RHF76::publishConfirmedHexMessage(char* message, size_t length, int timeout) {
    char response[BUFFER_MAX_LENGTH] = {0};
    memset(response, 0, BUFFER_MAX_LENGTH);

    char placeholder[2] = {0};
    String input = "";
    input.reserve(BUFFER_MAX_LENGTH);
    input += "AT+CMSGHEX=\"";

    for (size_t i = 0; i < length; i++) {
        if (length - i == 1) {
            sprintf(placeholder, "%02x", message[i]);
        } else {
            sprintf(placeholder, "%02x ", message[i]);
        }
        
        input += placeholder;
    }

    input += "\"\r\n";

    sendCommand((char*)input.c_str(), response, timeout);
    return (strstr(response, "+CMSGHEX: Done") != NULL);
}

void RHF76::setDataRate(rhf76_data_rate dataRate, rhf76_physical_type physicalType) {
    clearBuffer();
    
    switch (physicalType) {
        case EU434:
            sendCommand("AT+DR=EU433\r\n", NULL, 500);
            break;
        case EU868:
            sendCommand("AT+DR=EU868\r\n", NULL, 500);
            break;
        case US915:
            sendCommand("AT+DR=US915\r\n", NULL, 500);
            break;
        case AU920:
            sendCommand("AT+DR=AU920\r\n", NULL, 500);
            break;
        default:
            return;
    }

    delay(DEFAULT_TIMEWAIT);
    sprintf(buffer, "AT+DR=%d\r\n", dataRate);
    sendCommand(buffer, NULL, 500);
}

void RHF76::setAdaptiveDataRate(bool enable) {
    clearBuffer();

    if (enable) {
        sendCommand("AT+ADR=ON\r\n", NULL, 500);
    } else {
        sendCommand("AT+ADR=OFF\r\n", NULL, 500);
    }
}

void RHF76::setReceiveWindowFirst(bool enable) {
    if (enable) {
        sendCommand("AT+RXWIN1=ON\r\n", NULL, 1500);
    } else {
        sendCommand("AT+RXWIN1=OFF\r\n", NULL, 1500);
    }
}

void RHF76::setReceiveWindowFirst(unsigned char channel, float frequency) {
    clearBuffer();
    if (channel > 16) {
        channel = 16;
    }

    short decimalPoint = (short)(frequency * 10) % 10;
    sprintf(buffer, "AT+RXWIN1=%d,%d.%d\r\n", channel, (short)frequency, decimalPoint);
    sendCommand(buffer, NULL, 1500);
}

void RHF76::setReceiveWindowSecond(float frequency, rhf76_data_rate dataRate) {
    clearBuffer();
    sprintf(buffer, "AT+RXWIN2=%d.%d,%d\r\n", (short)frequency, short(frequency * 10) % 10, dataRate);
    sendCommand(buffer, NULL, 1500);
}

void RHF76::setReceiveWindowSecond(float frequency, rhf76_spreading_factor spreadingFactor, rhf76_band_width bandwidth) {
    clearBuffer();
    sprintf(buffer, "AT+RXWIN2=%d.%d,%d,%d\r\n", (short)frequency, short(frequency * 10) % 10, spreadingFactor, bandwidth);
    sendCommand(buffer, NULL, 1500);
}

void RHF76::setTXPower(int power) {
    clearBuffer();
    sprintf(buffer, "AT+POWER=%d\r\n", power);
    sendCommand(buffer, NULL, 500);
}

void RHF76::setDeviceMode(rhf76_device_mode deviceMode) {
    clearBuffer();
    if (deviceMode == LWABP) {
        sendCommand("AT+MODE=LWABP\r\n", NULL, 500);
    } else if (deviceMode == LWOTAA) {
        sendCommand("AT+MODE=LWOTAA\r\n", NULL, 500);
    }
}

void RHF76::setClassType(rhf76_class_type classType) {
    if (classType == CLASS_A) {
        sendCommand("AT+CLASS=A\r\n", NULL, 500);
    } else if(classType == CLASS_C) {
        sendCommand("AT+CLASS=C\r\n", NULL, 500);
    }
}

void RHF76::setReceiveWindowDelay(rhf76_window_delay windowDelay, unsigned short delayTime) {
    clearBuffer();
    switch (windowDelay) {
        case RECEIVE_DELAY1:
            sprintf(buffer, "AT+DELAY=RX1,%d\r\n", delayTime);
            break;
        case RECEIVE_DELAY2:
            sprintf(buffer, "AT+DELAY=RX2,%d\r\n", delayTime);
            break;
        case JOIN_ACCEPT_DELAY1:
            sprintf(buffer, "AT+DELAY=JRX1,%d\r\n", delayTime);
            break;
        case JOIN_ACCEPT_DELAY2:
            sprintf(buffer, "AT+DELAY=JRX2,%d\r\n", delayTime);
            break;
        default:
            return;
    }

    sendCommand(buffer, NULL, 2000);
}

void RHF76::setPort(int port) {
    clearBuffer();
    sprintf(buffer, "AT+PORT=%d\r\n", port);
    sendCommand(buffer, NULL, 500);
}

void RHF76::getCurrentPort(char* response, int timeout) {
    clearBuffer();
    sendCommand("AT+PORT=?\r\n", response, timeout);
}

void RHF76::reset() {
    sendCommand("AT+RESET\r\n", NULL, 3000);
}

void RHF76::setUnconfirmedMessageRepeatTime(int time) {
    clearBuffer();

    if (time > 15) {
        time = 15;
    } else if (time == 0) {
        time = 1;
    }

    sprintf(buffer, "AT+REPT=%d\r\n", time);
    sendCommand(buffer, NULL, 1000);
}

void RHF76::setConfirmedMessageRetryTime(int time) {
    clearBuffer();

    if (time > 15) {
        time = 15;
    } else if (time == 0) {
        time = 1;
    }

    sprintf(buffer, "AT+RETRY=%d\r\n", time);
    sendCommand(buffer, NULL, 1000);
}

short RHF76::receivePacket(char* packet, short length, short* rssi) {
    char* ptr;
    short number = 0;

    ptr = strstr(rxBuffer, "RSSI ");
    if (ptr) {
        *rssi = atoi(ptr + 5);
    } else {
        *rssi = -255;
    }

    ptr = strstr(rxBuffer, "RX: \"");
    if (ptr) {
        ptr += 5;
        for (short i = 0; ; i++) {
            char temp[2] = {0};
            unsigned char tmp = 0, result = 0;

            temp[0] = *(ptr + i * 3);
            temp[1] = *(ptr + i * 3 + 1);

            for (unsigned char j = 0; j < 2; j++) {
                if ((temp[j] >= '0') && (temp[j] <= '9')) {
                    tmp = temp[j] - '0';
                } else if ((temp[j] >= 'A') && (temp[j] <= 'F')) {
                    tmp = temp[j] - 'A' + 10;
                } else if ((temp[j] >= 'a') && (temp[j] <= 'f')) {
                    tmp = temp[j] - 'a' + 10;
                }

                result = result * 16 + tmp;
            }

            if (i < length) {
                packet[i] = result;
            }

            if (*(ptr + i * 3 + 3) == '\"' && *(ptr + i + 3 + 4) == '\r' && *(ptr + i * 3 + 5) == '\n') {
                number = i + 1;
                break;
            }
        }
    }

    ptr = strstr(rxBuffer, "MACCMD: \"");
    if (ptr) {
        packet[0] = 'M';
        packet[1] = 'A';
        packet[2] = 'C';
        packet[3] = 'C';
        packet[4] = 'M';
        packet[5] = 'D';
        packet[6] = ':';

        ptr += 9;
        for (short i = 0; ; i++) {
            char temp[2] = {0};
            unsigned char tmp = 0, result = 0;

            temp[0] = *(ptr + i * 3);
            temp[1] = *(ptr + i * 3 + 1);

            for (unsigned char j = 0; j < 2; j ++) {
                if ((temp[j] >= '0') && (temp[j] <= '9')) {
                    tmp = temp[j] - '0';
                } else if ((temp[j] >= 'A') && (temp[j] <= 'F')) {
                    tmp = temp[j] - 'A' + 10;
                } else if ((temp[j] >= 'a') && (temp[j] <= 'f')) {
                    tmp = temp[j] - 'a' + 10;
                }

                result = result * 16 + tmp;
            }

            if ((i + 7) < length) {
                buffer[i + 7] = result;
            }

            if(*(ptr + i * 3 + 3) == '\"' && *(ptr + i * 3 + 4) == '\r' && *(ptr + i * 3 + 5) == '\n') {
                number = i + 1 + 7;
                break;
            }
        }
    }

    memset(rxBuffer, 0, BUFFER_MAX_LENGTH);
    return number;
}

int RHF76::sendCommand(char* command, char* responseBuffer, int timeout) {
    while (stream->available()) {
        stream->read();
    }
    
    ESP_LOGI(TAG, ">cmd: %s", command);

    stream->print(command);
    delay(DEFAULT_TIMEWAIT);

    char response[BUFFER_MAX_LENGTH] = {0};
    memset(response, 0, BUFFER_MAX_LENGTH);

    int readLength = getResponse(response, BUFFER_MAX_LENGTH, timeout);
    if (readLength == 0) {
        ESP_LOGE(TAG, "No response!");
    } else {
        ESP_LOGI(TAG, "Response: %s", response);
    }

    if (responseBuffer != NULL) {
        memcpy(responseBuffer, response, readLength);
    }

    return readLength;
}

int RHF76::getResponse(char* target, int length, int timeout) {
    int start = millis();
    int i = 0;

    while (true) {
        while (stream->available() > 0) {
            target[i++] = stream->read();
        }

        if ((millis() - start) >= timeout) {
            return i;
        }
    }

    return 0;
}

void RHF76::factoryDefault() {
    sendCommand("AT+FDEFAULT=RISINGHF", NULL, 2000);
}

void RHF76::sleep() {
    sendCommand("AT+LOWPOWER\r\n", NULL, 1000);
}

void RHF76::wakeup() {
    // send any character to wake up
    sendCommand("A", NULL, 1000);
}

void RHF76::clearBuffer() {
    memset(buffer, 0, BUFFER_MAX_LENGTH);
}

void RHF76::startDFU() {
    clearBuffer();
    sendCommand("AT+DFU=ON\r\n", NULL, 2000);
}
