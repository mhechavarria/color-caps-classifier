//Blink without delay
unsigned long interval = 1000;
unsigned long previousMillis;
unsigned long contPasos = 0;



#define PASOS_MOTOR1 10
#define PIN_SENTIDO 6
#define PIN_PASOS 13
#define PIN_ENTRADA_DER 7
#define PIN_ENTRADA_IZQ 6

bool state = false;
bool DER = 1;
bool IZQ = 0;

typedef enum
{
  EST_INICIAL = 0,
  EST_WAIT,
  EST_GIRO_DER,
  EST_GIRO_IZQ
}estMef_motor1_enum;


void setup() 
{   
   // Capturar el primer millis
   previousMillis = millis();
   pinMode(PIN_PASOS, OUTPUT);
   pinMode(PIN_SENTIDO, OUTPUT);
   pinMode(PIN_ENTRADA_DER, INPUT_PULLUP);
   pinMode(PIN_ENTRADA_IZQ, INPUT_PULLUP);
}
void loop() {

giraMotor(HIGH, 10);

}

void MEF_principal (void)
{
  static estMef_motor1_enum estMef_motor1 = EST_INICIAL;

  switch (estMef_motor1)
  {
    case EST_INICIAL:
      digitalWrite(PIN_SENTIDO, DER); //
     //pensar logica para que se alinee
      estMef_motor1 = EST_WAIT;
    break;
    
    case EST_WAIT:
      if(!digitalRead(PIN_ENTRADA_DER))
      {
        giraMotor(DER, PASOS_MOTOR1);//girar para la derecha
        if(contPasos == PASOS_MOTOR1-1)
        {
          estMef_motor1 = EST_GIRO_DER;
          contPasos = 0;
        }
      }
      if(!digitalRead(PIN_ENTRADA_IZQ))
      {
        giraMotor(IZQ, PASOS); // girar para la izquierda
        if(contPasos == PASOS-1)
        {
          estMef_motor1 = EST_GIRO_IZQ;
          contPasos = 0;
        }
      }
    break;   
//       
//    case EST_GIRO_DER:
//      estMef_motor1 = EST_WAIT;
//    break;
//    
//    case EST_GIRO_IZQ:
//      giraMotor(SENTIDO, PASOS);
//      estMef_motor1 = EST_WAIT;
//    break;
    
    default:
      estMef_motor1 = EST_WAIT;
    break;
  }
}

void giraMotor(bool SENTIDO, unsigned long PASOS)
{
   unsigned long currentMillis = millis();
   
   if (((unsigned long)(currentMillis - previousMillis) >= interval) && contPasos < PASOS)
   {
       state = !state;
       if (state) 
       {
       digitalWrite(PIN_SENTIDO, SENTIDO);
       digitalWrite(PIN_PASOS, HIGH);
       contPasos ++;
       }      
       
       if (!state) 
       {
       digitalWrite(PIN_PASOS, LOW);
       }
       previousMillis = millis();
   }
}
