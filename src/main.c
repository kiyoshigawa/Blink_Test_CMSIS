//Include CMSIS definitions for everything
#include "stm32f070x6.h"

void delay(uint32_t delay_cycles){
  for(volatile int i=0; i<delay_cycles; i++){}
}

int main(void){
  //init things:

  //Setup External Oscillator:
  

  //GPIO Init:
  RCC->AHBENR |= RCC_AHBENR_GPIOAEN; //enable clock to GPIOA
  GPIOA->MODER |= GPIO_MODER_MODER5_0; //set the mode to output for PA5.
  GPIOA->OTYPER |= GPIO_OTYPER_OT_5; //set the type to output push-pull
  GPIOA->OSPEEDR = 0U; //set the whole GPIOA register to low speed.

  //loop:
  while(1){
    GPIOA->BSRR = GPIO_BSRR_BS_5;
    delay(1000000);
    GPIOA->BSRR = GPIO_BSRR_BR_5;
    delay(1000000);
  }

  //return 0;
}

void SystemInit(){
  /* Reset the RCC clock configuration to the default reset state ------------*/
  /* Set HSION bit */
  RCC->CR |= (uint32_t)0x00000001U;

  /* Reset SW[1:0], HPRE[3:0], PPRE[2:0], ADCPRE, MCOSEL[2:0], MCOPRE[2:0] and PLLNODIV bits */
  RCC->CFGR &= (uint32_t)0x08FFB80CU;
  
  /* Reset HSEON, CSSON and PLLON bits */
  RCC->CR &= (uint32_t)0xFEF6FFFFU;

  /* Reset HSEBYP bit */
  RCC->CR &= (uint32_t)0xFFFBFFFFU;

  /* Reset PLLSRC, PLLXTPRE and PLLMUL[3:0] bits */
  RCC->CFGR &= (uint32_t)0xFFC0FFFFU;

  /* Reset PREDIV[3:0] bits */
  RCC->CFGR2 &= (uint32_t)0xFFFFFFF0U;
  
  /* Reset USART1SW[1:0], I2C1SW, USBSW and ADCSW bits */
  RCC->CFGR3 &= (uint32_t)0xFFFFFE6CU;

  /* Set default USB clock to PLLCLK, since there is no HSI48 */
  RCC->CFGR3 |= (uint32_t)0x00000080U;  

  /* Reset HSI14 bit */
  RCC->CR2 &= (uint32_t)0xFFFFFFFEU;

  /* Disable all interrupts */
  RCC->CIR = 0x00000000U;
}