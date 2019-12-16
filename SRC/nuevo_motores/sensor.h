/////////////////////////////////
// DECLARACION ESTRUCTURAS MEF //
/////////////////////////////////
typedef enum
{
  EST_AREB_ESPERANDO_ACTIVACION = 0,
  EST_AREB_ACTIVADO,
  EST_AREB_ESPERANDO_DESACTIVACION,
  EST_AREB_DESACTIVADO  
}estMef_sensor_enum;

/////////////////////////////////////////////
// DECLARACION DE VARIABLES DE ANTIRREBOTE //
/////////////////////////////////////////////
unsigned long timAreb = 0;
#define tiempoAreb 5

//////////////////////////////////////////////////////////////
//                     FUNCIONES                            //
//////////////////////////////////////////////////////////////
void mef_sensor_1_antirreb(void);
void mef_sensor_2_antirreb(void);
