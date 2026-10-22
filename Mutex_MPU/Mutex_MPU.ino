#if CONFIG_FREERTOS_UNICORE
 static const BaseType_t app_cpu = 0;
#else
 static const BaseType_t app_cpu = 1;
#endif

#include <Wire.h>
#include <LiquidCrystal_I2C.h>
#include <Adafruit_MPU6050.h>
#include <Adafruit_Sensor.h>

static SemaphoreHandle_t mutex;

Adafruit_MPU6050 mpu1;
Adafruit_MPU6050 mpu2;
LiquidCrystal_I2C lcd(0x27, 16, 2); //Dirección de la lcd para el mismo puerto i2c

void MPU1(void *pvParameters) {
 while(1) {
if(xSemaphoreTake(mutex, 0) == pdTRUE) {
 sensors_event_t a, g, temp;
 mpu1.getEvent(&a, &g, &temp);
 
 lcd.setCursor(0, 0); 
 lcd.print("1:");
 lcd.print(temp.temperature, 1);
 lcd.print("C "); 

 xSemaphoreGive(mutex);
}
vTaskDelay(300 / portTICK_PERIOD_MS);
}
}

void MPU2(void *pvParameters) {
 while(1) {
 if(xSemaphoreTake(mutex, 0) == pdTRUE) {
 sensors_event_t a, g, temp;
 mpu2.getEvent(&a, &g, &temp);
 
 lcd.setCursor(0, 1); 
 lcd.print("2:");
lcd.print(g.gyro.z * 57.3, 1); 
lcd.print(" grados/s");
 
 xSemaphoreGive(mutex);
 }
 vTaskDelay(300 / portTICK_PERIOD_MS);
 }
}

void setup() {
 Wire.begin(8, 9);
 mutex = xSemaphoreCreateMutex();
 lcd.init();
 lcd.backlight();
 lcd.clear();
 mpu1.begin(0x68, &Wire); //Se asignan en diferentes direcciones porque usan el mismo i2c
 mpu2.begin(0x69, &Wire);

 xTaskCreatePinnedToCore(MPU1, "T1", 2048, NULL, 1, NULL, app_cpu);
 xTaskCreatePinnedToCore(MPU2, "T2", 2048, NULL, 1, NULL, app_cpu);
}

void loop() {

} 