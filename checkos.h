#ifndef CHECKOS_H
#define CHECKOS_H

#ifdef WIN32
#include <conio.h>

#else
#include <termios.h>
#include <unistd.h>
#include <stdio.h>
using namespace std;

int _getch(void)
{
struct termios oldt,
newt;
int ch;
tcgetattr( STDIN_FILENO, &oldt );
newt = oldt;
newt.c_lflag &= ~( ICANON | ECHO );
tcsetattr( STDIN_FILENO, TCSANOW, &newt );
ch = getchar();
tcsetattr( STDIN_FILENO, TCSANOW, &oldt );
return ch;
}
#endif

#endif