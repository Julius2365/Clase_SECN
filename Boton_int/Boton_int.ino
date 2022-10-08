struct Button {
  const int PIN;
  int numTimeButtonPressed;
  bool pressed; 
  //bool bStatus;
};

Button button1 = {33, 0, false};

void IRAM_ATTR isr_button(){
  button1.numTimeButtonPressed +=1;
  button1.pressed = true;
  //button1.bStatus = 1;
}

void setup() {
  Serial.begin(9600);
  pinMode(button1.PIN, INPUT);
  attachInterrupt(button1.PIN, isr_button, RISING);
}

void loop() {
  if (button1.pressed == true){
    Serial.printf("El Boton se ha presionado %u veces \n", button1.numTimeButtonPressed);
    button1.pressed=false;
  }//else{
    //Serial.print("bStatus: ");
    //Serial.println(button1.bStatus);
  
  delay(100);

}
