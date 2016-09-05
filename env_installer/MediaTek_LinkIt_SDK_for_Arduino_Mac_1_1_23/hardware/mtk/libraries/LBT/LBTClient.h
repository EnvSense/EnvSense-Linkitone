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

#ifndef LBTCLIENT_H
#define LBTCLIENT_H

#include "LTask.h"
#include "LBT.h"

struct LBTClientBeginContext : BTBase
{
    void* name;
    boolean result;
    LBTClientBeginContext():
        name(NULL),
        result(false)
    {

    }
};

struct LBTClientConnectContext : BTBase
{
    LBTAddress* address;
    boolean result;
    boolean is_set_pin;
    LBTClientConnectContext():
        address(NULL),
        result(false)
    {

    }
};

struct LBTClientScanContext : BTBase
{
    size_t time_out;
    size_t number;

    LBTClientScanContext():
        time_out(20),
        number(0)
    {

    }
};

struct LBTClientGetDeviceInfoContext : BTBase
{
    size_t index;
    LBTDeviceInfo* device_info;
    boolean result;

    LBTClientGetDeviceInfoContext():
        index(0),
        device_info(NULL),
        result(false)
    {

    }
};

struct LBTClientReadWriteContext : BTBase
{
    void *buf;
    VMUINT len;
    VMINT lenProcessed;	// Number of bytes read or written.

	LBTClientReadWriteContext():
		buf(NULL),
		len(1),
		lenProcessed(0)
	{

	}
};


// LBTClient class interface
class LBTClientClass  : public _LTaskClass, public Stream {

public:
	LBTRingBuffer *_rx_buffer;
	uint8_t _pincode_buffer[LBT_PIN_CODE_BUFFER_SIZE];
// Constructor
public:
	LBTClientClass(LBTRingBuffer* pRx_buffer);

// Method
public:

    // DESCRIPTION
    //    Initializes Bluetooth module and sets up a Bluetooth SPP client instance.
    // RETURNS
    //    true: Successful.
    //    false: Failed.
	// EXAMPLE
	// <code>
    // #include <LBTClient.h>
    //   
    // void setup()
    // {
    //   Serial.begin(9600);
    //   bool success = LBTClient.begin();
    //   if( !success )
    //   {
    //       Serial.println("Cannot begin Bluetooth Client successfully");
    //       // Do nothing.
    //       while(true);
    //   }
    //   else 
    //   {
    //       Serial.println("Bluetooth Client begins successfully");
    //   }
    // }
    //  
    // void loop()
    // {
    //   
    // }
	// </code> 
    boolean begin(void);

    // DESCRIPTION
    //    Closes corresponding Bluetooth SPP client instance and ends Bluetooth module.
    // RETURNS
    //    None.
	// EXAMPLE
	// <code>
    // #include <LBTClient.h>
    //       
    // void setup()
    // {
    //   Serial.begin(9600);
    //   bool success = LBTClient.begin();
    //   if( !success )
    //   {
    //       Serial.println("Cannot begin Bluetooth Client successfully");
    //       // Do nothing.
    //       while(true);
    //   } 
    //   else
    //   {
    //       Serial.println("Bluetooth Client begins successfully");
    //   }
    //  
    //   LBTClient.end();
    // }
    //  
    // void loop()
    // {
    //   
    // }
	// </code> 
    void end(void);

    // DESCRIPTION
    //    Connects Bluetooth SPP server with Bluetooth address.
    // PARAMETERS
    //    address: Refer to LBTAddress type
    //    pinCode: The Bluetooth 2.0 pincode. If you set it as a constant string, it will enable LinkIt One to communicate with a Bluetooth 2.0 device.
    // RETURNS
    //    true: Successful.
    //    false: Failed.
	// EXAMPLE
	// <code>
    // #include <LBT.h>
    // #include <LBTClient.h>
    //   
    // void setup()
    // {
    //   Serial.begin(9600);
    //   bool success = LBTClient.begin();
    //   if( !success )
    //   {
    //       Serial.println("Cannot begin Bluetooth Client successfully");
    //       // Do nothing.
    //       while(true);
    //   }
    //   else
    //   {
    //       Serial.println("Bluetooth Client begins successfully");
    //       // start scan, at most scan 15 seconds
    //       int num = LBTClient.scan(15);
    //  
    //       if(num > 0)
    //       {
    //           LBTDeviceInfo info = {0};
    //           if( LBTClient.getDeviceInfo(0, &info) )
    //           {
    //               bool conn_result = LBTClient.connect(info.address);//bool conn_result = LBTClient.connect(info.address, "1234");
    //               if( !conn_result )
    //               {
    //                   Serial.println("Cannot connect to SPP Server successfully");
    //                   // Do nothing.
    //                   while(true);
    //               }
    //               else
    //               {
    //                  Serial.println("Connect to SPP Server successfully");
    //               }
    //           }
    //           else
    //           {
    //               Serial.println("Device index not correct");
    //               // Do nothing.
    //               while(true);
    //           }
    //       } 
    //   }
    // }
	// </code> 
    boolean connect(
            LBTAddress &address,  //[IN] The Bluetooth address to connect with.
            const char* pinCode = NULL //[IN] Bluetooth 2.0 set pincode.
        );

    // DESCRIPTION
    //    Connects a Bluetooth SPP server with a Bluetooth address using a specified Bluetooth address.
    // PARAMETERS
    //    MACAddr: String format (const char *), for example: "12:34:56:ab:cd:ef".
    //    pinCode: The Bluetooth 2.0 pincode. If you set it as a constant string, it will enable LinkIt One to communicate with a Bluetooth 2.0 device.
    // RETURNS
    //    true: Successful.
    //    false: Failed.
	// EXAMPLE
	// <code>
    // #include <LBT.h>
    // #include <LBTClient.h>
    //   
    // void setup()
    // {
    //   Serial.begin(9600);
    //   bool success = LBTClient.begin();
    //   if( !success )
    //   {
    //       Serial.println("Cannot begin Bluetooth Client successfully");
    //       // Do nothing.
    //       while(true);
    //   }
    //   else
    //   {
    //       Serial.println("Bluetooth Client begins successfully");
    //       // start scan, at most scan 15 seconds
    //       int num = LBTClient.scan(15);
    //  
    //       if(num > 0)
    //       {
    //           LBTDeviceInfo info = {0};
    //           bool conn_result = LBTClient.connect("12:34:56:ab:cd:ef");//bool conn_result = LBTClient.connect("12:34:56:ab:cd:ef", "1234");
    //           if( !conn_result )
    //           {
    //               Serial.println("Cannot connect to SPP Server successfully");
    //               // Do nothing.
    //               while(true);
    //           }
    //           else
    //           {
    //              Serial.println("Connect to SPP Server successfully");
    //           }
    //       } 
    //   }
    // }
	// </code> 
    boolean connect(
            const char *MACAddr,  //[IN] The Bluetooth address to connect with.
            const char* pinCode = NULL //[IN] The Bluetooth 2.0 set pincode.
        );
    // DESCRIPTION
    //    Checks if any Bluetooth SPP server is connected.
    // RETURNS
    //    true: Yes.
    //    false: No.
	// EXAMPLE
	// <code>
    // #include <LBT.h>
    // #include <LBTClient.h>
    //      
    // LBTDeviceInfo info = {0};
    //  
    // void setup()
    // {
    //   Serial.begin(9600);
    //   bool success = LBTClient.begin();
    //   if( !success )
    //   {
    //       Serial.println("Cannot begin Bluetooth Client successfully");
    //       // Do nothing.
    //       while(true);
    //   }
    //   else
    //   {
    //       Serial.println("Bluetooth Client begins successfully");
    //       // start scan, at most scan 15 seconds
    //       int num = LBTClient.scan(15);
    //  
    //       if(num > 0)
    //       {
    //           if( LBTClient.getDeviceInfo(0, &info) )
    //           {
    //               Serial.println("Get device info of interested server");
    //           }
    //           else
    //           {
    //               Serial.println("Device index not correct");
    //               // Do nothing.
    //               while(true);
    //           }
    //       }
    //   }
    // }
	// </code> 
    boolean connected(void);

    // DESCRIPTION
    //    Scans for nearby Bluetooth devices, up to 10 devices can be scanned.
    // RETURNS
    //    Number of devices scanned.
	// EXAMPLE
	// <code>
    // #include <LBTClient.h>
    //   
    // void setup()
    // {
    //   Serial.begin(9600);
    //   bool success = LBTClient.begin();
    //   if( !success )
    //   {
    //       Serial.println("Cannot begin Bluetooth Client successfully");
    //       // Do nothing.
    //       while(true);
    //   }
    //   else
    //   {
    //       Serial.println("Bluetooth Client begins successfully");
    //       // start scan, at most scan 15 seconds
    //       int num = LBTClient.scan(15);
    //       Serial.print("Scanned Device number:");
    //       Serial.println(num);
    //   }
    // }
    //  
    // void loop()
    // {
    //   
    // }
	// </code> 
    int scan(
            size_t time_out = 20   // [IN] timeout duration in seconds of the scan process
        );

    // DESCRIPTION
    //    Gets scanned device information.
    // RETURNS
    //    true: Successful.
    //    false: Failed. Possible causes include unreasonable index number or the device hasn't been scanned before.
	// EXAMPLE
	// <code>
    // #include <LBT.h>
    // #include <LBTClient.h>
    //   
    // void setup()
    // {
    //   Serial.begin(9600);
    //   bool success = LBTClient.begin();
    //   if( !success )
    //   {
    //       Serial.println("Cannot begin Bluetooth Client successfully");
    //       // Do nothing.
    //       while(true);
    //   }
    //   else
    //   {
    //       Serial.println("Bluetooth Client begins successfully");
    //       // start scan, at most scan 15 seconds
    //       int num = LBTClient.scan(15);
    //       Serial.print("Scanned Device number:");
    //       Serial.println(num);
    //  
    //       for(int i = 0; i < num; ++i)
    //       {
    //           LBTDeviceInfo info = {0};
    //           bool success = LBTClient.getDeviceInfo(i, &info);
    //           if( success )
    //           {
    //               Serial.print("Device");
    //               Serial.println(i);
    //               Serial.print("   name:");
    //               Serial.println(info.name);
    //           }        
    //       }
    //   }
    // }
    //  
    // void loop()
    // {
    //   
    // }
	// </code> 
	boolean getDeviceInfo(
            size_t index,    // [IN] The device index of the scanned result.
            LBTDeviceInfo* dev_info    // [OUT] The acquired device information.
        );

    // DESCRIPTION
    //    Reads data from the Bluetooth SPP server.
    // RETURNS
    //    Number of bytes read.
    //    0: No data to read.
	// EXAMPLE
	// <code>
    // #include <LBT.h>
    // #include <LBTClient.h>
    //   
    // void setup()
    // {
    //   Serial.begin(9600);
    //   bool success = LBTClient.begin();
    //   if( !success )
    //   {
    //       Serial.println("Cannot begin Bluetooth Client successfully");
    //       // Do nothing.
    //       while(true);
    //   }
    //   else
    //   {
    //       Serial.println("Bluetooth Client begins successfully");
    //       // start scan, at most scan 15 seconds
    //       int num = LBTClient.scan(15);
    //  
    //       if(num > 0)
    //       {
    //           LBTDeviceInfo info = {0};
    //           if( LBTClient.getDeviceInfo(0, &info) )
    //           {
    //               bool conn_result = LBTClient.connect(info.address);
    //               if( !conn_result )
    //               {
    //                   Serial.println("Cannot connect to SPP Server successfully");
    //                   // Do nothing.
    //                   while(true);
    //               }
    //               else
    //               {
    //                  Serial.println("Connect to SPP Server successfully");
    //               }
    //           }
    //           else
    //           {
    //               Serial.println("Device index not correct");
    //               // Do nothing.
    //               while(true);
    //           }
    //       }
    //   }
    // }
    //  
    // void loop()
    // {
    //     char buffer[10];
    //     int read_size = LBTClient.read((uint8_t*)buffer, 10);
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
    //    Writes data to a Bluetooth SPP server.
    // RETURNS
    //    Number of bytes written.
    //    0: No buffer to write.
	// EXAMPLE
	// <code>
    // #include <LBT.h>
    // #include <LBTClient.h>
    //   
    // void setup()
    // {
    //   Serial.begin(9600);
    //   bool success = LBTClient.begin();
    //   if( !success )
    //   {
    //       Serial.println("Cannot begin Bluetooth Client successfully");
    //       // Do nothing.
    //       while(true);
    //   }
    //   else
    //   {
    //       Serial.println("Bluetooth Client begins successfully");
    //       // start scan, at most scan 15 seconds
    //       int num = LBTClient.scan(15);
    //  
    //       if(num > 0)
    //       {
    //           LBTDeviceInfo info = {0};
    //           if( LBTClient.getDeviceInfo(0, &info) )
    //           {
    //               bool conn_result = LBTClient.connect(info.address);
    //               if( !conn_result )
    //               {
    //                   Serial.println("Cannot connect to SPP Server successfully");
    //                   // Do nothing.
    //                   while(true);
    //               }
    //               else
    //               {
    //                  Serial.println("Connect to SPP Server successfully");
    //               }
    //           }
    //           else
    //           {
    //               Serial.println("Device index not correct");
    //               // Do nothing.
    //               while(true);
    //           }
    //       }
    //   }
    // }
    //  
    // void loop()
    // {
    //     char* buffer = "LinkIt BT Client";
    //     int write_size = LBTClient.write((uint8_t*)buffer, strlen(write_buf));
    //     if(write_size > 0)
    //     {
    //         Serial.print("write read: ");
    //         Serial.println(write_size);
    //     }
    //}
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
 // The first byte of incoming serial data available.
 // -1: No data is available.
    int peek(void);
    
 //  Waits for the transmission of outgoing serial data to complete.
    void flush(void);
    
// Writes a character. 
//
// RETURNS
// 1: Write successfully.
// 0: Write failed.
    size_t write(const uint8_t data  //[IN] Input character.
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

// The LBTClientClass object.
extern LBTClientClass LBTClient;

#endif //#ifndef LBTCLIENT_H
