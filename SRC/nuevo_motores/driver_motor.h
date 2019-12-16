struct giraMotorStatus
{
   bool state;
   unsigned int contPasos;
};

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

//////////////////////////////////////////////////////////////
//                DECLARACION DE VARIABLES                  //
//////////////////////////////////////////////////////////////
unsigned long contTimer = 0;
#define valorTimer 250

bool habilito_calib_der_m1 = 0;
bool habilito_calib_izq_m1 = 0;
bool habilito_calib_der_m2 = 0;
bool habilito_calib_izq_m2 = 0;
bool habilito_calib_der_m3 = 0;
bool habilito_calib_izq_m3 = 0;

///////////////////////////////////////////////////
// DECLARACION DE VARIABLES DE FUNCION giraMotor //
///////////////////////////////////////////////////
unsigned long interval = 6000; // modifica el ancho de los pulsos que van al pololu con 2000 se pierden pasos
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

////////////////////////////////////////
// BANDERAS DE COMUNICACION ENTRE MEF //
////////////////////////////////////////
bool habilito_motor1 = 0;
bool habilito_motor2 = 0;
bool habilito_motor3 = 0;

//////////////////////////////////////////////////////////////
//                     FUNCIONES                            //
//////////////////////////////////////////////////////////////
void giraMotor(uint8_t PIN_SENTIDO_MOTOR, uint8_t PIN_STEP_MOTOR, bool SENTIDO, unsigned long PASOS, struct giraMotorStatus *ptrMS);
void mef_motor1(void);
void mef_motor2(void);
void mef_motor3(void);
