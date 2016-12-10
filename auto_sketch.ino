//Header Files
#include "uarm_library.h"

//auto movement struct
struct a_movement
{
  float position_a[2][3];
  float position_b[6][3];
  float position_c[3][3];
};

//variable declaration
a_movement autoMove;
float armDifference = 0;

//setup function
void setup() {

  Wire.begin();      // join i2c bus (address optional for master)
  Serial.begin(9600); // start serial port at 9600 bps
}

//Main function for arduino
void loop() {

  //If there are any inputs in the serial port it will then execute this condition
  if (Serial.available() > 0)
  {

    //reading serial port
    char readSerial = Serial.read();
    Serial.println(readSerial);

    //----------------------------------  function 1  ------------------------------------
    // function below is for move uArm from current position to absolute coordinate
    // x = 13, y = -13, z = 3

    //if serial port sends 1 which means demo mode
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

    //if serial port sends A it will then proceed to save position A
    if (readSerial == 'A')
    {
      int count = 0;
      double temp;
      uarm.get_current_xyz();
      autoMove.position_a[count][0] = uarm.get_current_x();
      autoMove.position_a[count][1] = uarm.get_current_y();
      temp = uarm.get_current_z();
      autoMove.position_a[count][2] = temp + 5;
      count++;

      autoMove.position_a[count][0] = uarm.get_current_x();
      autoMove.position_a[count][1] = uarm.get_current_y();
      autoMove.position_a[count][2] = uarm.get_current_z() + armDifference;
      count++;
    }

    
    //if serial port sends b it will then proceed to save position b
    if (readSerial == 'b')
    {

      double temp;
      int count = 0;

      uarm.get_current_xyz();
      autoMove.position_b[count][0] = uarm.get_current_x();
      autoMove.position_b[count][1] = uarm.get_current_y();
      temp = uarm.get_current_z();
      autoMove.position_b[count][2] = temp + 5;
      count++;

      autoMove.position_b[count][0] = uarm.get_current_x();
      autoMove.position_b[count][1] = uarm.get_current_y();
      autoMove.position_b[count][2] = uarm.get_current_z();
      count++;

      autoMove.position_b[count][0] = -0.5;
      autoMove.position_b[count][1] = -5.55;
      autoMove.position_b[count][2] = 18;
      count++;

      autoMove.position_b[count][0] = uarm.get_current_x();
      autoMove.position_b[count][1] = uarm.get_current_y();
      temp = uarm.get_current_z();
      autoMove.position_b[count][2] = temp + 5;
      count++;

      autoMove.position_b[count][0] = uarm.get_current_x();
      autoMove.position_b[count][1] = uarm.get_current_y();
      autoMove.position_b[count][2] = uarm.get_current_z();
      count++;


      autoMove.position_b[count][0] = -0.5;
      autoMove.position_b[count][1] = -5.55;
      autoMove.position_b[count][2] = 18;
      count++;


    }

    
    //if serial port sends c it will then proceed to save position c
    if (readSerial == 'c')
    {
      double temp;
      int count = 0;
      uarm.get_current_xyz();
      autoMove.position_c[count][0] = uarm.get_current_x();
      autoMove.position_c[count][1] = uarm.get_current_y();
      temp = uarm.get_current_z();
      autoMove.position_c[count][2] = temp + 5;

      count++;

      autoMove.position_c[count][0] = uarm.get_current_x();
      autoMove.position_c[count][1] = uarm.get_current_y();
      temp = uarm.get_current_z();
      autoMove.position_c[count][2] = temp - armDifference;
      count++;

      autoMove.position_c[count][0] = -0.5;
      autoMove.position_c[count][1] = -5.55;
      autoMove.position_c[count][2] = 18;
    }

    
    //if serial port sends e it will then proceed to execute the movement of the arm
    if (readSerial == 'e')
    {
      uarm.set_servo_status(true, SERVO_ROT_NUM);
      uarm.set_servo_status(true, SERVO_LEFT_NUM);
      uarm.set_servo_status(true, SERVO_RIGHT_NUM);

      for (int i = 0; i < 2; i++)
      {
        if(i + 1 == 2)
        {
          autoMove.position_a[i][2] = autoMove.position_a[i][2] - armDifference;
        }
        delay(500);
        uarm.move_to(autoMove.position_a[i][0], autoMove.position_a[i][1], autoMove.position_a[i][2]);
        delay(1000);
        if (i + 1 == 2)
        {
          uarm.pump_on();
        }
      }

      for (int i = 0; i < 6; i++)
      {

        delay(500);
        uarm.move_to(autoMove.position_b[i][0], autoMove.position_b[i][1], autoMove.position_b[i][2]);
        delay(1000);
        if (i + 1 == 1 || i + 1 == 5 || i + 1 == 6)
        {
          uarm.pump_on();
        }
        else
        {
          uarm.pump_off();
        }
      }

      for (int i = 0; i < 3; i++)
      {
        if(i + 1 == 2)
        {
          autoMove.position_c[i][2] = autoMove.position_c[i][2] + armDifference;
        }
        delay(500);
        uarm.move_to(autoMove.position_c[i][0], autoMove.position_c[i][1], autoMove.position_c[i][2]);
        delay(1000);
        if (i + 1 == 2)
        {
          uarm.pump_off();
        }
      }

      uarm.set_servo_status(false, SERVO_ROT_NUM);
      uarm.set_servo_status(false, SERVO_LEFT_NUM);
      uarm.set_servo_status(false, SERVO_RIGHT_NUM);

      Serial.print('D');

    }

    
    //if serial port sends h it will then proceed to save the height of the object
    if (readSerial == 'h')
    {
      float temp;
      uarm.get_current_xyz();
      temp = uarm.get_current_z();
      armDifference = temp - 8.25;
    }

    
    //attach Servo function
    if (readSerial == 'a')
    {
      uarm.set_servo_status(true, SERVO_ROT_NUM);
      uarm.set_servo_status(true, SERVO_LEFT_NUM);
      uarm.set_servo_status(true, SERVO_RIGHT_NUM);

    }
  }
}
