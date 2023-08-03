/*ÁNODO COMÚN - Activo en bajo*/
const int DIGITOS[16][7] = {
/*0*/ {0,0,0,0,0,0,1},
/*1*/ {1,0,0,1,1,1,1},
/*2*/ {0,0,1,0,0,1,0},
/*3*/ {0,0,0,0,1,1,0},
/*4*/ {1,0,0,1,1,0,0},
/*5*/ {0,1,0,0,1,0,0},
/*6*/ {0,1,0,0,0,0,0},
/*7*/ {0,0,0,1,1,1,1},
/*8*/ {0,0,0,0,0,0,0},
/*9*/ {0,0,0,0,1,0,0},
/*A*/ {0,0,0,1,0,0,0},
/*B*/ {1,1,0,0,0,0,0},
/*C*/ {0,1,1,0,0,0,1},
/*D*/ {1,0,0,0,0,1,0},
/*E*/ {0,1,1,0,0,0,0},
/*F*/ {0,1,1,1,0,0,0}
};

#define OFF HIGH
#define A 2        // pines para cada segmento
#define B 3
#define C 4
#define D 5
#define E 6
#define F 7
#define G 8
#define N 7
const int SEGMENTOS[N] = {A,B,C,D,E,F,G}; //
int d=0, i=0;

#define PULSADOR 10    // Defino pines a sus respectivos nombres constantes
#define LED1_OUT 12
#define LED2_OUT 9
#define LED1_READ 13
#define LED2_READ 11
#define DEMORA 40

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
void init_display();        //se ejecuta al inicio para apagar el display
void print(int);          //se ejecuta al presionar el botón para imprimir en el display
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
  pinMode(A, OUTPUT);
  pinMode(B, OUTPUT);
  pinMode(C, OUTPUT);
  pinMode(D, OUTPUT);
  pinMode(E, OUTPUT);
  pinMode(F, OUTPUT);
  pinMode(G, OUTPUT);
  init_display();
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
  print(i); //El display cuenta cada vez que el botón es presionado
  if (i<15) i++;
  else i=0;
}

void buttonReleased() //Invierto el estado del led 2
{
  if (digitalRead(LED2_READ)==0) digitalWrite(LED2_OUT, HIGH);
  else digitalWrite(LED2_OUT, LOW);
}

void print(int d){ 
  for (int x=0; x<N; x++){
    digitalWrite(SEGMENTOS[x], DIGITOS[d][x]);
  }
}

void init_display(void) //Función para iniciar con el display apagado
{
  digitalWrite(A, HIGH);
  digitalWrite(B, HIGH);
  digitalWrite(C, HIGH);
  digitalWrite(D, HIGH);
  digitalWrite(E, HIGH);
  digitalWrite(F, HIGH);
  digitalWrite(G, HIGH);
}