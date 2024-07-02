
#include <DAC4725_lib.h>
/* ============ Setup & begin ============ */
bool DAC4725::begin(uint16_t Vdd){ //parameter 1  - supply votage 
  _vdd = Vdd;
  _address = DEFAULT_ADDRESS;
  buffer[0] = DEFAULT_MODE;
  Wire.begin();
  Wire.beginTransmission(_address);
}
bool DAC4725::begin(uint16_t Vdd, uint8_t address){//parameter 1  - supply votage, 2 - device address
  _address = address;
  buffer[0] = DEFAULT_MODE;
  _vdd = Vdd;
  Wire.begin();
  Wire.beginTransmission(_address);
}
bool DAC4725::begin(uint16_t Vdd, uint8_t address, MODE mode){//parameter 1  - supply votage, 2 - device address, 3 - device mode(standart, eeprom)
  _address = address;
  buffer[0] = mode;
  _vdd = Vdd;
  Wire.begin();
  Wire.beginTransmission(_address);
}
/* ============ Connection and check ============ */
bool DAC4725::checkConnect(){//check device connect, WARNING !!! you need to disconnect another I2C devices
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

uint16_t DAC4725::getAddress(){//get DAC I2C address , WARNING !!! you need to disconnect another I2C devices
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
/* ============ Set voltage & mode ============ */
void DAC4725::setVoltage(uint16_t mlVoltage){//set DAC output voltage. Parameter 1 - output voltage 
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
void DAC4725::setMode(MODE mode){//set new DAC mode
  buffer[0] = mode;
}
void DAC4725::disconnect(){//disconnect DAC from the I2C
  Wire.endTransmission(_address);
}
