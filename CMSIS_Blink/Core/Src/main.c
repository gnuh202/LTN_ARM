#include "main.h"

void SystemClock_Config(void);
void SysTick_Init(uint32_t time)
{
  SysTick->VAL = 0;
  SysTick->LOAD = 40*time-1;
  SysTick->CTRL = (SysTick_CTRL_ENABLE_Msk|SysTick_CTRL_CLKSOURCE_Msk);
}

void Delay_ms(uint32_t mS)
{
  uint32_t time = mS;
  SysTick_Init(1000);
  while(time != 0)
     while((SysTick->CTRL & SysTick_CTRL_COUNTFLAG_Msk) == SysTick_CTRL_COUNTFLAG_Msk)
	time--;
}

int main(void)
{
  HAL_Init();
  SystemClock_Config();

  RCC->APB2ENR |= RCC_APB2ENR_IOPCEN_Msk;   //enable portc clock
  GPIOC->CRH |= GPIO_CRH_MODE13_1;     		//PC13 output putpull, speed low
  GPIOC->ODR &= ~GPIO_PIN_13;				//reset state

  while (1)
  {
	  GPIOC->ODR ^= GPIO_PIN_13;
	  Delay_ms(500);
  }
}
void SystemClock_Config(void)
{
  RCC_OscInitTypeDef RCC_OscInitStruct = {0};
  RCC_ClkInitTypeDef RCC_ClkInitStruct = {0};
  RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_HSE;
  RCC_OscInitStruct.HSEState = RCC_HSE_ON;
  RCC_OscInitStruct.HSEPredivValue = RCC_HSE_PREDIV_DIV1;
  RCC_OscInitStruct.HSIState = RCC_HSI_ON;
  RCC_OscInitStruct.PLL.PLLState = RCC_PLL_ON;
  RCC_OscInitStruct.PLL.PLLSource = RCC_PLLSOURCE_HSE;
  RCC_OscInitStruct.PLL.PLLMUL = RCC_PLL_MUL5;
  if (HAL_RCC_OscConfig(&RCC_OscInitStruct) != HAL_OK)
  {
    Error_Handler();
  }
  RCC_ClkInitStruct.ClockType = RCC_CLOCKTYPE_HCLK|RCC_CLOCKTYPE_SYSCLK
                              |RCC_CLOCKTYPE_PCLK1|RCC_CLOCKTYPE_PCLK2;
  RCC_ClkInitStruct.SYSCLKSource = RCC_SYSCLKSOURCE_PLLCLK;
  RCC_ClkInitStruct.AHBCLKDivider = RCC_SYSCLK_DIV1;
  RCC_ClkInitStruct.APB1CLKDivider = RCC_HCLK_DIV2;
  RCC_ClkInitStruct.APB2CLKDivider = RCC_HCLK_DIV1;
  if (HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_1) != HAL_OK)
  {
    Error_Handler();
  }
}
void Error_Handler(void)
{
  __disable_irq();
  while (1);
}
