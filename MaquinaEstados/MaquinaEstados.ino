#if CONFIG_FREERTOS_UNICORE
static const BaseType_t App_CPU = 0;
#else
static const BaseType_t App_CPU = 1;
#endif
static const int a0 =4;
static const int a1 =5;
static const int a2 =6;
static const int a3 =7;
//El 0 es mayor prioridad
static const int sh =15;

static const int INI =16;
volatile int p = 0;

int led=17;
//static const int boton =4;
void P0(void *parameter){
 while(1){
if (p==0){
  digitalWrite(led,HIGH);
Serial.println("Espera");
vTaskDelay(330/portTICK_PERIOD_MS);
if (!digitalRead(a0)&&!digitalRead(INI)){
  p=1;
}
}
vTaskDelay(330/portTICK_PERIOD_MS);
}
}

void P1(void *parameter){
 while(1){
if (p==1){
Serial.println("Baja Taladro Rapidamente");

if (!digitalRead(a1)){
  p=2;
}
}
vTaskDelay(330/portTICK_PERIOD_MS);
}
}

void P2(void *parameter){
 while(1){
if (p==2){
Serial.println("Baja Taladro Lentamente");
Serial.println("Taladro Girando");

if (!digitalRead(a3)){
  p=3;
}
if (!digitalRead(sh)&&!digitalRead(a2)){
  p=5;
}
}
vTaskDelay(330/portTICK_PERIOD_MS);
}
}

void P3(void *parameter){
 while(1){
if (p==3){
Serial.println("Sube Taladro Lentamente");
Serial.println("Taladro Girando");

if (!digitalRead(a2)){
  p=4;
}
}
vTaskDelay(330/portTICK_PERIOD_MS);
}
}

void P4(void *parameter){
 while(1){
if (p==4){
Serial.println("Sube Taladro Rapidamente");

if (!digitalRead(a0)){
  p=0;
}
}
vTaskDelay(330/portTICK_PERIOD_MS);
}
}

void P5(void *parameter){
 while(1){
if (p==5){
Serial.println("Sube Taladro Lentamente");
Serial.println("Taladro Girando");

if (!digitalRead(a1)){
  p=6;
}
}
vTaskDelay(330/portTICK_PERIOD_MS);

}
}


void P6(void *parameter){
 while(1){
if (p==6){
Serial.println("Baja Taladro Lentamente");
Serial.println("Taladro Girando");

if (!digitalRead(a3)){
  p=3;
}
}
vTaskDelay(330/portTICK_PERIOD_MS);
}
}
//*void toggle_boton01(void *parameter){
// while(1){
//if (!digitalRead(boton)){
//  Serial.println("On");
//  vTaskDelay(5/portTICK_PERIOD_MS);
//}
//}
//}

void setup(){
pinMode (a0, INPUT_PULLUP);
pinMode (a1, INPUT_PULLUP);
pinMode (a2, INPUT_PULLUP);
pinMode (a3, INPUT_PULLUP);

pinMode (sh, INPUT_PULLUP);

pinMode (INI, INPUT_PULLUP);

pinMode (led, OUTPUT);

Serial.begin(9600);
//Creación de tareas
xTaskCreatePinnedToCore(
P0,		//Función a llamar
"P0",	//Nombre de la tarea
1024		,	//Función a llamar
NULL 	,		//Parametro para enviar a la función
1, 			//Prioridad de la tarea
NULL,			//Identificador o Manejador
App_CPU);

xTaskCreatePinnedToCore(
P1,		//Función a llamar
"P1",	//Nombre de la tarea
1024		,	//Función a llamar
NULL 	,		//Parametro para enviar a la función
1, 			//Prioridad de la tarea
NULL,			//Identificador o Manejador
App_CPU);
xTaskCreatePinnedToCore(
P2,		//Función a llamar
"P2",	//Nombre de la tarea
1024		,	//Función a llamar
NULL 	,		//Parametro para enviar a la función
1, 			//Prioridad de la tarea
NULL,			//Identificador o Manejador
App_CPU);
xTaskCreatePinnedToCore(
P3,		//Función a llamar
"P3",	//Nombre de la tarea
1024		,	//Función a llamar
NULL 	,		//Parametro para enviar a la función
1, 			//Prioridad de la tarea
NULL,			//Identificador o Manejador
App_CPU);
xTaskCreatePinnedToCore(
P4,		//Función a llamar
"P4",	//Nombre de la tarea
1024		,	//Función a llamar
NULL 	,		//Parametro para enviar a la función
1, 			//Prioridad de la tarea
NULL,			//Identificador o Manejador
App_CPU);
xTaskCreatePinnedToCore(
P5,		//Función a llamar
"P5",	//Nombre de la tarea
1024		,	//Función a llamar
NULL 	,		//Parametro para enviar a la función
1, 			//Prioridad de la tarea
NULL,			//Identificador o Manejador
App_CPU);
xTaskCreatePinnedToCore(
P6,		//Función a llamar
"P6",	//Nombre de la tarea
1024		,	//Función a llamar
NULL 	,		//Parametro para enviar a la función
1, 			//Prioridad de la tarea
NULL,			//Identificador o Manejador
App_CPU);
}

void loop(){
  // Se deja vacío porque el trabajo pesado lo hacen las tareas superiores.
}