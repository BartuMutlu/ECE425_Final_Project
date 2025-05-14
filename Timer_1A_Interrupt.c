/**
* @file Timer_1A_Interrupt.c
*
* @brief Source file for the Timer_1A_Interrupt driver.
*
* This file contains the function definitions for the Timer_0A_Interrupt driver.
* It uses the Timer 0A module ro generate perodic interrupts.
*
* @note Timer 0A has been configured to generate periodic interrupts every 1 ms
* for the Timers lab. This driver assumes that the system clock's frequency is 50MHz.
*
* Refer to the Table 2-9 (Interrupts) on pages 104 - 106 from the TM4C123G Microcontroller Datasheet
* to view the Vector Number, Interrupt Request (IRQ) Number, and Vector Address
* for each peripheral.
* 
* @author Bartu Mutlu
*/

#include "Timer_1A_Interrupt.h"

// Declare a pointer to the user-defined task
void (*Timer_1A_Task)(void);

void Timer_1A_Interrupt_Init(void(*task)(void))
{
	// Store the user-defined task function for use during interrupt handling
	Timer_1A_Task = task;
	
	// Set the R1 bit in the RCGCTIMER register to enable the clock for Timer 1A
	SYSCTL->RCGCTIMER |= 0x02;
	
	// Clear the TEAN bit (Bit 0) of the GPTMCTL register to disable Timer 1A
	TIMER1->CTL &= ~0x01;
	
	// Set the bit of the GPTMCFG field (Bits 2 to 0) in the GPTMCFG register
	// 0x4 = Select the 16-bit timer configuration
	TIMER1->CFG |= 0X04;
	
	// Set the bits of the GPTMCFG field (Bits 2 to 0) in the GPTMCFG register
	// 0x02 = Periodic Timer Mode
	TIMER1->TAMR |= 0X02;
	
	// Clear the bits of the TAPSR field (Bits 7 to 0) in the 
	// GPTMTAPR register before setting the prescale value
	TIMER1->TAPR &= ~0XFF;
	
	// Set the prescale value to 50 by setting the bits of the
	// TAPSR field (Bits 7 to 0) in the GPMTAPR register
	// New timer clock frequency = (50 MHz / 50) = 1 MHz
	TIMER1->TAPR = 50;
	
	// Set the timer interval load value by writing to the 
	// TAILR field (Bits 31 to 0) in the GPTMTAILR register
	// TIMER 0A Resolution = (1 us * 1000) = 1 ms
	TIMER1->TAILR = (1000-1);
	
	// Set the TATOCINT (Bit 0) to 1 in the GPTMICR register
	// The TATOICR bit will be automatically cleared when it is set to 1
	TIMER1->ICR |= 0x01;
	
	// Enable the Timer 1A interrupt by setting the TATOIM bit (Bit 0) in the GPTMIMR register
	TIMER1->IMR |= 0x01;

	// Set the priority level to 2 for the Timer 1A interrupt
	// In the Interrupt 20-23 Priority (PRI5) register,
	// the INTD field (Bits 15 to 13) corresponds to Intterupt Reequest (IRQ) 21
	// Timer 1A has an IRQ of 21
	NVIC->IPR[5] &= ~0x0000E000;
		
	NVIC->IPR[5] |= (2 << 13);
	
	// Enable IRQ 21 for Timer 0A by setting Bit 21 in the ISER[0] register
	NVIC->ISER[0] |= (1 << 21);
	
	// Set the TAEN bit (Bit 0) in the GPTMCTL register to enable Timer 0A
	TIMER1->CTL |= 0x01;
}

void TIMER1A_Handler(void)
{
	// Read the Timer 0A time-out interrupt flag
	if (TIMER1->MIS & 0x01)
	{
		// Execute the user-defined function
		(*Timer_1A_Task)();
		
		// Acknowledge the Timer 1A interrupt and clear it
		TIMER1->ICR |= 0x01;
	}
}


