/**
 * @file EduBase_LCD.c
 *
 * @brief Source code for the EduBase_LCD driver.
 *
 * This file contains the function definitions for the EduBase_LCD driver.
 * It interfaces with the EduBase Board 16x2 Liquid Crystal Display (LCD). 
 * The following pins are used:
 *  - Data Pin 4      [D4]  (PA2)
 *  - Data Pin 5      [D5]  (PA3)
 *  - Data Pin 6      [D6]  (PA4)
 *  - Data Pin 7      [D7]  (PA5)
 *	- LCD Enable      [E]   (PC6)
 *  - Register Select [RS]  (PE0)
 *
 * @note For more information regarding the LCD, refer to the HD44780 LCD Controller Datasheet.
 * Link: https://www.sparkfun.com/datasheets/LCD/HD44780.pdf
 *
 * @author Bartu Mutlu
 */
 
 #include "EduBase_LCD.h"
 static uint8_t display_control = 0x00;
 static uint8x4_t display_mode = 0x00;
 
 
// function for lcd ports intitialization
 
 void EduBase_LCD_Ports_Init(void)
 {
	SYSCTL -> RCGCGPIO |= 0x01;
	GPIOA -> DIR |= 0X3C;
	GPIOA->AFSEL &= ~0x3C;
	GPIOA->DEN |= 0x3C;
	GPIOA->DATA &= ~0x3C;
	SYSCTL->RCGCGPIO |= 0x04;
	GPIOC->DIR |= 0x40;
	GPIOC->AFSEL &= ~0x40;
	GPIOC->DEN |= 0x40;
	GPIOC->DATA &= ~0x40;
	SYSCTL->RCGCGPIO |= 0x10;
	GPIOE->DIR |= 0x01;
	GPIOE->AFSEL &= ~0x01;
	GPIOE->DEN |= 0x01;
	GPIOE->DATA &= ~0x01;
 }
 
 void EduBase_LCD_Pulse_Enable(void)
{
	GPIOC->DATA &= ~0x40;
	SysTick_Delay1us(1);
	
	GPIOC->DATA |= 0x40;
	SysTick_Delay1us(1);
	GPIOC->DATA &= ~0x40;
}

void EduBase_LCD_Write_4_Bits(uint8_t data, uint8_t control_flag)
{
	GPIOA->DATA |= (data & 0xF0) >> 0x2;
	
	if (control_flag & 0x01)
	{
		GPIOE->DATA |= 0x01;
	}else {
		GPIOE->DATA &= ~0x01;
	}
	
	EduBase_LCD_Pulse_Enable();
	
	GPIOA->DATA &= ~0x3C;
	SysTick_Delay1us(1000);
}

void EduBase_LCD_Send_Command(uint8_t command)
{
	EduBase_LCD_Write_4_Bits(command & 0xF0, SEND_COMMAND_FLAG);
	
	EduBase_LCD_Write_4_Bits(command << 0x4, SEND_COMMAND_FLAG);
	
	if (command < 3)
	{
		SysTick_Delay1us(1520);
	} else {
		SysTick_Delay1us(37);
	}

}

void EduBase_LCD_Send_Data(uint8_t data)
{
	EduBase_LCD_Write_4_Bits(data & 0xF0, SEND_DATA_FLAG);
	
	EduBase_LCD_Write_4_Bits( data << 0x4, SEND_DATA_FLAG);
}

void EduBase_LCD_Init(void)
{
	EduBase_LCD_Ports_Init();
	
	SysTick_Delay1us(50000);
	
	EduBase_LCD_Write_4_Bits(FUNCTION_SET | CONFIG_EIGHT_BIT_MODE, SEND_COMMAND_FLAG);
	SysTick_Delay1us(4500);
	
	EduBase_LCD_Write_4_Bits(FUNCTION_SET | CONFIG_EIGHT_BIT_MODE, SEND_COMMAND_FLAG);
	SysTick_Delay1us(4500);
	
	EduBase_LCD_Write_4_Bits(FUNCTION_SET | CONFIG_EIGHT_BIT_MODE, SEND_COMMAND_FLAG);
	SysTick_Delay1us(150);
	
	EduBase_LCD_Write_4_Bits(FUNCTION_SET | CONFIG_FOUR_BIT_MODE, SEND_COMMAND_FLAG);
	
	EduBase_LCD_Send_Command(FUNCTION_SET | CONFIG_5x10_DOTS | CONFIG_TWO_LINES);
	
	EduBase_LCD_Enable_Display();
	
	EduBase_LCD_Return_Home();
	
	EduBase_LCD_Clear_Display();
	
	EduBase_LCD_Disable_Cursor_Blink();
	EduBase_LCD_Disable_Cursor();

}

void EduBase_LCD_Clear_Display(void)
{
	EduBase_LCD_Send_Command(CLEAR_DISPLAY);

}

void EduBase_LCD_Return_Home(void)
{
	EduBase_LCD_Send_Command(RETURN_HOME);
}

void EduBase_LCD_Set_Cursor(uint8_t col, uint8_t row)
{
	if (col < 16){
		if (row == 0){
			EduBase_LCD_Send_Command(SET_DDRAM_ADDR | col);
		} else if (row == 1) {
			EduBase_LCD_Send_Command(SET_DDRAM_ADDR | (col + 0x40));
		}
	}

}

void EduBase_LCD_Disable_Display(void)
{
	display_control = display_control & ~(DISPLAY_ON);
	EduBase_LCD_Send_Command(DISPLAY_CONTROL | display_control);

}

void EduBase_LCD_Enable_Display(void)
{
	display_control = display_control | DISPLAY_ON;
	EduBase_LCD_Send_Command(DISPLAY_CONTROL | display_control);
}

void EduBase_LCD_Disable_Cursor(void)
{
	display_control = display_control & ~(CURSOR_ON);
	EduBase_LCD_Send_Command(DISPLAY_CONTROL | display_control);

}

void EduBase_LCD_Enable_Cursor(void)
{
	display_control = display_control | CURSOR_ON;
	EduBase_LCD_Send_Command(DISPLAY_CONTROL | display_control);
}

void EduBase_LCD_Disable_Cursor_Blink(void)
{
	display_control = display_control & ~CURSOR_BLINK_ON;
	EduBase_LCD_Send_Command(DISPLAY_CONTROL | display_control);
}

void EduBase_LCD_Enable_Cursor_Blink(void)
{
	display_control = display_control | CURSOR_BLINK_ON;
	EduBase_LCD_Send_Command(DISPLAY_CONTROL | display_control);

}

void EduBase_LCD_Scroll_Display_Left(void)
{
	EduBase_LCD_Send_Command(CURSOR_OR_DISPLAY_SHIFT | DISPLAY_MOVE | MOVE_LEFT);

}

void EduBase_LCD_Scroll_Display_Right(void)
{
	EduBase_LCD_Send_Command(CURSOR_OR_DISPLAY_SHIFT | DISPLAY_MOVE | MOVE_RIGHT);

}

void EduBase_LCD_Left_to_Right(void)
{
	display_mode = display_mode | ENTRY_SHIFT_INCREMENT;
	EduBase_LCD_Send_Command(ENTRY_MODE_SET | display_mode);

}

void EduBase_LCD_Right_to_Left(void)
{
	display_mode = display_mode & ~ENTRY_SHIFT_INCREMENT;
	EduBase_LCD_Send_Command(ENTRY_MODE_SET | display_mode);

}

void EduBase_LCD_Create_Custom_Character(uint8_t location, uint8_t character_buffer[])
{
	location = location & 0x7;
	EduBase_LCD_Send_Command(SET_CGRAM_ADDR | (location << 3));
	for (int i = 0; i < 0; i++){
		EduBase_LCD_Send_Data(character_buffer[i]);
	}

}

void EduBase_LCD_Display_String(char* string)
{
	for (unsigned int i=0; i < strlen(string); i++)
	{
		EduBase_LCD_Send_Data(string[i]);
	}

}

void EduBase_LCD_Display_Integer(int value)
{
	char integer_buffer[32];
	sprintf(integer_buffer, "%d", value);
	EduBase_LCD_Display_String(integer_buffer);
}

void EduBase_LCD_Display_Double(double value)
{
	char double_buffer[32];
	sprintf(double_buffer, "%.6f", value);
	EduBase_LCD_Display_String(double_buffer);

}