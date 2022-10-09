// Leer Json desde SPIFFS 
// Deserializar un Json e imprimirlo por serial

#include <ArduinoJson.h>
#include <SPIFFS.h>

//Payload creado con snprintf
#define BUFFER_LEN  256
char payload[BUFFER_LEN]; //Payload Serializado
//String json_string;

//Payload crearon con Json parser
//Doc: https://arduinojson.org/
//Ticket: Usar reservación de memoria en stack
//Usar el json assistant para calcular el LEN necesario para cada documento

#define JSON_BUFFER_INCOMING_LEN 200
#define JSON_BUFFER_OUTGOING_LEN 200
DynamicJsonDocument payload_in(JSON_BUFFER_INCOMING_LEN); //Json desde SPIFFS,SD,Serial o MQTT (Stream)
DynamicJsonDocument payload_out(JSON_BUFFER_OUTGOING_LEN);//Json hacia SPIFFS,SD,Serial o MQTT (Stream)

void setup() {
  
  //Inicializar perifericos
  Serial.begin(115200); 
  SPIFFS.begin(true);

  

  
}


void loop() {
    
  File file_json;
  file_json = SPIFFS.open("/json_test.txt", FILE_READ);
  deserializeJson(payload_in,file_json);
  
  file_json.close(); 

  //Extracción de atributos
  const char* nombre_alumno = payload_in["nombre_alumno"];

  Serial.print("nombre_alumno: ");
  Serial.println(nombre_alumno);
  delay(5000);
                      
}
