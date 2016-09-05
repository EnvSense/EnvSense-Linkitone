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



#ifndef _LINKITDateTime_h
#define _LINKITDateTime_h

//The datetimeInfo structure.
typedef struct
{
	int year; //The year.
	int mon;  //The month, beginning from 1.
	int day;  //The day, beginning from 1.
	int hour; //The hour, using 24-hour format. 
	int min;  //The minute.
	int sec;  //The second.
}datetimeInfo;

// LDatetimeClass defines system time related functions.
class LDateTimeClass
{
    
// Constructor / Destructor  
public:
	LDateTimeClass();

// Method
public:

	// Returns the current system time.
	//
	// RETURNS
	// 0: Successful.
	// -1: Failed.
	//
	// EXAMPLE
	//	<code>
	//	#include <LDateTime.h>
	//  datetimeInfo t;
	//  unsigned int rtc;
	//	void setup()
	//  {
	//    
	//  }
	//	void loop()
	//  {
	//      LDateTime.getTime(&t);
	//      LDateTime.getRtc(&rtc);
	//      delay(1000);
	//  }
	//	</code> 
	int getTime(
		datetimeInfo *time	// [OUT] The datetime information structure.
		); 
	
	// Set system time 
	//
	// RETURNS
	// 0: Successful.
	// -1: Failed.
	//
	// EXAMPLE
	//	<code>
	//	#include <LDateTime.h>
	//  datetimeInfo t;
	//	void setup()
	//  {
	//    
	//  }
	//	void loop()
	//  {
	//      LDateTime.getTime(&t);
	//      LDateTime.setTime(&t);
	//      delay(1000);
	//  }
	//	</code> 
	int setTime(
		datetimeInfo *time	// [IN] The datetime information structure.
		); 

	// Gets the time since the Epoch (00:00:00 UTC, January 1, 1970),
	// measured in seconds.
	//
	// RETURNS
	// 0: Successful.
	// -1: Failed.
	//
	// EXAMPLE
	//	<code>
	//	#include <LDateTime.h>
	//  datetimeInfo t;
	//  unsigned int rtc;
	//	void setup()
	//  {
	//    
	//  }
	//	void loop()
	//  {
	//      LDateTime.getTime(&t);
	//      LDateTime.getRtc(&rtc);
	//      delay(1000);
	//  }
	//	</code> 
	int getRtc(
		unsigned int *rtc	// [OUT] Points to the time in seconds.
		);
};

//LDateTime object
extern LDateTimeClass LDateTime;

#endif

