  #include <Servo.h>

  char data = 0; 
  Servo x;
  Servo y;
  void setup()
{
      Serial.begin(9600);                               
      x.attach(5);
      y.attach(6);
}

    void loop()
{
      if(Serial.available() > 0)  
   {
        data = Serial.read();       
        if(data == '1'){          
          x.write(90);
          y.write(90);}   
        else if(data == '0'){         
          x.write(0);
          y.write(0);}
          }
}
