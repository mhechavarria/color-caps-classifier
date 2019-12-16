#include <CircularBufferLib.h>
#include <TimerOne.h>

///////////////////////////////////////////////////
// DECLARACION DE VARIABLES DE FUNCION giraMotor //
///////////////////////////////////////////////////
unsigned long interval = 300000;
unsigned long previousMicros;

bool state1 = false;  //GIRAMOTOR1
bool state2 = false;  //GIRAMOTOR2
bool state3 = false;  //GIRAMOTOR3

unsigned int contPasos1 = 0;  //GIRAMOTOR1
unsigned int contPasos2 = 0;  //GIRAMOTOR2
unsigned int contPasos3 = 0;  //GIRAMOTOR3

////////////////////////////////////////////////////////////
// DECLARACION DE VARIABLES DE FUNCION seleccion de motor //
////////////////////////////////////////////////////////////
bool habilito_rojo = 0;
bool habilito_azul = 0;
bool habilito_amarillo= 0;
bool habilito_verde = 0;
bool habilito_naranja = 0;
bool habilito_gris = 0;

//////////////////////////////////////////////////////////////
// DECLARACION DE VARIABLES DE ESPERA DE CIERRE DE PALANCAS //
//////////////////////////////////////////////////////////////
unsigned long contTimer = 0;
#define valorTimer 1000

//////////////////////////
// DECLARACION DE PINES //
//////////////////////////
/* configracion de pines del motor 1*/
#define PIN_STEP_M1 17
#define PIN_SENTIDO_M1 18 // cambiar por 5
#define CANT_PASOS_MOTOR1 6

/* configracion de pines del sensor 1*/
#define PIN_ENTRADA_SENSOR1 2

/* configracion de pines del motor 2*/
#define PIN_STEP_M2 6
#define PIN_SENTIDO_M2 7
#define CANT_PASOS_MOTOR2 6

/* configracion de pines del sensor 2*/
#define PIN_ENTRADA_SENSOR2 3

/* configracion de pines del motor 3*/
#define PIN_STEP_M3 8
#define PIN_SENTIDO_M3 9 
#define CANT_PASOS_MOTOR3 20

//////////////////////////
// DIRECCION DE MOTORES //
//////////////////////////
#define DER 1
#define IZQ 0

////////////////////////////////////////
// BANDERAS DE COMUNICACION ENTRE MEF //
////////////////////////////////////////
bool habilito_motor1 = 0;
bool habilito_motor2 = 0;
bool habilito_motor3 = 0;
volatile bool newdata = 0;
volatile bool next_cap = 1;

/////////////////////////////////
// DECLARACION ESTRUCTURAS MEF //
/////////////////////////////////
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

/////////////////////////
// OTRAS DECLARACIONES //
/////////////////////////
struct giraMotorStatus
{
  bool state;
  unsigned int contPasos;
};

CircularBuffer<int> circularBuffer(5);

///////////////////////
// COMIENZO PROGRAMA //
///////////////////////
void setup() 
{  
   //Configuracion serial
   Serial.begin(9600);

   //Capturar el primer micros
   previousMicros = micros();

   /*pines del motor 1*/
   pinMode(PIN_STEP_M1, OUTPUT);
   pinMode(PIN_SENTIDO_M1, OUTPUT);

   /*pines del motor 2*/
   pinMode(PIN_STEP_M2, OUTPUT);
   pinMode(PIN_SENTIDO_M2, OUTPUT);

   /*pines del motor 3*/
   pinMode(PIN_STEP_M3, OUTPUT);
   pinMode(PIN_SENTIDO_M3, OUTPUT);

   /*Interrupcion de sensores*/
   pinMode(PIN_ENTRADA_SENSOR1, INPUT_PULLUP);
   pinMode(PIN_ENTRADA_SENSOR2, INPUT_PULLUP);

   attachInterrupt(digitalPinToInterrupt(PIN_ENTRADA_SENSOR1), sensor1, FALLING);
   attachInterrupt(digitalPinToInterrupt(PIN_ENTRADA_SENSOR2), sensor2, FALLING);

   /*Inicializo el timer*/
   Timer1.initialize(1000);         // Dispara cada 1 ms
   Timer1.attachInterrupt(ISR_Timer); // Activa la interrupcion y la asocia a ISR_Timer
}

void loop()
{
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
      digitalWrite(PIN_SENTIDO_M1, LOW); //Inicializo la direccion
      digitalWrite(PIN_STEP_M1, LOW);
      struct giraMotorStatus giraMotorStatus1;
      giraMotorStatus1.state = 0;
      giraMotorStatus1.contPasos = 0;
     //pensar logica para que se alinee
      estMef_motor1 = EST_WAIT;
    break;
    
    case EST_WAIT:
      if(habilito_naranja) //habilito_motor1 && 
      {
       estMef_motor1 = EST_GIRO_IZQ;
       habilito_naranja = 0;
       habilito_motor1 = 0;
       habilito_motor2 = 0;
       giraMotorStatus1.state = 0;
       giraMotorStatus1.contPasos = 0;
       Serial.println("EST_GIRO_IZQ M1");
      }
      if(habilito_gris) //habilito_motor1 && 
      {
        estMef_motor1 = EST_GIRO_DER;
        habilito_gris = 0;
        habilito_motor1 = 0;
        habilito_motor2 = 0;
        giraMotorStatus1.state = 0;
        giraMotorStatus1.contPasos = 0;
        Serial.println("EST_GIRO_DER M1");
      }
    break;

    case EST_GIRO_IZQ:
        giraMotor(PIN_SENTIDO_M1, PIN_STEP_M1, IZQ, CANT_PASOS_MOTOR1, &giraMotorStatus1);
        if(giraMotorStatus1.contPasos == CANT_PASOS_MOTOR1)
        {
          Serial.println("EST_CIERRE_ESPERA_IZQ M1");
          contTimer = valorTimer;
          giraMotorStatus1.contPasos = 0;
          digitalWrite(PIN_STEP_M1, LOW);
          estMef_motor1 = EST_CIERRE_ESPERA_IZQ;
        }
    break;
    
    case EST_GIRO_DER:
      giraMotor(PIN_SENTIDO_M1, PIN_STEP_M1, DER, CANT_PASOS_MOTOR1, &giraMotorStatus1);
      if(giraMotorStatus1.contPasos == CANT_PASOS_MOTOR1)
      {
          Serial.println("EST_CIERRE_ESPERA_DER M1");
          contTimer = valorTimer;
          giraMotorStatus1.contPasos = 0;
          digitalWrite(PIN_STEP_M1, LOW);
          estMef_motor1 = EST_CIERRE_ESPERA_DER;
       }
    break;

    case EST_CIERRE_ESPERA_IZQ:
      if(contTimer == 0)
      {
        Serial.println("EST_CIERRE_IZQ M1");
        estMef_motor1 = EST_CIERRE_IZQ;
      }
     break;

    case EST_CIERRE_ESPERA_DER:
      if(contTimer == 0)
      {
        Serial.println("EST_CIERRE_DER M1");
        estMef_motor1 = EST_CIERRE_DER;
      }
    break;

    case EST_CIERRE_IZQ:
      giraMotor(PIN_SENTIDO_M1, PIN_STEP_M1, DER, CANT_PASOS_MOTOR1, &giraMotorStatus1);
      if(giraMotorStatus1.contPasos == CANT_PASOS_MOTOR1)
      {
        Serial.println("EST_WAIT M1");
        estMef_motor1 = EST_WAIT;
        next_cap = 1;
        giraMotorStatus1.contPasos = 0;
        digitalWrite(PIN_STEP_M1, LOW);
        digitalWrite(PIN_SENTIDO_M1, LOW);
      }
    break;

    case EST_CIERRE_DER:
      giraMotor(PIN_SENTIDO_M1, PIN_STEP_M1, IZQ, CANT_PASOS_MOTOR1, &giraMotorStatus1);
      if(giraMotorStatus1.contPasos == CANT_PASOS_MOTOR1)
      {
        Serial.println("EST_WAIT M1");
        estMef_motor1 = EST_WAIT;
        next_cap = 1;
        giraMotorStatus1.contPasos = 0;
        digitalWrite(PIN_STEP_M1, LOW);
        digitalWrite(PIN_SENTIDO_M1, LOW);
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
      digitalWrite(PIN_SENTIDO_M2, LOW); //Inicializo la direccion
      digitalWrite(PIN_STEP_M2, LOW);
      struct giraMotorStatus giraMotorStatus2;
      giraMotorStatus2.state = 0;
      giraMotorStatus2.contPasos = 0;
      estMef_motor2 = EST_WAIT;
    break;
    
    case EST_WAIT:
      if(habilito_amarillo) //habilito_motor2 & 
      {
       estMef_motor2 = EST_GIRO_IZQ;
       habilito_amarillo = 0;
       habilito_motor1 = 0;
       habilito_motor2 = 0;
       giraMotorStatus2.state = 0;
       giraMotorStatus2.contPasos = 0;
       Serial.println("EST_GIRO_IZQ M2");
      }
      if(habilito_verde) //habilito_motor2 & 
      {
        estMef_motor2 = EST_GIRO_DER;
        habilito_verde = 0;
        habilito_motor1 = 0;
        habilito_motor2 = 0;
        giraMotorStatus2.state = 0;
        giraMotorStatus2.contPasos = 0;
        Serial.println("EST_GIRO_DER M2");
      }
    break;

    case EST_GIRO_IZQ:
        giraMotor(PIN_SENTIDO_M2, PIN_STEP_M2, IZQ, CANT_PASOS_MOTOR2, &giraMotorStatus2);
        if(giraMotorStatus2.contPasos == CANT_PASOS_MOTOR2)
        {
          Serial.println("EST_CIERRE_ESPERA_IZQ M2");
          contTimer = valorTimer;
          giraMotorStatus2.contPasos = 0;
          digitalWrite(PIN_STEP_M2, LOW);
          estMef_motor2 = EST_CIERRE_ESPERA_IZQ;
        }
    break;
    
    case EST_GIRO_DER:
      giraMotor(PIN_SENTIDO_M2, PIN_STEP_M2, DER, CANT_PASOS_MOTOR2, &giraMotorStatus2);
      if(giraMotorStatus2.contPasos == CANT_PASOS_MOTOR2)
      {
          Serial.println("EST_CIERRE_ESPERA_DER M2");
          contTimer = valorTimer;
          giraMotorStatus2.contPasos = 0;
          digitalWrite(PIN_STEP_M2, LOW);
          estMef_motor2 = EST_CIERRE_ESPERA_DER;
       }
    break;

    case EST_CIERRE_ESPERA_IZQ:
      if(contTimer == 0)
      {
        Serial.println("EST_CIERRE_IZQ M2");
        estMef_motor2 = EST_CIERRE_IZQ;
      }
     break;

    case EST_CIERRE_ESPERA_DER:
      if(contTimer == 0)
      {
        Serial.println("EST_CIERRE_DER M2");
        estMef_motor2 = EST_CIERRE_DER;
      }
    break;

    case EST_CIERRE_IZQ:
      giraMotor(PIN_SENTIDO_M2, PIN_STEP_M2, DER, CANT_PASOS_MOTOR2, &giraMotorStatus2);
      if(giraMotorStatus2.contPasos == CANT_PASOS_MOTOR2)
      {
        Serial.println("EST_WAIT M2");
        estMef_motor2 = EST_WAIT;
        next_cap = 1;
        giraMotorStatus2.contPasos = 0;
        digitalWrite(PIN_STEP_M2, LOW);
        digitalWrite(PIN_SENTIDO_M2, LOW);
      }
    break;

    case EST_CIERRE_DER:
      giraMotor(PIN_SENTIDO_M2, PIN_STEP_M2, IZQ, CANT_PASOS_MOTOR2, &giraMotorStatus2);
      if(giraMotorStatus2.contPasos == CANT_PASOS_MOTOR2)
      {
        Serial.println("EST_WAIT M2");
        estMef_motor2 = EST_WAIT;
        next_cap = 1;
        giraMotorStatus2.contPasos = 0;
        digitalWrite(PIN_STEP_M2, LOW);
        digitalWrite(PIN_SENTIDO_M1, LOW);
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
      digitalWrite(PIN_SENTIDO_M3, LOW); //Inicializo la direccion
      digitalWrite(PIN_STEP_M3, LOW);
      struct giraMotorStatus giraMotorStatus3;
      giraMotorStatus3.state = 0;
      giraMotorStatus3.contPasos = 0;
      estMef_motor3 = EST_WAIT;
    break;
    
    case EST_WAIT:
      if(habilito_rojo) //habilito_motor3 & 
      {
       estMef_motor3 = EST_GIRO_IZQ;
       habilito_rojo = 0;
       habilito_motor3 = 0;
       giraMotorStatus3.state = 0;
       giraMotorStatus3.contPasos = 0;
       Serial.println("Giro IZQ M3");
      }
      if(habilito_azul) //habilito_motor3 & 
      {
        estMef_motor3 = EST_GIRO_DER;
        habilito_azul = 0;
        habilito_motor3 = 0;
        giraMotorStatus3.state = 0;
        giraMotorStatus3.contPasos = 0;
        Serial.println("Giro DER M3");
      }
    break;

    case EST_GIRO_IZQ:
        giraMotor(PIN_SENTIDO_M3, PIN_STEP_M3, IZQ, CANT_PASOS_MOTOR3, &giraMotorStatus3);
        if(giraMotorStatus3.contPasos == CANT_PASOS_MOTOR3)
        {
          Serial.println("Espera giro IZQ 3");
          contTimer = valorTimer;
          giraMotorStatus3.contPasos = 0;
          digitalWrite(PIN_STEP_M3, LOW);
          estMef_motor3 = EST_CIERRE_ESPERA_IZQ;
        }
    break;
    
    case EST_GIRO_DER:
      giraMotor(PIN_SENTIDO_M3, PIN_STEP_M3, DER, CANT_PASOS_MOTOR3, &giraMotorStatus3);
      if(giraMotorStatus3.contPasos == CANT_PASOS_MOTOR3)
      {
          Serial.println("Espera giro DER 3");
          contTimer = valorTimer;
          giraMotorStatus3.contPasos = 0;
          digitalWrite(PIN_STEP_M3, LOW);
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
      giraMotor(PIN_SENTIDO_M3, PIN_STEP_M3, DER, CANT_PASOS_MOTOR3, &giraMotorStatus3);
      if(giraMotorStatus3.contPasos == CANT_PASOS_MOTOR3)
      {
        Serial.println("WAIT 3");
        estMef_motor3 = EST_WAIT;
        next_cap = 1;
        giraMotorStatus3.contPasos = 0;
        digitalWrite(PIN_STEP_M3, LOW);
        digitalWrite(PIN_SENTIDO_M3, LOW);
      }
    break;

    case EST_CIERRE_DER:
      giraMotor(PIN_SENTIDO_M3, PIN_STEP_M3, IZQ, CANT_PASOS_MOTOR3, &giraMotorStatus3);
      if(giraMotorStatus3.contPasos == CANT_PASOS_MOTOR3)
      {
        Serial.println("WAIT 3");
        estMef_motor3 = EST_WAIT;
        next_cap = 1;
        giraMotorStatus3.contPasos = 0;
        digitalWrite(PIN_STEP_M3, LOW);
        digitalWrite(PIN_SENTIDO_M3, LOW);
      }
    break;
    
    default:
      estMef_motor3 = EST_WAIT;
    break;
  }
}

/*ISR de interrupcion PIN 2*/
void sensor1(void)
{
  habilito_motor1 = 1;
  habilito_motor2 = 1;
  Serial.println("Sensor1");      
}

/*ISR de interrupcion PIN 3*/
void sensor2(void)
{
  habilito_motor3 = 1;
  Serial.println("Sensor2");      
}

void giraMotor(uint8_t PIN_SENTIDO_MOTOR, uint8_t PIN_STEP_MOTOR, bool SENTIDO, unsigned long PASOS, struct giraMotorStatus *ptrMS)
{
   unsigned long currentMicros = micros();
   
   if (((unsigned long)(currentMicros - previousMicros) >= interval)  && ((ptrMS->contPasos) < PASOS))
   {
       (ptrMS->state) = !(ptrMS->state);
       if (ptrMS->state) 
       {
       digitalWrite(PIN_SENTIDO_MOTOR, SENTIDO);
       digitalWrite(PIN_STEP_MOTOR, HIGH);
       (ptrMS->contPasos) ++;
       Serial.println("PASO");
       }      
       
       if (!(ptrMS->state))
       {
       digitalWrite(PIN_STEP_MOTOR, LOW);
       Serial.println("NO PASO");

       }
       if ((ptrMS->state) && ((ptrMS->contPasos) == PASOS))
       {
       (ptrMS->state) = !(ptrMS->state); //esto asegura que siempre se arranque con un step en high
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
//    if ((c != 'a') || (c != 'g') || (c != 'r') || (c != 'n') || (c != 'v') || (c != 'y'))
//    {
//    circularBuffer.ExtractLast();
//    newdata = 0;
//    }
    Serial.println("CARACTER RECIBIDO");
    Serial.println(c);

  } 
}

void mef_seleccion(void)
{
  if (newdata && next_cap) // && next_cap
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
