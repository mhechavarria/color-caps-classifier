
typedef enum
{
  EST_VALIDAR_DATOS = 0,
  EST_AGREGAR_BUFFER,
  EST_SELECCION,
  EST_CALIBRACION
}estMef_recepcion_enum;

static bool giroCompleto = false;

//////////////////////////////////////////////////////////////
//                     FUNCIONES                            //
//////////////////////////////////////////////////////////////
void mef_recepcion(void);
void RS485_sendEnable(void);
void RS485_receiveEnable(void);
