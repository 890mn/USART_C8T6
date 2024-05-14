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
    
    SysTick_Config(SystemCoreClock/1000);  //1ms�ж�һ��
    
	USART_SendString((int8_t*)"Hello Keil5!\r\n");
    
	/*OLED��ʼ��*/
	OLED_Init();
	
	
	while(1){			
		if(RXOVER == 1){
            /*��(0, 0)λ����ʾ�����ַ����������СΪ8*16����*/
            OLED_ShowString(0, 0, (char*)USART_RXBUF, OLED_8X16);
            
            /*����OLED_Update��������OLED�Դ���������ݸ��µ�OLEDӲ��������ʾ*/
            OLED_Update();
            
            /*��ʱ3000ms���۲�����*/
            Delay_ms(3000);

			for(i = 0; i < 20; ++i){
				USART_RXBUF[i] = 0; 
			}
            
			RXOVER = 0;
			USART_ITConfig(USART2,USART_IT_RXNE,ENABLE);
		}
	}
	
}
