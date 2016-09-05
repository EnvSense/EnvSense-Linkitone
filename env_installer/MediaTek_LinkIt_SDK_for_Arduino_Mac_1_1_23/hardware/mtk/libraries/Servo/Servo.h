/* 
  A servo is activated by creating an instance of the Servo class passing 
  the desired pin to the attach() method.
  The servos are pulsed in the background using the value most recently 
  written using the write() method.

  Note that analogWrite of PWM on pins associated with the timer are 
  disabled when the first servo is attached.
  Timers are seized as needed in groups of 12 servos - 24 servos use two 
  timers, 48 servos will use four.
  The sequence used to seize timers is defined in timers.h

    Modified 20 Aug 2014 by MediaTek Inc.
 */



#ifndef Servo_h
#define Servo_h

#include "vmsys.h"
#define timer16_Sequence_t VMINT

#define Servo_VERSION           2     // The software version of this library.

#define MIN_PULSE_WIDTH       544     // The shortest pulse width sent to a servo.  
#define MAX_PULSE_WIDTH      2400     // The longest pulse width sent to a servo. 
#define DEFAULT_PULSE_WIDTH  1500     // The default pulse width when a servo is attached.
#define REFRESH_INTERVAL    20000     // The minimum time to refresh the servo in microseconds. 

#define SERVOS_PER_TIMER       12     // The maximum number of servos controlled by a timer. 
#define _Nbr_16timers   4
#define MAX_SERVOS   (_Nbr_16timers  * SERVOS_PER_TIMER)

#define INVALID_SERVO         255     // The flag indicating an invalid servo index.

typedef struct  {
  VMUINT8 nbr        :6 ;             // The pin number from 0 to 63.
  VMUINT8 isActive   :1 ;             // If true, this channel is enabled; If false, the pin attached with a servo isn't pulsed. 
} ServoPin_t   ;  

typedef struct {
  ServoPin_t Pin;
  volatile unsigned int ticks;
} servo_t;

//DESCRIPTION
// Use the servo library to enable RC servo control on a LinkIt ONE circuit board. 
// Servo integrates gears and axes to provide accurate control.
//
// A standard servo system positions an axis in different angles, normally between 0 and 180 degrees.
// A rotating servo sets the rotation of axis to different speeds continuously.
//
//Note:
// Only pin (D3, D9) with PWM functionality can be used by the servo.
//
//EXAMPLE
//<code>
//#include <Servo.h>
//Servo myservo;
// 
//int potpin = 0;
//int val;
// 
//void setup()
//{
//  myservo.attach(9);                // The servo connecting to pin 9.
//}
// 
//void loop()
//{
//  val = analogRead(potpin);         // Reads from Pot pin.
//  val = map(val, 0, 1023, 0, 180);  // Map value from 0~1023 to 0~180.
//  myservo.write(val);               // The control servo.
//  delay(200);
//}
//<code>
class Servo
{
public:
  Servo();

  // DESCRIPTION
  //  Attaches a servo motor to a digital pin. Only digital pins supporting PWM (D3, D9) can use this function.
  // RETURNS
  //  The channel number, or 
  //  0: Failed.
  // EXAMPLE
  // <code>
  // #include <Servo.h>
  //  
  // Servo myservo;
  //  
  // void setup()
  // {
  //   myservo.attach(9);
  // }
  //  
  // void loop() 
  // {
  //   
  // }
  // </code> 
  VMUINT8 attach(
	  int pin	//The pin which needs servo attachment.
	  );

  // DESCRIPTION
  //  Attaches servo motor to a digital pin. Only digital pins supporting PWM (D3, D9) can use this function.
  // RETURNS
  //  Channel number or 
  //  0: Failed.
  // EXAMPLE
  // <code>
  // #include <Servo.h>
  //  
  // Servo myservo;
  //  
  // void setup()
  // {
  //   myservo.attach(9);
  // }
  //  
  // void loop() 
  // {
  //   
  // }
  // </code> 
  VMUINT8 attach(
	  int pin, //The pin which needs servo attachment.
	  int min, //(Optional)lower bound of PW, ms; PWM when servo motor is at 0 degree (default: 544).
	  int max  //(Optional)upper bound of PW, ms, PWM when servo motor is at 180 degrees (default: 2400).
	  );

  //To detach servo motor and pin. If all servo motors are bound, you can use PWM output and analogWrite for output.
  void detach();	

  // DESCRIPTION
  //  Writes a value to servo to control the corresponding lever.
  //  Sets up the lever angle for a standard servo motor in order to move the lever to the corresponding angle. To set up the rotation speed for a continuously rotating servo motor, use 0 to rotate in one direction in full speed; 180 to rotate in the opposite direction in full speed; and 90 to stay intact.
  // RETURNS
  //  Void.
  // EXAMPLE
  // <code>
  // #include <Servo.h>
  //  
  // Servo myservo;
  //  
  // void setup()
  // {
  //   myservo.attach(9);
  //   myservo.write(90);  // Sets servo to mid-point.
  // }
  //  
  // void loop() 
  // {
  //   
  // }
  // </code> 
  void write(
	  int value	//The angle written to servo, 0 ~ 180.
	  );


  // DESCRIPTION
  //  Writes a value to servo to control the corresponding lever. 
  //  Sets up the rotation angle of a standard servo motor. In terms of parameters for a standard servo:
  //   1000 means rotating counterclockwise in full speed. 
  //   2000 means clockwise in full speed. 
  //   1500 means in the middle.
  // 
  //  The following is extracted from Arduino's official website:
  //  For customers who do not operate following the standard method, for example by setting the response value of servo between 700 and 2300, in attempt to enlarge the limits to adjust the range of rotation. However, such operation may shorten the life of a servo and should be avoided.
  // RETURNS
  //  Void.
  // EXAMPLE
  // <code>
  // #include <Servo.h>
  //  
  // Servo myservo;
  //  
  // void setup()
  // {
  //   myservo.attach(9);
  //   myservo.writeMicroseconds(1500);  // Sets the servo to mid-point.
  // }
  //  
  // void loop() 
  // {
  //   
  // }
  // </code> 
  void writeMicroseconds(
	  int value	//The value of time in microseconds.
	  ); 

  // DESCRIPTION
  //  Reads the current rotation angle of the servo motor.
  // RETURNS
  //  Rotation angle of the servo, from 0 to 180 degrees.
  int read();

  // DESCRIPTION
  //  Detects if servo has been attached with a pin.
  // RETURNS
  //  True if pin is attached; otherwise false.
  bool attached();        

private:
   VMUINT8 servoIndex;               // Adds index for this servo into the channel data.
   VMINT8 min;                       // The minimum is this value times 4 added to MIN_PULSE_WIDTH.    
   VMINT8 max;                       // The maximum is this value times 4 added to MAX_PULSE_WIDTH.   
};

#endif
