# ECE 425 - Microprocessor Systems
**CSU Northridge**

**Department of Electrical and Computer Engineering**

## Final Project: Interactive Quiz Game Implementation

# Introduction

The purpose of the project is to utilize Tiva Launchpad and EduBase Board
to create an interactive quiz type game. 

# The Results and Video Demonstration Links

Demo Link: [text](https://youtube.com/shorts/jp6ssnIStek?feature=share)

# Background and Methodology

I have applied the following concepts of MCUs to realize this project.

1-	GPIO
2-	SysTick
3-	EduBaseBoard LED Screen
4-	PMOD ENC

I have achieved my goal by programming several source and header files such as:

questions.h : A header file that contains type definiton named Question and an array of type question that has 50 math related questions.

quiz_logic.c: The source file that displays 10 questions at random, prompts the user to pick 1 of the answers out of 4 given, and checks whether the selection was corrrect. The codes awards a point if the selection is correct and gives the correct answer if the choice is incorrect.
