#include "uarm_library.h"



double positon_b[6][3] = {0},{0}, position_c[6][3] = {0},{0};
double x[20] = {0}, y[20] = {0}, z[20] = {0};
int counter = 0, pump_status_manual[10] = {0}, pump_status_auto_a[10] = {0}, pump_status_auto_b[10], pump_status_auto_c[10];

void setup() {

  Wire.begin();      // join i2c bus (address optional for master)
  Serial.begin(9600); // start serial port at 9600 bps
}

void loop()
{}

void serialEvent() {


  while (Serial.available())
  {

    char readSerial = Serial.read();

    if (readSerial == '1')
    {

      uarm.set_servo_status(true, SERVO_ROT_NUM);
      uarm.set_servo_status(true, SERVO_LEFT_NUM);
      uarm.set_servo_status(true, SERVO_RIGHT_NUM);

      uarm.move_to(40, -15, 15);
      delay(1000);
      uarm.move_to(40, -15, 8);
      delay(1000);
      uarm.pump_on();
      delay(2000);
      uarm.move_to(40, -15, 15);
      delay(2000);
      uarm.move_to(0, 20, 10);
      delay(2000);
      uarm.move_to(0, -20, 10);
      delay(1000);
      uarm.pump_off();
      delay(2000);
      uarm.move_to(0, 20, 10);
      delay(2000);
      uarm.move_to(0, -20, 15);
      delay(1000);
      uarm.move_to(0, -20, 8);
      delay(1000);
      uarm.pump_on();
      delay(1000);
      uarm.move_to(0, -20, 15);
      delay(2000);
      uarm.move_to(0, 20, 15);
      delay(5000);
      uarm.move_to(-40, -10, 12);
      uarm.pump_off();
      delay(2000);
      uarm.move_to(0, 20, 10);
      delay(2000);

      uarm.set_servo_status(false, SERVO_ROT_NUM);
      uarm.set_servo_status(false, SERVO_LEFT_NUM);
      uarm.set_servo_status(false, SERVO_RIGHT_NUM);

    }

    else if (readSerial == 's')
    {

      uarm.get_current_xyz();
      x[counter] = uarm.get_current_x();
      y[counter] = uarm.get_current_y();
      z[counter] = uarm.get_current_z();
      pump_status_manual[counter] = 1;
      counter++;
    }

    else if (readSerial == 'o')
    {
      uarm.get_current_xyz();
      x[counter] = uarm.get_current_x();
      y[counter] = uarm.get_current_y();
      z[counter] = uarm.get_current_z();
      pump_status_manual[counter] = 0;
      counter++;
    }


    else if (readSerial == 'd')
    {
      char input;
      uarm.set_servo_status(true, SERVO_ROT_NUM);
      uarm.set_servo_status(true, SERVO_LEFT_NUM);
      uarm.set_servo_status(true, SERVO_RIGHT_NUM);
      do
      {
        for (int i = 0; i < counter; i++)
        {
          if (pumping_status_manual[i] == 1)
          {
            uarm.move_to(x[i], y[i], z[i]);
            delay(2000);
            uarm.pump_on();
            delay(2000);
          }

          else
          {
            uarm.move_to(x[i], y[i], z[i]);
            delay(2000);
            uarm.pump_off();
            delay(2000);
          }
        }
      } while (Serial.available() == 0);
      uarm.set_servo_status(false, SERVO_ROT_NUM);
      uarm.set_servo_status(false, SERVO_LEFT_NUM);
      uarm.set_servo_status(false, SERVO_RIGHT_NUM);
      uarm.pump_off();
    }

    else if (readSerial == 'b')
    {

      double temp;
      int count = 0;
      uarm.get_current_xyz();

      positon_b[count][0] = uarm.get_current_x();
      positon_b[count][1] = uarm.get_current_y();
      temp = uarm.get_current_z();
      positon_b[count][2] = temp + 5;
      pump_status_auto_b[count] = 1;
      count++;

      positon_b[count][0] = uarm.get_current_x();
      positon_b[count][1] = uarm.get_current_y();
      temp = uarm.get_current_z();
      positon_b[count][2] = temp + 2;
      pump_status_auto_b[count] = 0;
      count++;

      positon_b[count][0] = 0;
      positon_b[count][1] = 0;
      positon_b[count][2] = 0;
      pump_status_auto_b[count] = 0;
      count++;

      positon_b[count][0] = positon_b[0];
      positon_b[count][1] = positon_b[0];
      positon_b[count][2] = positon_b[0];
      pump_status_auto_b[count] = 0;
      count++;

      positon_b[count][0] = positon_b[1];
      positon_b[count][1] = positon_b[1];
      positon_b[count][2] = positon_b[1];
      pump_status_auto_b[count] = 1;
      count++;

      positon_b[count][0] = 0;
      positon_b[count][1] = 0;
      positon_b[count][2] = 0;
      pump_status_auto_b[count] = 1;
    }

    else if (readSerial == 'c')
    {
      int count = 0;
      double temp;
      uarm.get_current_xyz();
      position_c[count][0] = uarm.get_current_x();
      position_c[count][1] = uarm.get_current_y();
      temp = uarm.get_current_z();
      position_c[count][2] = temp + 5;
      pump_status_auto_c[count] = 1;
      count++;

      position_c[count][0] = uarm.get_current_x();
      position_c[count][1] = uarm.get_current_y();
      temp = uarm.get_current_z();
      position_c[count][2] = temp + 2;
      pump_status_auto_c[count] = 0;
      count++;

      position_c[count][0] = 0;
      position_c[count][1] = 0;
      position_c[count][2] = 0;
      pump_status_auto_c[count] = 0;
    }

    else if (readSerial == 'r')
    {
      int reset_counter = 0;
      while (reset_counter < 20)
      {
        x[reset_counter] = 0;
        y[reset_counter] = 0;
        z[reset_counter] = 0;
        reset_counter++;
      }

      for(int i = 0; i < 6; i++)
      {
        position_b[i][0] = 0;
        position_b[i][1] = 0;
        position_b[i][2] = 0;
        position_c[i][0] = 0;
        position_c[i][1] = 0;
        position_c[i][2] = 0;
      }

      int pump_reset = 0;
      while (pump_reset < 10)
      {
        pump_status_manual[pump_reset] = 0;
        pump_status_auto_a[pump_reset] = 0; 
        pump_status_auto_b[pump_reset] = 0; 
        pump_status_auto_c[pump_reset] = 0;
        pump_reset++;
      }

      counter = 0;
      pump_reset = 0;
    }

    else if (readSerial == 'a')
    {

    }

    else if (readSerial == 'e')
    {
      for (int x = 0; x < 6; x++)
      {
        uarm.move_to(position_b[x][0], position_b[x][1], position_b[x][2];
      }

      for (int x = 0; x < 3; x++)
      {
        uarm.move_to(position_c[x][0], position_c[x][1], position_c[x][2]);
      }
    }




  } // close read available
}
