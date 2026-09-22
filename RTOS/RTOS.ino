#if CONFIG_FREERTOS_UNICORE
static const BaseType_t App_CPU = 0;
#else
static const BaseType_t App_CPU = 1;
#endif
static const int led1 =5;
static const int led2 =6;
static const int led3 =7;
//static const int boton =4;
void toggle_led01(void *parameter){
 while(1){
digitalWrite(led1, HIGH);
vTaskDelay(500/portTICK_PERIOD_MS);
digitalWrite(led1,LOW);
vTaskDelay(500/portTICK_PERIOD_MS);
}
}
void toggle_led02(void *parameter){
 while(1){
digitalWrite(led2, HIGH);
vTaskDelay(330/portTICK_PERIOD_MS);
digitalWrite(led2,LOW);
vTaskDelay(330/portTICK_PERIOD_MS);
}
}
void toggle_boton01(void *parameter){
 while(1){
if (!digitalRead(boton)){
  Serial.println("On");
  vTaskDelay(5/portTICK_PERIOD_MS);
}
}
}

void setup(){
pinMode (led1, OUTPUT);
pinMode (led2, OUTPUT);
pinMode (boton, INPUT_PULLUP);
Serial.begin(9600);
//Creación de tareas
xTaskCreatePinnedToCore(
toggle_led01,		//Función a llamar
"toggle_led01",	//Nombre de la tarea
1024		,	//Función a llamar
NULL 	,		//Parametro para enviar a la función
1, 			//Prioridad de la tarea
NULL,			//Identificador o Manejador
App_CPU);
xTaskCreatePinnedToCore(
toggle_led02,		//Función a llamar
"toggle_led02",	//Nombre de la tarea
1024		,	//Función a llamar
NULL 	,		//Parametro para enviar a la función
1, 			//Prioridad de la tarea
NULL,			//Identificador o Manejador
App_CPU);
xTaskCreatePinnedToCore(
toggle_boton01,		//Función a llamar
"toggle_boton01",	//Nombre de la tarea
1024		,	//Función a llamar
NULL 	,		//Parametro para enviar a la función
1, 			//Prioridad de la tarea
NULL,			//Identificador o Manejador
App_CPU);
}


void loop(){
  // Se deja vacío porque el trabajo pesado lo hacen las tareas superiores.
}
