/*
 * TwoWire.h - TWI/I2C library for Arduino Due
 * Copyright (c) 2011 Cristian Maglie <c.maglie@bug.st>.
 * All rights reserved.
 *
 * This library is free software; you can redistribute it and/or
 * modify it under the terms of the GNU Lesser General Public
 * License as published by the Free Software Foundation; either
 * version 2.1 of the License, or (at your option) any later version.
 *
 * This library is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 * Lesser General Public License for more details.
 *
 * You should have received a copy of the GNU Lesser General Public
 * License along with this library; if not, write to the Free Software
 * Foundation, Inc., 51 Franklin St, Fifth Floor, Boston, MA  02110-1301  USA
 *
 * Modified 20 Aug 2014 by MediaTek Inc.
 */

#ifndef TwoWire_h
#define TwoWire_h
// Include Atmel CMSIS driver
//#include <include/twi.h>

#include "Stream.h"
#include "variant.h"

#define BUFFER_LENGTH 8


// TwoWire class interface enables LinkIt ONE to connect to other devices through I2C/TWI bus. It occupies pin D18 (SDA) as the serial data wire and pin D19 (SCL) as the serial clock wire.
class TwoWire : public Stream 
{
// Constructor / Destructor
public:
    TwoWire();

// Method
public:
    //DESCRIPTION
    // Sets up the host address for I2C communication. LinkIt ONE supports void TwoWire:begin(void),
    // which means the I2C bus is joined as a host. 
    // To use the Wire library, under normal conditions, this function must be called and called only once.
    //EXAMPLE
    // <code>
    // #include <Wire.h>
    // void setup()
    // {
    //     Wire.begin();
    // }
    // void loop()
    // {
    // 
    // }
    // </code> 
	void begin();
/* DOM-NOT_FOR_SDK-BEGIN */	
    // DESCRIPTION
    //  Initiates the wire library and joins the I2C bus as a master. This function should normally
    //  be called only once.
    void begin(
        uint8_t address		// [IN] The 7-bit address of the device.
        );				

    // DESCRIPTION
    //  Initiates the wire library and joins the I2C bus as a master. This function should normally
    //  be called only once.
    void begin(
        int	address			// [IN] The 7-bit address of the device.
        );
/* DOM-NOT_FOR_SDK-END */	

    //DESCRIPTION
    // Enables the communication with the slave at an assigned address. After that,
    // the data are written by using write() and transmitted by using endTransmission().
    //EXAMPLE
    // <code>
    // #include <Wire.h>
    // void setup()
    // {
    //     Wire.begin();
    // }
    // void loop()
    // {
    //     Wire.beginTransmission(0x27);
    //     Wire.write('a');
    //     Wire.endTransmission();
    // }
    // </code> 
    void beginTransmission(
        uint8_t	 address	// [IN] The address of the assigned slave, a 7-bit address, from 0 to 127.
        );	
		

    //DESCRIPTION
    // Enables the communication with the slave at an assigned address. After that,
    // the data are written by using write()and transmitted by using endTransmission().
	void beginTransmission(
		int	address				// [IN] The address of the assigned slave, a 7-bit address, from 0 to 127.
		);
	

    // DESCRIPTION
    // Ends the communication with the slave assigned by beginTransmission() and 
    // transmits the data buffered by write() to the slave.
    // RETURNS
    // Number of bytes of data sent to slave(unit:byte).
    // EXAMPLE
    // <code>
    // #include <Wire.h>
    // void setup()
    // {
    //     Wire.begin();
    // }
    // void loop()
    // {
    //     Wire.beginTransmission(0x27);
    //     Wire.write('a');
    //     Wire.endTransmission();
    // }
    // </code> 
	uint8_t endTransmission(void);
/* DOM-NOT_FOR_SDK-BEGIN */	
    // DESCRIPTION
    // Ends a transmission to a slave device that was started by beginTransmission()and transmits the bytes
    // that were queued by using write().
    // RETURNS
    // The number of bytes that were sent to the slave device.
    // SEE ALSO
    // beginTransmission
	uint8_t endTransmission(
		uint8_t sendStop
		);
/* DOM-NOT_FOR_SDK-END */	  

//DESCRIPTION
// Enables a master to request data from a slave and get data by using
// available() and read()functions.
//RETURNS
// Number of bytes returned from a slave.
//EXAMPLE
// <code>
// #include <Wire.h>
// void setup()
// {
//     Wire.begin();
// }
// void loop()
// {
//     Wire.requestFrom(0x27,6);
//     while((Wire.available()))
//     {
//         int c = Wire.read();
//     }
// }
// </code> 
	uint8_t requestFrom(
		uint8_t address,		// [IN]The address:7-bit slave address.
		uint8_t quantity		// [IN]The quantity:number of bytes requested.
		);
	
    // DESCRIPTION
    // Enables a master to request data from a slave and get data by using
    // available() and read()functions.
    // RETURNS
    // Number of bytes returned from a slave.
	uint8_t requestFrom(
		int address,		// [IN]The address: the 7-bit slave address.
		int quantity		// [IN]The quantity: number of bytes requested.
		);
/* DOM-NOT_FOR_SDK-BEGIN */		
    // DESCRIPTION
    // Enables the master to request bytes from a slave device. The bytes may be retrieved by using the
    // available() and read() functions.
    // RETURNS
    //  The number of bytes returned from a slave device.
	uint8_t requestFrom(
		uint8_t address,		// Parameter 1.
		uint8_t quantity,		// Parameter 2.
		uint8_t sendStop		// Parameter 3.
		);
	
    // DESCRIPTION
    // Enables the master to request bytes from a slave device. The bytes may be retrieved by using the
    // available() and read() functions.
    // RETURNS
    //  The number of bytes returned from a slave device.
	uint8_t requestFrom(
		int address,		// Parameter 1.
		int quantity,		// Parameter 2.
		int	sendStop		// Parameter 3.
		);
 /* DOM-NOT_FOR_SDK-END */	

    //DESCRIPTION
    // This function writes data into the queue and is called between functions beginTransmission()and endTransmission().
    //RETURNS
    // Number of bytes of data written into the queue.
    //EXAMPLE
    // <code>
    // #include <Wire.h>
    // void setup()
    // {
    //     Wire.begin();
    // }
    // void loop()
    // {
    //     Wire.beginTransmission(0x27);
    //     Wire.write('a');
    //     Wire.endTransmission();
    // }
    // </code> 
	virtual size_t write(
		uint8_t	data// [IN]A byte of data to be written.
		);
	

    //DESCRIPTION
    // This function writes data into the queue and is called between functions beginTransmission()and endTransmission().
    //RETURNS
    // Number of bytes of data written into the queue.
    //EXAMPLE
    // <code>
    // #include <Wire.h>
    // uint8_t data[3]={0,1,2};
    // void setup()
    // {
    //     Wire.begin();
    // }
    // void loop()
    // {
    //     Wire.beginTransmission(0x27);
    //     Wire.write(data,3);
    //     Wire.endTransmission();
    // }
    // </code> 

	virtual size_t write(
		const uint8_t * data,	//[IN]The address to be written data.
		size_t quantity		//[IN]The number of bytes of data written into the queue.
		);
	

    //DESCRIPTION
    // Returns the number of bytes the read() function can read.
    //RETURNS
    // Number of bytes that can be read.
    //EXAMPLE
    // <code>
    // #include <Wire.h>
    // void setup()
    // {
    //     Wire.begin();
    // }
    // void loop()
    // {
    //     Wire.requestFrom(0x27,6);
    //     while((Wire.available()))
    //     {
    //         int c = Wire.read();
    //     }
    // }
    // </code> 
	virtual int available(void);
	

    //DESCRIPTION
    // Reads a byte of data which are sent from master to slave or from 
    // slave to master. The master makes requests by using requestFrom().
    //RETURNS
    // The byte of data read.
    //EXAMPLE
    // <code>
    // #include <Wire.h>
    // void setup()
    // {
    //     Wire.begin();
    // }
    // void loop()
    // {
    //     Wire.requestFrom(0x27,6);
    //     while((Wire.available()))
    //     {
    //         int c = Wire.read();
    //     }
    // }
    // </code> 
	virtual int read(void);
	/* DOM-NOT_FOR_SDK-BEGIN */	
    // todo
	virtual int peek(void);
	
	// todo
	virtual void flush(void);
	
	// todo
	void onReceive(void(*)(int));
	
	// todo
	void onRequest(void(*)(void));

	// todo
    inline size_t write(unsigned long n) { return write((uint8_t)n); }
    
    // todo
    inline size_t write(long n) { return write((uint8_t)n); }
    
    // todo
    inline size_t write(unsigned int n) { return write((uint8_t)n); }
    
    // todo
    inline size_t write(int n) { return write((uint8_t)n); }
    
    // todo
    using Print::write;

	// todo
	void onService(void);
/* DOM-NOT_FOR_SDK-END */	
//The implementation.
private:
    // RX Buffer
    uint8_t rxBuffer[BUFFER_LENGTH];
    uint8_t rxBufferIndex;
    uint8_t rxBufferLength;

    // TX Buffer
    uint8_t txAddress;
    uint8_t txBuffer[BUFFER_LENGTH];
    uint8_t txBufferLength;

    // Service buffer
    uint8_t srvBuffer[BUFFER_LENGTH];
    uint8_t srvBufferIndex;
    uint8_t srvBufferLength;

    // Callback user functions
    void (*onRequestCallback)(void);
    void (*onReceiveCallback)(int);

    uint8_t bytes_per_transfer;
    uint8_t num_transfer;

    uint8_t bytes_per_read;
    uint8_t num_read;

    // This is called before initialization.
    //void (*onBeginCallback)(void);

    // The TWI instance.
    //Twi *twi;

    // The TWI state.
    enum TwoWireStatus {
        UNINITIALIZED,
        MASTER_IDLE,
        MASTER_SEND,
        MASTER_RECV,
        SLAVE_IDLE,
        SLAVE_RECV,
        SLAVE_SEND
    };
    TwoWireStatus status;

    // The TWI clock frequency.
    static const uint32_t TWI_CLOCK = 100000;

    // The Timeouts.
    static const uint32_t RECV_TIMEOUT = 100000;
    static const uint32_t XMIT_TIMEOUT = 100000;
};

//The Wire object.
extern TwoWire Wire;

#endif

