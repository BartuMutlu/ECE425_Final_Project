
#include "TM4C123GH6PM.h"
#include "SysTick_Delay.h"
#include "EduBase_LCD.h"
#include "PMOD_ENC.h"
#include "Timer_1A_Interrupt.h"
#include "GPIO.h"
#include "quiz_logic.h"

#define MAX_COUNT 15

static uint8_t state = 0;
static uint8_t last_state = 0;
static uint8_t pmod_enc_btn_pressed = 0;
static int prev_main_menu_counter = 0xFF;
static int main_menu_counter = 0;

void PMOD_ENC_Task(void);

int main(void){

	SysTick_Delay_Init();
	EduBase_LCD_Init();

	EduBase_LCD_Create_Custom_Character(RIGHT_ARROW_LOCATION,right_arrow);
	EduBase_LEDs_Init();
	PMOD_ENC_Init();
	Timer_1A_Interrupt_Init(&PMOD_ENC_Task);
	last_state = 	PMOD_ENC_Get_State();
	
	while(1)
	{
		if (prev_main_menu_counter != main_menu_counter)
		{
			EduBase_LCD_Clear_Display();
			Display_Main_Menu(main_menu_counter);
			prev_main_menu_counter = main_menu_counter;
		}
		Process_Main_Menu_Selection();
		SysTick_Delay1ms(100);
	}
}

void PMOD_ENC_Task(void){
	state = PMOD_ENC_Get_State();
	
	if (PMOD_ENC_Button_Read(state) && !PMOD_ENC_Button_Read(last_state))
	{
		pmod_enc_btn_pressed = 1;
	}
	
	if (main_menu_counter < 0)
	{
		main_menu_counter = 0;
	} else if ( main_menu_counter > MAX_COUNT)
	{
		main_menu_counter = MAX_COUNT;
	} else
	{
		main_menu_counter = main_menu_counter + PMOD_ENC_Get_Rotation(state, last_state);
	}
	last_state = state;
}

void Display_Main_Menu(int main_menu_state)
{
	switch(main_menu_state)
	{
		case 0x00:
		{
			EduBase_LCD_Set_Cursor(0,0);
			EduBase_LCD_Send_Data(0x03);
			EduBase_LCD_Set_Cursor(1,0);
			EduBase_LCD_Display_String("Start Quiz");
			break;
		}
	}
}

void Process_Main_Menu_Selection(void)
{
	if(pmod_enc_btn_pressed == 1)
	{
		pmod_enc_btn_pressed = 0;
		prev_main_menu_counter = 0xFF;
		
		switch(main_menu_counter)
		{
			case 0x00:
			{
				start_quiz();
				main_menu_counter = 0;
        prev_main_menu_counter = 0xFF;
        break;
			}
			default:
			break;				
		}
	}
}

