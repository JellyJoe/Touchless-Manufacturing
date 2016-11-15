/*PrimeDev - 2016*/
//headers
#include <SPI.h>
#include <Pixy.h>
#include <stdlib.h>

Pixy pixy;

void setup()
{
  Serial.begin(9600);
  pixy.init();

}

void loop()
{
  String input;
  if (Serial.available() > 0)
  {
    input = Serial.readStringUntil('\n');
    if (input.equals("Y"))
    {
      program();
    }
    
  }

}
//complete program
void program()
{
  static int j = 0;
  uint16_t blocks;
  int x_coordinate, y_coordinate, z_coordinate, signature;
  String buffer_string, str;
  boolean reply = true;

  blocks = pixy.getBlocks();//retrieve blocks
  if (blocks)
  {
    if (pixy.blocks[0].signature == 1)
    {
      //retrieve the xyz coordinates
      x_coordinate = pixy.blocks[0].x;
      y_coordinate = pixy.blocks[0].y;
      z_coordinate = pixy.blocks[0].height;

      buffer_string.remove(0);
      //concantenate x y z into a string
      buffer_string.concat(x_coordinate);
      buffer_string.concat(' ');
      buffer_string.concat(y_coordinate);
      buffer_string.concat(' ');
      buffer_string.concat(z_coordinate);
      buffer_string.concat(' ');

      //void loop() will continue to loop and receive but print only once
      Serial.print(buffer_string.c_str());
      readData(x_coordinate, y_coordinate, z_coordinate);
    }
  }
  else
  {
    delay(20);
    blocks = pixy.getBlocks();//retrieve blocks
    if (pixy.blocks[0].signature == 1)
    {
      //retrieve the xyz coordinates
      x_coordinate = pixy.blocks[0].x;
      y_coordinate = pixy.blocks[0].y;
      z_coordinate = pixy.blocks[0].height;

      buffer_string.remove(0);
      //concantenate x y z into a string
      buffer_string.concat(x_coordinate);
      buffer_string.concat(' ');
      buffer_string.concat(y_coordinate);
      buffer_string.concat(' ');
      buffer_string.concat(z_coordinate);
      buffer_string.concat(' ');

      //void loop() will continue to loop and receive but print only once
      Serial.print(buffer_string);
      readData(x_coordinate, y_coordinate, z_coordinate);
    }
  }

}

//to read any write data
//do verification of x coordinate, y coordinate and z coordinate
void readData(int x, int y, int z)
{
  String strdata, str;
  strdata.concat(x);
  strdata.concat(' ');
  strdata.concat(y);
  strdata.concat(' ');
  strdata.concat(z);

  str = Serial.readStringUntil('\n');
  if (str.equals(strdata))
  {
    Serial.print("Verified!");
  }


}




