#if CONFIG_FREERTOS_UNICORE
  static const BaseType_t app_cpu = 0;
#else
  static const BaseType_t app_cpu = 1;
#endif

//Tarea ----
void testTask (void *parameter){
  while(1){
    int a = 1;
    int b[100];
    for (int i=0 ; i<100; i++){
      b[i] = a + 1;
    }
    Serial.println(b[0]);
    
    Serial.print("------Stack------"); //Para saber en donde comienza
    Serial.println(uxTaskGetStackHighWaterMark(NULL));
    
    Serial.print("------Heap-------"); //Para saber en donde comienza
    Serial.println(xPortGetFreeHeapSize());
    
    int *ptr = (int*)pvPortMalloc(1024 * sizeof(int));
    
    //Condicion para realizar alguna accion antes de que exista un desbordamiento
    if (ptr==NULL){
      Serial.println("Sin espacio en memoria");
      vPortFree(NULL);
    } else {
      for (int i=0; i<1024; i++){
        ptr[i]=3; // NOTA: Corregido de prt a ptr
      }
      // vPortFree(ptr); // Es recomendable descomentar y agregar esto para liberar la memoria asignada dinámicamente y evitar un memory leak en cada ciclo.
    }
    
    Serial.print("Espacio libre despues de Malloc (bytes): ");
    Serial.println(xPortGetFreeHeapSize());
    
    vTaskDelay(100 / portTICK_PERIOD_MS);
  }
}

void setup() {
  Serial.begin(115200);
  vTaskDelay(100 / portTICK_PERIOD_MS);
  Serial.println(100 / portTICK_PERIOD_MS);
  Serial.println();
  Serial.println("Memoria freeRTOS"); // Corregido el typo "Momoria" a "Memoria"

  // --- AQUÍ SE AGREGA LA TAREA ---
  xTaskCreatePinnedToCore(
    testTask,       // Función que implementa la tarea
    "Test Task",    // Nombre en texto de la tarea (para depuración)
    2048,           // Tamaño del Stack (en bytes o palabras dependiendo del microcontrolador, 2048 es seguro)
    NULL,           // Parámetros de entrada para la tarea
    1,              // Prioridad de la tarea (1 es baja/normal)
    NULL,           // Handle de la tarea (NULL si no se necesita referencia)
    app_cpu         // Núcleo en el que se ejecutará (definido al inicio del código)
  );
}

void loop() {
  // put your main code here, to run repeatedly:
  // En FreeRTOS, el loop() usualmente se deja vacío o se usa para tareas de muy baja prioridad.
}