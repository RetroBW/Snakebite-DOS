#include <stdio.h>
#include <stdlib.h>
#include <graphics.h>
#include <conio.h>
#include <string.h>
#include <bios.h>
#include <ctype.h>

#define frame_color LIGHTBLUE
#define fore_color WHITE
#define back_color BLUE
#define hi_back CYAN
#define hi_fore WHITE

void main();
void init();
void welcome_scr();
scr();
void search_scr();
void search();
void list_scr();

void main()
	{
	int welcome_ena=1;

	unsigned int scr_no=0x1;				//initilize screen pointer

	init();

	if(welcome_ena) welcome_scr();			//welcome screen
		else
			{
			rectangle(5,5, 634,474);		//screen border
			setviewport(9,9, 630,470, 0);
			}

	do										//menu/screen generator loop
		{
		scr_no=scr(scr_no, frame_color, fore_color, back_color, hi_fore, hi_back);
		} while(scr_no);

	restorecrtmode();
	clrscr();
	}

/***********************************************************************************************************************
* Initialize graphics driver and graphic fonts.                                                                        *
***********************************************************************************************************************/

void init()
	{
	int graphdriver = DETECT, graphmode, errorcode;

	if(registerbgifont(gothic_font)<0)
		{
		printf("Error loading gothic font");
		exit(1);
		}

	if(registerbgifont(triplex_font)<0)
		{
		printf("Error loading triplex font");
		exit(1);
		}

	if(registerbgifont(small_font)<0)
		{
		printf("Error loading small font");
		exit(1);
		}

	if(registerbgifont(sansserif_font)<0)
		{
		printf("Error loading sanserif font");
		exit(1);
		}

	if(registerbgidriver(EGAVGA_driver)<0)	//init graphics driver
		{
		printf("EGA/VGA graphics monitor required");
		exit(0);
		}

	initgraph(&graphdriver, &graphmode, NULL);
	errorcode=graphresult();
	if(errorcode != grOk)
		{
		printf("Graphics error: %s\n", grapherrormsg(errorcode));
		closegraph();
		exit(1);
		}

	}

/***********************************************************************************************************************
* Generate welcome screen.  The welcome screen may be disabled by resetting the enable in the function main().         *
***********************************************************************************************************************/

void welcome_scr()
	{
	int wel_scr, frame, chr, ptr;
	char msg[80], buffer[80];

	setbkcolor(back_color);
	setcolor(fore_color);

	settextjustify(CENTER_TEXT, CENTER_TEXT);
	settextstyle(TRIPLEX_FONT, HORIZ_DIR, 4);

	rectangle(5,5, 634,474);

	for(frame=0; frame<3; frame++)
		{
		switch(frame)
			{
			case 0:
				setviewport(9,155, 630,204, 0);
				strcpy(msg, "Packaging");
				chr=9;
				break;
			case 1:
				setviewport(9,205, 630,254, 0);
				strcpy(msg, "Knowledge");
				chr=9;
				break;
			case 2:
				setviewport(9,255, 630,305, 0);
				strcpy(msg, "Base");
				chr=4;
				break;
			}

		for(ptr=0; ptr<=chr; ptr++)
			{
			clearviewport();
			strcpy(buffer, "");
			strncat(buffer, msg, ptr);
			outtextxy(310,25, buffer);
			}
		}

	setviewport(9,9, 630,470, 0);

	settextstyle(SMALL_FONT, HORIZ_DIR, 5);
	outtextxy(525,400, "Courtesy of");
	outtextxy(525,415, "Bill West");
	outtextxy(525,430, "10/2/92");

	delay(1500);
	}

