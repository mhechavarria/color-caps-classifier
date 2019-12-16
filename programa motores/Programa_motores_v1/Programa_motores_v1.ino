//Blink without delay
unsigned long interval = 1000;
unsigned long previousMillis;
unsigned long contPasos = 0;



#define PASOS_MOTOR1 9
#define PIN_SENTIDO 12
#define PIN_PASOS 13
#define PIN_ENTRADA_DER 7
#define PIN_ENTRADA_IZQ 6


bool state = false;
bool DER = HIGH;
bool IZQ = LOW;
bool habilito_step_m1 = 0;

typedef enum
{
  EST_INICIAL = 0,
  EST_WAIT,
  EST_GIRO_DER,
  EST_GIRO_IZQ
}estMef_motor1_enum;


void setup() 
{   
   pinMode(PIN_PASOS, OUTPUT);
   pinMode(PIN_SENTIDO, OUTPUT);
   pinMode(PIN_ENTRADA_DER, INPUT_PULLUP);
   pinMode(PIN_ENTRADA_IZQ, INPUT_PULLUP);


     /* Configuracion e inicializacion de TIMER 2 */
  SREG = (SREG & 0b01111111); //Desabilitar interrupciones
  TIMSK2 = TIMSK2|0b00000001; //Habilita la interrupcion por desbordamiento
  TCCR2B = 0b00000111; //Configura preescala para que FT2 sea de 250KHz
  SREG = (SREG & 0b01111111) | 0b10000000; //Habilitar interrupciones //Desabilitar interrupciones

}
void loop() 
{
  mef_principal();
}

void mef_motor_1(void)
{
  static estMef_motor1_enum estMef_motor1 = EST_INICIAL;

  switch (estMef_motor1)
  {
    case EST_INICIAL:
      digitalWrite(PIN_SENTIDO, DER);
     //pensar logica para que se alinee
      estMef_motor1 = EST_WAIT;
    break;
    
    case EST_WAIT:
      if(!digitalRead(PIN_ENTRADA_DER))//Gira derecha
      {
         digitalWrite(PIN_SENTIDO, DER);
         habilito_step_m1=1;
         estMef_motor1 = EST_GIRO_DER;
      }
      if(!digitalRead(PIN_ENTRADA_IZQ))//Gira izquierda
      {
         digitalWrite(PIN_SENTIDO, IZQ);
         habilito_step_m1=1;
         estMef_motor1 = EST_GIRO_IZQ;
      }
    break;   
       
    case EST_GIRO_DER:
        if(contPasos == PASOS_MOTOR1-1)
        {
          estMef_motor1 = EST_WAIT;
          // LIMPIO BANDERAS
          habilito_step_m1=0;
          contPasos = 0;
          digitalWrite(PIN_PASOS, LOW);
        }    
    break;
    
    case EST_GIRO_IZQ:
        if(contPasos == PASOS_MOTOR1-1)
        {
          estMef_motor1 = EST_WAIT;
          // LIMPIO BANDERAS
          habilito_step_m1=0;
          contPasos = 0;
          digitalWrite(PIN_PASOS, LOW);
        }    
    break;
    
    default:
      estMef_motor1 = EST_WAIT;
    break;
  }
}




// Mi base de tiempos es de 1 mS, me sirve para ajustar los pasos y alguna temporización
ISR(TIMER2_OVF_vect)
{
  // aca hay que poner la mef que tira los step
  if(habilito_step_m1)
  {
     state = !state;
     if (state) 
     {
     digitalWrite(PIN_PASOS, HIGH);
     contPasos ++;
     }      
     
     if (!state) 
     {
     digitalWrite(PIN_PASOS, LOW);
     }
  }
}











//void giraMotor(bool SENTIDO, unsigned long PASOS)
//{
//   unsigned long currentMillis = millis();
//   
//   if (((unsigned long)(currentMillis - previousMillis) >= interval) && contPasos < PASOS)
//   {
//       state = !state;
//       if (state) 
//       {
//       digitalWrite(PIN_SENTIDO, SENTIDO);
//       digitalWrite(PIN_PASOS, HIGH);
//       contPasos ++;
//       }      
//       
//       if (!state) 
//       {
//       digitalWrite(PIN_PASOS, LOW);
//       }
//       previousMillis = millis();
//   }
//}
