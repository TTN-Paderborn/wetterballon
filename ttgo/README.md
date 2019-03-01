# Projekt Wetterballon für das TTGO LoRa Board

Das Projektverzeichnis beinhaltet den Quellcode für das Projekt "Wetterballon" des TTN Paderborn für das TTGO LoRa Board (TTGO v2.1 - T3_v1.6). Er kann mit Visual Studio Code + PlatformIO verwendet und kompiliert werden.

# Sensoren

I2C:
 * BME280 - Temperatur und Luftdruck (innen)
 * BH1750 - Lichtintensität (außen)
 * SI1145 - UV Sensor (außen)
 * MPU-9250 - 9-DOF Gyroskop (innen)
 
OneWire:
 * DS18B20 - Temperatur (außen)

UART:
 * ublox NEO-6M - GPS Empfänger (innen)

SPI:
 * micro SD Karte (innen)

## Pins

Pin Mapping für den TTGO LoRa32 v2.1 - T3_v1.6.

I2C:
 * SDL - Pin 21
 * SCL - Pin 22

OneWire (DS18B20):
 * DQ - Pin 13
 * Pull-Up Widerstand (4k7) zwischen 3.3V und DQ

UART (GPS - wie TTGO T-Beam):
 * TX - Pin 12
 * RX - Pin 15