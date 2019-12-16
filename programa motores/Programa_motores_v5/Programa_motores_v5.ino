#include "CircularBufferLib.h"
#include <TimerOne.h>


unsigned long interval = 1000;
unsigned long intervaltemp = 100000;
unsigned long previousMicros;
unsigned long contPasos = 0;
unsigned long contPasos2 = 0;
bool habilito_rojo = 0;
bool habilito_azul = 0;
bool habilito_amarillo= 0;
bool habilito_verde = 0;
bool habilito_naranja = 0;
bool habilito_gris = 0;

unsigned long contTimer = 0;

unsigned long previousMicrosDerecha;
volatile bool newdata = 0;
volatile bool next_cap = 1;

/* configracion de pines del motor 1*/
#define STEP_M1 4
#define SENTIDO_M1 5
#define CANT_PASOS_MOTOR1 6

/* configracion de pines del sensor 1*/
#define PIN_ENTRADA_SENSOR1 2

/* configracion de pines del sensor 2*/
#define PIN_ENTRADA_SENSOR2 3

/* configracion de pines del motor 2*/
#define STEP_M2 6
#define SENTIDO_M2 7
#define CANT_PASOS_MOTOR2 6

/* configracion de pines del motor 3*/
#define STEP_M3 8
#define SENTIDO_M3 9
#define CANT_PASOS_MOTOR3 40

CircularBuffer<int> circularBuffer(5);

/*Banderas de comunicacion entre mef*/
bool habilito_motor1 = 0;
bool habilito_motor2 = 0;
bool habilito_motor3 = 0;

bool state = false;
bool state2 = false;
bool DER = 1;
bool IZQ = 0;

typedef enum
{
  EST_INICIAL = 0,
  EST_WAIT,
  EST_GIRO_DER,
  EST_GIRO_IZQ,
  EST_CIERRE_ESPERA_IZQ,
  EST_CIERRE_ESPERA_DER,
  EST_CIERRE_IZQ,
  EST_CIERRE_DER
}estMef_motor_enum;

typedef enum
{
  EST_SENSOR1_INIT = 0,
  EST_SENSOR1_OFF,
  EST_SENSOR1_ON
}estMef_sensor_enum;

void setup() 
{  
  
   //Configuracion serial
   Serial.begin(9600);

   // Capturar el primer micros
   previousMicros = micros();

   /*pines del motor 1*/
   pinMode(STEP_M1, OUTPUT);
   pinMode(SENTIDO_M1, OUTPUT);

   /*pines del motor 2*/
   pinMode(STEP_M2, OUTPUT);
   pinMode(SENTIDO_M2, OUTPUT);

   /*pines del motor 3*/
   pinMode(STEP_M3, OUTPUT);
   pinMode(SENTIDO_M3, OUTPUT);

   /*Interrupcion de sensores*/
   pinMode(PIN_ENTRADA_SENSOR1, INPUT_PULLUP);
   attachInterrupt(digitalPinToInterrupt(PIN_ENTRADA_SENSOR1), sensor1, FALLING);
   attachInterrupt(digitalPinToInterrupt(PIN_ENTRADA_SENSOR2), sensor2, FALLING);

   /*Inicializo el timer*/
   Timer1.initialize(1000);         // Dispara cada 1 ms
   Timer1.attachInterrupt(ISR_Timer); // Activa la interrupcion y la asocia a ISR_Timer
}
void loop() {
  if(Serial.available())
  {
    char d = Serial.read();
    if (d == '3')
    {
      giraMotor2(SENTIDO_M3, STEP_M3, IZQ, 1);
      contPasos2 = 0;
    }
  }
  mef_motor1();
  mef_motor2();
  mef_motor3();
  mef_recepcion_datos();
  mef_seleccion();
}

void mef_motor1 (void)
{
  static estMef_motor_enum estMef_motor1 = EST_INICIAL;

  switch (estMef_motor1)
  {
    case EST_INICIAL:
      digitalWrite(SENTIDO_M1, LOW); //Inicializo la direccion
      digitalWrite(STEP_M1, LOW);
     //pensar logica para que se alinee
      estMef_motor1 = EST_WAIT;
    break;
    
    case EST_WAIT:
      if(habilito_motor1 & habilito_naranja)
      {
       estMef_motor1 = EST_GIRO_IZQ;
       habilito_naranja = 0;
       habilito_motor1 = 0;
       habilito_motor2 = 0;
       Serial.println("Giro IZQ M1");
      }
      if(habilito_motor1 & habilito_gris)
      {
        estMef_motor1 = EST_GIRO_DER;
        habilito_gris = 0;
        habilito_motor1 = 0;
        habilito_motor2 = 0;
        Serial.println("Giro DER M1");
      }
    break;

    case EST_GIRO_IZQ:
        giraMotor(SENTIDO_M1, STEP_M1, IZQ, CANT_PASOS_MOTOR1);
        if(contPasos == CANT_PASOS_MOTOR1)
        {
          Serial.println("Espera giro IZQ 1");
          contTimer = 400;
          contPasos = 0;
          digitalWrite(STEP_M1, LOW);
          estMef_motor1 = EST_CIERRE_ESPERA_IZQ;
        }
    break;
    
    case EST_GIRO_DER:
      giraMotor(SENTIDO_M1, STEP_M1, DER, CANT_PASOS_MOTOR1);
      if(contPasos == CANT_PASOS_MOTOR1)
      {
          Serial.println("Espera giro DER 1");
          contTimer = 400;
          contPasos = 0;
          digitalWrite(STEP_M1, LOW);
          estMef_motor1 = EST_CIERRE_ESPERA_DER;
       }
    break;

    case EST_CIERRE_ESPERA_IZQ:
      if(contTimer == 0)
      {
        Serial.println("Cierre IZQ 1");
        estMef_motor1 = EST_CIERRE_IZQ;
      }
     break;

    case EST_CIERRE_ESPERA_DER:
      if(contTimer == 0)
      {
        Serial.println("Cierre DER 1");
        estMef_motor1 = EST_CIERRE_DER;
      }
    break;

    case EST_CIERRE_IZQ:
      giraMotor(SENTIDO_M1, STEP_M1, DER, CANT_PASOS_MOTOR1);
      if(contPasos == CANT_PASOS_MOTOR1)
      {
        Serial.println("WAIT 1");
        estMef_motor1 = EST_WAIT;
        next_cap = 1;
        contPasos = 0;
        digitalWrite(STEP_M1, LOW);
      }
    break;

    case EST_CIERRE_DER:
      giraMotor(SENTIDO_M1, STEP_M1, IZQ, CANT_PASOS_MOTOR1);
      if(contPasos == CANT_PASOS_MOTOR1)
      {
        Serial.println("WAIT 1");
        estMef_motor1 = EST_WAIT;
        next_cap = 1;
        contPasos = 0;
        digitalWrite(STEP_M1, LOW);
      }
    break;
    
    default:
      estMef_motor1 = EST_WAIT;
    break;
  }
}

void mef_motor2 (void)
{
  static estMef_motor_enum estMef_motor2 = EST_INICIAL;

  switch (estMef_motor2)
  {
    case EST_INICIAL:
      digitalWrite(SENTIDO_M2, LOW); //Inicializo la direccion
      digitalWrite(STEP_M2, LOW);
     //pensar logica para que se alinee
      estMef_motor2 = EST_WAIT;
    break;
    
    case EST_WAIT:
      if(habilito_motor2 & habilito_amarillo)
      {
       estMef_motor2 = EST_GIRO_IZQ;
       habilito_amarillo = 0;
       habilito_motor1 = 0;
       habilito_motor2 = 0;
       Serial.println("Giro IZQ M2");
      }
      if(habilito_motor2 & habilito_verde)
      {
        estMef_motor2 = EST_GIRO_DER;
        habilito_verde = 0;
        habilito_motor1 = 0;
        habilito_motor2 = 0;
        Serial.println("Giro DER M2");
      }
    break;

    case EST_GIRO_IZQ:
        giraMotor(SENTIDO_M2, STEP_M2, IZQ, CANT_PASOS_MOTOR2);
        if(contPasos == CANT_PASOS_MOTOR2)
        {
          Serial.println("Espera giro IZQ 2");
          contTimer = 400;
          contPasos = 0;
          digitalWrite(STEP_M2, LOW);
          estMef_motor2 = EST_CIERRE_ESPERA_IZQ;
        }
    break;
    
    case EST_GIRO_DER:
      giraMotor(SENTIDO_M2, STEP_M2, DER, CANT_PASOS_MOTOR2);
      if(contPasos == CANT_PASOS_MOTOR2)
      {
          Serial.println("Espera giro DER 2");
          contTimer = 400;
          contPasos = 0;
          digitalWrite(STEP_M2, LOW);
          estMef_motor2 = EST_CIERRE_ESPERA_DER;
       }
    break;

    case EST_CIERRE_ESPERA_IZQ:
      if(contTimer == 0)
      {
        Serial.println("Cierre IZQ 2");
        estMef_motor2 = EST_CIERRE_IZQ;
      }
     break;

    case EST_CIERRE_ESPERA_DER:
      if(contTimer == 0)
      {
        Serial.println("Cierre DER 2");
        estMef_motor2 = EST_CIERRE_DER;
      }
    break;

    case EST_CIERRE_IZQ:
      giraMotor(SENTIDO_M2, STEP_M2, DER, CANT_PASOS_MOTOR2);
      if(contPasos == CANT_PASOS_MOTOR2)
      {
        Serial.println("WAIT2");
        estMef_motor2 = EST_WAIT;
        next_cap = 1;
        contPasos = 0;
        digitalWrite(STEP_M2, LOW);
      }
    break;

    case EST_CIERRE_DER:
      giraMotor(SENTIDO_M2, STEP_M2, IZQ, CANT_PASOS_MOTOR2);
      if(contPasos == CANT_PASOS_MOTOR2)
      {
        Serial.println("WAIT2");
        estMef_motor2 = EST_WAIT;
        next_cap = 1;
        contPasos = 0;
        digitalWrite(STEP_M2, LOW);
      }
    break;
    
    default:
      estMef_motor2 = EST_WAIT;
    break;
  }
}

void mef_motor3 (void)
{
  static estMef_motor_enum estMef_motor3 = EST_INICIAL;

  switch (estMef_motor3)
  {
    case EST_INICIAL:
      digitalWrite(SENTIDO_M3, LOW); //Inicializo la direccion
      digitalWrite(STEP_M3, LOW);
     //pensar logica para que se alinee
      estMef_motor3 = EST_WAIT;
    break;
    
    case EST_WAIT:
      if(habilito_motor3 & habilito_rojo)
      {
       estMef_motor3 = EST_GIRO_IZQ;
       habilito_rojo = 0;
       habilito_motor3 = 0;
       Serial.println("Giro IZQ M3");
      }
      if(habilito_motor3 & habilito_azul)
      {
        estMef_motor3 = EST_GIRO_DER;
        habilito_azul = 0;
        habilito_motor3 = 0;
        Serial.println("Giro DER M3");
      }
    break;

    case EST_GIRO_IZQ:
        giraMotor(SENTIDO_M3, STEP_M3, IZQ, CANT_PASOS_MOTOR3);
        if(contPasos == CANT_PASOS_MOTOR3)
        {
          Serial.println("Espera giro IZQ 3");
          contTimer = 400;
          contPasos = 0;
          digitalWrite(STEP_M3, LOW);
          estMef_motor3 = EST_CIERRE_ESPERA_IZQ;
        }
    break;
    
    case EST_GIRO_DER:
      giraMotor(SENTIDO_M3, STEP_M3, DER, CANT_PASOS_MOTOR3);
      if(contPasos == CANT_PASOS_MOTOR3)
      {
          Serial.println("Espera giro DER 3");
          contTimer = 400;
          contPasos = 0;
          digitalWrite(STEP_M3, LOW);
          estMef_motor3 = EST_CIERRE_ESPERA_DER;
       }
    break;

    case EST_CIERRE_ESPERA_IZQ:
      if(contTimer == 0)
      {
        Serial.println("Cierre IZQ 3");
        estMef_motor3 = EST_CIERRE_IZQ;
      }
     break;

    case EST_CIERRE_ESPERA_DER:
      if(contTimer == 0)
      {
        Serial.println("Cierre DER 3");
        estMef_motor3 = EST_CIERRE_DER;
      }
    break;

    case EST_CIERRE_IZQ:
      giraMotor(SENTIDO_M3, STEP_M3, DER, CANT_PASOS_MOTOR3);
      if(contPasos == CANT_PASOS_MOTOR3)
      {
        Serial.println("WAIT 3");
        estMef_motor3 = EST_WAIT;
        next_cap = 1;
        contPasos = 0;
        digitalWrite(STEP_M3, LOW);
      }
    break;

    case EST_CIERRE_DER:
      giraMotor(SENTIDO_M3, STEP_M3, IZQ, CANT_PASOS_MOTOR3);
      if(contPasos == CANT_PASOS_MOTOR3)
      {
        Serial.println("WAIT 3");
        estMef_motor3 = EST_WAIT;
        next_cap = 1;
        contPasos = 0;
        digitalWrite(STEP_M3, LOW);
      }
    break;
    
    default:
      estMef_motor3 = EST_WAIT;
    break;
  }
}

void sensor1(void)
{
  habilito_motor1 = 1;
  habilito_motor2 = 1;
  Serial.println("Sensor1");      
}

void sensor2(void)
{
  habilito_motor3 = 1;
  Serial.println("Sensor2");      
}

void giraMotor(uint8_t PIN_SENTIDO_MOTOR, uint8_t PIN_STEP_MOTOR, bool SENTIDO, unsigned long PASOS)
{
   unsigned long currentMicros = micros();
   
   if (((unsigned long)(currentMicros - previousMicros) >= interval)  && (contPasos < PASOS+1))
   {
       state = !state;
       if (state) 
       {
       digitalWrite(PIN_SENTIDO_MOTOR, SENTIDO);
       digitalWrite(PIN_STEP_MOTOR, HIGH);
       contPasos ++;
       //Serial.println("PASO");
       }      
       
       if (!state) 
       {
       digitalWrite(PIN_STEP_MOTOR, LOW);
       //Serial.println("NO PASO");

       }
       previousMicros = micros();
   }
}


void giraMotor2(uint8_t PIN_SENTIDO_MOTOR, uint8_t PIN_STEP_MOTOR, bool SENTIDO, unsigned long PASOS)
{
   unsigned long currentMicros = micros();
   if (((unsigned long)(currentMicros - previousMicros) >= interval)  && (contPasos < PASOS+1))
   {
       state2 = !state2;
       if (state2) 
       {
       digitalWrite(PIN_SENTIDO_MOTOR, SENTIDO);
       digitalWrite(PIN_STEP_MOTOR, HIGH);
       contPasos2 ++;
       //Serial.println("PASO");
       }      
       
       if (!state2) 
       {
       digitalWrite(PIN_STEP_MOTOR, LOW);
       //Serial.println("NO PASO");

       }
       previousMicros = micros();
   }
}

void mef_recepcion_datos (void)
{
  if (Serial.available()) 
  {
    char c = Serial.read();
    circularBuffer.Add(c);
    newdata = 1;
  } 
}

void mef_seleccion(void)
{
  if (newdata && next_cap)
  {
    Serial.println("Busca dato");
    int dato = circularBuffer.ExtractLast();
    Serial.println(dato);
    if(dato == 'r')
    {
      habilito_rojo = 1;
      Serial.println("rojo");
    }
    if(dato == 'a')
    {
      habilito_azul = 1;
      Serial.println("azul");
    }
    if(dato == 'g')
    {
      habilito_gris = 1;
      Serial.println("gris");
    }
    if(dato == 'n')
    {
      habilito_naranja = 1;
      Serial.println("naranja");
    }
    if(dato == 'v')
    {
      habilito_verde = 1;
      Serial.println("verde");
    }
    if(dato == 'y')
    {
      habilito_amarillo = 1;
      Serial.println("amarillo");
    }
    newdata = 0;
    next_cap = 0;
  }
}

void ISR_Timer()
{
  if(contTimer)
    contTimer--;
}
