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


#ifndef LBTSERVER_H
#define LBTSERVER_H

#include "LTask.h"
#include "LBT.h"



struct LBTServerBeginContext : BTBase
{
    void* name;
    boolean result;
    boolean is_set_pin;
    LBTServerBeginContext():
        name(NULL),
        result(false)
    {

    }
};

struct LBTServerAcceptContext : BTBase
{
    size_t time_out;
    boolean result;
    LBTAddress *address;

    LBTServerAcceptContext():
        time_out(20),
        result(false),
        address(NULL)
    {

    }
};

struct LBTServerGetHostDeviceInfoContext : BTBase
{
    LBTDeviceInfo* device_info;
    boolean result;

    LBTServerGetHostDeviceInfoContext():
        device_info(NULL),
        result(false)
    {

    }
};

struct LBTServerReadWriteContext : BTBase
{
    void *buf;
    VMINT len;
    VMINT lenProcessed;	// Number of bytes read or written.

	LBTServerReadWriteContext():
		buf(NULL),
		len(1),
		lenProcessed(0)
	{

	}
};


// LBTServer class interface.
class LBTServerClass  : public _LTaskClass,public Stream{
public:
	LBTRingBuffer *_rx_buffer;
	uint8_t _pincode_buffer[LBT_PIN_CODE_BUFFER_SIZE];
// Constructor
public:
	LBTServerClass(LBTRingBuffer* pRx_buffer);

// Method
public:

    // DESCRIPTION
    //    Initializes Bluetooth module and sets up a Bluetooth SPP server instance.
    // PARAMETERS
    //    name: The device name to set. 
    //    pinCode: Bluetooth 2.0 pincode, if you set it as a constant string, it will enable LinkIt One to communicate with a Bluetooth 2.0 device.
    // RETURNS
    //    true: Successful.
    //    false: Failed.
	// EXAMPLE
	// <code>
    // #include <LBTServer.h>
    //   
    // void setup()
    // {
    //   Serial.begin(9600);
    //   bool success = LBTServer.begin((uint8_t*)"LBTServer"); //bool success = LBTServer.begin((uint8_t*)"BTServer",(uint8_t*)"1234");
    //   if( !success )
    //   {
    //       Serial.println("Cannot begin Bluetooth Server successfully");
    //       // Do nothing.
    //       while(true);
    //   }
    //   else
    //   {
    //       Serial.println("Bluetooth Server begins successfully");
    //   }
    // }
    //  
    // void loop()
    // {
    //   
    // }
    // 
	// </code> 
    boolean begin(
           const uint8_t* name = NULL,   //[IN] The device name to set.
           const uint8_t* pinCode = NULL //[IN] The Bluetooth 2.0 pincode.
        );

    // DESCRIPTION
    //    Closes the corresponding SPP server instance and ends Bluetooth module.
    // RETURNS
    //    None.
	// EXAMPLE
	// <code>
    // #include <LBTServer.h>
    //   
    // void setup()
    // {
    //   Serial.begin(9600);
    //   bool success = LBTServer.begin();
    //   if( !success )
    //   {
    //       Serial.println("Cannot begin Bluetooth Server successfully");
    //       // Do nothing.
    //       while(true);
    //   }
    //   else
    //   {
    //       Serial.println("Bluetooth Server begins successfully");
    //   }
    //   
    //   LBTServer.end();
    // }
    //  
    // void loop()
    // {
    //   
    // }
	// </code> 
    void end(void);

    // DESCRIPTION
    //    Accepts a Bluetooth SPP client's connection request. 
    //    Returns as long as the connection is made or the request has reached timeout limit.
    // PARAMETERS
    //    time_out: The timeout for accepting connection.
    // RETURNS
    //    true: Successful.
    //    false: Failed.
	// EXAMPLE
	// <code>
    // #include <LBT.h>
    // #include <LBTServer.h>
    //   
    // void setup()
    // {
    //   Serial.begin(9600);
    //   bool success = LBTServer.begin();
    //   if( !success )
    //   {
    //       Serial.println("Cannot begin Bluetooth Server successfully");
    //       // Do nothing.
    //       while(true);
    //   }
    //   else
    //   {
    //       Serial.println("Bluetooth Server begins successfully");
    //   }
    //  
    //   // Waiting for SPP Client to connect.
    //   bool connected = LBTServer.accept(20);
    //  
    //   if( !connected )
    //   {
    //       Serial.println("No connection request yet");
    //       // Do nothing.
    //       while(true);
    //   }
    //   else
    //   {
    //       Serial.println("Connected");
    //   }
    // }
    //  
    // void loop()
    // {
    //  
    // }
	// </code> 
    boolean accept(
            size_t time_out = 20  //[IN] The Bluetooth SPP client connection request timeout length.
        );
        
    // DESCRIPTION
    //    Accepts Bluetooth SPP client's connection request from a specified Bluetooth address.
    //    Returns as long as the connection is made or the request reaches timeout.
    // PARAMETERS
    //    time_out: The timeout for accepting connection.
    //    MACAddr: The string format (const char *), for example: "12:34:56:ab:cd:ef".
    // RETURNS
    //    true: Successful.
    //    false: Failed.
	// EXAMPLE
	// <code>
    // #include <LBT.h>
    // #include <LBTServer.h>
    //   
    // void setup()
    // {
    //   Serial.begin(9600);
    //   bool success = LBTServer.begin();
    //   if( !success )
    //   {
    //       Serial.println("Cannot begin Bluetooth Server successfully");
    //       // Do nothing.
    //       while(true);
    //   }
    //   else
    //   {
    //       Serial.println("Bluetooth Server begins successfully");
    //   }
    //  
    //   // Waiting for a Bluetooth SPP Client to connect.
    //   bool connected = LBTServer.accept(20, "12:34:56:ab:cd:ef");
    //  
    //   if( !connected )
    //   {
    //       Serial.println("No connection request yet");
    //       // Do nothing.
    //       while(true);
    //   }
    //   else
    //   {
    //       Serial.println("Connected");
    //   }
    // }
    //  
    // void loop()
    // {
    //  
    // }
	// </code> 
    boolean accept(
            size_t time_out,    // [IN] timeout duration while waiting for SPP client's connection request
            const char *MACAddr // [IN] string format (const char *), the format is like "12:34:56:ab:cd:ef".
            );

    // DESCRIPTION
    //    Checks if any Bluetooth SPP client is connected.
    // RETURNS
    //    true: Yes.
    //    false: No.
	// EXAMPLE
	// <code>
    // #include <LBT.h>
    // #include <LBTServer.h>
    //   
    // void setup()
    // {
    //   Serial.begin(9600);
    //   bool success = LBTServer.begin();
    //   if( !success )
    //   {
    //       Serial.println("Cannot begin Bluetooth Server successfully");
    //       // Do nothing.
    //       while(true);
    //   }
    //   else
    //   {
    //       Serial.println("Bluetooth Server begins successfully");
    //   }
    //  
    // }
    //  
    // void loop()
    // {
    // ¡¡¡¡ if(!LBTServer.connected())
    //     {
    //        // waiting for Spp Client to connect
    //        bool connected = LBTServer.accept(20);
    //  
    //        if( !connected )
    //        {
    //            Serial.println("No connection request yet");
    //            // Do nothing.
    //            while(true);
    //        }
    //        else
    //        {
    //            Serial.println("Connected");
    //        }
    //     }
    //     else
    //     {
    //         char buffer[10];
    //         int read_size = LBTServer.read((uint8_t*)buffer, 10);
    //         if(read_size > 0)
    //         {
    //             Serial.print("size read: ");
    //             Serial.println(read_size);
    //             Serial.println(buffer);
    //         }
    //     }
    // }
	// </code> 
    boolean connected(void);

    // DESCRIPTION
    //    Gets scanned device information.
    // RETURNS
    //    true: Successful.
    //    false: Failed. Possible causes include unreasonable index or the device hasn't been scanned before.
	// EXAMPLE
	// <code>
	// #include <LBT.h>
    // #include <LBTServer.h>
    //  
    // void setup()
    // {
    //   Serial.begin(9600);
    //   bool success = LBTServer.begin("LBTServer");
    //   if( !success )
    //   {
    //       Serial.println("Cannot begin Bluetooth Server successfully");
    //       // Do nothing.
    //       while(true);
    //   }
    //   else
    //   {
    //       Serial.println("Bluetooth Server begins successfully");
    //       LBTDeviceInfo info = {0};
    //       bool success = LBTServer.getHostDeviceInfo(i, &info);
    //       if( success )
    //       {
    //           Serial.print("Device name:");
    //           Serial.println(info.name);
    //       }
    //   }
    // }
    //  
    // void loop()
    // {
    //   
    // }
	// </code> 
	boolean getHostDeviceInfo(
            LBTDeviceInfo* dev_info    // [OUT] Device information acquired.
        );

    // DESCRIPTION
    //    Reads data from a Bluetooth SPP client.
    // RETURNS
    //    Number of bytes read.
    //    0: No data to read.
	// EXAMPLE
	// <code>
    // #include <LBT.h>
    // #include <LBTServer.h>
    //  
    // void setup()
    // {
    //   Serial.begin(9600);
    //   bool success = LBTServer.begin();
    //   if( !success )
    //   {
    //       Serial.println("Cannot begin Bluetooth Server successfully");
    //       // Do nothing.
    //       while(true);
    //   }
    //   else
    //   {
    //       Serial.println("Bluetooth Server begins successfully");
    //   }
    //  
    //   // waiting for Bluetooth SPP client to connect.
    //   bool connected = LBTServer.accept(20);
    //  
    //   if( !connected )
    //   {
    //       Serial.println("No connection request yet");
    //       // Do nothing.
    //       while(true);
    //   }
    //   else
    //   {
    //       Serial.println("Connected");
    //   }
    // }
    //  
    // void loop()
    // {
    //     char buffer[10];
    //     int read_size = LBTServer.read((uint8_t*)buffer, 10);
    //     if(read_size > 0)
    //     {
    //         Serial.print("size read: ");
    //         Serial.println(read_size);
    //         Serial.println(buffer);
    //     }
    // }
	// </code> 

    int read(void);

    // DESCRIPTION
    //    Writes data to a Bluetooth SPP client.
    // RETURNS
    //    Number of bytes written.
    //    0: Write failed.
	// EXAMPLE
	// <code>
    // #include <LBT.h>
    // #include <LBTServer.h>
    //  
    // void setup()
    // {
    //   Serial.begin(9600);
    //   bool success = LBTServer.begin();
    //   if( !success )
    //   {
    //       Serial.println("Cannot begin Bluetooth Server successfully");
    //       // Do nothing.
    //       while(true);
    //   }
    //   else
    //   {
    //       Serial.println("Bluetooth Server begins successfully");
    //   }
    //  
    //   // waiting for Spp Client to connect
    //   bool connected = LBTServer.accept(20);
    //  
    //   if( !connected )
    //   {
    //       Serial.println("No connection request yet");
    //       // Do nothing.
    //       while(true);
    //   }
    //   else
    //   {
    //       Serial.println("Connected");
    //   }
    // }
    //  
    // void loop()
    // {
    //     char* buffer = "LinkIt BT Server";
    //     int write_size = LBTServer.write((uint8_t*)buffer, strlen(buffer));
    //     if(write_size > 0)
    //     {
    //         Serial.print("Size written: ");
    //         Serial.println(write_size);
    //     }
    // }
	// </code> 
    size_t write(
            const uint8_t* buf,    // [IN] The data to write.
            size_t size = 1        // [IN] The size of the buffer.
        );

 // Gets the number of bytes(characters) available for reading from the serial port.
 //
 // RETURNS
 // The numbers of bytes available to read.        
    int available(void);
    
 // Returns the next byte of incoming serial data without removing it from the 
 //  internal serial buffer.
 //
 // RETURNS
 // The first byte of incoming serial data available, -1 if no data is available.   
    int peek(void);
    
 //  Waits for the transmission of outgoing serial data to complete.
    void flush(void);
    
// Writes a character. 
//
// RETURNS
// 1: Write successfully.
// 0: Write failed.   
    size_t write(const uint8_t data  //[IN] The input character.
                );
                
    using Print::write;

    void post_signal_write();
    void post_signal_read();
private:
    int m_post_write;
    VM_SIGNAL_ID m_signal_write;
    int m_post_read;
    VM_SIGNAL_ID m_signal_read;
};

// The LBTServerClass object.
extern LBTServerClass LBTServer;

#endif //#ifndef LBTSERVER_H
