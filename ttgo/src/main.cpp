#include <Arduino.h>

#include <Wire.h>
#include <SPI.h>
#include <Adafruit_Sensor.h>
#include <Adafruit_BME280.h>
#include "Adafruit_SI1145.h"
#include <BH1750.h>
#include "MPU9250.h"

// TTGO v2.1 - T3_v1.6
#define I2C_SDL 21
#define I2C_SCL 22

// Bosch BME280
#define SEALEVELPRESSURE_HPA (1039.00)
Adafruit_BME280 bme;

// UV Sensor
Adafruit_SI1145 uv = Adafruit_SI1145();

// light meter
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
  Serial.println(F("IMU Test begin"));

  // start communication with the BME280
  status = bme.begin(0x76);
  if (!status) {
      Serial.println("Could not find a valid BME280 sensor, check wiring!");
      while (1);
  }
  Serial.println(F("BME280 Test begin"));

  if (! uv.begin()) {
    Serial.println("Didn't find Si1145");
    while (1);
  }
  Serial.println(F("SI1145 Test begin"));

  Serial.println("Initialization completed!");
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

  // show BME280 sensor data
  Serial.print("Temperature = ");
  Serial.print(bme.readTemperature());
  Serial.println(" *C");

  Serial.print("Pressure = ");

  Serial.print(bme.readPressure() / 100.0F);
  Serial.println(" hPa");

  Serial.print("Approx. Altitude = ");
  Serial.print(bme.readAltitude(SEALEVELPRESSURE_HPA));
  Serial.println(" m");

  Serial.print("Humidity = ");
  Serial.print(bme.readHumidity());
  Serial.println(" %");

  // UV sensor
  Serial.print("Vis: "); Serial.println(uv.readVisible());
  Serial.print("IR: "); Serial.println(uv.readIR());
  
  // Uncomment if you have an IR LED attached to LED pin!
  //Serial.print("Prox: "); Serial.println(uv.readProx());

  float UVindex = uv.readUV();
  // the index is multiplied by 100 so to get the
  // integer index, divide by 100!
  UVindex /= 100.0;  
  Serial.print("UV: ");  Serial.println(UVindex);

  Serial.println();

  delay(1000);
}