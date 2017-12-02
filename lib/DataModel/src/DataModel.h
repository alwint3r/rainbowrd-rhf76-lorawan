#ifndef COMPONENT_DATA_MODEL_H
#define COMPONENT_DATA_MODEL_H

#include <Arduino.h>

class DataModel {
public:
    DataModel(size_t bufferSize = 256);
    virtual ~DataModel();

    size_t getBufferSize();
    uint8_t* getBuffer();
    void clearBuffer();

    template<typename T>
    size_t write(T value) {
        if ((sizeof(value) + writeLength) >= maxBufferSize || writeLength >= maxBufferSize) {
            return 0;
        }

        memcpy(buffer + writeLength, &value, sizeof(value));
        writeLength += sizeof(value);

        return sizeof(value);
    }

private:
    uint8_t* buffer;
    size_t writeLength;
    size_t maxBufferSize;
};

#endif
