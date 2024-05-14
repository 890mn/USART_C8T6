#include "stm32f10x_it.h"
#include "usart.h"
#include "delay.h"
#include "oled.h"

uint32_t TimingDelay = 0;
uint8_t USART_RXBUF[20];
extern uint8_t RXOVER;

int main(void)
{
	int i;
	USART_Config();
    
    SysTick_Config(SystemCoreClock/1000);  //1ms中断一次
    
	USART_SendString((int8_t*)"Hello Keil5!\r\n");
    
	/*OLED初始化*/
	OLED_Init();
	
	
	while(1){			
		if(RXOVER == 1){
            /*在(0, 0)位置显示发送字符串，字体大小为8*16点阵*/
            OLED_ShowString(0, 0, (char*)USART_RXBUF, OLED_8X16);
            
            /*调用OLED_Update函数，将OLED显存数组的内容更新到OLED硬件进行显示*/
            OLED_Update();
            
            /*延时3000ms，观察现象*/
            Delay_ms(3000);

			for(i = 0; i < 20; ++i){
				USART_RXBUF[i] = 0; 
			}
            
			RXOVER = 0;
			USART_ITConfig(USART2,USART_IT_RXNE,ENABLE);
		}
	}
	
}
