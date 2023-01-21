// colors.cpp
// Name: Color setting library
// Author: Luke Devenney
// Date: 10/12/2021

#include <iostream>
#include <string>

#include "colors.h"

using namespace std;

string translateColorNum(int colorNum) {
	string colorName;
	switch (colorNum) {
		case 0:
			colorName = "black";
			break;
		case 1:
			colorName = "red";
			break;
		case 2:
			colorName = "green";
			break;
		case 3:
			colorName = "yellow";
			break;
		case 4:
			colorName = "blue";
			break;
		case 5:
			colorName = "magenta";
			break;
		case 6:
			colorName = "cyan";
			break;
		case 7:
			colorName = "white";
			break;
		default:
			colorName = "reset";
			break;
	}
	return colorName;
}

string randColor() {
	int colorNum = rand()%8;
	return translateColorNum(colorNum);
}

void setColor(string name, bool background, bool bold) {
	int colorNum = 0;

	if (name == "black") colorNum = 30;
	if (name == "red") colorNum =  31;
	if (name == "green") colorNum = 32;
	if (name == "yellow") colorNum =  33;
	if (name == "blue") colorNum = 34;
	if (name == "magenta") colorNum =  35;
	if (name == "cyan") colorNum = 36;
	if (name == "grey") colorNum = 37;
	if (name == "reset") colorNum =  0;
	if (name == "invert") colorNum = 7;
	
	if (name == "brown") colorNum = 1094;
	if (name == "white") colorNum = 1253;
	if (name == "sand") colorNum = 1221;

	if (background) colorNum += (colorNum<1000)? 10 : 1000;
	if (bold) colorNum += 60;

	if (colorNum < 1000) setColorNum(colorNum);
	else setColor216(colorNum-1000);
}

void setColor216(int colorNum) {
	switch (colorNum) {
		case 94:
			cout<<"\033[38;5;94m";
			break;
		case 130:
			cout<<"\033[38;5;130m";
			break;
		case 221:
			cout<<"\033[38;5;221m";
			break;
		case 248:
                        cout<<"\033[38;5;248m";
                        break;
		case 249:
			cout<<"\033[38;5;249m";
			break;
		case 250:
			cout<<"\033[38;5;250m";
			break;
		case 251:
                        cout<<"\033[38;5;251m";
                        break;
		case 252:
                        cout<<"\033[38;5;252m";
                        break;
		case 253:
                        cout<<"\033[38;5;253m";
                        break;
		case 1094:
			cout<<"\033[48;5;94m";
			break;
		case 1130:
			cout<<"\033[48;5;130m";
			break;
		case 1221:
			cout<<"\033[48;5;221m";
			break;
		case 1248:
                        cout<<"\033[48;5;248m";
                        break;
		case 1249:
			cout<<"\033[48;5;249m";
			break;
		case 1250:
			cout<<"\033[48;5;250m";
			break;
		case 1251:
                        cout<<"\033[48;5;251m";
                        break;
		case 1252:
                        cout<<"\033[48;5;252m";
                        break;
		case 1253:
                        cout<<"\033[48;5;253m";
                        break;
	}
}

void setColorNum(int colorNum) {
	switch (colorNum) {
		case 0:
			cout<<"\033[0m";
			break;
		case 7:
			cout<< "\033[7m";
			break;
		case 30:
			cout<<"\033[30m";
			break;
		case 31:
			cout<<"\033[31m";
			break;
		case 32:
			cout<<"\033[32m";
			break;
		case 33:
			cout<<"\033[33m";
			break;
		case 34:
			cout<<"\033[34m";
			break;
		case 35:
			cout<<"\033[35m";
			break;
		case 36:
			cout<<"\033[36m";
			break;
		case 37:
			cout<<"\033[37m";
			break;
		case 40:
			cout<<"\033[40m";
			break;
		case 41:
			cout<<"\033[41m";
			break;
		case 42:
			cout<<"\033[42m";
			break;
		case 43:
			cout<<"\033[43m";
			break;
		case 44:
			cout<<"\033[44m";
			break;
		case 45:
			cout<<"\033[45m";
			break;
		case 46:
			cout<<"\033[46m";
			break;
		case 47:
			cout<<"\033[47m";
			break;
		case 90:
			cout<<"\033[90m";
			break;
		case 91:
			cout<<"\033[91m";
			break;
		case 92:
			cout<<"\033[92m";
			break;
		case 93:
			cout<<"\033[93m";
			break;
		case 94:
			cout<<"\033[94m";
			break;
		case 95:
			cout<<"\033[95m";
			break;
		case 96:
			cout<<"\033[96m";
			break;
		case 97:
			cout<<"\033[97m";
			break;
		case 100:
			cout<<"\033[100m";
			break;
		case 101:
			cout<<"\033[101m";
			break;
		case 102:
			cout<<"\033[102m";
			break;
		case 103:
			cout<<"\033[103m";
			break;
		case 104:
			cout<<"\033[104m";
			break;
		case 105:
			cout<<"\033[105m";
			break;
		case 106:
			cout<<"\033[106m";
			break;
		case 107:
			cout<<"\033[107m";
			break;
		default:
			cout<<"\033[0m";
			break;
	}
}
