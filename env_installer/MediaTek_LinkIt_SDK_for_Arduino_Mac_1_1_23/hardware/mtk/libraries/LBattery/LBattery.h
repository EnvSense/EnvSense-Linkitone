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


#ifndef _LBATTERY_H
#define _LBATTERY_H

#include "LTask.h"


// LBattery class interface. You can use this library to get battery information such as charging status and battery power level.
class LBatteryClass  : public _LTaskClass {

// Constructor / Destructor
public:
	LBatteryClass() { };

// Method
public:
	// DESCRIPTION
	//     Gets the battery power level. The return value includes 0, 33, 66, or 100 percent.
	// RETURNS
	//     Percentage of battery power level.
	int level();
	
	// DESCRIPTION
	//     Gets the battery charging status - charging or not charging.
	// RETURNS
	//     true: It's in charging state. 
	//		 false: It's not in charging state.
	boolean isCharging();

private:
	int m_level;
	boolean m_charging;
};

extern LBatteryClass LBattery;

#endif
