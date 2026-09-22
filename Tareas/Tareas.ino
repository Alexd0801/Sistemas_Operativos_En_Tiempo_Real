#if CONFIG_FREERTOS_UNICORE
static const BaseType_t App_CPU = 0;
#else
static const BaseType_t App_CPU = 1;
#endif

static const int LED1 = 4; 
static const int LED2 = 5; 
static const int LED3 = 6; 
static const int LED4 = 7; 

static TaskHandle_t tarea_1 = NULL;
static TaskHandle_t tarea_2 = NULL;   //Manejables

//Volatile int p = 0;
void Tarea01(void *parameter){
while(1){
digitalWrite(LED1,HIGH);
  vTaskDelay(2000/portTICK_PERIOD_MS);
digitalWrite(LED1,LOW);
digitalWrite(LED2,HIGH);
  vTaskDelay(1000/portTICK_PERIOD_MS);
digitalWrite(LED2,LOW);
digitalWrite(LED3,HIGH);
  vTaskDelay(2000/portTICK_PERIOD_MS);
digitalWrite(LED3,LOW);

}
}

void Tarea02(void *parameter){
  while(1){
digitalWrite(LED4,HIGH);
  vTaskDelay(20/portTICK_PERIOD_MS);
digitalWrite(LED4,LOW);
  vTaskDelay(20/portTICK_PERIOD_MS);
  }
}

void Tarea03(void *parameter){
  while(1){


    String lectura = Serial.readStringUntil('\n');
    if (lectura == "A"){
    vTaskSuspend(tarea_1);
    }
    if (lectura == "a"){
    vTaskResume(tarea_1);
    }
    if (lectura == "B"){
    vTaskSuspend(tarea_2);
    }
    if (lectura == "b"){
    vTaskResume(tarea_2);
    }
        if (lectura == "1"){
    digitalWrite(LED1,LOW);
    digitalWrite(LED2,LOW);
    digitalWrite(LED3,LOW);
    vTaskDelete(tarea_1);
    }
        if (lectura == "2"){
    digitalWrite(LED4,LOW);
    vTaskDelete(tarea_2);
    }
    vTaskDelay(20/portTICK_PERIOD_MS);
}
}
void setup(){
  Serial.begin(9600);
  pinMode(LED1, OUTPUT);
  pinMode(LED2, OUTPUT);
  pinMode(LED3, OUTPUT);
  pinMode(LED4, OUTPUT);
  
  xTaskCreatePinnedToCore(
Tarea01,		//Función a llamar
"Tarea01",	//Nombre de la tarea
4096		,	//Función a llamar
NULL 	,		//Parametro para enviar a la función
1, 			//Prioridad de la tarea
&tarea_1,			//Identificador o Manejador
App_CPU);
  xTaskCreatePinnedToCore(
Tarea02,		//Función a llamar
"Tarea02",	//Nombre de la tarea
4096		,	//Función a llamar
NULL 	,		//Parametro para enviar a la función
1, 			//Prioridad de la tarea
&tarea_2,			//Identificador o Manejador
App_CPU);


  xTaskCreatePinnedToCore(
Tarea03,		//Función a llamar
"Tarea03",	//Nombre de la tarea
4096		,	//Función a llamar
NULL 	,		//Parametro para enviar a la función
1, 			//Prioridad de la tarea
NULL,			//Identificador o Manejador
App_CPU);
}

void loop(){

}
