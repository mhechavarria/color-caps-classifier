#include "comunicacion.h"

void mef_recepcion (void)
{
  static estMef_recepcion_enum estMef_recepcion = EST_VALIDAR_DATOS;
  static int c, dato;

  switch (estMef_recepcion)
  {
    case EST_VALIDAR_DATOS:
      
      if (Serial.available()) 
      {
        //Agregar el procesamiento de la respuesta de la arduino que mueve las paletas
        c = Serial.read();
        if(c == 'r' || c == 'a' || c == 'g' || c == 'n' || c == 'v' || c == 'y' || c == 'm')
        {
         Serial.println("AGREGO AL BUFFER");
         circularBuffer.push(c);
         RS485_sendEnable();
         Serial.println('k');
         RS485_receiveEnable();
        }
        if(c == 'k'){
          giroCompleto=true;
          habilito_motor1 = 1; //bandera de motor
          habilito_motor2 = 1;
          habilito_motor3 = 1;
        }
        if(c == '7' || c == '8' || c == '4' || c == '5' || c == '1' || c == '2')
        {
          estMef_recepcion = EST_CALIBRACION;
          Serial.println(c);
        }
        if(c == 'x')
        {
          Serial.println(c);
          habilito_motor1 = 0;//esto es para cuando dejamos de usar la maquina por un tiempo y quedan las banderas guardadas
          habilito_motor2 = 0;
          habilito_motor3 = 0;
          habilito_gris = 0;
          habilito_verde = 0;
          habilito_azul = 0;
          habilito_amarillo = 0;
          habilito_naranja = 0;
          habilito_rojo = 0;
          circularBuffer.clear();
          estMef_recepcion = EST_VALIDAR_DATOS;
         }
      }
    break;
    
   case EST_CALIBRACION:
    if(c == '7')
    {
      habilito_calib_izq_m1 = 1;
      estMef_recepcion = EST_VALIDAR_DATOS;
      //Serial.println("habilito_calib_izq_m1");
    }    
    if(c == '8')
    {
      habilito_calib_der_m1 = 1;
      estMef_recepcion = EST_VALIDAR_DATOS;
      //Serial.println("habilito_calib_der_m1");
    }
    if(c == '4')
    {
      habilito_calib_izq_m2 = 1;
      estMef_recepcion = EST_VALIDAR_DATOS;
      //Serial.println("habilito_calib_izq_m2");
    }    
    if(c == '5')
    {
      habilito_calib_der_m2 = 1;
      estMef_recepcion = EST_VALIDAR_DATOS;
      //Serial.println("habilito_calib_der_m2");
    }
    if(c == '1')
    {
      habilito_calib_izq_m3 = 1;
      estMef_recepcion = EST_VALIDAR_DATOS;
      //Serial.println("habilito_calib_izq_m3");
    }    
    if(c == '2')
    {
      habilito_calib_der_m3 = 1;
      estMef_recepcion = EST_VALIDAR_DATOS;
      //Serial.println("habilito_calib_der_m3");
    }
    break;
    
    default:
      estMef_recepcion = EST_VALIDAR_DATOS;
    break;
  }    
}


void mef_seleccion(void){  
static int dato;
    if(giroCompleto && !circularBuffer.isEmpty()){
      giroCompleto=false;
      Serial.println("BUSCA DATO");
      dato = circularBuffer.shift();
      Serial.println(dato);
      if(dato == 'r')
      {
        habilito_rojo = 1;
        habilito_timeOut = 1;
        Serial.println("rojo");
      }
      if(dato == 'a')
      {
        habilito_azul = 1;
        habilito_timeOut = 1;
        Serial.println("azul");
      }
      if(dato == 'g')
      {
        habilito_gris = 1;
        habilito_timeOut = 1;   
        Serial.println("gris");
      }
      if(dato == 'n')
      {
        habilito_naranja = 1;
        habilito_timeOut = 1;
        Serial.println("naranja");
      }
      if(dato == 'v')
      {
        habilito_verde = 1;
        habilito_timeOut = 1;
        Serial.println("verde");
      }
      if(dato == 'y')
      {
        habilito_amarillo = 1;
        habilito_timeOut = 1;
        
        Serial.println("amarillo");
      }
    }
    else if(giroCompleto){ giroCompleto=false;}
}

void RS485_sendEnable(void){
  digitalWrite(PIN_485, HIGH);
}

void RS485_receiveEnable(void){
  digitalWrite(PIN_485, LOW);
}
