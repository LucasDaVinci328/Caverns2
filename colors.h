#ifndef COLORS_DEF
#define COLORS_DEF

#include <string>
#include <iostream>
using namespace std;

void reset() {
	cout<<"\033[0m";
}

class Color {
	public:
		int red = 0;
		int green = 0;
		int blue = 0;
		Color(int r, int g, int b) {
			red = r;
			green = g;
			blue = b;
		}
		void setup(int r, int g, int b) {
			red = r;
			green = g;
			blue = b;
		}
		void foreground() {
			cout<<"\033[38;2;" + to_string(red) + ";" + to_string(green) + ";" + to_string(blue) + "m";
		}
		void background() {
			cout<<"\033[48;2;" + to_string(red) + ";" + to_string(green) + ";" + to_string(blue) + "m";
		}
};

void set_foreground(int red, int green, int blue) {
	cout<<"\033[38;2;" + to_string(red) + ";" + to_string(green) + ";" + to_string(blue) + "m";
}

void set_background(int red, int green, int blue) {
	cout<<"\033[48;2;" + to_string(red) + ";" + to_string(green) + ";" + to_string(blue) + "m";
}


#endif