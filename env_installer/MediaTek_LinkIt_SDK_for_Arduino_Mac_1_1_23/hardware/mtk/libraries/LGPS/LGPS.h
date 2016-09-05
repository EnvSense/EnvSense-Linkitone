/*
  Copyright (c) 2014 MediaTek Inc.  All right reserved.

  This library is free software; you can redistribute it and/or
  modify it under the terms of the GNU Lesser General Public
  License as published by the Free Software Foundation; either
  version 2.1 of the License..

  This library is distributed in the hope that it will be useful,
  but WITHOUT ANY WARRANTY; without even the implied warranty of
  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. 
   See the GNU Lesser General Public License for more details.
*/

#ifndef _LGPS_H
#define _LGPS_H

#include "LTask.h"

#define GPS_MAX_GPGGA_SENTENCE_LENGTH 100
#define GPS_MAX_GPGSA_SENTENCE_LENGTH 80
#define GPS_MAX_GPRMC_SENTENCE_LENGTH 100
#define GPS_MAX_GPVTG_SENTENCE_LENGTH 80
#define GPS_MAX_GPGSV_SENTENCE_LENGTH 400
#define GPS_MAX_GLGSV_SENTENCE_LENGTH 400
#define GPS_MAX_BDGSV_SENTENCE_LENGTH 400
#define GPS_MAX_BDGSA_SENTENCE_LENGTH 80
#define GPS_MAX_GLGSA_SENTENCE_LENGTH 80

// GPS sentence (NMEA) information.
typedef struct
{
    unsigned char  GPGGA[GPS_MAX_GPGGA_SENTENCE_LENGTH+1];   //  For example, $GPGGA,123519,4807.038,N,01131.000,E,1,08,0.9,545.4,M,46.9,M,,*47
    unsigned char  GPGSA[GPS_MAX_GPGSA_SENTENCE_LENGTH+1];   //  For example, $GPGSA,A,3,01,20,19,13,,,,,,,,,40.4,24.4,32.2*0A
    unsigned char  GPRMC[GPS_MAX_GPRMC_SENTENCE_LENGTH+1];   //  For example, $GPRMC,024813.640,A,3158.4608,N,11848.3737,E,10.05,324.27,150706,,,A*50
    unsigned char  GPVTG[GPS_MAX_GPVTG_SENTENCE_LENGTH+1];   //  For example, $GPVTG,89.68,T,,M,0.00,N,0.0,K*5F
    unsigned char  GPGSV[GPS_MAX_GPGSV_SENTENCE_LENGTH+1];   //  For example, $GPGSV,3,1,10,20,78,331,45,01,59,235,47,22,41,069,,13,32,252,45*70
    unsigned char  GLGSV[GPS_MAX_GLGSV_SENTENCE_LENGTH+1];   //  The GSV's GLONASS data.
    unsigned char  GLGSA[GPS_MAX_GLGSA_SENTENCE_LENGTH+1];   //  The GSA's GLONASS data
    unsigned char  BDGSV[GPS_MAX_BDGSV_SENTENCE_LENGTH+1];   //  The GSV's BEIDOU data.
    unsigned char  BDGSA[GPS_MAX_BDGSA_SENTENCE_LENGTH+1];   //  The GSA's BEIDOU data.
} gpsSentenceInfoStruct;

// The GPS mode.
typedef enum
{
    GPS_START_MODE_NULL,
    GPS_HOT_START,               // GPS selects this mode when it remembers its last calculated position and the last recorded satellites is still in view. If you are at same location when the GPS was turned off, the GPS is capable of positioning in the shortest time.
    GPS_WARM_START,           // GPS selects this mode when it remembers its last calculated position but the last recorded satellites is not in view. In this mode the GPS takes more time to locate the satellites and position.
    GPS_COLD_START,             // GPS selects this mode when it only has the current time. It takes longer time to locate the GPS information.
    GPS_FULL_START,              // GPS selects this mode when it has no information. A full restart takes the longest to process.
    GPS_START_TYPE_END
}gpsModeEnum;

/* The GPS type */
typedef enum
{
    GPS_ONLY,		/* GPS ONLY. */
    GPS_GLONASS,	/* GPS and GLONASS. */
    GPS_BEIDOU,		/* GPS and BEIDOU. */
    GPS_TYPE_END
} gpsTypeEnum;

// The LGPS class interface. You can use the object LGPS to get GPS data using this library. The basic flow of controlling GPS are as follows:
class LGPSClass  : public _LTaskClass {

// The constructor/destructor.
public:
	LGPSClass() { };

// Method
public:
	 // DESCRIPTION
	 //     Turns on the GPS device.
	 // EXAMPLE
	 //  <code>
	 //  #include <LGPS.h>
	 //  gpsSentenceInfoStruct info;
        //  void setup()
	 //  {
	 //     LGPS.powerOn();
	 //     delay(500);
	 //  }
	 //  void loop()
	//  {
	//     LGPS.getData(&info);
	//     delay(2000);
	//  }
	//  </code>
	void powerOn(
			gpsTypeEnum type = GPS_GLONASS    // [IN] Please refer the enum gpsTypeEnum. The default is GPS and GLONASS.
		);

	 // DESCRIPTION
	 //     Turns off the GPS.
	 //     Note: Turning off GPS when GPS data isn't required can save power.
	void powerOff(void);

	 // DESCRIPTION
	 //    Sets up GPS start mode. This interface is used for testing only and it's not needed in normal usage.
	void setMode(
			gpsModeEnum mode    // [IN] Please refer the enum gpsModeEnum.
		);

	 // DESCRIPTION
	 //    Get the GPS data.
	void getData(
			gpsSentenceInfoStruct* info    // [OUT] Please refer the struct gpsSentenceInfoStruct.
			);
	
public:
	void setData(gpsSentenceInfoStruct* info);

private:
	gpsSentenceInfoStruct m_info;

};

extern LGPSClass LGPS;

#endif
