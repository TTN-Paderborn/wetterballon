/*
 * app_gps.h
 *
 *  Created on: 18.12.2018
 *      Author: rex
 */

#ifndef INC_APP_GPS_H_
#define INC_APP_GPS_H_

#include "app_minmea.h"

extern void app_gps_init();
extern void app_gps_loop();
extern void app_gps_receive_char(uint8_t received_char);

typedef struct app_gps_data {
    struct minmea_time time;
    struct minmea_date date;
    struct minmea_float latitude;
    struct minmea_float longitude;
    bool fix_valid;
    int satellites_tracked;
    struct minmea_float altitude;
    char altitude_units;
    struct minmea_float height;
    char height_units;
    struct minmea_float hdop;
    struct minmea_float vdop;
    struct minmea_float pdop;
} SAppGPSData;

extern SAppGPSData app_gps_data;

#endif /* INC_APP_GPS_H_ */
