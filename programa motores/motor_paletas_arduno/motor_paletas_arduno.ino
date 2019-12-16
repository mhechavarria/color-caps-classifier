//////////////////////////
// DECLARACION DE PINES //
//////////////////////////
/* configracion de pines del motor 1*/
#define PIN_STEP_M1 13 //en nano es 17
#define PIN_SENTIDO_M1 12  //en nano es 18
#define DELAY 230

void setup() 
{
  /*serial*/
  Serial.begin(9600);
  /*pines del motor 1*/
  pinMode(PIN_STEP_M1, OUTPUT);
  digitalWrite(PIN_STEP_M1, LOW);
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
      }
    }
  }
}
