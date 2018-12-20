/*
 * app_gps.c
 *
 *  Created on: 18.12.2018
 *      Author: rex
 */

#include <stdio.h>
#include <string.h>

#include "main.h"

#include "app_gps.h"
#include "app_minmea.h"

SAppGPSData app_gps_data;

static void parse_buffer(const char * pBuffer);
static void handle_rmc(const char * pBuffer);
static void handle_gga(const char * pBuffer);
static void handle_gsv(const char * pBuffer);
static void handle_gsa(const char * pBuffer);
static void handle_gll(const char * pBuffer);
static void handle_vtg(const char * pBuffer);

static uint8_t gps_receive_buffer[128];
static uint8_t gps_parse_buffer[128];
static uint8_t gps_receive_length;
static uint8_t gps_receive_buffer_ready;

void app_gps_init()
{
	gps_receive_buffer_ready = 0;
	gps_receive_length = 0;

	app_gps_data.fix_valid = false;
	app_gps_data.satellites_tracked = 0;
	app_gps_data.latitude.value = 0;
	app_gps_data.latitude.scale = 0;
	app_gps_data.longitude.value = 0;
	app_gps_data.longitude.scale = 0;
	app_gps_data.altitude.value = 0;
	app_gps_data.altitude.scale = 0;
	app_gps_data.altitude_units = ' ';
	app_gps_data.height.value = 0;
	app_gps_data.height.scale = 0;
	app_gps_data.height_units = ' ';
	app_gps_data.hdop.value = 0;
	app_gps_data.hdop.scale = 0;
	app_gps_data.time.hours = 0;
	app_gps_data.time.minutes = 0;
	app_gps_data.time.seconds = 0;
	app_gps_data.time.microseconds = 0;
	app_gps_data.date.year = 0;
	app_gps_data.date.month = 0;
	app_gps_data.date.day = 0;
}

void app_gps_loop()
{
	if (gps_receive_buffer_ready == 1) {
		gps_receive_buffer_ready = 0;
//		printf("GPS:='%s'\n", gps_parse_buffer);

		parse_buffer((const char *)gps_parse_buffer);
	}
}

void app_gps_receive_char(uint8_t received_char)
{
	if (gps_receive_length < sizeof(gps_receive_buffer)) {
		if (received_char == '\n') {
			gps_receive_buffer[gps_receive_length] = '\0';
			strcpy((char *)gps_parse_buffer, (char *)gps_receive_buffer);
			gps_receive_length = 0;
			gps_receive_buffer_ready = 1;
		}
		else if (received_char != '\r') {
			gps_receive_buffer[gps_receive_length++] = received_char;
		}
	}
	else {
		gps_receive_length = 0;
	}
}

void parse_buffer(const char * pBuffer)
{
	enum minmea_sentence_id id = minmea_sentence_id(pBuffer, false);

    switch (id) {
        case MINMEA_SENTENCE_RMC:
        	handle_rmc(pBuffer);
        	break;

        case MINMEA_SENTENCE_GGA:
        	handle_gga(pBuffer);
        	break;

        case MINMEA_SENTENCE_GSV:
        	handle_gsv(pBuffer);
        	break;

        case MINMEA_SENTENCE_GSA:
        	handle_gsa(pBuffer);
        	break;

        case MINMEA_SENTENCE_GLL:
        	handle_gll(pBuffer);
        	break;

        case MINMEA_SENTENCE_VTG:
        	handle_vtg(pBuffer);
        	break;

        case MINMEA_UNKNOWN:
        	printf("Unknown Sentence\n");
        	break;

        case MINMEA_INVALID:
        	printf("Invalid Sentence rc = %d\n", mimea_last_result);
        	break;

        default:
        	printf("Sentence id = %d\n", id);
        	break;
    }

    if (app_gps_data.fix_valid) {
    	HAL_GPIO_WritePin(LED1_GPIO_Port, LED1_Pin, GPIO_PIN_SET);
    }
    else {
    	HAL_GPIO_WritePin(LED1_GPIO_Port, LED1_Pin, GPIO_PIN_RESET);
    }
}

void handle_rmc(const char * pBuffer)
{
	struct minmea_sentence_rmc frame;
	enum minmea_result result = minmea_parse_rmc(&frame, pBuffer);

	if (result == MINMEA_OK) {
		app_gps_data.time = frame.time;
		app_gps_data.date = frame.date;
		app_gps_data.latitude = frame.latitude;
		app_gps_data.longitude = frame.longitude;
		app_gps_data.fix_valid = frame.valid;
	}
	else {
//		printf("Error parsing RMC rc=%d\n", result);
	}
}

void handle_gga(const char * pBuffer)
{
    struct minmea_sentence_gga frame;
    enum minmea_result result = minmea_parse_gga(&frame, (char *)pBuffer);
    if (result == MINMEA_OK) {
		app_gps_data.time = frame.time;
		app_gps_data.latitude = frame.latitude;
		app_gps_data.longitude = frame.longitude;
		app_gps_data.fix_valid = frame.fix_quality > 0;
		app_gps_data.hdop = frame.hdop;
		app_gps_data.altitude = frame.altitude;
		app_gps_data.altitude_units = frame.altitude_units;
		app_gps_data.height = frame.height;
		app_gps_data.height_units = frame.height_units;
    }
    else {
//    	printf("Error parsing GGA rc=%d\n", result);
    }
}

void handle_gsv(const char * pBuffer)
{
    struct minmea_sentence_gsv frame;
    enum minmea_result result = minmea_parse_gsv(&frame, (char *)pBuffer);
    if (result == MINMEA_OK) {
#if 0
        printf("$GSV: message %d of %d\n", frame.msg_nr, frame.total_msgs);
        printf("$GSV: satellites in view: %d\n", frame.total_sats);
        for (int i = 0; i < 4; i++)
            printf("$GSV: sat nr %d, elevation: %d, azimuth: %d, snr: %d dbm\n",
                frame.sats[i].nr,
                frame.sats[i].elevation,
                frame.sats[i].azimuth,
                frame.sats[i].snr);
#endif
    }
    else {
//    	printf("Error parsing GSV rc=%d\n", result);
    }
}

void handle_gsa(const char * pBuffer)
{
    struct minmea_sentence_gsa frame;
    enum minmea_result result = minmea_parse_gsa(&frame, (char *)pBuffer);
    if (result == MINMEA_OK) {
		app_gps_data.hdop = frame.hdop;
		app_gps_data.pdop = frame.pdop;
		app_gps_data.vdop = frame.vdop;
    }
    else {
//    	printf("Error parsing GSA rc=%d\n", result);
    }
}

void handle_gll(const char * pBuffer)
{
    struct minmea_sentence_gll frame;
    enum minmea_result result = minmea_parse_gll(&frame, (char *)pBuffer);
    if (result == MINMEA_OK) {
    }
    else {
//    	printf("Error parsing GLL rc=%d\n", result);
    }
}

void handle_vtg(const char * pBuffer)
{
    struct minmea_sentence_vtg frame;
    enum minmea_result result = minmea_parse_vtg(&frame, (char *)pBuffer);
    if (result == MINMEA_OK) {
    }
    else {
//    	printf("Error parsing VTG rc=%d\n", result);
    }
}
