#include <sd_defines.h>
#include <SD.h>
#include <sd_diskio.h>
#include <Adafruit_BMP085.h>

#define PIN_LED 32

Adafruit_BMP085 bmp;
File readings;
File read_me;
char payload[50]; //Datos a escribir en SD y Serial

void setup() {
  Serial.begin(9600); //Inicializar serial UART-USB
  bmp.begin(0x77); //Inicializar comunicacion I2C con el sensor barometrico  
  SD.begin(); //Inicializar SD

  pinMode(PIN_LED,OUTPUT);

  //readme
  read_me = SD.open("/README.txt, FILE_WRITE");
  read_me.print("Archivo de lecturasdel sensor BMP180\n Temperatura [°C],Presion[Pa]");
  read_me.close();
}

void loop() {
  float T=bmp.readTemperature();
  float P= bmp.readPressure();
  //Escribo las lecturas en payload
  sprintf(payload,"%.2f,%.2f",T,P);
  Serial.println(payload);
  //Abro archivo y escribo
  
  digitalWrite (PIN_LED, HIGH);
    readings = SD.open("/readings.csv",FILE_APPEND);
    readings.println(payload);
    readings.close();
  digitalWrite(PIN_LED, LOW);  
  delay(500);
}
