#include "fun.h"

void main();
void init_graph();
void welcome_scr();
void fun_scr();

void main()
{	int welcome_ena=1;	//1 = enable welcome screen

	char
		line_1[] = "Welcome",		//welcome screen messages
		line_2[] = "to",
		line_3[] = "Snakebite";

	/*initialize graphics and fonts*/
	init_graph();

	if(welcome_ena)
		welcome_scr(hi_fore, back_color, line_1, line_2, line_3);

	/*call game function*/
	fun_scr();

	/*clean up*/
	restorecrtmode();
	clrscr();
}