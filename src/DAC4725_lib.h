
#ifndef DAC4725_h
#define DAC4725_h
#include <Arduino.h>
#include <Wire.h>

#define DEFAULT_ADDRESS 0x61
typedef enum {
    DEFAULT_MODE = 0b01000000,//startd mode
    EEPROM_MODE = 0b01100000// mode with write to DAC eeprom
}MODE;
class DAC4725
{
    public:
        bool begin(uint16_t Vdd);
        bool begin(uint16_t Vdd, uint8_t address);
        bool begin(uint16_t Vdd, uint8_t address, MODE mode);
        void disconnect();
        bool checkConnect();
        uint16_t getAddress();
        void setVoltage(uint16_t mlVoltage);
        void setMode(MODE mode);
    private:
        uint8_t _address;
        uint16_t buffer[3];
        uint16_t _vdd;
        uint16_t _mlVoltage;
    /* data */
};
#endif
