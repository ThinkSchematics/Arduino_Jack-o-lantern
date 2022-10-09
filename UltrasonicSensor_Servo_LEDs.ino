/*
 * Name: Johnny - ThinkSchematics.com 
 * Date: 7 Oct 2022
 * Last Modified: 7 Oct 2022
 * 
 * Code samples/barrow/insperation/background info/recognition from following pages:
 * Blinking an LED - https://www.arduino.cc/en/Tutorial/BuiltInExamples/Blink
 * Analog PWM - https://docs.arduino.cc/tutorials/generic/secrets-of-arduino-pwm
 * Random number - https://www.arduino.cc/reference/en/language/functions/random-numbers/random/
 * 
 * Datasheet found at: https://cdn.sparkfun.com/datasheets/Sensors/Proximity/HCSR04.pdf
 * 
 * Things to do:  
 * --clean up code (make it run smother) get help 
 * --Consider putting LEDs on a 555 timer or somethings, so they don't stop flashing due to delays in code
 * --do some comparison between sensors... the servo is jumping back and forth
 * --try to make it more natural eye movement
 * --Add SD card and audio out, then have it say "spooky stuff" when it detects something
 * 
*/

#include <Servo.h>  //servo lib

//right ultrasonic sensor
float distanceR = 0.0;
int const echoR = 10; //yellow wire
int const triggerR = 2;  //blue wire

//left ultrasonic sensor
float distanceL = 0.0;
int const echoL = 6; //yellow wire
int const triggerL = 7;  //blue wire

//servo
int pos = 0;    // variable to store the servo position
Servo myservo;  // create servo object to control a servo
               

//try to keep from going into servo if statements if not needed
int state;

//code for the LEDs
int redLED = 3;
int yellowLED = 4;
int randomNumber;





void setup()
{
  Serial.begin(9600);   //start the serial monitor at 9600 baud
  //right ultrasonic sensor
  pinMode(triggerR, OUTPUT);  //connected to trigger pin 11
  pinMode(echoR, INPUT);    //connected to echo pin 8

  //left ultrasonic sensor
  pinMode(triggerL, OUTPUT);  //connected to trigger pin 11
  pinMode(echoL, INPUT);    //connected to echo pin 8

  myservo.attach(9);  // attaches the servo on pin 9 to the servo object

  // pin mode setup for redLED and yellowLED as an output.
  pinMode(redLED, OUTPUT);
  pinMode(yellowLED, OUTPUT);

} // end setup function



void loop()
{ 
  //LED code
  randomNumber = random(10-255);
  //digitalWrite(redLED, HIGH);   // turn the LED on (HIGH is the voltage level)
  analogWrite(redLED, randomNumber);
  analogWrite(yellowLED, randomNumber);
  delay(10);                       // wait for a bit, might get rid of this

  
  //code for Right ultrasonic sensor to take a reading
  digitalWrite(triggerR, HIGH); //set the trigger pin high for 10 microseconds
  delayMicroseconds(10);    // different delay usec, this is a must
  digitalWrite(triggerR, LOW); 
                    //  PulseIn measures the time for the echo pin to go from LOW to HIGH in microseconds
                    //  distance is half the pulse time multiplied by speed of sound at 6000 feet altitude
                    //   in inches per microsecond
  distanceR=pulseIn(echoR,HIGH)/2*0.01242;

  //code for Right ultrasonic sensor to take a reading, might be able to combine witht he other sensor
  digitalWrite(triggerL, HIGH);
  delayMicroseconds(10);    // different delay usec
  digitalWrite(triggerL, LOW);  
  distanceL=pulseIn(echoL,HIGH)/2*0.01242;

  delay(10); //might be able to remove, I tend to add delays for troubleshooting

  //this IF Statement sees if the distanc from the right sensor is less than the left sensor
  //then checks to see if that distance is less than 14 inches (distance of person from the the sensor)
  //also checks to see if it is is already looing right
  //if all of these conditions are met then in runs the code inside the IF statement
  if((distanceR < distanceL) && (distanceR <= 14) && (state !=7))
  {
      //can't figure out how to make these two print statements into one, must be an Arduino thing
      Serial.print("Moving to the Right.  Distance for Right sensor is: ");
      Serial.println(distanceR);

      while(pos <= 89)
      {
        myservo.write(pos);
        pos = pos + 1;
        delay(20); //might be able to reduce this number but don't want the eyes to move too fast
      }//end while loop

      state = 7;
  }//end if statement
  


  //this will send the eyes back to the center
  if ((distanceL > 15) && (distanceR > 15) && (state !=4))
  {
    Serial.println("Moving to the Center");
    pos = 45;
    myservo.write(pos);
    state = 4;
  }


  //this does the same thing as the code for the right sensor and turning the right, but this time for turning to the left  
  if((distanceL < distanceR) && (distanceL <= 14) && (state !=8) )
  {
    //why doesn't Arduino allow a person to combine these two print statements?  I can't see how to do that if possible
    Serial.print("Moving to the Left.  Distance for Left sensor is: ");
    Serial.println(distanceL);


      while(pos >= 1)
      {
        myservo.write(pos);
        pos = pos - 1;
        delay(20); //might be able reduce this number, but we don't want the eyes to move too quickly
      }//end while loop
      state = 8;
  }//end if statement

  
} // end loop function
