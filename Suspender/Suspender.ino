#if CONFIG_FREERTOS_UNICORE
static const BaseType_t App_CPU = 0;
#else
static const BaseType_t App_CPU = 1;
#endif

const char msg[]= "Hola mundo UPIIZ";

static TaskHandle_t tarea_1 = NULL;
static TaskHandle_t tarea_2 = NULL;

void Tarea01(void *parameter){
  int msg_lenght = strlen(msg);
  for (int i = 0; i<msg_lenght; i++){
    Serial.print(msg[i]);
    vTaskDelay(1/portTICK_PERIOD_MS);
  }
  Serial.println();
  vTaskDelay(1000/portTICK_PERIOD_MS);
}

void Tarea02(void *parameter){
  Serial.print('+');
  vTaskDelay(100/portTICK_PERIOD_MS);
}


void setup(){
  Serial.begin(300);
  vTaskDelay(1000/portTICK_PERIOD_MS);
  Serial.println();
  Serial.println("-----Mensaje de Inicio-----");
  
  xTaskCreatePinnedToCore(
Tarea01,		//Función a llamar
"Tarea01",	//Nombre de la tarea
1024		,	//Función a llamar
NULL 	,		//Parametro para enviar a la función
1, 			//Prioridad de la tarea
&tarea_1,			//Identificador o Manejador
App_CPU);
  xTaskCreatePinnedToCore(
Tarea02,		//Función a llamar
"Tarea02",	//Nombre de la tarea
1024		,	//Función a llamar
NULL 	,		//Parametro para enviar a la función
1, 			//Prioridad de la tarea
&tarea_2,			//Identificador o Manejador
App_CPU);

}

void loop(){
  for (int i=0; i<3; i++){
    vTaskSuspend(tarea_2);
    vTaskDelay(2000/portTICK_PERIOD_MS);
    vTaskResume(tarea_2);
    vTaskDelay(2000/portTICK_PERIOD_MS);    
  }

  if (tarea_1 != NULL){
    vTaskDelete(tarea_1);
    tarea_1 = NULL;
  }
}


