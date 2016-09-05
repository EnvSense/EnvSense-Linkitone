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



#ifndef _LINKITGSM_h
#define _LINKITGSM_h

#include <Arduino.h>
#include "LTask.h"

#define LGSM_MAX_SMS_LEN    500

// LinkIt SMS support class.
class LSMSClass : public Stream
{
// Constructor / Destructor    
public:
    LSMSClass(void);
    ~LSMSClass(void);

// Method
public:
    using Print::write; // Pull in write(str) and write(buf, size) from Print.

	// DESCRIPTION
	//  This function is the step two of sending an SMS, which is to write one byte at a time into the SMS content.
  //  You can also use print() to write one string into SMS content at a time.
	// RETURNS
	//  1: Successful. 
	//  0: Failed.
    size_t write(
        uint8_t c   // [IN] The byte to write.
    );

	// DESCRIPTION
	//  This function is the step one of sending an SMS, which is to input the destination number.
	// RETURNS
	//  1: Successful. 
	//  0: Failed.
    int beginSMS(
        const char* to  // [IN] The SMS destination number. 
    );

	// DESCRIPTION
	//  This function checks if the SMS module is ready or not.
	// RETURNS
	//  1: Ready. 
	//  0: Not ready. 
    int ready();

	// DESCRIPTION
	//  This function is the last step of sending an SMS, which is to confirm and send out the SMS.
	// RETURNS
	//  1: Send successfully. 
	//  0: Send failed.
    int endSMS();

	// DESCRIPTION
	//  This function checks if there are any unread SMS.
	// RETURNS
	//  1: There are unread SMS. 
	//  0: There are no unread SMS.
    int available();

	// DESCRIPTION
	//  This function returns the source number of the unread SMS.
 	// RETURNS
	//  Length of the returning SMS number. 
  //  0: There is no unread SMS.
  //  The required input size without filling the input array, if the size of input array is too small. Please call the function again with a larger array.
    int remoteNumber(
        char* number,   // [OUT] The array to save SMS number.
        int nlength     // [IN] The size of the array.
    ); 

	// DESCRIPTION
	//  Reads the content of the unread SMS, one byte at a time.
  //  The difference between read() and peek() is that read() moves the cursor but peak() does not.
	// RETURNS
	//  One byte of SMS content. 
	//  -1: It has reached the end of SMS.
    int read();

	// DESCRIPTION
	//  Reads the content of the unread SMS, one byte at a time without moving the cursor.
  //  Repeatedly calling peek() will return the same result.
	// RETURNS
	//  One byte of SMS content. 
	//  -1: It has reached the end of SMS.
    int peek();

	// DESCRIPTION
	//  Deletes the unread SMS.
  //  This function requires an unread SMS checked by available().
    void flush();

private:

    // The write SMS for a member.
    String _toNumber;   // The maximum length for TP-DA/OA should be 12 octets (14 characters).
    String _toContent;

    // The read SMS for a member.
    int _msgId;         // The current SMS ID.
    char *_msgNumber;   // The number data of current SMS.
    char *_msgContent;  // The content data of current SMS.

    int _msgPos;        // The current position of content (for sequential read/peak).

    
};

extern LSMSClass LSMS;

enum LVoiceCall_voiceCall_st { IDLE_CALL, CALLING, RECEIVINGCALL, TALKING};

// LinkIt Voice call support class
class LVoiceCallClass : public _LTaskClass
{
// Constructor / Destructor    
public:
    LVoiceCallClass(void);
    ~LVoiceCallClass(void);

// Method
public:

	// DESCRIPTION
	//  Checks if the previous voice operation has executed successfully.
	// RETURNS
	//  1: Previous operation executed successfully. 
	//  0: Failed.
    int ready();

	// DESCRIPTION
	//  Makes a voice call to a specified number.
	// RETURNS
	//  1: Callout succesfully. 
	//  0: Failed.
    int voiceCall(
        const char* to,  // [IN] The number to call.
        unsigned long timeout=30000 // [IN] The timeout count.
    );

	// DESCRIPTION
	//  Checks status of the voice call.
	// RETURNS
	//  0: Idle_call. 
	//  1: Calling. 
	//  2: Receiving a call. 
	//  3: Talking.
    char getVoiceCallStatus(void);

	// DESCRIPTION
	//  Accepts an incoming voice call.
	// RETURNS
	//  1: Answer successfully. 
	//  0: Answer failed.
    int answerCall(void);


	// DESCRIPTION
	//  Retrieves the calling number.
 	// RETURNS
	//  1: Retrieve successfully. 
	//  0: Retrieve failed.
    int retrieveCallingNumber(
        char* number,   // [OUT] The array to save call number.
        int nlength     // [IN] The size of the array.
    ); 

	// DESCRIPTION
	//  Hang up an established call or during incoming rings. 
	// RETURNS
	//  1: Hang up successfully. 
	//  0: Hang up failed.
    int hangCall(void);

private:

    
};

extern LVoiceCallClass LVoiceCall;

#undef LINKITGSM_DEBUG

#ifdef LINKITGSM_DEBUG
#define LGSMLOG(x) Serial.println(x)
#else
#define LGSMLOG(x)  
#endif

#endif

