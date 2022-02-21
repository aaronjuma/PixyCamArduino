#include <Pixy2.h>
#include <Wire.h>
Pixy2 pixy;
int x_pos;
int y_pos;
String output;

void setup() {
  Serial.begin(115200);
  Wire.begin(4);
  Wire.onRequest(requestEvent); // Register a function to be called when a master requests data from this slave device
  pixy.init();
  output = "none";
}

void loop() {
  pixy.ccc.getBlocks();
  double area = 0, temp;
  int biggest;
  if (pixy.ccc.numBlocks)
  {
    for (int i=0; i<pixy.ccc.numBlocks; i++) {
      temp = pixy.ccc.blocks[i].m_y;
      if(temp > area){
        area = temp;
        biggest = i;
      }
    }
    x_pos = pixy.ccc.blocks[biggest].m_x;
    y_pos = pixy.ccc.blocks[biggest].m_y;


    output = x_pos;

    delay(70); //gives time for everything to process
    Serial.println(output);
  }  
}

void requestEvent(){//called when RoboRIO request a message from this device
  Wire.write(output.c_str()); //writes data to the RoboRIO, converts it to string
  Serial.println(output);
}
