//This code will work on an Arduino Uno and Mega
//This code was written to be easy to understand.
//Modify this code as you see fit.
//This code will output data to the Arduino serial monitor.
//Type commands into the Arduino serial monitor to control the EZO-PMP.
//This code was written in the Arduino 1.8.9 IDE
//This code was last tested 7/2019


#include <Wire.h>    //enable I2C.
#define address 104  //default I2C ID number for EZO-PMP Embedded Dosing Pump.



char computerdata[20];            //we make a 20 byte character array to hold incoming data from a pc/mac/other.
byte received_from_computer = 0;  //we need to know how many characters have been received.    //a flag to signal when data has been received from the pc/mac/other.
byte code = 0;                    //used to hold the I2C response code.
char pmp_data[20];                //we make a 20 byte character array to hold incoming data from the EZO-PMP.
byte in_char = 0;                 //used as a 1 byte buffer to store in bound bytes from the EZO-PMP.
byte i = 0;
bool pmp_success = false;  //counter used for pmp_data array.
int time_ = 250;           //used to change the delay needed depending on the command sent to the EZO-PMP.
float pmp_float;           //float var used to hold the float value of the EZO-PMP.


void setup()  //hardware initialization.
{
  Serial.begin(9600);  //enable serial port.
  Wire.begin();        //enable I2C port.
}


void loop() {
  //computerdata[0] = 'r';
  computerdata[0] = 'd';
  computerdata[1] = ',';
  computerdata[2] = '6';
  computerdata[3] = '0';

  if (pmp_success == false) {
    Wire.beginTransmission(address);  //call the device by its ID number.
    Wire.write(computerdata);         //transmit the command that was sent through the serial port.
    Wire.endTransmission();           //end the I2C data transmission.

    delay(time_);  //wait the correct amount of time for the device to complete its instruction.

    Wire.requestFrom(address, 20, 1);  //call the device and request 20 bytes (this may be more than we need)
    code = Wire.read();

    switch (code) {  //switch case based on what the response code is.
      case 1:        //decimal 1.
        Serial.println("Success");
        pmp_success = true;  //means the command was successful.
        break;               //exits the switch case.

      case 2:                      //decimal 2.
        Serial.println("Failed");  //means the command has failed.
        break;                     //exits the switch case.

      case 254:                     //decimal 254.
        Serial.println("Pending");  //means the command has not yet been finished calculating.
        break;                      //exits the switch case.

      case 255:                     //decimal 255.
        Serial.println("No Data");  //means there is no further data to send.
        break;                      //exits the switch case.
    }


    while (Wire.available()) {  //are there bytes to receive.
      in_char = Wire.read();    //receive a byte.
      pmp_data[i] = in_char;    //load this byte into our array.
      i += 1;                   //incur the counter for the array element.
      if (in_char == 0) {       //if we see that we have been sent a null command.
        i = 0;                  //reset the counter i to 0.
        break;                  //exit the while loop.
      }
    }

    Serial.println(pmp_data);  //print the data.

    pmp_float = atof(pmp_data);  //the first byte is the response code, we read this separately.
  }
}
