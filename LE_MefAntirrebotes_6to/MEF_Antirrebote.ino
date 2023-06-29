#define PULSADOR 10    // Defino pines a sus respectivos nombres constantes
#define LED1_OUT 2
#define LED2_OUT 4
#define LED1_READ 13
#define LED2_READ 8
#define DEMORA 

unsigned long t_now;

typedef enum
{
  BUTTON_UP,
  BUTTON_FALLING,
  BUTTON_DOWN,
  BUTTON_RISING,
}debounceState_t; //cada estado posible es enumerado (0 a 3)

void debounceFSM_init();   //ejecutada una sola vez
void debounceFSM_update(); //se ejecuta siempre
void buttonPressed();      //se ejecuta cuando estado==button_up
void buttonReleased();     //se ejecuta cuando estado==button_down

debounceState_t estado;

void setup ()
{
  pinMode(PULSADOR,INPUT);  // Se inicializa cada pin a usar
  pinMode(LED1_OUT,OUTPUT);
  pinMode(LED2_OUT,OUTPUT);
  pinMode(LED1_READ,INPUT);
  pinMode(LED2_READ,INPUT);
  Serial.begin(9600);       // Se inicializa el puerto serie
  debounceFSM_init();       // Se ejecuta una sola vez la función "init"
  t_now = millis();
}

void loop()
{
  debounceFSM_update();
  //Serial.println(digitalRead(PULSADOR)); chequeo de tensión del pulsador
}

void debounceFSM_init() //Establece a "estado" en 0 (BUTTON_UP)
{
  estado = BUTTON_UP;
}

void debounceFSM_update()
{
  switch(estado) //Se evalua cada caso que "estado" puede tener
  {
  case BUTTON_UP:
    t_now = millis();
    Serial.println("estado: BUTTON_UP");
    if (digitalRead(PULSADOR)==0) estado = BUTTON_FALLING;
    break;
    
  case BUTTON_FALLING:
    Serial.println("estado: BUTTON_FALLING");
    if (millis() - t_now > DEMORA)
    {
       if (digitalRead(PULSADOR)==0)
       {
         buttonPressed();
         estado = BUTTON_DOWN;
       }
    else estado = BUTTON_UP;
    }
    break;
    
  case BUTTON_DOWN:
    t_now = millis();
    Serial.println("estado: BUTTON_DOWN");
    if (digitalRead(PULSADOR)==1) estado = BUTTON_RISING;
    break;
    
  case BUTTON_RISING:
    Serial.println("estado: BUTTON_RISING");
    if (millis() - t_now > DEMORA)
    {
       if (digitalRead(PULSADOR)==1)
       {
         buttonReleased();
         estado = BUTTON_UP;
       }
    else estado = BUTTON_DOWN;
    }
  }
}

void buttonPressed() //Invierto el estado del led 1
{
  if (digitalRead(LED1_READ)==0) digitalWrite(LED1_OUT, HIGH);
  else digitalWrite(LED1_OUT, LOW);
}

void buttonReleased() //Invierto el estado del led 2
{
  if (digitalRead(LED2_READ)==0) digitalWrite(LED2_OUT, HIGH);
  else digitalWrite(LED2_OUT, LOW);
}
void buttonReleased() //Invierto el estado del led 2
{
  if (digitalRead(LED2_READ)==0) digitalWrite(LED2_OUT, HIGH);
  else digitalWrite(LED2_OUT, LOW);
}
