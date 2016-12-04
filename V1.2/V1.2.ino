#include "uarm_library.h"

struct m_movement
{
  double x;
  double y;
  double z;
  bool pumping;
};

struct a_movement
{
  double position_b[6][3];
  double position_c[3][3];
  int pumping_b[6];
};


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

    }

    if (readSerial == '2')
    {
      char input;
      int count = 0;
      m_movement Manual[10];
      Serial.flush();
      do
      {
        while (Serial.available() == 0);
        input = Serial.read();
        if (input == 's')
        {
          Serial.flush();
          uarm.get_current_xyz();
          Manual[count].x = uarm.get_current_x();
          Manual[count].y = uarm.get_current_y();
          Manual[count].z = uarm.get_current_z();
          Manual[count].pumping = true;
          count++;
        }

        if (input == 'o')
        {
          Serial.flush();
          uarm.get_current_xyz();
          Manual[count].x = uarm.get_current_x();
          Manual[count].y = uarm.get_current_y();
          Manual[count].z = uarm.get_current_z();
          Manual[count].pumping = false;
          count++;
        }

      } while (input != 'd');
      char input2;
      uarm.set_servo_status(true, SERVO_ROT_NUM);
      uarm.set_servo_status(true, SERVO_LEFT_NUM);
      uarm.set_servo_status(true, SERVO_RIGHT_NUM);
      int cycle = 0;
      double offset1,offset2,offset3;
      offset1 = uarm.read_servo_offset(SERVO_ROT_NUM);
      offset2 = uarm.read_servo_offset(SERVO_LEFT_NUM);
      offset3 = uarm.read_servo_offset(SERVO_RIGHT_NUM);
      
      do
      {
        for (int i = 0; i < count; i++)
        {

          uarm.move_to(Manual[i].x-0.45, Manual[i].y+offset2, Manual[i].z);
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

        cycle++;
        input2 = Serial.read();
        if (input2 == 'c')
        {
          Serial.print(cycle);
        }

      } while (input2 != 'c');
      uarm.set_servo_status(false, SERVO_ROT_NUM);
      uarm.set_servo_status(false, SERVO_LEFT_NUM);
      uarm.set_servo_status(false, SERVO_RIGHT_NUM);
      uarm.pump_off();
    }


    //----------------------------------  function d  ------------------------------------
    // Detach Servo

    if (readSerial == 'd') {
      uarm.set_servo_status(false, SERVO_ROT_NUM);
      uarm.set_servo_status(false, SERVO_LEFT_NUM);
      uarm.set_servo_status(false, SERVO_RIGHT_NUM);

    }
    //----------------------------------  function a  ------------------------------------
    // Detach Servo

    if (readSerial == 'a') {
      uarm.set_servo_status(true, SERVO_ROT_NUM);
      uarm.set_servo_status(true, SERVO_LEFT_NUM);
      uarm.set_servo_status(true, SERVO_RIGHT_NUM);

    }

    //        if (readSerial == '3')
    //        {
    //          a_movement autoMove;
    //          char input2;
    //          do
    //          {
    //            while (Serial.available() == 0);
    //            input2 = Serial.read();
    //            if (input2 == 'b')
    //            {
    //
    //              double temp;
    //              int count = 0;
    //
    //              uarm.get_current_xyz();
    //              autoMove.position_b[count][0] = uarm.get_current_x();
    //              autoMove.position_b[count][1] = uarm.get_current_y();
    //              temp = uarm.get_current_z();
    //              autoMove.position_b[count][2] = temp + 5;
    //              count++;
    //
    //              autoMove.position_b[count][0] = uarm.get_current_x();
    //              autoMove.position_b[count][1] = uarm.get_current_y();
    //              autoMove.position_b[count][2] = uarm.get_current_z();
    //              count++;
    //
    //              autoMove.position_b[count][0] = -0.5;
    //              autoMove.position_b[count][1] = -5.55;
    //              autoMove.position_b[count][2] = 18;
    //              count++;
    //
    //              autoMove.position_b[count][0] = uarm.get_current_x();
    //              autoMove.position_b[count][1] = uarm.get_current_y();
    //              temp = uarm.get_current_z();
    //              autoMove.position_b[count][2] = temp + 5;
    //              count++;
    //
    //              autoMove.position_b[count][0] = uarm.get_current_x();
    //              autoMove.position_b[count][1] = uarm.get_current_y();
    //              autoMove.position_b[count][2] = uarm.get_current_z();
    //              count++;
    //
    //
    //              autoMove.position_b[count][0] = -0.5;
    //              autoMove.position_b[count][1] = -5.55;
    //              autoMove.position_b[count][2] = 18;
    //              count++;
    //
    //
    //            }
    //
    //            else if (input2 == 'c')
    //            {
    //              double temp;
    //              int count = 0;
    //              uarm.get_current_xyz();
    //              autoMove.position_c[count][0] = uarm.get_current_x();
    //              autoMove.position_c[count][1] = uarm.get_current_y();
    //              temp = uarm.get_current_z();
    //              autoMove.position_c[count][2] = temp + 5;
    //
    //              count++;
    //
    //              autoMove.position_c[count][0] = uarm.get_current_x();
    //              autoMove.position_c[count][1] = uarm.get_current_y();
    //              temp = uarm.get_current_z();
    //              autoMove.position_c[count][2] = temp;
    //              count++;
    //
    //              autoMove.position_c[count][0] = -0.5;
    //              autoMove.position_c[count][1] = -5.55;
    //              autoMove.position_c[count][2] = 18;
    //            }
    //
    //          } while (input2 != 'd');
    //
    //          uarm.set_servo_status(true, SERVO_ROT_NUM);
    //          uarm.set_servo_status(true, SERVO_LEFT_NUM);
    //          uarm.set_servo_status(true, SERVO_RIGHT_NUM);
    //          for (int i = 0; i < 6; i++)
    //          {
    //
    //            delay(500);
    //            uarm.move_to(autoMove.position_b[i][0], autoMove.position_b[i][1], autoMove.position_b[i][2]);
    //            Serial.print(autoMove.position_b[i][0]);
    //            Serial.print(",");
    //            Serial.print(autoMove.position_b[i][1]);
    //            Serial.print(",");
    //            Serial.print(autoMove.position_b[i][2]);
    //            Serial.print("\n");
    //            delay(2000);
    //          }
    //
    //          for (int i = 0; i < 3; i++)
    //          {
    //
    //            delay(500);
    //            uarm.move_to(autoMove.position_c[i][0], autoMove.position_c[i][1], autoMove.position_c[i][2]);
    //            Serial.print(autoMove.position_c[i][0]);
    //            Serial.print(",");
    //            Serial.print(autoMove.position_c[i][1]);
    //            Serial.print(",");
    //            Serial.print(autoMove.position_c[i][2]);
    //            Serial.print("\n");
    //            delay(2000);
    //          }
    //
    //          uarm.set_servo_status(false, SERVO_ROT_NUM);
    //          uarm.set_servo_status(false, SERVO_LEFT_NUM);
    //          uarm.set_servo_status(false, SERVO_RIGHT_NUM);
    //
    //        }
  }

}