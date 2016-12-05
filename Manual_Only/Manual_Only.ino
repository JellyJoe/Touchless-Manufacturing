#include "uarm_library.h"

struct m_movement
{
  double x;
  double y;
  double z;
  bool pumping;
};

m_movement Manual[10];
int count = 0;
void setup() {

  Wire.begin();      // join i2c bus (address optional for master)
  Serial.begin(9600); // start serial port at 9600 bps
}


void loop() {

  if (Serial.available() > 0)
  {

    char readSerial = Serial.read();
    Serial.println(readSerial);

    //----------------------------------  function 1  ------------------------------------
    // function below is for move uArm from current position to absolute coordinate
    // x = 13, y = -13, z = 3


    if (readSerial == '1') {

      uarm.move_to(40, -15, 15);
      delay(1000);
      uarm.move_to(40, -15, 7);
      delay(1000);
      uarm.pump_on();
      delay(1000);
      uarm.move_to(40, -15, 15);
      delay(1000);
      uarm.move_to(-5, -20, 10);
      delay(1000);
      uarm.pump_off();
      delay(1000);
      uarm.move_to(-5, 20, 10);
      delay(1000);
      uarm.move_to(-5, -20, 15);
      delay(1000);
      uarm.move_to(-5, -20, 8);
      delay(1000);
      uarm.pump_on();
      delay(1000);
      uarm.move_to(-5, -20, 15);
      delay(1000);
      //uarm.move_to(-5, 20, 15);
      //delay(5000);
      uarm.move_to(-40, -10, 12);
      delay(1000);
      uarm.pump_off();
      delay(1000);
      uarm.move_to(5, 20, 10);
      delay(1000);
      uarm.set_servo_status(false, SERVO_ROT_NUM);
      uarm.set_servo_status(false, SERVO_LEFT_NUM);
      uarm.set_servo_status(false, SERVO_RIGHT_NUM);

    }

    if (readSerial == 's')
    {
      uarm.get_current_xyz();
      Manual[count].x = uarm.get_current_x();
      Manual[count].y = uarm.get_current_y();
      Manual[count].z = uarm.get_current_z();
      Manual[count].pumping = true;
      count++;
    }

    if (readSerial == 'o')
    {
      uarm.get_current_xyz();
      Manual[count].x = uarm.get_current_x();
      Manual[count].y = uarm.get_current_y();
      Manual[count].z = uarm.get_current_z();
      Manual[count].pumping = false;
      count++;
    }



    if (readSerial == 'd')
    {
      uarm.set_servo_status(true, SERVO_ROT_NUM);
      uarm.set_servo_status(true, SERVO_LEFT_NUM);
      uarm.set_servo_status(true, SERVO_RIGHT_NUM);
      int cycle = 0;
      char input2;
      double offset1, offset2, offset3;
      offset1 = uarm.read_servo_offset(SERVO_ROT_NUM);
      offset2 = uarm.read_servo_offset(SERVO_LEFT_NUM);
      offset3 = uarm.read_servo_offset(SERVO_RIGHT_NUM);
      do
      {
        for (int i = 0; i < count; i++)
        {

          uarm.move_to(Manual[i].x - 0.45, Manual[i].y + offset2, Manual[i].z);
          delay(1000);
          if (Manual[i].pumping == true)
          {
            uarm.pump_on();
          }

          else
          {
            uarm.pump_off();

          }
          delay(1000);

        }
      } while (input2 != 'c');


      uarm.set_servo_status(false, SERVO_ROT_NUM);
      uarm.set_servo_status(false, SERVO_LEFT_NUM);
      uarm.set_servo_status(false, SERVO_RIGHT_NUM);
      uarm.pump_off();
    }

    //----------------------------------  function a  ------------------------------------
    // Detach Servo

    if (readSerial == 'a')
    {
      uarm.set_servo_status(true, SERVO_ROT_NUM);
      uarm.set_servo_status(true, SERVO_LEFT_NUM);
      uarm.set_servo_status(true, SERVO_RIGHT_NUM);

    }
  }
}
