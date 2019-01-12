#include <Arduino.h>

#include <Wire.h>
#include <BH1750.h>
#include "MPU9250.h"

// TTGO v2.1 - T3_v1.6
#define I2C_SDL 21
#define I2C_SCL 22

BH1750 lightMeter;

// an MPU9250 object with the MPU-9250 sensor on I2C bus 0 with address 0x68
MPU9250 IMU(Wire,0x68);
int status;

void setup()
{
  Serial.begin(9600);
 
  // Initialize the I2C bus (BH1750 library doesn't do this automatically)
  Wire.begin(I2C_SDL, I2C_SCL);

  if (!lightMeter.begin())
  {
    Serial.println(F("BH1750 initialisation unsuccessful"));
    while(1) {}
  }
  Serial.println(F("BH1750 Test begin"));

  // start communication with IMU 
  status = IMU.begin();
  if (status < 0) {
    Serial.println(F("IMU initialization unsuccessful"));
    Serial.print(F("Status: "));
    Serial.println(status);
    while(1) {}
  }
  Serial.println(F("BH1750 Test begin"));
}

void loop() 
{
  // get light sensor data
  float lux = lightMeter.readLightLevel();
  Serial.print(F("Light: "));
  Serial.print(lux);
  Serial.println(F(" lx"));
  delay(1000);

  // get gyroscope data
  IMU.readSensor();
  Serial.print(IMU.getAccelX_mss(),6);
  Serial.print("\t");
  Serial.print(IMU.getAccelY_mss(),6);
  Serial.print("\t");
  Serial.print(IMU.getAccelZ_mss(),6);
  Serial.print("\t");
  Serial.print(IMU.getGyroX_rads(),6);
  Serial.print("\t");
  Serial.print(IMU.getGyroY_rads(),6);
  Serial.print("\t");
  Serial.print(IMU.getGyroZ_rads(),6);
  Serial.print("\t");
  Serial.print(IMU.getMagX_uT(),6);
  Serial.print("\t");
  Serial.print(IMU.getMagY_uT(),6);
  Serial.print("\t");
  Serial.print(IMU.getMagZ_uT(),6);
  Serial.print("\t");
  Serial.println(IMU.getTemperature_C(),6);
  delay(1000);
}