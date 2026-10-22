#if CONFIG_FREERTOS_UNICORE
  static const BaseType_t app_cpu=0;
#else
  static const BaseType_t app_cpu=0;
#endif

#include <Wire.h>
#include <Adafruit_MPU6050.h>
#include <Adafruit_Sensor.h>

Adafruit_MPU6050 mpu1;
Adafruit_MPU6050 mpu2;

float alfa=0.8;

struct Aceleracion1{ //Agrupamos para mandar los datos en conjunto por la Queue
  float x1;
  float y1;
  float z1;
};
struct Aceleracion2{ //Agrupamos para mandar los datos en conjunto por la Queue
  float x2;
  float y2;
  float z2;
};

struct Aceleracionfil1{ //Agrupamos para mandar los datos en conjunto por la Queue
  float x3;
  float y3;
  float z3;
};
struct Aceleracionfil2{ //Agrupamos para mandar los datos en conjunto por la Queue
  float x4;
  float y4;
  float z4;
};

static const uint8_t queue_len = 5 ;
static QueueHandle_t Filtro_1;
static QueueHandle_t Filtro_2;
static QueueHandle_t Print_1;
static QueueHandle_t Print_2;

static SemaphoreHandle_t mutex;
static SemaphoreHandle_t mutex2;

void Print1(void *parameters){
  Aceleracion1 Aceleracion_c;
  Aceleracionfil1 Aceleracion_fil;
while(1){

  if(xSemaphoreTake(mutex, portMAX_DELAY) == pdTRUE){
     sensors_event_t a, g, temp;
     mpu1.getEvent(&a, &g, &temp);
  Aceleracion_c.x1 = a.acceleration.x;
  Aceleracion_c.y1 = a.acceleration.y;
  Aceleracion_c.z1 = a.acceleration.z;
     xQueueSend(Print_1, (void*)&Aceleracion_c,0);
          xSemaphoreGive(mutex);
  }
   if (xQueueReceive(Filtro_1, (void*)&Aceleracion_fil,portMAX_DELAY)==pdTRUE){
    if(xSemaphoreTake(mutex,portMAX_DELAY)==pdTRUE){
Serial.print("MPU1 Ax filtrado: ");
Serial.print(Aceleracion_fil.x3);
Serial.print(", Ay filtrado: ");
Serial.print(Aceleracion_fil.y3);
Serial.print(", Az filtrado: ");
Serial.println(Aceleracion_fil.z3);
          xSemaphoreGive(mutex);
    }
   }

    vTaskDelay(1000/portTICK_PERIOD_MS);
  }
}

void Filtro1(void *parameters){
  Aceleracion1 Aceleracion_rec;
  Aceleracionfil1 Aceleracion_filt;
  float vfx=0;
  float vfy=0;
  float vfz=0;
while(1){
    if(xQueueReceive(Print_1, (void*)&Aceleracion_rec,portMAX_DELAY)==pdTRUE){
  if(xSemaphoreTake(mutex, portMAX_DELAY) == pdTRUE){
Serial.print("MPU1 Ax crudo: ");
Serial.print(Aceleracion_rec.x1);
Serial.print(", Ay crudo: ");
Serial.print(Aceleracion_rec.y1);
Serial.print(", Az crudo: ");
Serial.println(Aceleracion_rec.z1);
        xSemaphoreGive(mutex);
  }
Aceleracion_filt.x3 = (alfa*Aceleracion_rec.x1)+(1-alfa)*vfx;
Aceleracion_filt.y3 = (alfa*Aceleracion_rec.y1)+(1-alfa)*vfy;
Aceleracion_filt.z3 = (alfa*Aceleracion_rec.z1)+(1-alfa)*vfz;

vfx=Aceleracion_filt.x3;
vfx=Aceleracion_filt.y3;
vfx=Aceleracion_filt.z3;

xQueueSend(Filtro_1,(void*)&Aceleracion_filt,0);


  }
    }


  }

void Print2(void *parameters){
  Aceleracion2 Aceleracion_c;
  Aceleracionfil2 Aceleracion_fil;
while(1){

  if(xSemaphoreTake(mutex, portMAX_DELAY) == pdTRUE){
     sensors_event_t a, g, temp;
     mpu2.getEvent(&a, &g, &temp);
  Aceleracion_c.x2 = a.acceleration.x;
  Aceleracion_c.y2 = a.acceleration.y;
  Aceleracion_c.z2 = a.acceleration.z;
     xQueueSend(Print_2, (void*)&Aceleracion_c,0);
          xSemaphoreGive(mutex);
  }
   if (xQueueReceive(Filtro_2, (void*)&Aceleracion_fil,portMAX_DELAY)==pdTRUE){
    if(xSemaphoreTake(mutex,portMAX_DELAY)==pdTRUE){
Serial.print("MPU2 Ax Filtrado: ");
Serial.print(Aceleracion_fil.x4);
Serial.print(", Ay Filtrado: ");
Serial.print(Aceleracion_fil.y4);
Serial.print(", Az Filtrado: ");
Serial.println(Aceleracion_fil.z4);
          xSemaphoreGive(mutex);
    }
   }

    vTaskDelay(1000/portTICK_PERIOD_MS);
  }
}

void Filtro2(void *parameters){
  Aceleracion2 Aceleracion_rec;
  Aceleracionfil2 Aceleracion_filt;
  float vfx=0;
  float vfy=0;
  float vfz=0;
while(1){
    if(xQueueReceive(Print_2, (void*)&Aceleracion_rec,portMAX_DELAY)==pdTRUE){
  if(xSemaphoreTake(mutex, portMAX_DELAY) == pdTRUE){
Serial.print("MPU2 Ax Crudo: ");
Serial.print(Aceleracion_rec.x2);
Serial.print(" MPU2 Ay Crudo: ");
Serial.print(Aceleracion_rec.y2);
Serial.print(" MPU2 Az Crudo: ");
Serial.println(Aceleracion_rec.z2);
        xSemaphoreGive(mutex);
  }
Aceleracion_filt.x4 = (alfa*Aceleracion_rec.x2)+(1-alfa)*vfx;
Aceleracion_filt.y4 = (alfa*Aceleracion_rec.y2)+(1-alfa)*vfy;
Aceleracion_filt.z4 = (alfa*Aceleracion_rec.z2)+(1-alfa)*vfz;

vfx=Aceleracion_filt.x4;
vfx=Aceleracion_filt.y4;
vfx=Aceleracion_filt.z4;

xQueueSend(Filtro_2,(void*)&Aceleracion_filt,0);


  }
    }


  }


void setup() {
  Serial.begin(115200);
     Wire.begin(8, 9);
  vTaskDelay(1000/portTICK_PERIOD_MS);
  mpu1.begin(0x68, &Wire);
  mpu2.begin(0x69, &Wire);

 mutex = xSemaphoreCreateMutex();

Filtro_1 = xQueueCreate(queue_len, sizeof(Aceleracionfil1));  
  Filtro_2 = xQueueCreate(queue_len, sizeof(Aceleracionfil2));
  Print_1 = xQueueCreate(queue_len, sizeof(Aceleracion1));
  Print_2 = xQueueCreate(queue_len, sizeof(Aceleracion2));
  xTaskCreatePinnedToCore(Print1, "Tarea1", 4096, NULL, 1, NULL, app_cpu);
  xTaskCreatePinnedToCore(Filtro1, "Tarea2", 4096, NULL, 1, NULL, app_cpu);
  xTaskCreatePinnedToCore(Print2, "Tarea3", 4096, NULL, 1, NULL, app_cpu);
  xTaskCreatePinnedToCore(Filtro2, "Tarea4", 4096, NULL, 1, NULL, app_cpu);
  vTaskDelete(NULL);
}

void loop() {
  // put your main code here, to run repeatedly:

}