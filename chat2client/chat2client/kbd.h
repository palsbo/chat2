#pragma once
#include <conio.h>
#include <stdio.h>
#include <stdlib.h>
#include <iostream>

typedef void(*kbdinp) (char * msg, int len);

class KBD {
private:
	kbdinp kbdInp;
	char input[50] = "";
	int len = 0;
public:
	void onInput(kbdinp _kbdinp) {
		kbdInp = _kbdinp;
	}
	bool loop() {
		if (_kbhit())
		{
			char c = _getch();
			if (c == 0) {
				c = _getch(); // get extended code
			}
			else {
				if ((c >= ' ') && (c <= 'z')) {
					std::cout << c;
					input[len++] = c;
				}
				else if (c == 13) {
					kbdInp(&input[0], len);
					memset(input, 0, sizeof(input));
					if (len == 0) return false;
					len = 0;
				}
				else if (c == 8) {
					len -= 1;
					std::cout << c << " " << c;
				}
			}
		}
		return true;
	}
} kbd;
