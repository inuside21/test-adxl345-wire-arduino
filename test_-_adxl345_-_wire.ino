#include<Wire.h>

#define accel_module (0x1d)         // SDO-> Vcc
#define accel_module2 (0x53)       // SDO-> GND

byte values[6];
byte values2[6];
char output[512];
char output2[512];

void getAccelration(int accelSensor, int cal)
{
  int xyzregister = 0x32;
  int x, y, z;

  Wire.beginTransmission(accelSensor);
  Wire.write(0x2D);
  Wire.write(0);
  Wire.endTransmission();
  Wire.beginTransmission(accelSensor);
  Wire.write(0x2D);
  Wire.write(16);
  Wire.endTransmission();
  Wire.beginTransmission(accelSensor);
  Wire.write(0x2D);
  Wire.write(8);
  Wire.endTransmission();

  Wire.beginTransmission(accelSensor);
  Wire.write(xyzregister);
  Wire.endTransmission();

  Wire.beginTransmission(accelSensor);
  Wire.requestFrom(accelSensor, 6);

  int i = 0;
  while(Wire.available())
  {
    values[i] = Wire.read();
    i++;
    }
  Wire.endTransmission();

  x = (((int)values[1]) << 8) | values[0];
  y = (((int)values[3])<< 8) | values[2];
  z = (((int)values[5]) << 8) | values[4];
  sprintf(output, "%d",z);
  Serial.print(output);
  }

  
void setup()
{
  Wire.begin();
  Serial.begin(9600);
}

void loop() 
{
  getAccelration(accel_module, 205); // ********accel 0x1D*********//
  Serial.print("    From2: ");
  getAccelration(accel_module2, 28);  //*******accel 0x53********//

  Serial.println();  
  
  delay(200); 
}
