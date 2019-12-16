//////////////////////////
// DECLARACION DE PINES //
//////////////////////////
/* configracion de pines del motor 1*/
#define PIN_STEP_M1 13 //en nano es 17
#define PIN_SENTIDO_M1 12  //en nano es 18
#define DELAY 230

/* PIN del modulo RS485*/
#define PIN_485 12



void setup() 
{
  /*serial*/
  Serial.begin(9600);
  /*PIN del modulo RS485*/
   pinMode(PIN_485, OUTPUT);
  /*pines del motor 1*/
  pinMode(PIN_STEP_M1, OUTPUT);
  digitalWrite(PIN_STEP_M1, LOW);
  RS485_sendEnable();
}

void loop() 
{
  static uint8_t c;
  if (Serial.available())
  {
    c = Serial.read();
    //Serial.println((uint8_t) c);
    if (c == 'p')
    {
      for(int i=0; i<533; i++)
      {
        digitalWrite(PIN_STEP_M1, HIGH);   // turn the LED on (HIGH is the voltage level)
        delayMicroseconds(DELAY);                       // wait for a second
        digitalWrite(PIN_STEP_M1, LOW);    // turn the LED off by making the voltage LOW
        delayMicroseconds(DELAY);                       // wait for a second
      }
      //RS485_sendEnable();
      Serial.println((uint8_t) 'k');
      //RS485_receiveEnable();
    }
    Serial.println((uint8_t) 'k');
    delay(500);
  }
}


/*           FUNCIONES            */

void RS485_sendEnable(void){
  delay(5);
  digitalWrite(PIN_485, HIGH);
  delay(5);
}

void RS485_receiveEnable(void){
  delay(5);
  digitalWrite(PIN_485, LOW);
  delay(5);
}
