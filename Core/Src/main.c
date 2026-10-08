#include "stm32f10x.h"
#include "FreeRTOS.h"
#include "task.h"

typedef struct
{
    uint8_t pin;
    float freq;
} LED_Config;

void LED_Task(void *arg)
{
    LED_Config *led=(LED_Config*)arg;
    TickType_t t=pdMS_TO_TICKS((uint32_t)(500.0f/led->freq));

    while(1)
    {
        GPIOA->ODR^=(1<<led->pin);
        vTaskDelay(t);
    }
}

LED_Config led0={0,0.1f};
LED_Config led1={1,1.0f};
LED_Config led2={2,10.0f};

int main(void)
{
    RCC->APB2ENR|=RCC_APB2ENR_IOPAEN;
		GPIOA->CRL = 0x11111111;

    xTaskCreate(LED_Task,"LED0",128,&led0,1,0);
    xTaskCreate(LED_Task,"LED1",128,&led1,1,0);
    xTaskCreate(LED_Task,"LED2",128,&led2,1,0);

    vTaskStartScheduler();

    while(1);
}