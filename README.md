Example Project using LoRaWAN with Rainbowrd
============================================

This is an example PlatformIO project to send data via RHF76 LoRa module.

### Installing PlatformIO on Windows (Bahasa Indonesia)

Check [this file](https://github.com/alwint3r/rainbowrd-rhf76-lorawan/blob/master/platformio_windows_installation_id.md) for PlatformIO  for Windows installation guide in Bahasa Indonesia.


### Before Compiling

Change these definition values with the correct ones. You can edit these values in [src/RainbowrdLoRaWAN.cpp](https://github.com/alwint3r/rainbowrd-rhf76-lorawan/blob/master/src/RainbowrdLoRaWAN.cpp) files.

```c++
#define DEVADDR ""
#define NWKSKEY ""
#define APPSKEY ""
```