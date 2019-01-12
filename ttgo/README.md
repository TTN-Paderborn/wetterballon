# Projekt Wetterballon für das TTGO LoRa Board

Das Projektverzeichnis beinhaltet den Quellcode für das Projekt "Wetterballon" des TTN Paderborn für das TTGO LoRa Board (TTGO v2.1 - T3_v1.6). Er kann mit Visual Studio Code + PlatformIO verwendet und kompiliert werden.

# Sensoren

I2C:
 * BMP280 - Temperatur und Luftdruck (innen)
 * BH1750 - Lichtintensität (außen)
 * SI1145 - UV Sensor (außen)
 * MPU-9250 - 9-DOF Gyroskop (innen)
 
OneWire:
 * DS18B20 - Temperatur (außen)

UART:
 * ublox NEO-6M - GPS Empfänger (innen)

SPI:
 * micro SD Karte (innen)
