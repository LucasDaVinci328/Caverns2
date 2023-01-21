#ifndef TYPEFONT_H
#define TYPEFONT_H

// typefont.h
// Name: typefont library
// Author: Luke Devenney
// Date: 10/29/2021

#include <string>
#include <fstream>
#include <iostream>

#include "box.h"

using namespace std;

void newLine(int height = 6) {
	downwards(height);
	for(int i = 0; i <= height; i++)
		cout<<'\n';
	upwards(height);
}

void type(string message, int size = 1) {
	const int MAX_SIZE = 5;
	const int LINE_LENGTH = 200;
	if (size<1) size = 1;

	newLine(size*5+1);
	upwards(size*5+1);

	int width = 0;

	for (int i = 0; i < message.length(); i++) {
		width+=size*5+1;
		if (width>LINE_LENGTH) {
			newLine(size*5+1); 
			width = 0; 
		}
		if (message[i]==' ') {
			rightwards(size*5);
			continue;
		}
		message[i] = toupper(message[i]);
		ifstream fin;
		fin.open("letters.txt");
		if (fin.fail()) break;
		string input;
		while(input[0]!=message[i] & !fin.eof()) fin>>input;
		char letterOrig[5][5];
		
		for (int j = 0; j < 5; j++)
			for (int g = 0; g < 5; g++)
				letterOrig[j][g] = ' ';	
	
		getline(fin, input, '\n');

		for (int j = 0; j < 5; j++) {
			getline(fin, input, '\n');
			for (int g = 0; g < 5; g++) 
				letterOrig[j][g] = input[g];
		}

		char letter[MAX_SIZE*5+2][MAX_SIZE*5+2];

		for (int j = 0; j < MAX_SIZE*5+2; j++)
			for (int g = 0; g < MAX_SIZE*5+2; g++)
				letter[j][g] = ' ';	

		for (int j = 1; j <=size*5; j++)
			for (int g = 1; g <=size*5; g++) 
				letter[j][g] = letterOrig[(j-1)/size][(g-1)/size];
			
		
		for (int j = 1; j <=size*5; j++) {
			for (int g = 1; g <=size*5; g++) {
				if (letter[j][g]!=' ') {
					bool diagonal = 0;
					int colID[4];
					colID[0] = (letter[j+1][g] == ' ')? 0 : 1;
					colID[1] = (letter[j][g-1] == ' ')? 0 : 1;
					colID[2] = (letter[j][g+1] == ' ')? 0 : 1;
					colID[3] = (letter[j-1][g] == ' ')? 0 : 1; 
					int colSUM = colID[0] + colID[1]*2 + colID[2]*4 + colID[3]*8;

					switch(colSUM) {
						case 0:
							letter[j][g] = 'o';
							diagonal = 1;
							break;
						case 1:
							letter[j][g] = '|';
							diagonal = 1;
							break;
						case 2:
							letter[j][g] = '-';
							diagonal = 1;
							break;
						case 1+2:
							letter[j][g] =  -3;
							break;
						case 4:
							letter[j][g] = '-';
							diagonal = 1;
							break;
						case 1+4:
							letter[j][g] = -4;
							break;
						case 2+4:
							letter[j][g] = '-';
							break;
						case 1+2+4:
							letter[j][g] = '-';
							break;	
						case 8:
							letter[j][g] = '|';
							diagonal = 1;
							break;
						case 1+8:
							letter[j][g] = '|';
							break;
						case 2+8:
							letter[j][g] = -1;
							break;
						case 1+2+8:
							letter[j][g] = '|';
							break;
						case 4+8:
							letter[j][g] = -2;
							break;
						case 1+4+8:
							letter[j][g] = '|';
							break;
						case 2+4+8:
							letter[j][g] = '-';
							break;
						case 1+2+4+8:
							letter[j][g] = -5;
							break;							
					}
				if (diagonal) {
					colID[3] = (letter[j-1][g+1] == ' ')? 0 : 1;
					colID[2] = (letter[j-1][g-1] == ' ')? 0 : 1;
					colID[1] = (letter[j+1][g+1] == ' ')? 0 : 1;
					colID[0] = (letter[j+1][g-1] == ' ')? 0 : 1; 
					colSUM = colID[0] + colID[1]*2 + colID[2]*4 + colID[3]*8;
										
					switch(colSUM) {
						case 0:
							break;
						case 1:
							letter[j][g] = '/';
							break;	
						case 2:
							letter[j][g] = 92;
							break;
						case 2+1:
							letter[j][g] = '^';
							break;
						case 4:
							letter[j][g] = 92;
							break;
						case 4+1:
							letter[j][g] = ')';
							break;	
						case 4+2:
							letter[j][g] = 92;
							break;
						case 4+2+1:
							letter[j][g] = 92;
							break;	
						case 8:
							letter[j][g] = '/';
							break;
						case 8+1:
							letter[j][g] = '/';
							break;	
						case 8+2:
							letter[j][g] = '(';
							break;
						case 8+2+1:
							letter[j][g] = '/';
							break;
						case 8+4:
							letter[j][g] = 'v';
							break;
						case 8+4+1:
							letter[j][g] = '/';
							break;	
						case 8+4+2:
							letter[j][g] = 92;
							break;
						case 8+4+2+1:
							letter[j][g] = 'X';
							break;
					}
				}
				}
			}
		}

		if (!fin.eof()) {
			for (int j = 1; j <=size*5; j++) {
				for (int g = 1; g <=size*5; g++) {
					switch(letter[j][g]) {
						case -1:
							cout<<"J";
							break;
						case -2:
							cout<<"L";
							break;
						case -3:
							cout<<"ㄱ";
							leftwards(1);
							break;
						case -4:
							cout<<"Γ";
							break;
						case -5:
							cout<<' ';
							break;
						default:
							cout<<letter[j][g];
					}
				}
				downwards(1);
				leftwards(size*5);
			}

		upwards(size*5);
		rightwards(size*5+2);
		}

		fin.close();
	}
	downwards(size*5);
	cout<<"\n";
}
	
#endif