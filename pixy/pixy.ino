//headers
#include <SPI.h>
#include <Pixy.h>
Pixy pixy;

//setup the arduino's serial port and pixy
void setup()
{
  //arduino to computer default speed of communication
  Serial.begin(9600);
  //initialize pixy with object name call pixy
  pixy.init();
}

void loop()
{
  //variables, to call the getblocks function
  uint16_t blocks;
  //Check for any input value
  if (Serial.available() > 0)
  {
    //read for input value
    char input = Serial.read();
    //continue loop if input value is 'y'
    while (input == 'y')
    {
      //pixy will start detecting for any blocks
      blocks = pixy.getBlocks();

      //if 1 block is detected
      if (blocks == 1)
      {
        //if the blocks is a signature 1 then print 'T', means True, else print 'F', means False
        if (pixy.blocks[0].signature == 1)
        {
          Serial.print("T");
          //set delay so printing of 'T' is not too fast
          delay(500);
        }
        else
        {
          Serial.print("F");
          //set delay so printing of 'F' is not too fast
          delay(500);

        }
      }
      //if not detected continue to read  because the blocks might return value 0 can be means there is stale data and not means by no object/blocks detected
      else
      {
        delay(20);//make a delay of 20ms because a frame take 20ms to process
        blocks = pixy.getBlocks();
        //when 1 block detected 
        if (blocks == 1)
        {
          //if the block is signature 1 then print 'T', else print 'F'
          if (pixy.blocks[0].signature == 1)
          {
            Serial.print("T");
            //set delay so printing of 'T' is not too fast
            delay(500);

          }
          else
          {
            Serial.print("F");
            //set delay so printing of 'F' is not too fast
            delay(500);

          }
        }
        else//Guarantee no block detected
        {
          //print "F" for no blocks detected or detected blocks is not equal to 1
          Serial.print("F");
          delay(500);

        }
      }
    }
  }

}

