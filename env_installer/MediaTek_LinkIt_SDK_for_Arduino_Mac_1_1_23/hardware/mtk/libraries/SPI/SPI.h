/*
 * Copyright (c) 2010 by Cristian Maglie <c.maglie@bug.st>
 * SPI Master library for Arduino.
 *
 * This file is free software; you can redistribute it and/or modify
 * it under the terms of either the GNU General Public License version 2
 * or the GNU Lesser General Public License version 2.1, both as
 * published by the Free Software Foundation.
 *
 * Modified 20 Aug 2014 by MediaTek Inc.
 */

#ifndef _SPI_H_INCLUDED
#define _SPI_H_INCLUDED

#include "variant.h"
#include "vmdcl_spi.h"
#include <stdio.h>

// SPI clock is 1/4 of the system clock.
#define SPI_CLOCK_DIV4 0x00
// SPI clock is 1/16 of the system clock.
#define SPI_CLOCK_DIV16 0x01
// SPI clock is 1/64 of the system clock.
#define SPI_CLOCK_DIV64 0x02
// SPI clock is 1/128 of the system clock.
#define SPI_CLOCK_DIV128 0x03
// SPI clock is 1/2 of the system clock.
#define SPI_CLOCK_DIV2 0x04
// SPI clock is 1/8 of the system clock.
#define SPI_CLOCK_DIV8 0x05
// SPI clock is 1/32 of the system clock.
#define SPI_CLOCK_DIV32 0x06

// SPI data transfer mode 0.
#define SPI_MODE0 0x02
// SPI data transfer mode 1.
#define SPI_MODE1 0x00
// SPI data transfer mode 2.
#define SPI_MODE2 0x03
// SPI data transfer mode 3.
#define SPI_MODE3 0x01

// SPI class interface is used to control SPI port to conduct data communication between the processor and multitudes of peripheral devices.
class SPIClass {
	
// The constructor / destructor. 
public: 
    SPIClass(void);
    
// Method  
public:  
//DESCRIPTION
// Sends a byte of data to slave and receives a byte of data from the slave simultaneously.
//RETURNS
// Data returned from slave to master.
//EXAMPLE
// <code>
// #include <SPI.h>
// #define SS_PIN    10
//
// void setup()
// {
//     pinMode(SS_PIN, OUTPUT);
//     SPI.begin();    
// }
// void loop()
// {
//     byte ret_val;
//     digitalWrite(SS_PIN, LOW);
//     ret_val = SPI.transfer(100);
//     digitalWrite(SS_PIN, HIGH);
//     delay(1000);
// }
// </code> 
    byte transfer(
        uint8_t _data  // [IN] The data sent from master to slave.
    );

//DESCRIPTION
// Initializes and sets up the SPI mode. It also initializes the status of pins.
//EXAMPLE
// <code>
// #include <SPI.h>
// #define SS_PIN    10
// 
// void setup()
// {
//     pinMode(SS_PIN, OUTPUT);
//     SPI.begin();    
// }
// void loop()
// {
//     byte ret_val;
//     digitalWrite(SS_PIN, LOW);
//     ret_val = SPI.transfer(100);
//     digitalWrite(SS_PIN, HIGH);
//     delay(1000);
// }
// </code> 
    void begin(void);
// 
//DESCRIPTION
// Disables the SPI data transmission.
//EXAMPLE
// <code>
// #include <SPI.h>
// #define SS_PIN    10
// int value = 0;
//
// void setup()
// {
//     pinMode(SS_PIN, OUTPUT);
//     SPI.begin();    
// }
// void loop()
// {
//     for (value = 0; value < 255; value++)
//     {
//         digitalWrite(SS_PIN, LOW);
//         SPI.transfer(value);
//         digitalWrite(SS_PIN, HIGH);
//         delay(1000);
//     }
//     SPI.end();
// }
// </code> 
    void end(void);

//DESCRIPTION
// Sets up the order of data transmission, which can be MSBFIRST (MSB first) or LSBFIRST (LSB first).
//EXAMPLE
// <code>
// #include <SPI.h>
// #define SS_PIN    10
//
// void setup()
// {
//     pinMode(SS_PIN, OUTPUT);
//     SPI.begin(); 
//     SPI.setBitOrder(MSBFIRST); 
// }
// void loop()
// {
//     byte ret_val;
//     digitalWrite(SS_PIN, LOW);
//     ret_val = SPI.transfer(100);
//     digitalWrite(SS_PIN, HIGH);
//     delay(1000);
// }
// </code> 
    void setBitOrder(
        BitOrder bit_order // [IN] The data transmission order (MSBFIRST or LSBFIRST).
        );

//DESCRIPTION
// Sets up the SPI data transmission mode.
//EXAMPLE
// <code>
// #include <SPI.h>
// #define SS_PIN    10
//
// void setup()
// {
//     pinMode(SS_PIN, OUTPUT);
//     SPI.begin(); 
//     SPI.setDataMode(SPI_MODE1); 
// }
// void loop()
// {
//     byte ret_val;
//     digitalWrite(SS_PIN, LOW);
//     ret_val = SPI.transfer(100);
//     digitalWrite(SS_PIN, HIGH);
//     delay(1000);
// }
// </code>
    void setDataMode(
        uint8_t mode  // [IN] The SPI data transmission mode (SPI_MODE0 ~ SPI_MODE3).
        );

//DESCRIPTION
// Sets up clock divider to control the speed of data transmission. 
//EXAMPLE
// <code>
// #include <SPI.h>
// #define SS_PIN    10
// 
// void setup()
// {
//     pinMode(SS_PIN, OUTPUT);
//     SPI.begin(); 
//     SPI.setClockDivider(SPI_CLOCK_DIV8); 
// }
// void loop()
// {
//     byte ret_val;
//     digitalWrite(SS_PIN, LOW);
//     ret_val = SPI.transfer(100);
//     digitalWrite(SS_PIN, HIGH);
//     delay(1000);
// }
// </code>
    void setClockDivider(
        uint8_t clock_div  // [IN] The clock divider (SPI_CLOCK_DIV2 ~ SPI_CLOCK_DIV128).
        );
  
//DESCRIPTION
// Writes block memory to slave. The memory size needs to be 2^X in exponential form. 
//RETURNS
// The size to write, or
// 0:Failed.
//EXAMPLE
// <code>
// #include <SPI.h>
// #define SS_PIN    10
// 
// void setup()
// {
//     pinMode(SS_PIN, OUTPUT);
//     SPI.begin(); 
//     SPI.setClockDivider(SPI_CLOCK_DIV8); 
// }
// void loop()
// {
//     byte ret_val;
//     uint8_t mem[64];
//     //    //    memset(mem, 0, 64);
//     digitalWrite(SS_PIN, LOW);
//     SPI.write(mem, 64);
//     digitalWrite(SS_PIN, HIGH);
//     delay(1000);
// }
// </code>
    uint32_t write(
        uint8_t* _data,   // [IN] The point of data sent from master to slave.
        uint32_t size     // [IN] The data size to send.
        );
  private:

    // The SPI configuration data.
    vm_spi_config_para_t conf_data;

    // The SPI handle.
    VM_DCL_HANDLE spi_handle;

    // Specifies SPI mode. 
    vm_spi_mode_t  spi_data;

    // Write buffer.
    VMUINT8 write_buff;

    // Writes buffer length.
    VMUINT32 write_len;

    // Reads buffer.
    VMUINT8 read_buff;

    // Reads buffer length.
    VMUINT32 read_len;

    uint32_t write_2x(uint8_t* _data,uint32_t size);

};

//The SPI object.
extern SPIClass SPI;

#endif
