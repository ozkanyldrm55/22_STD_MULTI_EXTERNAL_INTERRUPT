/*
 * burada yaptýgimiz islem 1 butona bastýgýmýzda ledler 12 den 15 e dogru yanacak , 2. butona bastigimizde 15 den 12 ye dogru yanacak
 * ancak 1 buton calisirken 2. botona basarsak 1.butonun islemi bittiginde 2. botunun islemi baslar.
 * 2. buton calisirken 1. butona basarsak 1. boton devreye girer .cünki öncelik 1. botonda
 */

#include "stm32f4xx.h"
#include "stm32f4_discovery.h"

GPIO_InitTypeDef GPIO_InitStruct;
EXTI_InitTypeDef EXTI_InitStruct;
NVIC_InitTypeDef NVIC_InitStruct;

void delay(uint32_t time)
{
	while(time--);
}

GPIO_Config(void)
{
		RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOD,ENABLE);
		RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOA,ENABLE);

		GPIO_InitStruct.GPIO_Mode = GPIO_Mode_OUT;
		GPIO_InitStruct.GPIO_OType = GPIO_OType_PP;
		GPIO_InitStruct.GPIO_Pin = GPIO_Pin_12 | GPIO_Pin_13 | GPIO_Pin_14 | GPIO_Pin_15;
		GPIO_InitStruct.GPIO_PuPd = GPIO_PuPd_NOPULL;
		GPIO_InitStruct.GPIO_Speed = GPIO_Speed_100MHz;

		GPIO_Init(GPIOD ,&GPIO_InitStruct);

		GPIO_InitStruct.GPIO_Mode = GPIO_Mode_IN;
		GPIO_InitStruct.GPIO_OType = GPIO_OType_PP;
		GPIO_InitStruct.GPIO_Pin = GPIO_Pin_1 | GPIO_Pin_2;
		GPIO_InitStruct.GPIO_PuPd = GPIO_PuPd_DOWN;
		GPIO_InitStruct.GPIO_Speed = GPIO_Speed_100MHz;

		GPIO_Init(GPIOA ,&GPIO_InitStruct);
}

EXTI_Config(void)
{
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_SYSCFG,ENABLE);

	EXTI_InitStruct.EXTI_Line = EXTI_Line1 | EXTI_Line2; // GPIO_Pin_1 | GPIO_Pin_2 pinlerini kullandigimiz icin ilgili line larý kullandýk
	EXTI_InitStruct.EXTI_LineCmd = ENABLE;
	EXTI_InitStruct.EXTI_Mode = EXTI_Mode_Interrupt;
	EXTI_InitStruct.EXTI_Trigger = EXTI_Trigger_Rising; //yukselen kenar tetiklemesi secildi.

	EXTI_Init(&EXTI_InitStruct);


	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_1); //interrupt kesme onceligini ayarlamak icin kullanilir.

	NVIC_InitStruct.NVIC_IRQChannel = EXTI1_IRQn; // EXTI1_IRQn - EXTI2_IRQn ye gore daha onceliklidir cunki  NVIC_IRQChannelPreemptionPriority degeri daha dusuktur
	NVIC_InitStruct.NVIC_IRQChannelCmd = ENABLE;
	NVIC_InitStruct.NVIC_IRQChannelPreemptionPriority = 0;
	NVIC_InitStruct.NVIC_IRQChannelSubPriority = 0;

	NVIC_Init(&NVIC_InitStruct);

	NVIC_InitStruct.NVIC_IRQChannel = EXTI2_IRQn;
	NVIC_InitStruct.NVIC_IRQChannelCmd = ENABLE;
	NVIC_InitStruct.NVIC_IRQChannelPreemptionPriority = 1;
	NVIC_InitStruct.NVIC_IRQChannelSubPriority = 0;

	NVIC_Init(&NVIC_InitStruct);
}

void EXTI1_IRQHandler() //1. butona basildiginda bu fonk girilecek
{
	if(EXTI_GetITStatus(EXTI_Line1) != RESET) // bayrak kalktý mý kontrol ediliyor.
	{
		GPIO_ResetBits(GPIOD,GPIO_Pin_All);
		GPIO_SetBits(GPIOD,GPIO_Pin_12);
		delay(16800000);
		GPIO_SetBits(GPIOD,GPIO_Pin_13);
		delay(16800000);
		GPIO_SetBits(GPIOD,GPIO_Pin_14);
		delay(16800000);
		GPIO_SetBits(GPIOD,GPIO_Pin_15);
		delay(16800000);

		EXTI_ClearITPendingBit(EXTI_Line1); // bayragý temizledik
	}
}

void EXTI2_IRQHandler()
{
	if(EXTI_GetFlagStatus(EXTI_Line2) !=RESET)
	{
		GPIO_ResetBits(GPIOD,GPIO_Pin_All);
		GPIO_SetBits(GPIOD,GPIO_Pin_15);
		delay(16800000);
		GPIO_SetBits(GPIOD,GPIO_Pin_14);
		delay(16800000);
		GPIO_SetBits(GPIOD,GPIO_Pin_13);
		delay(16800000);
		GPIO_SetBits(GPIOD,GPIO_Pin_12);
		delay(16800000);

		EXTI_ClearITPendingBit(EXTI_Line2); // ÝNTERRUPT bayragý temizledik
	}
}

int main(void)
{
	GPIO_Config();
	EXTI_Config();

  while (1)
  {

  }
}


void EVAL_AUDIO_TransferComplete_CallBack(uint32_t pBuffer, uint32_t Size){
  /* TODO, implement your code here */
  return;
}

/*
 * Callback used by stm324xg_eval_audio_codec.c.
 * Refer to stm324xg_eval_audio_codec.h for more info.
 */
uint16_t EVAL_AUDIO_GetSampleCallBack(void){
  /* TODO, implement your code here */
  return -1;
}
