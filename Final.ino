#include <Servo.h>

// Declare left and right servos
Servo servoLeft; 
Servo servoRight; 
int err = 0;
int kp = 15;
int ki = 15;
int st=0;

float threshold = 1.0;

int l = A4;
int m = A3;
int r = A2;

int ll = A5;
int rr = A1;

int grid[8] = {2,1, 3, 3, 2, 2, 2,0}; // 0 - Stop, 1 - Left, 2 - Straight, 3 - Right
int index = 0;

void setup() // Built-in initialization block
{
  Serial.begin(9600); //Enable serial communication
  servoLeft.attach(13); // Attach left signal to pin 13
  servoRight.attach(12); // Attach right signal to pin 12
  servoLeft.writeMicroseconds(1500); // limit speed (Full speed forward use 1700)
  servoRight.writeMicroseconds(1500); //Full speed forward use 1300
}

void loop() // Main loop auto-repeats
{
  Serial.print("l = "); // Display "A3 = "
  Serial.print(Left(l)); // Display measured A3 volts
  Serial.println("Left"); // Display " Voltage of Left sensor" & add newline

  Serial.print("m = "); // Display "A4 = "
  Serial.print(Middle(m)); // Display measured A4 volts
  Serial.println("Middle"); // Display " Voltage of Middle sensor" & add newline

  Serial.print("r = "); // Display "A5 = "
  Serial.print(Right(r)); // Display measured A5 volts
  Serial.println("Right"); // Display " Voltage of Right sensor" & add newline
  
  Serial.print("rr = "); // Display "A5 = "
  Serial.print(Right(rr)); // Display measured A5 volts
  Serial.println("Right most"); // Display " Voltage of Right sensor" & add newline

  Serial.print("ll = "); // Display "A5 = "
  Serial.print(Left(ll)); // Display measured A5 volts
  Serial.println("Left most"); // Display " Voltage of Right sensor" & add newline

  if ((Left(ll) < threshold) ||(Right(rr) < threshold))
  {               
    switch(grid[index])
    {
      case 1:     forward(st);
                  delay(250);
                  left90();
                  delay(500);
                  index++;
                  break;
      case 2:     st++;
                  forward(st);
                  delay(250);
                  err = 0;
                  index++;
                  break;
      case 3:     forward(st);
                  delay(250);
                  right90();
                  delay(250);
                  index++;
                  break;
      case 0:     servoLeft.detach(); // Stop servo signals
                  servoRight.detach();
                  while(1)
                  {}
                  break;
    }
 }

//For Left Sensor A3
  if (Left(l) < threshold) // If left sensor detected then turn Right
  {
    st = 0;
    err--;
    left(err);
  }

  //For Right Sensor A5
  if(Right(r) < threshold) // If Right sensor detected then turn Right
  {
    st=0;
    err++;
    right(err);
  }
  
  if((Left(l) > threshold && Right(r) > threshold)) //If both are white run forward
  { 
    st++;
    forward(st);
    err = 0;
  }
}

void left(int e)
  {
    servoLeft.writeMicroseconds(1500); 
    servoRight.writeMicroseconds(1500 + (e*ki) - kp);
  }

void right(int e)
  {
    servoLeft.writeMicroseconds(1500 + (e*ki) + kp); 
    servoRight.writeMicroseconds(1500);
  }

void forward(int st)
  {
    servoLeft.writeMicroseconds(1500 + (st*20) + (err*ki)); // Full speed forward 1700
    servoRight.writeMicroseconds(1500 - (st*20) + (err*ki)); //1300
  }

float Left(int l) // Measures volts at adPin
{ // Returns floating point voltage
  return float(analogRead(l)) * 5.0 / 1024.0;
}

float Middle(int m) // Measures volts at adPin
{ // Returns floating point voltage
  return float(analogRead(m)) * 5.0 / 1024.0;
}

float Right(int r) // Measures volts at adPin
{ // Returns floating point voltage
  return float(analogRead(r)) * 5.0 / 1024.0;
}

void left90()
{
    servoLeft.writeMicroseconds(1450); 
    servoRight.writeMicroseconds(1450);
    delay(500);
    servoLeft.writeMicroseconds(1450); 
    servoRight.writeMicroseconds(1450);
}

void right90()
{
  
  servoLeft.writeMicroseconds(1550); 
  servoRight.writeMicroseconds(1550);
  delay(500);
  servoLeft.writeMicroseconds(1550); 
  servoRight.writeMicroseconds(1550);
}

void fwd()
{
  
  servoLeft.writeMicroseconds(1550); 
  servoRight.writeMicroseconds(1500);
}
 
