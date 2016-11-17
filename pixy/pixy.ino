/*PrimeDev - 2016*/
//headers
#include <SPI.h>
#include <Pixy.h>
Pixy pixy;

void setup()
{
  Serial.begin(9600);
  pixy.init();//initialize the pixy

}

void loop()
{
  //variables
  char input;
  uint16_t blocks;
  //once pixy receive power supply pixy is always on and always detecting
  //impossible to stop pixy from detecting unless it is detach from power supply
  //this is why pixy.getBlocks have to keep in a loop
  //read if there is any blocks detected
  blocks = pixy.getBlocks();
  //if blocks is detected it will return value of 1
  if (blocks)
  {
    if (pixy.blocks[0].signature == 1)//check if pixy detected signature is 1
    {
      //check for user input
      if (Serial.available() > 0)
      {
        input = Serial.read();
        if (input == 'Y')
        {
          pixy.blocks[0].print();//display pixy information
        }

      }
    }
  }
  //if not detected continue to read  because the blocks return value 0 can be means there is stale data and not means by no object detected
  else
  {
    delay(20);//make a delay of 20ms because a frame take 20ms to process
    blocks = pixy.getBlocks();
    if (blocks)//when blocks is not 0
    {
      
      if (pixy.blocks[0].signature == 1)//check if pixy detected signature is 1
      {
        //check if there is any input from user
        if (Serial.available() > 0)
        {
          input = Serial.read();
          if (input == 'Y')
          {
            pixy.blocks[0].print();//display pixy information
          }
         
        }
      }
    }
    else
    {
      //check if there is any input from user
      if (Serial.available() > 0)
      {
        input = Serial.read();
        if (input == 'Y')
        {
          pixy.blocks[0].print();//display the pixy information
        }

      }
    }

  }

}

