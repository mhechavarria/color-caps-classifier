//Blink without delay
unsigned long interval = 250000;
unsigned long previousMicros;
unsigned long contPasos = 0;



#define PIN_STEP_MOTOR1 13
#define PIN_SENTIDO_MOTOR1 12
#define PIN_ENTRADA_DER 7
#define PIN_ENTRADA_IZQ 6


#define CANT_PASOS_MOTOR1 5



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
   previousMicros = micros();
   pinMode(PIN_STEP_MOTOR1, OUTPUT);
   pinMode(PIN_SENTIDO_MOTOR1, OUTPUT);
   pinMode(PIN_ENTRADA_DER, INPUT_PULLUP);
   pinMode(PIN_ENTRADA_IZQ, INPUT_PULLUP);
}
void loop() {
  mef_motor1();
}

void mef_motor1 (void)
{
  static estMef_motor1_enum estMef_motor1 = EST_INICIAL;

  switch (estMef_motor1)
  {
    case EST_INICIAL:
      digitalWrite(PIN_SENTIDO_MOTOR1, IZQ); //Inicializo la direccion
      digitalWrite(PIN_STEP_MOTOR1, LOW);
     //pensar logica para que se alinee
      estMef_motor1 = EST_WAIT;
    break;
    
    case EST_WAIT:
      if(!digitalRead(PIN_ENTRADA_DER))
      {
        estMef_motor1 = EST_GIRO_DER;
      }
      if(!digitalRead(PIN_ENTRADA_IZQ))
      {
        estMef_motor1 = EST_GIRO_DER;
      }
    break;   
       
    case EST_GIRO_DER:
        giraMotor(DER, CANT_PASOS_MOTOR1);//girar para la derecha
        if(contPasos == CANT_PASOS_MOTOR1)
        {
          estMef_motor1 = EST_WAIT;
          contPasos = 0;
          digitalWrite(PIN_STEP_MOTOR1, LOW);
        }
    break;
    
    case EST_GIRO_IZQ:
        giraMotor(IZQ, CANT_PASOS_MOTOR1); // girar para la izquierda
        if(contPasos == CANT_PASOS_MOTOR1)
        {
          estMef_motor1 = EST_WAIT;
          contPasos = 0;
          digitalWrite(PIN_STEP_MOTOR1, LOW);
        }
    break;
    
    default:
      estMef_motor1 = EST_WAIT;
    break;
  }
}

void giraMotor(bool SENTIDO, unsigned long PASOS)
{
   unsigned long currentMicros = micros();
   
   if (((unsigned long)(currentMicros - previousMicros) >= interval) && (contPasos < PASOS+1))
   {
       state = !state;
       if (state) 
       {
       digitalWrite(PIN_SENTIDO_MOTOR1, SENTIDO);
       digitalWrite(PIN_STEP_MOTOR1, HIGH);
       contPasos ++;
       }      
       
       if (!state) 
       {
       digitalWrite(PIN_STEP_MOTOR1, LOW);
       }
       previousMicros = micros();
   }
}
