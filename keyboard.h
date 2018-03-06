#include <conio.h>

using namespace std;

#define KB_UP 72 
#define KB_DOWN 80
#define KB_LEFT 75
#define KB_RIGHT 77
#define KB_ENTER 13
#define UPPER_SHOT 'W'
#define LOWER_SHOT 'S'

short keyboardActions();

short keyboardActions() {
	short KB_code = 0;
	while (1) {
		if (_kbhit()) {
			KB_code = getch();
			if (char(KB_code) == 'w' || char(KB_code) == 's')
				KB_code -= 32;
			
			switch (KB_code) {
			case KB_LEFT:
				break;
			case KB_RIGHT:
				break;
			case KB_UP:
				break;
			case KB_DOWN:
				break;
			case KB_ENTER:
				break;
			case UPPER_SHOT:
				break;
			case LOWER_SHOT:
				break;
			default:
				return -1;
			}
			return KB_code;

		}
	}
}
