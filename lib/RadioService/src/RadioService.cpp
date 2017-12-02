#include "RadioService.h"

RadioService::RadioService(Stream* stream):
 stream(stream) {
 }

RadioService::~RadioService() {
    if (rhf76 != NULL) {
        delete rhf76;
        rhf76 = NULL;
    }

    if (stream != NULL) {
        delete stream;
        stream = NULL;
    }
}

void RadioService::begin(const char* devId, const char* nwkSKey, const char* appSKey) {
    this->devId = devId;
    this->nwkSKey = nwkSKey;
    this->appSKey = appSKey;

    rhf76 = new RHF76();
    rhf76->begin(stream);

    rhf76->reset();
    rhf76->setClassType(CLASS_A);
    rhf76->setDeviceMode(LWABP);
    rhf76->setDevAddr(devId);
    rhf76->setNwkSKey(nwkSKey);
    rhf76->setAppSKey(appSKey);
    rhf76->setUnconfirmedMessageRepeatTime(5);
    rhf76->setConfirmedMessageRetryTime(5);

    rhf76->getId(NULL);
    rhf76->getVersion(NULL);
    rhf76->getCurrentPort(NULL);

    rhf76->setDataRate(DR3, AU920);
    rhf76->setAdaptiveDataRate(true);
    rhf76->setTXPower(14);
    rhf76->setReceiveWindowFirst(true);
    rhf76->setReceiveWindowSecond(923.3, DR1);
}

bool RadioService::publishMessage(char* payload, size_t length) {
    return rhf76->publishHexMessage(payload, length);
}

