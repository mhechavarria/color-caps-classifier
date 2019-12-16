void mef_sensor_1_antirreb(void){
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
        habilito_timeOut = 0;
        conTimeOut = valorconTimeOut;          
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
        Serial.println("EST_AREB_ACTIVADO_2");

      }
    break;
    
    case EST_AREB_ACTIVADO:
      if(digitalRead(PIN_ENTRADA_SENSOR2) && (timAreb == 0))
      {
        estMef_sensor_2 = EST_AREB_ESPERANDO_DESACTIVACION;
        Serial.println("EST_AREB_ESPERANDO_DESACTIVACION_2");
      }
      if(!digitalRead(PIN_ENTRADA_SENSOR2))
      {
        estMef_sensor_2 = EST_AREB_ESPERANDO_ACTIVACION;
        Serial.println("EST_AREB_ESPERANDO_ACTIVACION_2");
      }
    break;
    
    case EST_AREB_ESPERANDO_DESACTIVACION:
      if(!digitalRead(PIN_ENTRADA_SENSOR2))
      {
        timAreb = tiempoAreb; // configurar macros para 10 segundos
        estMef_sensor_2 = EST_AREB_DESACTIVADO;
        Serial.println("EST_AREB_DESACTIVADO_2");
      }
    break;
    
    case EST_AREB_DESACTIVADO:
      if(!digitalRead(PIN_ENTRADA_SENSOR2) && (timAreb == 0))
      {        
        habilito_motor3 = 1;
        estMef_sensor_2 = EST_AREB_ESPERANDO_ACTIVACION;
        Serial.println("EST_AREB_ESPERANDO_ACTIVACION_2");
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
