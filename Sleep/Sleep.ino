#define uS_TO_S_FACTOR 1000000  //Factor de conversion de us a s
#define TIME_TO_SLEEP 10        //Tiempo durante el que lo queremos dormir 
#define LED_PIN 32              // Led

void setup() {
  Serial.begin(115200);
  //Configuracion Light Sleep
  //la función esp_sleep_enable_timer_wakeup(tiempo en us)
  pinMode(LED_PIN, OUTPUT);
  
  esp_sleep_enable_timer_wakeup(TIME_TO_SLEEP*uS_TO_S_FACTOR); //10 segundos para despertar
  Serial.println("Configurando ESP32 para dormir por " + String(TIME_TO_SLEEP) + " segundos.");
}

void loop() {
  digitalWrite(LED_PIN, LOW);
  delay(5);
  //Usando esp_light_sleep_start() inicia el modo ligth_sleep
  esp_light_sleep_start(); //Se va a quedar en light sleep hasta que no le digamos lo contrario

  digitalWrite(LED_PIN, HIGH);
  delay(500);

  print_wakeup_reason();
}

//-----------------------------------------------------------------------------------------
//Función que vamos a usar despues para ver cual fue la razon para despertar
void print_wakeup_reason(){
  //Se usa un tipo de dato especial de la librería para dormir 
  //esp_sleep_wakeup_cause_t (esa t al final significa type)
  esp_sleep_wakeup_cause_t wakeup_reason;

  wakeup_reason = esp_sleep_get_wakeup_cause();

    switch (wakeup_reason){
    case ESP_SLEEP_WAKEUP_EXT0:
      Serial.println("Inicio causado por señal en el RTC_IO (periféricos del RTC)");
    break;

    case ESP_SLEEP_WAKEUP_EXT1:
      Serial.println("Inicio causado por señal en el RTC_CNTL (controlador del RTC)");
    break;

    case ESP_SLEEP_WAKEUP_TIMER:
      Serial.println("Inicio causado por señal en un timer");
    break;

    case ESP_SLEEP_WAKEUP_TOUCHPAD:
      Serial.println("Inicio causado por señal en un pin touch (botón del ESP32)");
    break;

    case ESP_SLEEP_WAKEUP_ULP:
      Serial.println("Inicio causado por señal lanzada por el ULP(ultralow) Croprocessor");
    break;

    default:
      Serial.printf("El inicio no fue causado por ninguna razón conocida: %d \n", wakeup_reason);
    break;
    }
}
//-----------------------------------------------------------------------------------------
