#include <Servo.h>
#include <SPI.h>        // Include SPI library (needed for the SD card)
#include <SD.h>         // Include SD library
#include <DHT.h>        // Include DHT sensor library
 
#define DHTPIN 4            // DHT11 data pin is connected to Arduino pin 4
#define DHTTYPE DHT11       // DHT11 sensor is used
DHT dht(DHTPIN, DHTTYPE);
File dataFile;// Initialize DHT library
char data = 0; //Variable for storing received data
Servo x;
void setup()
{
   Serial.begin(9600);
  while (!Serial)
    ; // wait for serial port to connect. Needed for native USB port only
  Serial.print("Initializing SD card...");
  if (!SD.begin()) {
    Serial.println("initialization failed!");
    while (1);
  }
  Serial.println("initialization done.");
  delay(2000);
}
   //Sets the baud for serial data transmission                               
//    x.attach(9); //Sets digital pin 13 as output pin
}
uint16_t line = 1;
void loop()
{
   delay(1000);
  // Read humidity
  byte RH = dht.readHumidity();
  //Read temperature in degree Celsius
  byte Temp = dht.readTemperature();
  
  dataFile = SD.open("DHT11Log.txt", FILE_WRITE);
  
  // if the file opened okay, write to it:
  if (dataFile) {
    Serial.print(line);
    Serial.print(":    Temperature = ");
    Serial.print(Temp);
    Serial.print("°C,    Humidity = ");
    Serial.print(RH);
    Serial.println("%");
    // Write data to SD card file (DHT11Log.txt)
    dataFile.print(line++);
    dataFile.print(":    Temperature = ");
    dataFile.print(Temp);
    dataFile.print("°C,    Humidity = ");
    dataFile.print(RH);
    dataFile.println("%");
    dataFile.close();
    
  }
  // if the file didn't open, print an error:
  else
    Serial.println("error opening DHT11Log.txt");
   if(Serial.available() > 0)  // Send data only when you receive data:
   {
      data = Serial.read();        //Read the  incoming  data and store it into variable data
      Serial.print(data);          //Print Value inside data in Serial monitor
      Serial.print("\n");          //New line
      if(data == '1')              // Checks whether value of data is equal to 1
         x.write(90);   //If value is 1 then LED turns ON
      else if(data == '0')         //  Checks  whether value of data is equal to 0
         x.write(0);    //If value is 0 then LED turns OFF
   }
}
