
#include "DAC4725_lib.h"
bool DAC4725::begin(uint16_t Vdd){
  _vdd = Vdd;
  _address = DEFAULT_ADDRESS;
  buffer[0] = DEFAULT_MODE;
  Wire.begin();
  Wire.beginTransmission(_address);
}
bool DAC4725::begin(uint16_t Vdd, uint8_t address){
  _address = address;
  buffer[0] = DEFAULT_MODE;
  _vdd = Vdd;
  Wire.begin();
  Wire.beginTransmission(_address);
}
bool DAC4725::begin(uint16_t Vdd, uint8_t address, MODE mode){
  _address = address;
  buffer[0] = mode;
  _vdd = Vdd;
  Wire.begin();
  Wire.beginTransmission(_address);
}
bool DAC4725::checkConnect(){
    byte error, address;
    int nDevices;
    Serial.begin(9600);
    Serial.println("Scanning...");
 
    nDevices = 0;
    for(address = 8; address < 127; address++ ){
        Wire.beginTransmission(address);
        error = Wire.endTransmission();
 
        if (error == 0){
            Serial.println("I2C device found");
            return true;
            nDevices++;
        }
        else if (error==4) {
            return false;
        } 
    }
 
}

uint16_t DAC4725::getAddress(){
    byte error, address;
    int nDevices;
 
    Serial.println("Scanning...");
 
    nDevices = 0;
    for(address = 8; address < 127; address++ ){
        Wire.beginTransmission(address);
        error = Wire.endTransmission();
 
        if (error == 0){
            //Serial.print("I2C device found at address 0x");
            if (address<16)
                Serial.print("0");
                Serial.print(address,HEX);
                Serial.println(" !");
                return true;
                nDevices++;
        }
        // else if (error==4) {
        //     //Serial.print("Unknow error at address 0x");
        //     if (address<16)
        //         Serial.print("0");
        //     Serial.println(address,HEX);
        // } 
    }
    if (nDevices == 0)
        //Serial.println("No I2C devices found\n");
        return false;
    else
        //Serial.println("done\n");
    Wire.begin();
    Wire.beginTransmission(_address);
    return address;
 
}
void DAC4725::setVoltage(uint16_t mlVoltage){
    Wire.beginTransmission(_address);
  _mlVoltage = mlVoltage;
  uint16_t DAC_in;
  long prometeus;
  prometeus = (long)_mlVoltage * (long)4095;
  DAC_in = prometeus / (long)_vdd;
  buffer[1] = DAC_in >> 4;
  buffer[2] = DAC_in << 4;
  Wire.write(buffer[0]);
  Wire.write(buffer[1]);
  Wire.write(buffer[2]);
  Wire.endTransmission(_address);
}
void DAC4725::setMode(MODE mode){
  buffer[0] = mode;
}
void DAC4725::disconnect(){
  Wire.endTransmission(_address);
}