#include "DataModel.h"

DataModel::DataModel(size_t bufferSize):
 writeLength(0),
 maxBufferSize(bufferSize) {
    assert(bufferSize >= 0);

    buffer = (uint8_t*)malloc(maxBufferSize);

    assert(buffer != NULL);
 }

DataModel::~DataModel() {
    delete buffer;
}

void DataModel::clearBuffer() {
    memset(buffer, 0, maxBufferSize);
    writeLength  = 0;
}

uint8_t* DataModel::getBuffer() {
    return buffer;
}

size_t DataModel::getBufferSize() {
    return writeLength;
}