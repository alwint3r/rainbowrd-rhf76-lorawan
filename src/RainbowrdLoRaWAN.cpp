#include <Arduino.h>
#include <RadioService.h>
#include <HardwareSerial.h>
#include <DataModel.h>

/** Replace these values with the correct ones! */
#define DEVADDR ""
#define NWKSKEY ""
#define APPSKEY ""

HardwareSerial loraSerial(2);
RadioService radioSvc(&loraSerial);
DataModel loraPayload;

static unsigned long lastPublished = 0;

void setup() {
    Serial.begin(9600);

    /** Initialize LoRa module serial driver and communication handler */
    loraSerial.begin(9600, SERIAL_8N1, 13, 14);
    radioSvc.begin(DEVADDR, NWKSKEY, APPSKEY);
}

void loop() {
    if (millis() - lastPublished >= 30 * 1000) {
        lastPublished = millis();

        /** Write data to buffer.
         * NOTE: use actual data from measurement result
         * instead of this dummy data!
         */
        int32_t temperature = 2648;
        int32_t humidity = 5802;

        loraPayload.clearBuffer();
        loraPayload.write(temperature);
        loraPayload.write(humidity);

        /** Publish data from buffer */
        if (radioSvc.publishMessage((char*)loraPayload.getBuffer(), loraPayload.getBufferSize())) {
            Serial.println("Successfully transmitted message");
        } else {
            Serial.println("Failed to transmit message");
        }
    }
}
