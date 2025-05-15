# ECE 425 - Microprocessor Systems
**CSU Northridge**

**Department of Electrical and Computer Engineering**

## Final Project: Interactive Quiz Game Implementation

# Introduction

The purpose of the project is to utilize Tiva Launchpad and EduBase Board
to create an interactive quiz type game. 

# The Results and Video Demonstration Links

Demo Link: [Demo](https://youtube.com/shorts/jp6ssnIStek?feature=share)

# Background and Methodology

I have applied the following concepts of MCUs to realize this project.

1-	GPIO
2-	SysTick
3-	EduBaseBoard LED Screen
4-	PMOD ENC

I have achieved my goal by programming several source and header files such as:

questions.h : A header file that contains type definiton named Question and an array of type question that has 50 math related questions.

quiz_logic.c: The source file that displays 10 questions at random, prompts the user to pick 1 of the answers out of 4 given, and checks whether the selection was corrrect. The codes awards a point if the selection is correct and gives the correct answer if the choice is incorrect.

Upon starting the program, the LCD displays a menu consisting only 1 option: “Start Quiz”. Upon pressing this option, the quiz_logic code executes, starting the quiz game. The code gives 10 questions chosen at random from the questions database. The database itself contains 50 math related questions, 4 answer choices in each question for the user to select from and the index that points to the correct choice. 
When the user makes the selection using the PMOD_ENC module, the quiz logic checks the index of the choice selected. If the selection matches the index, the question is deemed correct, and the code gives a point and displays “Correct!”, if it is incorrect the code displays “Incorrect!” and displays the correct answer. After a few seconds, the code displays the next question. At the end of the quiz game, the code displays the total score earned.