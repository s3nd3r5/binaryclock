#include <bitset>
#include <curses.h>
#include <ctime>
#include <locale.h>
#include <unistd.h>

const wchar_t ON_0 = L'1';
const wchar_t OFF_0 = L'0';

const wchar_t ON_1 = L'\u25C9';
const wchar_t OFF_1 = L'\u25CE';

const wchar_t ON_2 = L'\u25A0';
const wchar_t OFF_2 = L'\u25A1';

wchar_t ON, OFF;

void writeBinary(int time)
{
	std::bitset<6> bin = time;
	for(int i = bin.size()-1; i >= 0; i--)
	{
		printw("%C",bin[i]?ON:OFF);
		if(i!=0) printw(" ");
	}
}

int main(int argc, char *argv[])
{
	if(argc == 2)
	{
		switch(*argv[1])
		{
			case '1':
				ON = ON_1;
				OFF = OFF_1;
				break;
			case '2':
				ON = ON_2;
				OFF = OFF_2;
				break;	
			default:
				ON=ON_0;
				OFF=OFF_0;
				break;
		}
	}
	setlocale(LC_ALL,"");
	initscr();
	curs_set(0);
	tm *tm_struct;
	int prev_sec = -1;
	time_t t;
	do{
		t = time(NULL);
		tm_struct = localtime(&t);
		int hour = tm_struct->tm_hour;
		int minute = tm_struct->tm_min;
		int seconds = tm_struct->tm_sec;
		if(prev_sec != seconds){
			prev_sec = seconds;
			clear();
			writeBinary(hour);
			printw("\n");
			writeBinary(minute);
			printw("\n");
			writeBinary(seconds);
			refresh();
		}
		usleep(50000);
	}while(true);

	endwin();
	return 0;
}
