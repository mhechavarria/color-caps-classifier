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
      estMef_motor1 = EST_WAIT;
    break;
    
    case EST_WAIT:

      if(habilito_calib_der_m1) // calibracion derecha
      {
        habilito_calib_der_m1 = 0;
        habilito_calib_izq_m1 = 0;
        giraMotorStatus1.state = 0;
        giraMotorStatus1.contPasos = 0;
        //Serial.println("CALIBRACION M1 DERECHA");
        estMef_motor1 = EST_CALIB_DER;
      }
      
      if(habilito_calib_izq_m1) // calibracion izquierda
      {
        habilito_calib_der_m1 = 0;
        habilito_calib_izq_m1 = 0;
        giraMotorStatus1.state = 0;
        giraMotorStatus1.contPasos = 0;
        //Serial.println("CALIBRACION M1 IZQUIERDA");
        estMef_motor1 = EST_CALIB_IZQ;
      }
      
      if(habilito_motor1 && habilito_naranja) //habilito_motor1 && 
      {
        estMef_motor1 = EST_GIRO_IZQ;
        habilito_naranja = 0;
        habilito_motor1 = 0;
        habilito_motor2 = 0;
        habilito_motor3 = 0;
        giraMotorStatus1.state = 0;
        giraMotorStatus1.contPasos = 0;
        Serial.println("EST_GIRO_IZQ_M1");
      }

      if(habilito_motor1 && habilito_gris) //habilito_motor1 && 
      {
        estMef_motor1 = EST_GIRO_DER;
        habilito_gris = 0;
        habilito_motor1 = 0;
        habilito_motor2 = 0;
        habilito_motor3 = 0;
        giraMotorStatus1.state = 0;
        giraMotorStatus1.contPasos = 0;
        Serial.println("EST_GIRO_DER_M1");
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
          Serial.println("EST_CIERRE_ESPERA_IZQ_M1");
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
          Serial.println("EST_CIERRE_ESPERA_DER_M1");
          contTimer = valorTimer;
          giraMotorStatus1.contPasos = 0;
          digitalWrite(PIN_STEP_M1, LOW);
          estMef_motor1 = EST_CIERRE_ESPERA_DER;
       }
    break;

    case EST_CIERRE_ESPERA_IZQ:
      if(contTimer == 0)
      {
        Serial.println("EST_CIERRE_IZQ_M1");
        estMef_motor1 = EST_CIERRE_IZQ;
      }
     break;

    case EST_CIERRE_ESPERA_DER:
      if(contTimer == 0)
      {
        Serial.println("EST_CIERRE_DER_M1");
        estMef_motor1 = EST_CIERRE_DER;
      }
    break;

    case EST_CIERRE_IZQ:
      giraMotor(PIN_SENTIDO_M1, PIN_STEP_M1, DER, CANT_PASOS_MOTOR1, &giraMotorStatus1);
      if(giraMotorStatus1.contPasos == CANT_PASOS_MOTOR1)
      {
        Serial.println("EST_WAIT_M1");
        estMef_motor1 = EST_WAIT;
        habilito_motor1 = 0;
        giraMotorStatus1.contPasos = 0;
        digitalWrite(PIN_STEP_M1, LOW);
        digitalWrite(PIN_SENTIDO_M1, LOW);
        RS485_sendEnable();
        Serial.println('c');
        RS485_receiveEnable();
      }
    break;

    case EST_CIERRE_DER:
      giraMotor(PIN_SENTIDO_M1, PIN_STEP_M1, IZQ, CANT_PASOS_MOTOR1, &giraMotorStatus1);
      if(giraMotorStatus1.contPasos == CANT_PASOS_MOTOR1)
      {
        Serial.println("EST_WAIT_M1");
        estMef_motor1 = EST_WAIT;
        habilito_motor1 = 0;
        giraMotorStatus1.contPasos = 0;
        digitalWrite(PIN_STEP_M1, LOW);
        digitalWrite(PIN_SENTIDO_M1, LOW);
        RS485_sendEnable();
        Serial.println('c');
        RS485_receiveEnable();
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
      if(habilito_calib_der_m2) // calibracion derecha
      {
        habilito_calib_der_m2 = 0;
        habilito_calib_izq_m2 = 0;
        giraMotorStatus2.state = 0;
        giraMotorStatus2.contPasos = 0;
        //Serial.println("CALIBRACION M2 DERECHA");
        estMef_motor2 = EST_CALIB_DER;
      }
      
      if(habilito_calib_izq_m2) // calibracion izquierda
      {
        habilito_calib_der_m2 = 0;
        habilito_calib_izq_m2 = 0;
        giraMotorStatus2.state = 0;
        giraMotorStatus2.contPasos = 0; 
        //Serial.println("CALIBRACION M2 IZQUIERDA");
        estMef_motor2 = EST_CALIB_IZQ;
      }
    
      if(habilito_motor2 && habilito_amarillo) //habilito_motor2 &&  
      {
       estMef_motor2 = EST_GIRO_IZQ;
       habilito_amarillo = 0;
       habilito_motor1 = 0;
       habilito_motor2 = 0;
       habilito_motor3 = 0;       
       giraMotorStatus2.state = 0;
       giraMotorStatus2.contPasos = 0;
       Serial.println("EST_GIRO_IZQ_M2");
      }
      if(habilito_motor2 && habilito_verde) //habilito_motor2 & 
      {
        estMef_motor2 = EST_GIRO_DER;
        habilito_verde = 0;
        habilito_motor1 = 0;
        habilito_motor2 = 0;
        habilito_motor3 = 0;
        giraMotorStatus2.state = 0;
        giraMotorStatus2.contPasos = 0;
        Serial.println("EST_GIRO_DER_M2");
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
        habilito_motor2 = 0;
        giraMotorStatus2.contPasos = 0;
        digitalWrite(PIN_STEP_M2, LOW);
        digitalWrite(PIN_SENTIDO_M2, LOW);
        RS485_sendEnable();
        Serial.println('c');
        RS485_receiveEnable();
      }
    break;

    case EST_CIERRE_DER:
      giraMotor(PIN_SENTIDO_M2, PIN_STEP_M2, IZQ, CANT_PASOS_MOTOR2, &giraMotorStatus2);
      if(giraMotorStatus2.contPasos == CANT_PASOS_MOTOR2)
      {
        //Serial.println("EST_WAIT_M2");
        estMef_motor2 = EST_WAIT;
        habilito_motor2 = 0;
        giraMotorStatus2.contPasos = 0;
        digitalWrite(PIN_STEP_M2, LOW);
        digitalWrite(PIN_SENTIDO_M1, LOW);
        RS485_sendEnable();
        Serial.println('c');
        RS485_receiveEnable();
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
//    contTimerCalib = valorTimerCalib;
      
      giraMotorStatus3.state = 0;
      giraMotorStatus3.contPasos = 0;
      estMef_motor3 = EST_WAIT;
    break;
    
    case EST_WAIT:
      if(habilito_calib_der_m3) // calibracion derecha
      {
        habilito_calib_der_m3 = 0;
        habilito_calib_izq_m3 = 0;
        giraMotorStatus3.state = 0;
        giraMotorStatus3.contPasos = 0;
        //Serial.println("CALIBRACION M3 DERECHA");
        estMef_motor3 = EST_CALIB_DER;
      }
      
      if(habilito_calib_izq_m3) // calibracion izquierda
      {
        habilito_calib_der_m3 = 0;
        habilito_calib_izq_m3 = 0;
        giraMotorStatus3.state = 0;
        giraMotorStatus3.contPasos = 0;  
        //Serial.println("CALIBRACION M3 IZQUIERDA");
        estMef_motor3 = EST_CALIB_IZQ;
      }
    
      if(habilito_motor3 && habilito_rojo) //habilito_motor3 &&  
      {
       estMef_motor3 = EST_GIRO_IZQ;
       habilito_rojo = 0;
       habilito_motor1 = 0;
       habilito_motor2 = 0;
       habilito_motor3 = 0;
       giraMotorStatus3.state = 0;
       giraMotorStatus3.contPasos = 0;
      }
      
      if(habilito_motor3 && habilito_azul) //habilito_motor3 & 
      {
        estMef_motor3 = EST_GIRO_DER;
        habilito_azul = 0;
        habilito_motor1 = 0;
        habilito_motor2 = 0;
        habilito_motor3 = 0;
        giraMotorStatus3.state = 0;
        giraMotorStatus3.contPasos = 0;
        Serial.println("EST_GIRO_DER_M3_AZUL");
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
          Serial.println("EST_CIERRE_ESPERA_DER_M3");
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
        habilito_motor3 = 0;
        giraMotorStatus3.contPasos = 0;
        digitalWrite(PIN_STEP_M3, LOW);
        digitalWrite(PIN_SENTIDO_M3, LOW);
        RS485_sendEnable();
        Serial.println('c');
        RS485_receiveEnable();
      }
    break;

    case EST_CIERRE_DER:
      giraMotor(PIN_SENTIDO_M3, PIN_STEP_M3, IZQ, CANT_PASOS_MOTOR3, &giraMotorStatus3);
      if(giraMotorStatus3.contPasos == CANT_PASOS_MOTOR3)
      {
        //Serial.println("EST_WAIT_M3");
        estMef_motor3 = EST_WAIT;
        habilito_motor3 = 0;
        giraMotorStatus3.contPasos = 0;
        digitalWrite(PIN_STEP_M3, LOW);
        digitalWrite(PIN_SENTIDO_M3, LOW);
        RS485_sendEnable();
        Serial.println('c');
        RS485_receiveEnable();
      }
    break;
    
    default:
      estMef_motor3 = EST_WAIT;
    break;
  }
}
}
