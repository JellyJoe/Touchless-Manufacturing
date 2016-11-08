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
    int j;
    static int j = 0;
    uint16_t blocks;
    int x_coordinate, y_coordinate, z_coordinate;
    String buffer_string;

    blocks = pixy.getBlocks();

    if (blocks)
    {
        i++;

        if(i % 50 == 0)
        {
            for(j = 0; j < blocks; j++)
            {
                x_coordinate = pixy.blocks[j].x;
                y_coordinate = pixy.blocks[j].y;
                z_coordinate = pixy.blocks[j].height;

                buffer_string.remove(0);
                buffer_string.concat(x_coordinate);
                buffer_string.concat(' ');
                buffer_string.concat(y_coordinate);
                buffer_string.concat(' ');
                buffer_string.concat(z_coordinate);
                buffer_string.concat(' ');

                Serial.print(buffer_string.c_str());
            }
        }
    }
}
