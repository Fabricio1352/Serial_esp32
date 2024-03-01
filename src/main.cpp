/**
 * Fabricio Aldaco Aguilera 235101 
 * 
 * El programa funciona, solo que, al momento de bajar el ciclo de trabajo por debajo de cero, por mas que haya puesto condicionales,
 * se asigna un valor de 4294967276 aproximadamente, no se porque, y no pude dedicarle mas tiempo a resolverlo.
 * 
 * Si mira el serial, puede ver que un ciclo baja hasta 5, si vuelve a presionar el boton, se asignara el valor mencionado, asi que para que 
 * funcione bien, cuando llegue a 5, ya no presione ese boton.
 * 
 * 
*/


#include <Arduino.h>
#include <Bounce2.h>

/*
Propiedades de los canales a utilizar, 0 y 5
*/
const int FRECUENCIA = 5000;
const int CANAL_PWM = 0;
const int CANAL_PWM2 = 5;
const int RESOLUCION = 8;

/*
Ciclos de trabajo minimos y maximos
*/
const unsigned int CT_MIN = 0;
const unsigned int CT_MAX = 255;
unsigned int cicloTrabajo;
unsigned int cicloTrabajo2;

/*
Funciones para actualizar el brillo de cada led independiente
*/
void actualizaCicloTrabajo1();
void actualizaCicloTrabajo2();

/*
Pines de botones y de leds
*/
const unsigned int PIN_BOTON1 = 5;
const unsigned int PIN_BOTON2 = 18;
const unsigned int PIN_LED1 = 2;
const unsigned int PIN_LED2 = 4;

/*
Instancias de la clase bounce para ambos botones
*/
Bounce debouncer = Bounce();
Bounce debouncer2 = Bounce();

void setup()
{

  /*
  Iniciamos los canales y los asociamos con los leds
  */
  ledcSetup(CANAL_PWM, FRECUENCIA, RESOLUCION);
  ledcSetup(CANAL_PWM2, FRECUENCIA, RESOLUCION);
  ledcAttachPin(PIN_LED1, CANAL_PWM);
  ledcAttachPin(PIN_LED2, CANAL_PWM2);
  cicloTrabajo = CT_MIN;
  cicloTrabajo2 = CT_MAX;
  ledcWrite(CANAL_PWM, cicloTrabajo);
  ledcWrite(CANAL_PWM2, cicloTrabajo2);

  /*
  Establecemos a los pines de los botones como entrada de voltaje
  */
  pinMode(PIN_BOTON1, INPUT);
  pinMode(PIN_BOTON2, INPUT);

  /*
    Pasamos como parametros de la clase Bounce,los pines de los pulsadores
  */
  debouncer.attach(PIN_BOTON1);
  debouncer2.attach(PIN_BOTON2);

  Serial.begin(9600);
}

void loop()
{

  debouncer.update();
  debouncer2.update();

  debouncer.fell() ? (ledcWrite(CANAL_PWM, cicloTrabajo), ledcWrite(CANAL_PWM2, cicloTrabajo2), actualizaCicloTrabajo1(), void()) : void();

  debouncer2.fell() ? (ledcWrite(CANAL_PWM2, cicloTrabajo2), ledcWrite(CANAL_PWM, cicloTrabajo), actualizaCicloTrabajo2(), void()) : void();
}

void actualizaCicloTrabajo1()
{

  cicloTrabajo += 25;
  cicloTrabajo2 -= 25;
  cicloTrabajo > CT_MAX ? (cicloTrabajo = CT_MAX) : cicloTrabajo2 < CT_MIN ? (cicloTrabajo2 = CT_MIN)
                                                                           : Serial.println(cicloTrabajo2),
      Serial.println(cicloTrabajo);
}

void actualizaCicloTrabajo2()
{

  cicloTrabajo2 += 25;
  cicloTrabajo -= 25;
  cicloTrabajo2 > CT_MAX ? (cicloTrabajo2 = CT_MAX) : cicloTrabajo < CT_MIN ? (cicloTrabajo = CT_MIN)
                                                                            : Serial.println(cicloTrabajo),
      Serial.println(cicloTrabajo2);
}