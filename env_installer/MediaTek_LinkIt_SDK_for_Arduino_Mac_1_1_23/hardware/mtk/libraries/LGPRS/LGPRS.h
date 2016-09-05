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
#ifndef LGPRS_h
#define LGPRS_h

#include "Arduino.h"
#include "IPAddress.h"
#include "vmnwsetting.h"
#include "vmconn.h"

class LGPRSConnectContext;

//LGPRS Class.
class LGPRSClass
{
public:

	/* DOM-NOT_FOR_SDK-BEGIN */
    LGPRSClass();
    /* DOM-NOT_FOR_SDK-END */	

    // DESCRIPTION
    //  Sets up the Access Point Name (APN) used to connect to a GPRS network using data provided by your telecom operator.  
    // 
    // PARAMETERS
    //  apn: The char string, Access Point Name (APN) provided by the telecom operator.
    //  username: The char string, username provided by the telecom operator. Pass NULL if the telecom operator does not provide the username information.
    //  password: The char string, password provided by the telecom operator. Pass NULL if the telecom operator does not provide the password information.
    //
    // RETURN
    //  1: APN setup succeeded.
    //  0: APN setup failed.
    int attachGPRS(const char *apn, const char *username, const char *password);

    // DESCRIPTION
    //  Detects Access Point Name (APN) information from the SIM card and use it to connect to a GPRS network.
    // 
    // RETURN
    //  1: APN setup succeeded.
    //  0: APN setup failed.
    int attachGPRS();

    // DESCRIPTION
    //  Resolves the given hostname to an IP address.
    // 
    // PARAMETERS
    //  aHostname: The URL name string to be resolved.
    //  aResult: The IP address structure to store the returned IP address.
    // 
    // RETURNS
    //  1: The aIPAddrString is converted to an IP address successfully. 
    //  error code: Failed.
    int hostByName(const char* aHostname, IPAddress& aResult); 

    VMINT getAPN() const;
    friend class LGPRSServer;
    friend class LGPRSClient;
    
private:
    boolean m_simCardReady;
    boolean m_customAPN;
    static boolean gprsCheckSIM(void *userData);
};

extern LGPRSClass LGPRS;

#endif // #ifndef LGPRS_h