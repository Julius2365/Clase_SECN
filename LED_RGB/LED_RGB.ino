#define LED_R 14
#define LED_G 27 
#define LED_B 12
#define PIN_BUTTON 33

int led_status = 0;

//debouncing
unsigned long lastDebounceTime = 0;
unsigned long debounceDelay = 200; //delay para debouncing en ms

//Al presionar un botón, cambia el color del led
void IRAM_ATTR isr_button(){
  if ((millis() - lastDebounceTime) > debounceDelay){
     led_status++; if (led_status >= 8){led_status = 0;}
     lastDebounceTime = millis();
  }
}

void setup() {
  //Button
  pinMode(PIN_BUTTON, INPUT);
  attachInterrupt (PIN_BUTTON,isr_button, RISING);

  //Leds
  pinMode (LED_R, OUTPUT);
  pinMode (LED_G, OUTPUT);
  pinMode (LED_B, OUTPUT);
  
  Serial.begin(115200);
}

void loop() {
  switch (led_status){
    case 1:  //rojo
      digitalWrite(LED_R, LOW);
      digitalWrite(LED_G, HIGH);
      digitalWrite(LED_B, HIGH);
    break;
    
    case 2:  //Green
      digitalWrite(LED_R, HIGH);
      digitalWrite(LED_G, LOW);
      digitalWrite(LED_B, HIGH);
    break;
    
    case 3:  //blue
      digitalWrite(LED_R, HIGH);
      digitalWrite(LED_G, HIGH);
      digitalWrite(LED_B, LOW);
    break;
    
    case 4:  //rojo
      digitalWrite(LED_R, HIGH);
      digitalWrite(LED_G, LOW);
      digitalWrite(LED_B, LOW);
    break;
    
    case 5:  //Yellow
      digitalWrite(LED_R, LOW);
      digitalWrite(LED_G, LOW);
      digitalWrite(LED_B, HIGH);
    break;
    
    case 6:  //magenta
      digitalWrite(LED_R, LOW);
      digitalWrite(LED_G, HIGH);
      digitalWrite(LED_B, LOW);
    break;

    case 7:  //white
      digitalWrite(LED_R, LOW);
      digitalWrite(LED_G, LOW);
      digitalWrite(LED_B, LOW);
    break;
    
    default:  //rojo
      digitalWrite(LED_R, HIGH);
      digitalWrite(LED_G, HIGH);
      digitalWrite(LED_B, HIGH);
    break;
  }

}
