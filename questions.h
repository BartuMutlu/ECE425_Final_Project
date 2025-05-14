/**
 * @file questions.h
 *
 * @brief Header file for the database for questions.
 *
 * This file contains the type definition for questions named Question and 
 * initializes an array of Question that contains 25 questions
 * 
 * @note The type Question has 3 elements
 * Name: the element that contains the questions itself
 * Choices: The choices that user has to select
 * Correct: The integer that indexes the correct choice from the Choices element
 *
 * @author Bartu Mutlu
 */


#include <stdio.h>
#include <string.h>
 
 typedef struct {
	char name[256];
	char choices[4][64];
	int correct;
 }Question;
 
 Question questions[25] = 
 {
	{"8 * 4",
	{"32","16","36", "40"},1},
	{"Root of 49?",
	{"4","7","2","10"},2},
	{"4 squared?",
	{"64","161","16","1"},3},
	{"11 * 12",
	{"124","111","123","132"},4},
	{"234 + 123 = ?",
	{"357","302","356","2334"},1},	
	{"12 * 1234",
	{"1245","1400","14808","9999"},3},
	{"11 * 12",
	{"133","130","134","132"},4},	
	{"2x * 3 = 15",
	{"x = 5/2","x = 3/5","x = 2/3","x = 11/3"},1},
	{"121-192",
	{"71","-72","70","-71"},4},	
	{"11 + 999",
	{"1001","1000","1010","1100"},3},
	{"5 cubed?",
	{"25","125","625","5"},2},	
	{"9999 + 1",
	{"1","10","1000","10000"},4},
	{"4 power 5?",
	{"16","1024","64","72"},2},	
	{"x^2 = 64",
	{"x = 5","x = 6","x = 7","x = 8"},4},
	{"Select prime number.",
	{"11","12" ,"134","214"},1},	
	{"12-12*123+1",
	{"-1453","-1463","1463","1234"},2},
	{"Root of 144?",
	{"11","13","14","12"},4},	
	{"23 * 23",
	{"529","234","500","525"},1},
	{"log 12 = ?",
	{"1.912","1.0734","1.079","2 "},3},	
	{"2x - 145 = 10",
	{"x = 76.5","x = 75","x = 70","x = 77.5"},4}, 
	{"123 * 124",
	{"15252","15000","15200 ","12500"},1},	
	{"11111 - 1000",
	{"10101","10000","10111","1110"},3},
	{"9 * 9991",
	{"90000","89919","89920","19293"},2},	
	{"999999 + 1",
	{"1000000","10000","100","100000"},1},
	{"12345 * 4321",
	{"53342745","12134","2113","4532"},1},	
	};
 