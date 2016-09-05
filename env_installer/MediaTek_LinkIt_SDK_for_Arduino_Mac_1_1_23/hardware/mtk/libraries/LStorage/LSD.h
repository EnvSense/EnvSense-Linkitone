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



#ifndef _LINKITSD_h
#define _LINKITSD_h

#include "LStorage.h"

// LinkIt SD support class.
class LSDClass : public LDrive
{
/* DOM-NOT_FOR_SDK-BEGIN */	
// Constructor / Destructor    
public:
    LSDClass(void);
    ~LSDClass(void);
/* DOM-NOT_FOR_SDK-END */	

	// DESCRIPTION
	//  Initializes the SD module.
	// RETURNS
	//  true: Successfully.
	//  false: Failed.
    virtual boolean begin();
    
};

// The global LSD object. Use it to manipulate the SD.
extern LSDClass LSD;

#endif

