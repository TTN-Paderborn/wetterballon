# Projekt Wetterballon für das TTGO LoRa Board

Das Projektverzeichnis beinhaltet den Quellcode für das Projekt "Wetterballon" des TTN Paderborn für das TTGO LoRa Board (TTGO v2.1 - T3_v1.6). Er kann mit Visual Studio Code + PlatformIO verwendet und kompiliert werden.

# Sensoren / Hardware

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
 * Micro SD-Karte (innen)

## Pins

Pin Mapping für den TTGO LoRa32 v2.1 - T3_v1.6.

I2C:
 * SDL - Pin 21
 * SCL - Pin 22

OneWire (DS18B20):
 * DQ - Pin 34
 * Pull-Up Widerstand (4k7) zwischen 3.3V und DQ

UART (GPS - wie TTGO T-Beam):
 * TX - Pin 23
 * RX - Pin 19

SD-Karte:
 * SD2 - Pin 12
 * SD3 (CS) - Pin 13
 * CMD (MOSI) - Pin 15
 * CLK (SCK) - Pin 14
 * SD0 (MISO) - Pin 2
 * SD1 - Pin 4

Batteriespannung:
 * ADC1 - Pin 35 (100k / 100k Spannungsteiler)

LoRa:
 * SCK - Pin 5
 * CS - Pin 18
 * MISO - Pin 19
 * MOSI - Pin 27
 * RST - EN
 * IRQ / DIO0 - Pin 26
 * DIO1 - Pin 33
 * DIO2 - Pin 32 / NC