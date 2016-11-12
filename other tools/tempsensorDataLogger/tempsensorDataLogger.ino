/*************************************************** 
  This is a library example for the MLX90614 Temp Sensor

  Designed specifically to work with the MLX90614 sensors in the
  adafruit shop
  ----> https://www.adafruit.com/products/1748
  ----> https://www.adafruit.com/products/1749

  These sensors use I2C to communicate, 2 pins are required to  
  interface
  Adafruit invests time and resources providing this open source code, 
  please support Adafruit and open-source hardware by purchasing 
  products from Adafruit!

  Written by Limor Fried/Ladyada for Adafruit Industries.  
  BSD license, all text above must be included in any redistribution
 ****************************************************/

#include <Wire.h>
#include <Adafruit_MLX90614.h>
#include <SPI.h>
#include <SD.h>

Adafruit_MLX90614 mlx = Adafruit_MLX90614();
const int chipSelect = 4;
String ambientTempFileName = "ambTemp";
String objectTempFileName = "objTemp";
String pirFileName = "pirSign";

int pirPin = 7;

void setup() {
  Serial.begin(9600);
  mlx.begin();  
  Serial.print("Initializing SD card...");

  // see if the card is present and can be initialized:
  if (!SD.begin(chipSelect)) {
    Serial.println("Card failed, or not present");
    // don't do anything more:
    return;
  }
  Serial.println("card initialized.");
  pinMode(pirPin, INPUT);
  
  objectTempFileName = getFileName(objectTempFileName);
  ambientTempFileName = getFileName(ambientTempFileName);
  pirFileName = getFileName(pirFileName);
  Serial.println(objectTempFileName);
  Serial.println(ambientTempFileName);
  Serial.println(pirFileName);
}

String getFileName(String filename){
    for (int i=0; i <= 9; i++){
      String testName = filename + (String) i + ".txt";
      if(!SD.exists(testName)){
        return testName;
      }
    }
    return filename + "9" + ".txt";
}

void loop() {
  unsigned long timeStart = millis();
  
  Serial.print("Ambient = "); Serial.print(mlx.readAmbientTempC()); 
  Serial.print("*C\tObject = "); Serial.print(mlx.readObjectTempC()); Serial.println("*C");
  Serial.println();

  String dataString = String(mlx.readObjectTempC(),2);
  dataString = dataString + ",";
    
  // open the file. note that only one file can be open at a time,
  // so you have to close this one before opening another.
  File dataFile1 = SD.open(objectTempFileName, FILE_WRITE);

  // if the file is available, write to it:
  if (dataFile1) {
    dataFile1.println(dataString);
    dataFile1.close();
    // print to the serial port too:
    Serial.println(dataString);
  }
  // if the file isn't open, pop up an error:
  else {
    Serial.println("error opening objtempc.txt");
  }
  
  dataString = String(mlx.readAmbientTempC(),2);
  dataString = dataString + ",";
  File dataFile2 = SD.open(ambientTempFileName, FILE_WRITE);

  // if the file is available, write to it:
  if (dataFile2) {
    dataFile2.println(dataString);
    dataFile2.close();
    // print to the serial port too:
    Serial.println(dataString);
  }
  // if the file isn't open, pop up an error:
  else {
    Serial.println("error opening ambTempC.txt");
  }
  
  
  dataString = digitalRead(pirPin);
  dataString = dataString + ",";
  File dataFile3 = SD.open(pirFileName, FILE_WRITE);

  // if the file is available, write to it:
  if (dataFile3) {
    dataFile3.println(dataString);
    dataFile3.close();
    // print to the serial port too:
    Serial.println(dataString);
  }
  // if the file isn't open, pop up an error:
  else {
    Serial.println("error opening pir data file");
  }

  unsigned long waitTime = 500 - (millis() - timeStart);
  Serial.println(waitTime);
  if(waitTime > 500){
    waitTime = 500;
    }
  delay(waitTime);
}
