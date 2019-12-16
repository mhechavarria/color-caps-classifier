#define   A   3
#define   B   4
#define   C   5 
#define   D   6
//#define   del 25
//#define  inter 25
#define intermedios

//uint8_t tabla_doble[4] = {0b10101111, 0b10110111, 0b10101111, 0b11001111};
uint8_t tabla_doble[4] = {0b00111111, 0b10011111, 0b11001111, 0b01101111};
uint8_t tabla[4] =       {0b11110111, 0b11101111, 0b11011111, 0b10111111};
uint8_t index = 0;
uint8_t index_doble = 0;
uint32_t del = 20;
uint32_t delayMicro = 0;
uint32_t inter = 1;
uint16_t j = 0;
bool start = 1;
void setup() {
  // put your setup code here, to run once:
  pinMode(A, OUTPUT);
  pinMode(B, OUTPUT);
  pinMode(C, OUTPUT);
  pinMode(D, OUTPUT);
  pinMode(LED_BUILTIN, OUTPUT);
  digitalWrite(LED_BUILTIN, 0);
  digitalWrite(A, 1);
  digitalWrite(B, 1);
  digitalWrite(C, 1);
  digitalWrite(D, 1);
  Serial.begin(9600);
}

void step()
{
  if(index <3)
  {
    index++;
  }
  else
  {
    index = 0;
  }
  PORTD = tabla[index];
  delay(del);
}

void doble_step()
{
  
  PORTD = tabla_doble[index_doble];
  if(index_doble <3)
  {
    index_doble++;
  }
  else
  {
    index_doble = 0;
  }
  delay(del);  
}
void loop()
{
  /*
  for(int i = 0; i<20; i++)
  {
    doble_step();
  }
  delay(30);
  digitalWrite(A, 1);
  digitalWrite(B, 1);
  digitalWrite(C, 1);
  digitalWrite(D, 1);
  delay(400);*/
  if(Serial.available())
  {
    char c = Serial.read();
    if(c == 'a')
    {
      step();
      Serial.print("Index:  ");
      if(start)
      {
        Serial.println(index-1);
        start = 0;
      }
      else
        Serial.println(index);
      digitalWrite(A, 1);
      digitalWrite(B, 1);
      digitalWrite(C, 1);
      digitalWrite(D, 1);
      
    }
    if( c == 's')
    {
      doble_step();
      Serial.print("Index doble:  ");
      if(start)
      {
        Serial.println(index_doble-1);
        start = 0;
      }
      else
        Serial.println(index_doble);
      digitalWrite(A, 1);
      digitalWrite(B, 1);
      digitalWrite(C, 1);
      digitalWrite(D, 1);
      
    }
  }
}
  /*for(int i = 0; i < 17; i++)
  {
    step();
  }
  delay(150);
  for(int i = 0; i < 17; i++)
  {
    step();
  }
  delay(150);
  for(int i = 0; i < 16; i++)
  {
    step();
  }
  delay(150);
  for(int i = 0; i < 17; i++)
  {
    step();
  }
  delay(150);

  
}

/*

void loop() {
  //doble
  for(int i = 0; i < 4; i++)
  {
  digitalWrite(A, 0);
  digitalWrite(B, 1);
  digitalWrite(C, 0);
  digitalWrite(D, 1);
  delay(delayMicro);
  digitalWrite(A, 1);
  digitalWrite(B, 1);
  digitalWrite(C, 1);
  digitalWrite(D, 1);
  delay(del);
  digitalWrite(A, 0);
  digitalWrite(B, 1);
  digitalWrite(C, 1);
  digitalWrite(D, 0);
  delay(delayMicro);
  digitalWrite(A, 1);
  digitalWrite(B, 1);
  digitalWrite(C, 1);
  digitalWrite(D, 1);
  delay(del);
  digitalWrite(A, 1);
  digitalWrite(B, 0);
  digitalWrite(C, 1);
  digitalWrite(D, 0);
  delay(delayMicro);
  digitalWrite(A, 1);
  digitalWrite(B, 1);
  digitalWrite(C, 1);
  digitalWrite(D, 1);
  delay(del);
  digitalWrite(A, 1);
  digitalWrite(B, 0);
  digitalWrite(C, 0);
  digitalWrite(D, 1);
  delay(delayMicro);
  digitalWrite(A, 1);
  digitalWrite(B, 1);
  digitalWrite(C, 1);
  digitalWrite(D, 1);
  delay(del);
  }
  delay(250);
  }

  */
  /*
  for(int i = 0; i< 25; i++)
  {
  digitalWrite(A, 0);
  digitalWrite(B, 1);
  digitalWrite(C, 0);
  digitalWrite(D, 1);
  delayMicroseconds(del);
  #ifdef intermedios
  digitalWrite(A, 1);
  digitalWrite(B, 1);
  digitalWrite(C, 1);
  digitalWrite(D, 1);
  delayMicroseconds(inter);
  #endif
  digitalWrite(A, 0);
  digitalWrite(B, 1);
  digitalWrite(C, 1);
  digitalWrite(D, 0);
  delayMicroseconds(del);
  #ifdef intermedios
  digitalWrite(A, 1);
  digitalWrite(B, 1);
  digitalWrite(C, 1);
  digitalWrite(D, 1);
  delayMicroseconds(inter);
  #endif
  digitalWrite(A, 1);
  digitalWrite(B, 0);
  digitalWrite(C, 1); 
  digitalWrite(D, 0);
  delayMicroseconds(del);
  #ifdef intermedios
  digitalWrite(A, 1);
  digitalWrite(B, 1);
  digitalWrite(C, 1);
  digitalWrite(D, 1);
  delayMicroseconds(inter);
  #endif
  digitalWrite(A, 1);
  digitalWrite(B, 0);
  digitalWrite(C, 0);
  digitalWrite(D, 1);
  delayMicroseconds(del);
  #ifdef intermedios
  digitalWrite(A, 1);
  digitalWrite(B, 1);
  digitalWrite(C, 1);
  digitalWrite(D, 1);
  delayMicroseconds(inter);
  #endif
  }
  delay(500);
  */
 /* 
  digitalWrite(A, 1);
  digitalWrite(B, 0);
  digitalWrite(C, 1);
  digitalWrite(D, 0);
  delay(del);
  digitalWrite(A, 0);
  digitalWrite(B, 1);
  digitalWrite(C, 1);
  digitalWrite(D, 0);
  delay(del);
  digitalWrite(A, 0);
  digitalWrite(B, 1);
  digitalWrite(C, 0);
  digitalWrite(D, 1);
  delay(del);
  digitalWrite(A, 1);
  digitalWrite(B, 0);
  digitalWrite(C, 0);
  digitalWrite(D, 1);
  delay(del);
  */

