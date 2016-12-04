/*PrimeDev - 2016*/
//headers
#include <SPI.h>
#include <Pixy.h>
Pixy pixy;

void setup()
{
  Serial.begin(9600);
  //wait for user input
  while(Serial.available() == 0){}
  pixy.init();//initialize the pixy
}

void loop()
{
  //variables
  uint16_t blocks;
  //once pixy receive power supply pixy is always on and always detecting
  //impossible to stop pixy from detecting unless it is detach from power supply
  //this is why pixy.getBlocks have to keep in a loop
  //read if there is any blocks detected
  blocks = pixy.getBlocks();

  //if 2 blocks is detected, print "T", True
  if (blocks == 2)
  {
    if (pixy.blocks[0].signature == 1 && pixy.blocks[1].signature == 3)
    {
      Serial.print("T");
      delay(500);
    }
    else
    {
      Serial.print("F");
      delay(500);
    }
  }
  //if not detected continue to read  because the blocks return value 0 can be means there is stale data and not means by no object detected
  else
  {
    delay(20);//make a delay of 20ms because a frame take 20ms to process
    blocks = pixy.getBlocks();
    //when 2 blocks detected which are number of signature detected
    //print "T" true
    if (blocks == 2)
    {
      if (pixy.blocks[0].signature == 1 && pixy.blocks[1].signature == 3)
      {
        Serial.print("T");
        delay(500);
      }
      else
      {
        Serial.print("F");
        delay(500);
      }
    }
    else
    {
      //print "F" is no blocks detected or detected blocks is less than 1 or equal to 1
      Serial.print("F");
      delay(500);
    }
  }

}

