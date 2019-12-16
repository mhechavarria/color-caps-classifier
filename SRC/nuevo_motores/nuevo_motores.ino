#include <CircularBuffer.h>

#include <TimerOne.h>
#include "driver_motor.h"
#include "sensor.h"


/////////////////////////////////////////
// DECLARACION DE VARIABLES DE TIMEOUT //
/////////////////////////////////////////
bool habilito_timeOut = 0;
unsigned long conTimeOut = 1500;
#define valorconTimeOut 1000;


//////////////////////////
// DECLARACION DE PINES //
//////////////////////////
/* configracion de pines del motor 1*/
#define PIN_STEP_M1 17 //en nano es 17
#define PIN_SENTIDO_M1 18  //en nano es 18 
#define CANT_PASOS_MOTOR1 8

/* configracion de pines del sensor 1*/
#define PIN_ENTRADA_SENSOR1 12


/* configracion de pines del motor 2*/
#define PIN_STEP_M2 5 //en nano es 5
#define PIN_SENTIDO_M2 4 //en nano es 4
#define CANT_PASOS_MOTOR2 8

/* configracion de pines del sensor 2*/
#define PIN_ENTRADA_SENSOR2 3

/* configracion de pines del motor 3*/
#define PIN_STEP_M3 7 //en nano es 7
#define PIN_SENTIDO_M3 6 //en nano es 6
#define CANT_PASOS_MOTOR3 8

/* PIN del modulo RS485*/
#define PIN_485 2


//////////////////////////
// DIRECCION DE MOTORES //
//////////////////////////
#define DER 1
#define IZQ 0




/////////////////////////
// OTRAS DECLARACIONES //
/////////////////////////

CircularBuffer<int, 3> circularBuffer;

void printArray(int* x, int length, char separator)
{
  for (int iCount = 0; iCount < length-1; iCount++)
  {
    Serial.print(x[iCount]);
    Serial.print(separator);
  }
  Serial.print(x[length - 1]);
  //Serial.println();
}

void setup() 
{  
   //Configuracion serial
   Serial.begin(9600);
   RS485_receiveEnable();

   //Capturar el primer micros
   previousMicros = micros();
   
   /*pines del motor 1*/
   pinMode(PIN_STEP_M1, OUTPUT);
   pinMode(PIN_SENTIDO_M1, OUTPUT);
   digitalWrite(PIN_STEP_M1, LOW);
   digitalWrite(PIN_SENTIDO_M1, LOW);

   /*pines del motor 2*/
   pinMode(PIN_STEP_M2, OUTPUT);
   pinMode(PIN_SENTIDO_M2, OUTPUT);   
   digitalWrite(PIN_STEP_M2, LOW);
   digitalWrite(PIN_SENTIDO_M2, LOW);

   /*pines del motor 3*/
   pinMode(PIN_STEP_M3, OUTPUT);
   pinMode(PIN_SENTIDO_M3, OUTPUT);
   digitalWrite(PIN_STEP_M3, LOW);
   digitalWrite(PIN_SENTIDO_M3, LOW);

   /*Interrupcion de sensores*/
   pinMode(PIN_ENTRADA_SENSOR1, INPUT);
   pinMode(PIN_ENTRADA_SENSOR2, INPUT);

   /*PIN del modulo RS485*/
   pinMode(PIN_485, OUTPUT);


//   attachInterrupt(digitalPinToInterrupt(PIN_ENTRADA_SENSOR1), sensor1, FALLING);
//   attachInterrupt(digitalPinToInterrupt(PIN_ENTRADA_SENSOR2), sensor2, FALLING);

   /*Inicializo el timer*/
   Timer1.initialize(1000);         // Dispara cada 1 ms
   Timer1.attachInterrupt(ISR_Timer); // Activa la interrupcion y la asocia a ISR_Timer

        
        habilito_timeOut = 0;
}

void loop()
{
  mef_motor1();
  mef_motor2();
  mef_motor3();
  //mef_sensor_1_antirreb();
  //mef_sensor_2_antirreb();
  mef_recepcion();
  mef_seleccion();
  time_out_banderas();
}



void time_out_banderas(void)
{
  if(conTimeOut == 0 && habilito_timeOut)
  {
    RS485_sendEnable();
    Serial.println('c');
    Serial.println("Timeout");
    RS485_receiveEnable();
    
    habilito_gris = 0;
    habilito_verde = 0;
    habilito_rojo = 0;
    habilito_azul = 0;
    habilito_amarillo = 0;
    habilito_naranja = 0;  
    habilito_timeOut = 0; 
    conTimeOut = valorconTimeOut; 
  }
}



void ISR_Timer()
{
  if(contTimer)
  {
    contTimer--;
  }
  if(timAreb)
  {
    timAreb--;
  }
  if(habilito_timeOut)
  {
    conTimeOut --;
  }
  
}
