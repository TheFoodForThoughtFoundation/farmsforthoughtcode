//This code will work on an Arduino Uno and Mega
//This code was written to be easy to understand.
//Modify this code as you see fit.
//This code will output data to the Arduino serial monitor.
//Type commands into the Arduino serial monitor to control the EZO Humidity sensor.
//This code was written in the Arduino 2.0.4 IDE
//This code was last tested 4/2023


#include <Wire.h>    //enable I2C.
#define address 111  //default I2C ID number for EZO Humidity sensor.



char computerdata[50];            //we make a 20 byte character array to hold incoming data from a pc/mac/other.
byte received_from_computer = 0;  //we need to know how many characters have been received.
byte serial_event = false;        //a flag to signal when data has been received from the pc/mac/other.
byte code = 0;                    //used to hold the I2C response code.
char Humidity_data[50];           //we make a 2-byte character array to hold incoming data from the Humidity sensor.
byte in_char = 0;                 //used as a 1 byte buffer to store inbound bytes from the Humidity  sensor.
byte i = 0;                       //counter used for Humidity_data array.
int time_ = 300;                  //used to set the delay needed to process the command sent to the EZO Humidity sensor.

char *HUM;  //char pointer used in string parsing.
char *TMP;  //char pointer used in string parsing.
char *NUL;  //char pointer used in string parsing (the sensor outputs some text that we don't need).
char *DEW;  //char pointer used in string parsing.

float HUM_float;  //float var used to hold the float value of the humidity.
float TMP_float;  //float var used to hold the float value of the temperature.
float DEW_float;  //float var used to hold the float value of the dew point.



void setup()  //hardware initialization.
{
  Serial.begin(9600);  //enable serial port.
  Wire.begin();        //enable I2C port.
}



void loop() {
  computerdata[i] = 'r';  //telling to read
//   computerdata[0] = 'o';  //telling to read
//  computerdata[1] = ',';
//   computerdata[2] = 'd';
//   computerdata[3] = 'e';
//   computerdata[4] = 'w';
//   computerdata[5] = ',';
//   computerdata[6] = '1';

  Wire.beginTransmission(address);  //call the circuit by its ID number.
  Wire.write(computerdata);         //transmit the command that was sent through the serial port.
  Wire.endTransmission();           //end the I2C data transmission.


  delay(time_);  //wait the correct amount of time for the circuit to complete its instruction.

  Wire.requestFrom(address, 50, 1);  //call the circuit and request 25 bytes.
  code = Wire.read();                //the first byte is the response code, we read this separately.

  switch (code) {                 //switch case based on what the response code is.
    case 1:                       //decimal 1.
      Serial.println("Success");  //means the command was successful.
      break;                      //exits the switch case.

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



  while (Wire.available()) {     //are there bytes to receive.
    in_char = Wire.read();       //receive a byte.
    Humidity_data[i] = in_char;  //load this byte into our array.
    i += 1;                      //incur the counter for the array element.
    if (in_char == 0) {          //if we see that we have been sent a null command.
      i = 0;                     //reset the counter i to 0.
      break;                     //exit the while loop.
    }
  }

  Serial.println(Humidity_data);  //print the data.


  if (computerdata[0] == 'r') string_pars();  //uncomment this function if you would like to break up the comma separated string into its individual parts.
}

void string_pars() {  //this function will break up the CSV string into its 3 individual parts. HUM|TMP|DEW.
                      //this is done using the C command “strtok”.

  HUM = strtok(Humidity_data, ",");  //let's pars the string at each comma.
  TMP = strtok(NULL, ",");           //let's pars the string at each comma.
  NUL = strtok(NULL, ",");           //let's pars the string at each comma (the sensor outputs the word "DEW" in the string, we dont need it.
  DEW = strtok(NULL, ",");           //let's pars the string at each comma.
  Serial.println(TMP==NULL);

  Serial.println();  //this just makes the output easier to read by adding an extra blank line.

  Serial.print("HUM:");  //we now print each value we parsed separately.
  Serial.println(HUM);   //this is the humidity value.

  Serial.print("Air TMP:");  //we now print each value we parsed separately.
  TMP_float = atof(TMP);
  Serial.println((TMP_float*9.0)/5.0+32);       //this is the air temperatur value.

  Serial.print("DEW:");  //we now print each value we parsed separately.
  Serial.println(DEW);      //this just makes the output easier to read by adding an extra blank line.


  HUM_float = atof(HUM);
  DEW_float = atof(DEW);
}
