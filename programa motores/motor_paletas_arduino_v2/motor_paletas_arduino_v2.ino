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
  RS485_receiveEnable();
}

void loop() 
{
  static int c;
  if (Serial.available())
  {
    c = Serial.read();
    Serial.println(c);
    if (c == 'p')
    {
      for(int i=0; i<533; i++)
      {
        digitalWrite(PIN_STEP_M1, HIGH);   // turn the LED on (HIGH is the voltage level)
        delayMicroseconds(DELAY);                       // wait for a second
        digitalWrite(PIN_STEP_M1, LOW);    // turn the LED off by making the voltage LOW
        delayMicroseconds(DELAY);                       // wait for a second
        if(i==0){
          RS485_sendEnable();
          Serial.println('k');
          RS485_receiveEnable();
        }
      }
    }
  }
}


/*           FUNCIONES            */

void RS485_sendEnable(void){
  digitalWrite(PIN_485, HIGH);
}

void RS485_receiveEnable(void){
  digitalWrite(PIN_485, LOW);
}
