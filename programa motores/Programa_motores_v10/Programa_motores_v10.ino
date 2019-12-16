#include <CircularBufferLib.h>
#include <TimerOne.h>

///////////////////////////////////////////////////
// DECLARACION DE VARIABLES DE FUNCION giraMotor //
///////////////////////////////////////////////////
unsigned long interval = 10000; // modifica el ancho de los pulsos que van al pololu con 2000 se pierden pasos
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

/////////////////////////////////////////////
// DECLARACION DE VARIABLES DE CALIBRACION //
/////////////////////////////////////////////
bool habilito_calib_der_m1 = 0;
bool habilito_calib_izq_m1 = 0;
bool habilito_calib_der_m2 = 0;
bool habilito_calib_izq_m2 = 0;
bool habilito_calib_der_m3 = 0;
bool habilito_calib_izq_m3 = 0;

unsigned long contTimerCalib = 0;
#define valorTimerCalib 20000; // este timer deja en alto el pin 13 para que los pololu hagan autohome


/////////////////////////////////////////////
// DECLARACION DE VARIABLES DE ANTIRREBOTE //
/////////////////////////////////////////////
unsigned long timAreb = 0;
#define tiempoAreb 5

/* configracion de pin enable de los pololu*/
#define PIN_ENABLE_POLOLU 13

//////////////////////////////////////////////////////////////
// DECLARACION DE VARIABLES DE ESPERA DE CIERRE DE PALANCAS //
//////////////////////////////////////////////////////////////
unsigned long contTimer = 0;
#define valorTimer 1000


//////////////////////////
// DECLARACION DE PINES //
//////////////////////////
/* configracion de pines del motor 1*/
#define PIN_STEP_M1 17 //en nano es 17
#define PIN_SENTIDO_M1 18  //en nano es 18 
#define CANT_PASOS_MOTOR1 8

/* configracion de pines del sensor 1*/
#define PIN_ENTRADA_SENSOR1 2


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
volatile bool next_cap = 0;

/////////////////////////////////
// DECLARACION ESTRUCTURAS MEF //
/////////////////////////////////
typedef enum
{
  EST_INICIAL = 0,
  EST_WAIT,
  EST_CALIB_DER,
  EST_CALIB_IZQ,
  EST_GIRO_DER,
  EST_GIRO_IZQ,
  EST_CIERRE_ESPERA_IZQ,
  EST_CIERRE_ESPERA_DER,
  EST_CIERRE_IZQ,
  EST_CIERRE_DER
}estMef_motor_enum;

typedef enum
{
  EST_VALIDAR_DATOS = 0,
  EST_AGREGAR_BUFFER,
  EST_SELECCION,
  EST_CALIBRACION
}estMef_comunicacion_enum;

typedef enum
{
  EST_AREB_ESPERANDO_ACTIVACION = 0,
  EST_AREB_ACTIVADO,
  EST_AREB_ESPERANDO_DESACTIVACION,
  EST_AREB_DESACTIVADO  
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

///////////////////////
// COMIENZO PROGRAMA //
///////////////////////
void setup() 
{  
   //Configuracion serial
   Serial.begin(9600);

   //Capturar el primer micros
   previousMicros = micros();

   /*pin enable de los pololu*/
   pinMode(PIN_ENABLE_POLOLU, OUTPUT);
   digitalWrite(PIN_ENABLE_POLOLU, HIGH);
   
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

//   attachInterrupt(digitalPinToInterrupt(PIN_ENTRADA_SENSOR1), sensor1, FALLING);
//   attachInterrupt(digitalPinToInterrupt(PIN_ENTRADA_SENSOR2), sensor2, FALLING);

   /*Inicializo el timer*/
   Timer1.initialize(1000);         // Dispara cada 1 ms
   Timer1.attachInterrupt(ISR_Timer); // Activa la interrupcion y la asocia a ISR_Timer
}

void loop()
{
  mef_motor1();
  mef_motor2();
  mef_motor3();
  mef_sensor_1_antirreb();
  //mef_sensor_2_antirreb();
  mef_comunicacion();
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
      contTimerCalib = valorTimerCalib;
      estMef_motor1 = EST_WAIT;
    break;
    
    case EST_WAIT:
      if(contTimerCalib == 0)
      {
        digitalWrite(PIN_ENABLE_POLOLU, LOW); // bajo el pin enable para conectar los pololu
      }
      
      if(habilito_calib_der_m1) // calibracion derecha
      {
        habilito_calib_der_m1 = 0;
        habilito_calib_izq_m1 = 0;
        giraMotorStatus1.state = 0;
        giraMotorStatus1.contPasos = 0;
        next_cap = 1;
        //Serial.println("CALIBRACION M1 DERECHA");
        estMef_motor1 = EST_CALIB_DER;
      }
      
      if(habilito_calib_izq_m1) // calibracion izquierda
      {
        habilito_calib_der_m1 = 0;
        habilito_calib_izq_m1 = 0;
        giraMotorStatus1.state = 0;
        giraMotorStatus1.contPasos = 0;
        next_cap = 1;       
        //Serial.println("CALIBRACION M1 IZQUIERDA");
        estMef_motor1 = EST_CALIB_IZQ;
      }
      
      if(habilito_motor1 && habilito_naranja) //habilito_motor1 && 
      {
        estMef_motor1 = EST_GIRO_IZQ;
        habilito_naranja = 0;
        habilito_motor1 = 0;
        habilito_motor2 = 0;
        giraMotorStatus1.state = 0;
        giraMotorStatus1.contPasos = 0;
        //Serial.println("EST_GIRO_IZQ_M1");
      }

      if(habilito_motor1 && habilito_gris) //habilito_motor1 && 
      {
        estMef_motor1 = EST_GIRO_DER;
        habilito_gris = 0;
        habilito_motor1 = 0;
        habilito_motor2 = 0;
        giraMotorStatus1.state = 0;
        giraMotorStatus1.contPasos = 0;
        //Serial.println("EST_GIRO_DER_M1");
      }
    break;
    
    case EST_CALIB_IZQ:
        giraMotor(PIN_SENTIDO_M1, PIN_STEP_M1, IZQ, 1, &giraMotorStatus1);
        if(giraMotorStatus1.contPasos == 1)
        {
          //Serial.println("EST_CALIB_IZQ_M1");
          giraMotorStatus1.contPasos = 0;
          digitalWrite(PIN_STEP_M1, LOW);
          estMef_motor1 = EST_WAIT;
        }    
    break;
    
    case EST_CALIB_DER:
        giraMotor(PIN_SENTIDO_M1, PIN_STEP_M1, DER, 1, &giraMotorStatus1);
        if(giraMotorStatus1.contPasos == 1)
        {
          //Serial.println("EST_CALIB_DER_M1");
          giraMotorStatus1.contPasos = 0;
          digitalWrite(PIN_STEP_M1, LOW);
          estMef_motor1 = EST_WAIT;
        }    
    break;

    case EST_GIRO_IZQ:
        giraMotor(PIN_SENTIDO_M1, PIN_STEP_M1, IZQ, CANT_PASOS_MOTOR1, &giraMotorStatus1);
        if(giraMotorStatus1.contPasos == CANT_PASOS_MOTOR1)
        {
          //Serial.println("EST_CIERRE_ESPERA_IZQ_M1");
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
          //Serial.println("EST_CIERRE_ESPERA_DER_M1");
          contTimer = valorTimer;
          giraMotorStatus1.contPasos = 0;
          digitalWrite(PIN_STEP_M1, LOW);
          estMef_motor1 = EST_CIERRE_ESPERA_DER;
       }
    break;

    case EST_CIERRE_ESPERA_IZQ:
      if(contTimer == 0)
      {
        //Serial.println("EST_CIERRE_IZQ_M1");
        estMef_motor1 = EST_CIERRE_IZQ;
      }
     break;

    case EST_CIERRE_ESPERA_DER:
      if(contTimer == 0)
      {
        //Serial.println("EST_CIERRE_DER_M1");
        estMef_motor1 = EST_CIERRE_DER;
      }
    break;

    case EST_CIERRE_IZQ:
      giraMotor(PIN_SENTIDO_M1, PIN_STEP_M1, DER, CANT_PASOS_MOTOR1, &giraMotorStatus1);
      if(giraMotorStatus1.contPasos == CANT_PASOS_MOTOR1)
      {
        //Serial.println("EST_WAIT_M1");
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
        //Serial.println("EST_WAIT_M1");
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
      //contTimerCalib = valorTimerCalib;
      
      giraMotorStatus2.state = 0;
      giraMotorStatus2.contPasos = 0;
      estMef_motor2 = EST_WAIT;
    break;
    
    case EST_WAIT:
//      if(contTimerCalib == 0)
//      {
//        digitalWrite(PIN_ENABLE_POLOLU, LOW); // bajo el pin enable para conectar los pololu
//      }
    
      if(habilito_calib_der_m2) // calibracion derecha
      {
        habilito_calib_der_m2 = 0;
        habilito_calib_izq_m2 = 0;
        giraMotorStatus2.state = 0;
        giraMotorStatus2.contPasos = 0;
        next_cap = 1;
        //Serial.println("CALIBRACION M2 DERECHA");
        estMef_motor2 = EST_CALIB_DER;
      }
      
      if(habilito_calib_izq_m2) // calibracion izquierda
      {
        habilito_calib_der_m2 = 0;
        habilito_calib_izq_m2 = 0;
        giraMotorStatus2.state = 0;
        giraMotorStatus2.contPasos = 0;
        next_cap = 1;       
        //Serial.println("CALIBRACION M2 IZQUIERDA");
        estMef_motor2 = EST_CALIB_IZQ;
      }
    
      if(habilito_motor2 && habilito_amarillo) //habilito_motor2 &&  
      {
       estMef_motor2 = EST_GIRO_IZQ;
       habilito_amarillo = 0;
       habilito_motor1 = 0;
       habilito_motor2 = 0;
       giraMotorStatus2.state = 0;
       giraMotorStatus2.contPasos = 0;
       //Serial.println("EST_GIRO_IZQ_M2");
      }
      if(habilito_motor2 && habilito_verde) //habilito_motor2 & 
      {
        estMef_motor2 = EST_GIRO_DER;
        habilito_verde = 0;
        habilito_motor1 = 0;
        habilito_motor2 = 0;
        giraMotorStatus2.state = 0;
        giraMotorStatus2.contPasos = 0;
        //Serial.println("EST_GIRO_DER_M2");
      }
    break;

    case EST_CALIB_IZQ:
        giraMotor(PIN_SENTIDO_M2, PIN_STEP_M2, IZQ, 1, &giraMotorStatus2);
        if(giraMotorStatus2.contPasos == 1)
        {
          //Serial.println("EST_CALIB_IZQ_M2");
          giraMotorStatus2.contPasos = 0;
          digitalWrite(PIN_STEP_M2, LOW);
          estMef_motor2 = EST_WAIT;
        }    
    break;
    
    case EST_CALIB_DER:
        giraMotor(PIN_SENTIDO_M2, PIN_STEP_M2, DER, 1, &giraMotorStatus2);
        if(giraMotorStatus2.contPasos == 1)
        {
          //Serial.println("EST_CALIB_DER_M2");
          giraMotorStatus2.contPasos = 0;
          digitalWrite(PIN_STEP_M2, LOW);
          estMef_motor2 = EST_WAIT;
        }    
    break;
    
    case EST_GIRO_IZQ:
        giraMotor(PIN_SENTIDO_M2, PIN_STEP_M2, IZQ, CANT_PASOS_MOTOR2, &giraMotorStatus2);
        if(giraMotorStatus2.contPasos == CANT_PASOS_MOTOR2)
        {
          //Serial.println("EST_CIERRE_ESPERA_IZQ_M2");
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
          //Serial.println("EST_CIERRE_ESPERA_DER_M2");
          contTimer = valorTimer;
          giraMotorStatus2.contPasos = 0;
          digitalWrite(PIN_STEP_M2, LOW);
          estMef_motor2 = EST_CIERRE_ESPERA_DER;
       }
    break;

    case EST_CIERRE_ESPERA_IZQ:
      if(contTimer == 0)
      {
        //Serial.println("EST_CIERRE_IZQ_M2");
        estMef_motor2 = EST_CIERRE_IZQ;
      }
     break;

    case EST_CIERRE_ESPERA_DER:
      if(contTimer == 0)
      {
        //Serial.println("EST_CIERRE_DER_M2");
        estMef_motor2 = EST_CIERRE_DER;
      }
    break;

    case EST_CIERRE_IZQ:
      giraMotor(PIN_SENTIDO_M2, PIN_STEP_M2, DER, CANT_PASOS_MOTOR2, &giraMotorStatus2);
      if(giraMotorStatus2.contPasos == CANT_PASOS_MOTOR2)
      {
        //Serial.println("EST_WAIT_M2");
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
        //Serial.println("EST_WAIT_M2");
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
//      contTimerCalib = valorTimerCalib;
      
      giraMotorStatus3.state = 0;
      giraMotorStatus3.contPasos = 0;
      estMef_motor3 = EST_WAIT;
    break;
    
    case EST_WAIT:
//      if(contTimerCalib == 0)
//      {
//        digitalWrite(PIN_ENABLE_POLOLU, LOW); // bajo el pin enable para conectar los pololu
//      }
    
      if(habilito_calib_der_m3) // calibracion derecha
      {
        habilito_calib_der_m3 = 0;
        habilito_calib_izq_m3 = 0;
        giraMotorStatus3.state = 0;
        giraMotorStatus3.contPasos = 0;
        next_cap = 1;
        //Serial.println("CALIBRACION M3 DERECHA");
        estMef_motor3 = EST_CALIB_DER;
      }
      
      if(habilito_calib_izq_m3) // calibracion izquierda
      {
        habilito_calib_der_m3 = 0;
        habilito_calib_izq_m3 = 0;
        giraMotorStatus3.state = 0;
        giraMotorStatus3.contPasos = 0;
        next_cap = 1;       
        //Serial.println("CALIBRACION M3 IZQUIERDA");
        estMef_motor3 = EST_CALIB_IZQ;
      }
    
      if(habilito_motor3 && habilito_rojo) //habilito_motor3 &&  
      {
       estMef_motor3 = EST_GIRO_IZQ;
       habilito_rojo = 0;
       habilito_motor3 = 0;
       giraMotorStatus3.state = 0;
       giraMotorStatus3.contPasos = 0;
       //Serial.println("EST_GIRO_IZQ_M3");
      }
      
      if(habilito_motor3 && habilito_azul) //habilito_motor3 & 
      {
        estMef_motor3 = EST_GIRO_DER;
        habilito_azul = 0;
        habilito_motor3 = 0;
        giraMotorStatus3.state = 0;
        giraMotorStatus3.contPasos = 0;
        //Serial.println("EST_GIRO_DER_M3");
      }
    break;

    case EST_CALIB_IZQ:
        giraMotor(PIN_SENTIDO_M3, PIN_STEP_M3, IZQ, 1, &giraMotorStatus3);
        if(giraMotorStatus3.contPasos == 1)
        {
          //Serial.println("EST_CALIB_IZQ_M3");
          giraMotorStatus3.contPasos = 0;
          digitalWrite(PIN_STEP_M3, LOW);
          estMef_motor3 = EST_WAIT;
        }    
    break;
    
    case EST_CALIB_DER:
        giraMotor(PIN_SENTIDO_M3, PIN_STEP_M3, DER, 1, &giraMotorStatus3);
        if(giraMotorStatus3.contPasos == 1)
        {
          //Serial.println("EST_CALIB_DER_M3");
          giraMotorStatus3.contPasos = 0;
          digitalWrite(PIN_STEP_M3, LOW);
          estMef_motor3 = EST_WAIT;
        }    
    break;

    case EST_GIRO_IZQ:
        giraMotor(PIN_SENTIDO_M3, PIN_STEP_M3, IZQ, CANT_PASOS_MOTOR3, &giraMotorStatus3);
        if(giraMotorStatus3.contPasos == CANT_PASOS_MOTOR3)
        {
          //Serial.println("EST_CIERRE_ESPERA_IZQ_M3");
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
          //Serial.println("EST_CIERRE_ESPERA_DER_M3");
          contTimer = valorTimer;
          giraMotorStatus3.contPasos = 0;
          digitalWrite(PIN_STEP_M3, LOW);
          estMef_motor3 = EST_CIERRE_ESPERA_DER;
       }
    break;

    case EST_CIERRE_ESPERA_IZQ:
      if(contTimer == 0)
      {
        //Serial.println("EST_CIERRE_IZQ_M3");
        estMef_motor3 = EST_CIERRE_IZQ;
      }
     break;

    case EST_CIERRE_ESPERA_DER:
      if(contTimer == 0)
      {
        //Serial.println("EST_CIERRE_DER_M3");
        estMef_motor3 = EST_CIERRE_DER;
      }
    break;

    case EST_CIERRE_IZQ:
      giraMotor(PIN_SENTIDO_M3, PIN_STEP_M3, DER, CANT_PASOS_MOTOR3, &giraMotorStatus3);
      if(giraMotorStatus3.contPasos == CANT_PASOS_MOTOR3)
      {
        //Serial.println("EST_WAIT_M3");
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
        //Serial.println("EST_WAIT_M3");
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
       ////Serial.println("PASO");
       ////Serial.println(SENTIDO);
       }      
       
       if (!(ptrMS->state))
       {
       digitalWrite(PIN_STEP_MOTOR, LOW);
       ////Serial.println("NO PASO");

       }
       if ((ptrMS->state) && ((ptrMS->contPasos) == PASOS))
       {
       (ptrMS->state) = !(ptrMS->state); //esto asegura que siempre se arranque con un step en high
       }

       previousMicros = micros();
   }
}


void mef_comunicacion (void)
{
  static estMef_comunicacion_enum estMef_comunicacion = EST_VALIDAR_DATOS;
  static int c, dato;

  switch (estMef_comunicacion)
  {
    case EST_VALIDAR_DATOS:
      if (Serial.available()) 
      {
        c = Serial.read();
        if(c == 'r' || c == 'a' || c == 'g' || c == 'n' || c == 'v' || c == 'y')
        {
          estMef_comunicacion = EST_AGREGAR_BUFFER;
        }
        if(c == '7' || c == '8' || c == '4' || c == '5' || c == '1' || c == '2')
        {
          estMef_comunicacion = EST_CALIBRACION;
        }
      }
    break;
    
    case EST_AGREGAR_BUFFER:
      circularBuffer.Add(c);
      //Serial.println("CARACTER RECIBIDO");
      //Serial.println(c);

//      Serial.print("Count:");
//      Serial.print(circularBuffer.Count());
//      Serial.print("\t\tFirst:");
//      Serial.print(circularBuffer.First());
//      Serial.print("\t\tLast:");
//      Serial.print(circularBuffer.Last());
//      Serial.print("\t\tData:");
//      printArray(circularBuffer.ToArray(), circularBuffer.Count(), ',');
      
      if(circularBuffer.Count() != 3)
      {
        estMef_comunicacion = EST_VALIDAR_DATOS;
      }
      if(circularBuffer.Count() == 3)
      {
        estMef_comunicacion = EST_SELECCION;
      }
    break;
    
    case EST_SELECCION:
    Serial.println("Busca dato");
    dato = circularBuffer.ExtractFirst();
    Serial.println(dato);
    if(dato == 'r')
    {
      habilito_rojo = 1;
      Serial.println("rojo");
      Serial.println(habilito_rojo);
    }
    if(dato == 'a')
    {
      habilito_azul = 1;
      Serial.println("azul");
      Serial.println(habilito_azul);
    }
    if(dato == 'g')
    {
      habilito_gris = 1;
      Serial.println("gris");
      Serial.println(habilito_gris);
    }
    if(dato == 'n')
    {
      habilito_naranja = 1;
      Serial.println("naranja");
      Serial.println(habilito_naranja);
    }
    if(dato == 'v')
    {
      habilito_verde = 1;
      Serial.println("verde");
      Serial.println(habilito_verde);
    }
    if(dato == 'y')
    {
      habilito_amarillo = 1;
      Serial.println("amarillo");
      Serial.println(habilito_amarillo);
    }
    if(circularBuffer.Count() != 3)
    {
      estMef_comunicacion = EST_VALIDAR_DATOS;
    }
    next_cap = 0;
    break;

    case EST_CALIBRACION:
    if(c == '7')
    {
      habilito_calib_izq_m1 = 1;
      estMef_comunicacion = EST_VALIDAR_DATOS;
      //Serial.println("habilito_calib_izq_m1");
    }    
    if(c == '8')
    {
      habilito_calib_der_m1 = 1;
      estMef_comunicacion = EST_VALIDAR_DATOS;
      //Serial.println("habilito_calib_der_m1");
    }
    if(c == '4')
    {
      habilito_calib_izq_m2 = 1;
      estMef_comunicacion = EST_VALIDAR_DATOS;
      //Serial.println("habilito_calib_izq_m2");
    }    
    if(c == '5')
    {
      habilito_calib_der_m2 = 1;
      estMef_comunicacion = EST_VALIDAR_DATOS;
      //Serial.println("habilito_calib_der_m2");
    }
    if(c == '1')
    {
      habilito_calib_izq_m3 = 1;
      estMef_comunicacion = EST_VALIDAR_DATOS;
      //Serial.println("habilito_calib_izq_m3");
    }    
    if(c == '2')
    {
      habilito_calib_der_m3 = 1;
      estMef_comunicacion = EST_VALIDAR_DATOS;
      //Serial.println("habilito_calib_der_m3");
    }
    break;
    
    default:
      estMef_comunicacion = EST_VALIDAR_DATOS;
    break;
  }    
}

void mef_sensor_1_antirreb(void)
{
  static estMef_sensor_enum estMef_sensor_1 = EST_AREB_ESPERANDO_ACTIVACION;  

  switch (estMef_sensor_1)
  {
    case EST_AREB_ESPERANDO_ACTIVACION:
      if(digitalRead(PIN_ENTRADA_SENSOR1))
      {
        timAreb = tiempoAreb; // configurar macros para 10 segundos
        estMef_sensor_1 = EST_AREB_ACTIVADO;
        Serial.println("EST_AREB_ACTIVADO_1");

      }
    break;
    
    case EST_AREB_ACTIVADO:
      if(digitalRead(PIN_ENTRADA_SENSOR1) && (timAreb == 0))
      {
        estMef_sensor_1 = EST_AREB_ESPERANDO_DESACTIVACION;
        Serial.println("EST_AREB_ESPERANDO_DESACTIVACION_1");
      }
      if(!digitalRead(PIN_ENTRADA_SENSOR1))
      {
        estMef_sensor_1 = EST_AREB_ESPERANDO_ACTIVACION;
        Serial.println("EST_AREB_ESPERANDO_ACTIVACION_1");
      }
    break;
    
    case EST_AREB_ESPERANDO_DESACTIVACION:
      if(!digitalRead(PIN_ENTRADA_SENSOR1))
      {
        timAreb = tiempoAreb; // configurar macros para 10 segundos
        estMef_sensor_1 = EST_AREB_DESACTIVADO;
        Serial.println("EST_AREB_DESACTIVADO_1");
      }
    break;
    
    case EST_AREB_DESACTIVADO:
      if(!digitalRead(PIN_ENTRADA_SENSOR1) && (timAreb == 0))
      {        
        habilito_motor1 = 1; //bandera de motor
        habilito_motor2 = 1;
        habilito_motor3 = 1;
        estMef_sensor_1 = EST_AREB_ESPERANDO_ACTIVACION;
        Serial.println("EST_AREB_ESPERANDO_ACTIVACION_1");

      }
        if(digitalRead(PIN_ENTRADA_SENSOR1))
      {
        estMef_sensor_1 = EST_AREB_ESPERANDO_DESACTIVACION;
      }
    break;
    
    default:
      estMef_sensor_1 = EST_AREB_ESPERANDO_ACTIVACION;
    break;    
  }
}

void mef_sensor_2_antirreb(void)
{
  static estMef_sensor_enum estMef_sensor_2 = EST_AREB_ESPERANDO_ACTIVACION;  

  switch (estMef_sensor_2)
  {
    case EST_AREB_ESPERANDO_ACTIVACION:
      if(digitalRead(PIN_ENTRADA_SENSOR2))
      {
        timAreb = tiempoAreb; // configurar macros para 10 segundos
        estMef_sensor_2 = EST_AREB_ACTIVADO;
        //Serial.println("EST_AREB_ACTIVADO_2");

      }
    break;
    
    case EST_AREB_ACTIVADO:
      if(digitalRead(PIN_ENTRADA_SENSOR2) && (timAreb == 0))
      {
        estMef_sensor_2 = EST_AREB_ESPERANDO_DESACTIVACION;
        //Serial.println("EST_AREB_ESPERANDO_DESACTIVACION_2");
      }
      if(!digitalRead(PIN_ENTRADA_SENSOR2))
      {
        estMef_sensor_2 = EST_AREB_ESPERANDO_ACTIVACION;
        //Serial.println("EST_AREB_ESPERANDO_ACTIVACION_2");
      }
    break;
    
    case EST_AREB_ESPERANDO_DESACTIVACION:
      if(!digitalRead(PIN_ENTRADA_SENSOR2))
      {
        timAreb = tiempoAreb; // configurar macros para 10 segundos
        estMef_sensor_2 = EST_AREB_DESACTIVADO;
        //Serial.println("EST_AREB_DESACTIVADO_2");
      }
    break;
    
    case EST_AREB_DESACTIVADO:
      if(!digitalRead(PIN_ENTRADA_SENSOR2) && (timAreb == 0))
      {        
        habilito_motor3 = 1;
        estMef_sensor_2 = EST_AREB_ESPERANDO_ACTIVACION;
        //Serial.println("EST_AREB_ESPERANDO_ACTIVACION_2");

      }
        if(digitalRead(PIN_ENTRADA_SENSOR2))
      {
        estMef_sensor_2 = EST_AREB_ESPERANDO_DESACTIVACION;
      }
    break;
    
    default:
      estMef_sensor_2 = EST_AREB_ESPERANDO_ACTIVACION;
    break;    
  }
}


void ISR_Timer()
{
  if(contTimer)
  {
    contTimer--;
  }
  if(contTimerCalib)
  {
    contTimerCalib--;
  }
  if(timAreb)
  {
    timAreb--;
  }
}
