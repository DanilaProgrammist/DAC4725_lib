#include "DAC4725_lib.h"
DAC4725 DAC; //Class object
void setup() {
  // put your setup code here, to run once:
  DAC.begin(5070, 0x60);// Device init 5070 - Vdd voltage, 0x60 - address
  if(DAC.checkConnect()){ // Check device connect
    Serial.println("DAC connect");
  }
}
void loop() {
  // put your main code here, to run repeatedly:
  DAC.setVoltage(1000);//set voltage loop, parameter - millivolts
  delay(1000);
  DAC.setVoltage(1500);
  delay(1000);
  DAC.setVoltage(2000);
  delay(1000);
  DAC.setVoltage(2500);
  delay(1000);
  DAC.setVoltage(3000);
  delay(1000);
  DAC.setVoltage(3500);
  delay(1000);
  DAC.setVoltage(4000);
  delay(1000);
  DAC.setVoltage(4500);
  delay(1000);
  DAC.setVoltage(5000);
  delay(1000);
  
}
