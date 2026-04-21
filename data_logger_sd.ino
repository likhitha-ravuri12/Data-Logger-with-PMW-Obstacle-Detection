#include <SPI.h>
#include <SD.h>

#define TEMP_PIN A1
#define LDR_PIN A0
#define SD_CS 10   // Chip Select pin

unsigned long startTime;

File dataFile;

void setup() {
  Serial.begin(9600);

  // Initialize SD card
  if (!SD.begin(SD_CS)) {
    Serial.println("SD Card initialization failed!");
    return;
  }
  Serial.println("SD Card ready.");

  // Create/Open file
  dataFile = SD.open("data.csv", FILE_WRITE);

  if (dataFile) {
    dataFile.println("Time(s),Temperature(C),Light");
    dataFile.close();
  }

  startTime = millis();
}

void loop() {
  int tempValue = analogRead(TEMP_PIN);
  int light = analogRead(LDR_PIN);

  // Simple mapping for temp module
  float temperature = map(tempValue, 0, 1023, 20, 50);

  unsigned long timeStamp = (millis() - startTime) / 1000;

  dataFile = SD.open("data.csv", FILE_WRITE);

  if (dataFile) {
    dataFile.print(timeStamp);
    dataFile.print(",");
    dataFile.print(temperature);
    dataFile.print(",");
    dataFile.println(light);

    dataFile.close();
  }

  // Print to Serial also
  Serial.print(timeStamp);
  Serial.print(",");
  Serial.print(temperature);
  Serial.print(",");
  Serial.println(light);

  delay(1000); // 1 second interval
}