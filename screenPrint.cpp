// screenPrint.cpp
// Name: Screen Print
// Author: Luke Devenney
// Date: 10/14/2021

#include <string>
#include <iostream>

#include "constants.h"
#include "colors.h"
#include "box.h"
#include "cavegrowth.h"
#include "screenPrint.h"

using namespace std;

void setscrn(block screen[][WIDTH]) {
	
	for(int y=HEIGHT-1; y>=0; y--) {//character encoder
        	for(int x=0; x<WIDTH; x++) {
			screen[y][x].display = ' ';
			screen[y][x].fore = Color(0, 0, 0);
			int charID[10] = {0, ((y==0) | (x==0))? 1 : screen[y-1][x-1].collision, (y==0)? 1 :screen[y-1][x].collision, ((y==0) | (x==WIDTH-1))? 1 : screen[y-1][x+1].collision, (x==0)? 1 : screen[y][x-1].collision, screen[y][x].collision, (x==WIDTH-1)? 1 : screen[y][x+1].collision, ((y==HEIGHT-1) | (x==0))? 1 : screen[y+1][x-1].collision, (y==HEIGHT-1)? 1 : screen[y+1][x].collision, ((y==HEIGHT-1) | (x==WIDTH-1))? 1 : screen[y+1][x+1].collision};
				
			int charIDSum = (1*charID[2])+(2*charID[4])+(4*charID[5])+(8*charID[6])+(16*charID[8]);			
			char charIDsquare = ' ';
			string oldBack = screen[y][x].displayBack;
			screen[y][x].displayBack = "black";
			switch(charIDSum) {
				case 16+8+4+2:
				case 16+8+4+2+1:
				case 8+4+2:
				case 8+4+2+1:
					screen[y][x].displayBack = oldBack;
					screen[y][x].display = ' ';
					if ((rand()%3==0) & (screen[y][x].oreCharacter!=' ')) {
						screen[y][x].displayFore = screen[y][x].oreColor;
						charIDsquare = screen[y][x].oreCharacter;
					}
					break;
				case 16:
				case 16+8:
       		                case 16+2:
                                case 2+8+16:
					if ((charID[7]==1) & (charID[9]==1)) {
						charIDsquare = -5;
					} else {
						charIDsquare = ' ';
					}
					break;
				case 1+2+8+16:
					charIDsquare = -6;
					break;
				case 8:
				case 2:
				case 0:
				case 4:
				case 8+2:
					charIDsquare = ' ';
					break;
				case 8+4:
					charIDsquare = '<';
					break;
				case 4+2:
					charIDsquare = '>';
					break;
				case 16+4+1:
					charIDsquare = -1;
					break;
				case 1+2:
				case 1+8:
					if ((charID[1]==0) || (charID[3]==0)) {
					        screen[y][x].back = Color(0, 0, 0);
						charIDsquare = ' ';  
					} else {
						charIDsquare = '_';
					}
					break;	
				case 7:
				case 28:
					charIDsquare = 92;
					break;
				case 13:
				case 22:
					charIDsquare = '/';
					break;
				case 1:
				case 1+16:
				case 1+8+16:
                        	case 1+2+16:
                                case 1+2+8:
					if (charID[1]==1 && charID[3]==1) {
						charIDsquare = '_';
					} else {
						screen[y][x].back = Color(0, 0, 0);
						charIDsquare = ' ';
					}
					break;
				case 1+2+4+16:
				case 1+4+8+16:
					charIDsquare = '|';
					break;
				case 4+16:
					charIDsquare = 'V';
					break;
				case 5:
					charIDsquare = -2;
					break;
				default:
					charIDsquare = '&';
					break;
			}		
			screen[y][x].display = charIDsquare;
		}
	}

}

void printscrn(block screen[][WIDTH]) {
	system("clear");
	cout<<"\n";
	upwards(1);
	box(WIDTH+2, HEIGHT+2);
	cout<<"\n";
	upwards(HEIGHT+1);
	rightwards(1);
	
		
	for (int y = HEIGHT-1; y>=0; y--) {
		for (int x = 0; x < WIDTH; x++) {
			reset();
			screen[y][x].fore.foreground();
			screen[y][x].back.background();
			if (screen[y][x].display>0) {
				char c = screen[y][x].display;
				cout<< c;
			} else if (screen[y][x].display==0) {
				cout<<"Y";
			} else {
				switch(screen[y][x].display) {
					case -1:
						cout<< "॥";
						break;
					case -2:
						cout<< "Λ";
						break;
					case -3:
						cout<< "♙";
						break;
					case -4:
						cout<< "-";
						break;
					case -5:
						cout<< "‾";
						break;
					case -6:
						cout<< "\033[4m";
						cout<< "‾";
						break;
					default:
						cout<< ")";
						break;
				}
			}
		}
		downwards(1);
		leftwards(WIDTH);
	}
	reset();
	cout<<"\n";

}			
