#include <Arduino.h>

#include <Wire.h>
#include <BH1750.h>

// TTGO v2.1 - T3_v1.6
#define I2C_SDL 21
#define I2C_SCL 22

BH1750 lightMeter;


void setup(){

  Serial.begin(9600);
 
  // Initialize the I2C bus (BH1750 library doesn't do this automatically)
  Wire.begin(I2C_SDL, I2C_SCL);
  // On esp8266 you can select SCL and SDA pins using Wire.begin(D4, D3);

  lightMeter.begin();

  Serial.println(F("BH1750 Test begin"));
}


void loop() {
  float lux = lightMeter.readLightLevel();
  Serial.print("Light: ");
  Serial.print(lux);
  Serial.println(" lx");
  delay(1000);
}