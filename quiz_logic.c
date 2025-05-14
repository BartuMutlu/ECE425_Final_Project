/**
 * @file quiz_logic.c
 *
 * @brief Source code for the quiz logic.
 *
 * This file contains the functions for quiz logic 
 * that will create the quiz game
 *
 * @author Bartu Mutlu
 */


#include "TM4C123GH6PM.h"
#include "SysTick_Delay.h"
#include "PMOD_ENC.h"
#include "EduBase_LCD.h"
#include "questions.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int checkAnswer(Question q, int user_answer)
{
    return ((user_answer + 1) == q.correct);
}

void start_quiz()
{
    int limit = 10;
    int total = sizeof(questions) / sizeof(questions[0]); 
    int score = 0;

    TIMER1->CTL &= ~0x01;  

    for (int i = 0; i < limit; i++) {
        EduBase_LCD_Clear_Display();
        SysTick_Delay1ms(2);  

        int index = rand() % total;
        Question current_question = questions[index];

        EduBase_LCD_Set_Cursor(0, 0);
        char question_line[17];
        snprintf(question_line, sizeof(question_line), "%.16s", current_question.name);
        EduBase_LCD_Display_String(question_line);

        EduBase_LCD_Set_Cursor(0, 1);
        EduBase_LCD_Send_Data(0x03);  
        EduBase_LCD_Set_Cursor(1, 1);
        char choice[16];
        snprintf(choice, sizeof(choice), "%.15s", current_question.choices[0]);  
        EduBase_LCD_Display_String(choice);

        uint8_t enc_last_state = PMOD_ENC_Get_State();
        int selection = 0;
        int prev_selection = 0;
        int length = strlen(choice);

        while (1) {
            uint8_t enc_state = PMOD_ENC_Get_State();

            if (PMOD_ENC_Button_Read(enc_state) && !PMOD_ENC_Button_Read(enc_last_state)) {
                break;
            }

            int rotation = PMOD_ENC_Get_Rotation(enc_state, enc_last_state);
            if (rotation != 0) {
                selection += rotation;
                if (selection < 0) {
                    selection = 0;
                } else if (selection > 3) {
                    selection = 3;
                }
                if (selection != prev_selection) {
                    EduBase_LCD_Set_Cursor(1, 1);
                    snprintf(choice, sizeof(choice), "%.15s", current_question.choices[selection]);
                    EduBase_LCD_Display_String(choice);
                    int length_new = strlen(choice);
                    if (length_new < length) {
                        for (int j = length_new; j < length; j++) {
                            EduBase_LCD_Send_Data(' ');
                        }
                    }
                    length = length_new;
                    prev_selection = selection;
                }
            }

            enc_last_state = enc_state;
            SysTick_Delay1ms(50);  
        }

        int user_answer = selection;
        int is_correct = checkAnswer(current_question, user_answer);

        if (is_correct) {
            EduBase_LCD_Set_Cursor(0, 0);
            EduBase_LCD_Display_String("Correct!");
            int corr_len = strlen("Correct!");
            EduBase_LCD_Set_Cursor(corr_len, 0);
            for (int j = corr_len; j < 16; j++) {
                EduBase_LCD_Send_Data(' ');
            }
        } else {
            EduBase_LCD_Set_Cursor(0, 0);
            EduBase_LCD_Display_String("Incorrect!");

						int incorr_len = strlen("Incorrect!");
            EduBase_LCD_Set_Cursor(incorr_len, 0);
            for (int j = incorr_len; j < 16; j++) {
                EduBase_LCD_Send_Data(' ');
            }

            EduBase_LCD_Set_Cursor(0, 1);
            char ans[17];
            snprintf(ans, sizeof(ans), "Ans: %.11s", current_question.choices[current_question.correct - 1]);
            EduBase_LCD_Display_String(ans);

            int ans_len = strlen(ans);
            EduBase_LCD_Set_Cursor(ans_len, 1);
            for (int j = ans_len; j < 16; j++) {
                EduBase_LCD_Send_Data(' ');
            }
        }

        if (is_correct) {
            score++;
        }

        if (is_correct) {
            SysTick_Delay1ms(1000);
        } else {
            SysTick_Delay1ms(2000);
        }

        total -= 1;
        questions[index] = questions[total];
    }

			EduBase_LCD_Clear_Display();
			EduBase_LCD_Set_Cursor(0, 0);
			EduBase_LCD_Display_String("Quiz completed!");
			char scoreMsg[17];
			snprintf(scoreMsg, sizeof(scoreMsg), "Score: %d/%d", score, limit);
			EduBase_LCD_Set_Cursor(0, 1);
			EduBase_LCD_Display_String(scoreMsg);
			SysTick_Delay1ms(3000); 
		
			TIMER1->CTL |= 0x01; 
}