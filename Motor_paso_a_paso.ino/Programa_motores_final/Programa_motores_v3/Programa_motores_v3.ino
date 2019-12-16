#include "CircularBufferLib.h"
#include <TimerOne.h>


unsigned long interval = 100000;
unsigned long intervaltemp = 3000000;
unsigned long previousMicros;
unsigned long contPasos = 0;

unsigned long cont = 0;
unsigned long volver = 0;

unsigned long previousMicrosDerecha;


/* configracion de pines del motor 1*/
#define PIN_STEP_MOTOR1 13
#define PIN_SENTIDO_MOTOR1 12
//#define PIN_ENTRADA_DER 6
//#define PIN_ENTRADA_IZQ 7  // CAMBIAR EN EL PROGRMA DEL DRIVE
#define CANT_PASOS_MOTOR1 10

/* configracion de pines del sensor 1*/
#define PIN_ENTRADA_SENSOR1 2

///* configracion de pines del motor 2*/
//#define PIN_STEP_MOTOR2 13
//#define PIN_SENTIDO_MOTOR2 12
//#define CANT_PASOS_MOTOR2 10
//
///* configracion de pines del sensor 2*/
//#define PIN_ENTRADA_SENSOR2 11
//
///* configracion de pines del motor 1*/
//#define PIN_STEP_MOTOR3 13
//#define PIN_SENTIDO_MOTOR3 12
//#define CANT_PASOS_MOTOR3 10
//
///* configracion de pines del sensor 3*/
//#define PIN_ENTRADA_SENSOR3 11

CircularBuffer<int> circularBuffer(5);

/*Banderas de comunicacion entre mef*/
bool habilito_motor1 = 0;
bool habilito_rojo_m1 = 0;
bool temp_derecha = 0;



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
  
   //Configuracion serial
   Serial.begin(9600);
   for (int iCount = 0; iCount <= 5; iCount++)
   {
    circularBuffer.Add(0);
   }
   
   // Capturar el primer micros
   previousMicros = micros();

   /*pines del motor 1*/
   pinMode(PIN_STEP_MOTOR1, OUTPUT);
   pinMode(PIN_SENTIDO_MOTOR1, OUTPUT);


   /* Interrupcion de sensores*/
   pinMode(PIN_ENTRADA_SENSOR1, INPUT_PULLUP);
   attachInterrupt(digitalPinToInterrupt(PIN_ENTRADA_SENSOR1), juancarlos, FALLING);

   /*Inicializo el timer*/
   Timer1.initialize(1000);         // Dispara cada 250 ms
   Timer1.attachInterrupt(ISR_Timer); // Activa la interrupcion y la asocia a ISR_Timer
}
void loop() {
  mef_motor1();
  mef_recepcion_datos();
  mef_seleccion();
}

void mef_motor1 (void)
{
  static estMef_motor1_enum estMef_motor1 = EST_INICIAL;

  switch (estMef_motor1)
  {
    case EST_INICIAL:
      digitalWrite(PIN_SENTIDO_MOTOR1, LOW); //Inicializo la direccion
      digitalWrite(PIN_STEP_MOTOR1, LOW);
     //pensar logica para que se alinee
      estMef_motor1 = EST_WAIT;
    break;
    
    case EST_WAIT:
      if(habilito_motor1)
      {
       estMef_motor1 = EST_GIRO_DER;
      }
      if(habilito_motor1)
      {
        estMef_motor1 = EST_GIRO_IZQ; // ACA HAY QUE CAMBIAR POR IZQ EN EL DRIVE
      }
      break;

    
//       unsigned long currentMicrosDerecha = micros();
//       if (((unsigned long)(currentMicrosDerecha - previousMicrosDerecha) >= intervaltemp))
//       {
//           estMef_motor1 = EST_GIRO_DER;
//           previousMicros = micros();
//       }      
////      if(temp_derecha)
////      {
////        estMef_motor1 = EST_GIRO_DER;
////      }
//      if((habilito_rojo_m1 == 1)&&(habilito_motor1 == 1)) // acá habilito que gire a la izquierda para que salga la roja    (habilito_motor1 == 1
//      {
//        estMef_motor1 = EST_GIRO_IZQ; // ACA HAY QUE CAMBIAR POR IZQ EN EL DRIVE
//      }
//    break;   
       
    case EST_GIRO_DER:
        giraMotor(DER, CANT_PASOS_MOTOR1);//girar para la derecha
        
        if(contPasos == CANT_PASOS_MOTOR1)
        {
          cont = 5000;
        }

        if(volver)
        {
          volver = 0;
          estMef_motor1 = EST_WAIT;
          contPasos = 0;
          habilito_motor1 = 0;
          temp_derecha = 0;
          digitalWrite(PIN_STEP_MOTOR1, LOW);
        }
    break;
    
    case EST_GIRO_IZQ:
    //CONFIGURAR LA VUELTA DEL MOTOR
        giraMotor(IZQ, CANT_PASOS_MOTOR1); // girar para la izquierda
        
        if(contPasos == CANT_PASOS_MOTOR1)
        {
          estMef_motor1 = EST_WAIT;
          contPasos = 0;
          habilito_motor1 = 0;
          habilito_rojo_m1 = 0;
          intervaltemp = 3000000;
          digitalWrite(PIN_STEP_MOTOR1, LOW);
          previousMicrosDerecha = micros();
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



void mef_recepcion_datos (void)
{
  if (Serial.available()>0) 
  {
    char c = Serial.read();
    circularBuffer.Add(c);
  } 
}


void mef_seleccion(void)
{
  int dato = circularBuffer.ExtractFirst();
  if(dato == 'r')
  {
    habilito_rojo_m1 = 1;
    Serial.print("r");
    Serial.println();
  }
}

void ISR_Timer()
{
  cont--;
  if(cont == 0)
  {
    volver = 1;
  }
}
