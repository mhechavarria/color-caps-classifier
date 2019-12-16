#include "CircularBufferLib.h"

unsigned long interval = 100000;
unsigned long previousMicros;
unsigned long contPasos = 0;


const byte interruptPin = 2;

/* configracion de pines del motor 1*/
#define PIN_STEP_MOTOR1 13
#define PIN_SENTIDO_MOTOR1 12
#define PIN_ENTRADA_DER 6
#define PIN_ENTRADA_IZQ 7  // CAMBIAR EN EL PROGRMA DEL DRIVE
#define CANT_PASOS_MOTOR1 10

/* configracion de pines del sensor 1*/
#define PIN_ENTRADA_SENSOR1 11

///* configracion de pines del motor 2*/
//#define PIN_STEP_MOTOR2 13
//#define PIN_SENTIDO_MOTOR2 12
//#define CANT_PASOS_MOTOR2 10
//
///* configracion de pines del sensor 2*/
//#define PIN_ENTRADA_SENSOR2 11
//
///* configracion de pines del motor 3*/
//#define PIN_STEP_MOTOR3 13
//#define PIN_SENTIDO_MOTOR3 12
//#define CANT_PASOS_MOTOR3 10
//
///* configracion de pines del sensor 3*/
//#define PIN_ENTRADA_SENSOR3 11


bool habilito_motor1 = 0;
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


typedef enum
{
  EST_SENSOR1_INIT = 0,
  EST_SENSOR1_OFF,
  EST_SENSOR1_ON
}estMef_sensor1_enum;

void setup() 
{   
   // Capturar el primer millis
   previousMicros = micros();

   /*pines del motor 1*/
   pinMode(PIN_STEP_MOTOR1, OUTPUT);
   pinMode(PIN_SENTIDO_MOTOR1, OUTPUT);
   pinMode(PIN_ENTRADA_DER, INPUT_PULLUP);
   pinMode(PIN_ENTRADA_IZQ, INPUT_PULLUP);

   /* Interrupcion de sensores*/
   pinMode(interruptPin, INPUT_PULLUP);
   attachInterrupt(digitalPinToInterrupt(interruptPin), juancarlos, RISING);


}
void loop() {
  mef_motor1();
  //mef_sensor1();
}

void mef_motor1 (void)
{
  static estMef_motor1_enum estMef_motor1 = EST_INICIAL;

  switch (!estMef_motor1)
  {
    case EST_INICIAL:
      digitalWrite(PIN_SENTIDO_MOTOR1, LOW); //Inicializo la direccion
      digitalWrite(PIN_STEP_MOTOR1, LOW);
     //pensar logica para que se alinee
      estMef_motor1 = EST_WAIT;
    break;
    
    case EST_WAIT:
//      if(habilito_motor1)
//      {
//        estMef_motor1 = EST_GIRO_DER;
//      }
      if(habilito_motor1)
      {
        estMef_motor1 = EST_GIRO_IZQ; // ACA HAY QUE CAMBIAR POR IZQ EN EL DRIVE
      }
    break;   
       
    case EST_GIRO_DER:
        giraMotor(DER, CANT_PASOS_MOTOR1);//girar para la derecha
        
        if(contPasos == CANT_PASOS_MOTOR1)
        {
          estMef_motor1 = EST_WAIT;
          contPasos = 0;
          habilito_motor1 = 0;
          digitalWrite(PIN_STEP_MOTOR1, LOW);
        }
    break;
    
    case EST_GIRO_IZQ:
        giraMotor(IZQ, CANT_PASOS_MOTOR1); // girar para la izquierda
        
        if(contPasos == CANT_PASOS_MOTOR1)
        {
          estMef_motor1 = EST_WAIT;
          contPasos = 0;
          habilito_motor1 = 0;
          digitalWrite(PIN_STEP_MOTOR1, LOW);
        }
    break;
    
    default:
      estMef_motor1 = EST_WAIT;
    break;
  }
}
void juancarlos(void)
{
  habilito_motor1 = 1;
}

void mef_sensor1 (void)
{
    static estMef_sensor1_enum estMef_sensor1 = EST_SENSOR1_INIT;

    switch (estMef_sensor1)
    {
      case EST_SENSOR1_INIT:
      estMef_sensor1 = EST_SENSOR1_OFF;
      break;
      
      case EST_SENSOR1_OFF:
      if(!digitalRead(PIN_ENTRADA_SENSOR1))
      {
        habilito_motor1 = 1;
        estMef_sensor1 = EST_SENSOR1_ON;
      }
      break;
      
      case EST_SENSOR1_ON:
      if(digitalRead(PIN_ENTRADA_SENSOR1))
      {
        estMef_sensor1 = EST_SENSOR1_OFF;
      }
      break;    

      default:
      estMef_sensor1 = EST_SENSOR1_OFF;
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
