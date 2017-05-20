/* Sweep
 by BARRAGAN <http://barraganstudio.com> 
 This example code is in the public domain.

 modified 8 Nov 2013
 by Scott Fitzgerald
 http://arduino.cc/en/Tutorial/Sweep
*/ 

#include <Servo.h> 
 
Servo myservo;  // create servo object to control a servo 
                // twelve servo objects can be created on most boards
 
int pos = 0;    // variable to store the servo position 

// Left and right limits
// Calibrate and set iLevel here.
int iLevel = 82;
int iRockLeft = iLevel - 45;
int iRockRight = iLevel + 45;
// Cradle rocking speed, higher number == higher delay = slower speed;
int iDelay = 15;
// PWM pin
int iServoPin = 9;


// String to store commands received via serial monitor
String strMsg = ""; 
// Available commands
String strWelcome = "*** Cradle Rocker v0.1 ***\nType a number:\n1 - Level/Change flask\n2 - Rock\n3 - Drain\n4 - Menu\n\n";

void setup() 
{ 
  myservo.attach(iServoPin);  // attaches the servo on pin 9 to the servo object 
  Serial.begin(9600);
  printHelp();
  myservo.write(iLevel); 
} 

void processMsg(String strMsg)
{
  // remove trailing characters
  strMsg.trim();
 
  // Could be a case statement
  if(strMsg == "1") {
    Serial.print("1");  
    level();
  }
  if(strMsg == "2") {
    Serial.print("2");      
    rock();
  }
  if(strMsg == "3") {
    Serial.print("3");      
    drain();
  }  
  if(strMsg == "4") {
    Serial.print("4");      
    printHelp();
  }    
}

void printHelp()
{
  Serial.print(strWelcome);  
}

void level()
{
  int iPos = myservo.read();
  if(iPos > iLevel)
  {
    for(pos = iPos; pos >= iLevel; pos -= 1) // goes from 0 degrees to 180 degrees 
    {                                  // in steps of 1 degree 
      myservo.write(pos);              // tell servo to go to position in variable 'pos' 
      delay(iDelay);                       // waits 15ms for the servo to reach the position 
    }         
  }
  if(iPos < iLevel)
  {
    for(pos = iPos; pos <= iLevel; pos += 1) // goes from 0 degrees to 180 degrees 
    {                                  // in steps of 1 degree 
      myservo.write(pos);              // tell servo to go to position in variable 'pos' 
      delay(iDelay);                       // waits 15ms for the servo to reach the position 
    }      
  }
}

void rock()
{
    level();
    rightFromLevel();
    rockRight();
    rockLeft();
    levelFromRight();
}

void rockLeft()
{
    for(pos = iRockLeft; pos <= iRockRight; pos += 1) // goes from 0 degrees to 180 degrees 
    {                                  // in steps of 1 degree 
      myservo.write(pos);              // tell servo to go to position in variable 'pos' 
      delay(iDelay);                       // waits 15ms for the servo to reach the position 
    }   
}

void rockRight()
{
    for(pos = iRockRight; pos >= iRockLeft; pos-=1)     // goes from 180 degrees to 0 degrees 
    {                                
      myservo.write(pos);              // tell servo to go to position in variable 'pos' 
      delay(iDelay);                       // waits 15ms for the servo to reach the position 
    }  
}

void levelFromLeft()
{
    for(pos = myservo.read(); pos <= iLevel; pos += 1) // goes from 0 degrees to 180 degrees 
    {                                  // in steps of 1 degree 
      myservo.write(pos);              // tell servo to go to position in variable 'pos' 
      delay(iDelay);                       // waits 15ms for the servo to reach the position 
    }    
}

void leftFromLevel()
{
    for(pos = iLevel; pos >= iRockLeft; pos -= 1) // goes from 0 degrees to 180 degrees 
    {                                  // in steps of 1 degree 
      myservo.write(pos);              // tell servo to go to position in variable 'pos' 
      delay(iDelay);                       // waits 15ms for the servo to reach the position 
    }    
}

void rightFromLevel()
{
    for(pos = iLevel; pos <= iRockRight; pos += 1) // goes from 0 degrees to 180 degrees 
    {                                  // in steps of 1 degree 
      myservo.write(pos);              // tell servo to go to position in variable 'pos' 
      delay(iDelay);                       // waits 15ms for the servo to reach the position 
    }    
}

void levelFromRight()
{
    for(pos = iRockRight; pos >= iLevel; pos -= 1) // goes from 0 degrees to 180 degrees 
    {                                  // in steps of 1 degree 
      myservo.write(pos);              // tell servo to go to position in variable 'pos' 
      delay(iDelay);                       // waits 15ms for the servo to reach the position 
    }    
}

void drain()
{
  leftFromLevel(); 
}

void loop() 
{ 
  // receive message from serial and deal with it
  while (Serial.available() > 0) {
    char inChar = Serial.read();
    strMsg += inChar;
  }
  // Delay used for human readability so we don't split messages
  // typed in Serial Monitor. 
  // If application at the other end can identify beginning and end
  // of message such as delimiters, delay is not required.
  delay(200);
  if (strMsg.length() > 0) {
    processMsg(strMsg); 
    strMsg = ""; 
  }
} 

