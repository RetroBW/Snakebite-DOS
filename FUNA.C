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
	settextstyle(TRIPLEX_FONT, HORIZ_DIR, 6);

	rectangle(5,5, 634,474);

	for(frame=0; frame<3; frame++)
		{
		switch(frame)
			{
			case 0:
				setviewport(9,155, 630,204, 0);
				strcpy(msg, "Welcome");
				chr=8;
				break;
			case 1:
				setviewport(9,205, 630,254, 0);
				strcpy(msg, "to");
				chr=3;
				break;
			case 2:
				setviewport(9,255, 630,305, 0);
				strcpy(msg, "Snakebite");
				chr=9;
				break;
			}

		for(ptr=0; ptr<=chr; ptr++)
			{
			clearviewport();
			strcpy(buffer, "");
			strncat(buffer, msg, ptr);
			setcolor(DARKGRAY);
			outtextxy(315,20, buffer);
			setcolor(hi_fore);
			outtextxy(310,25, buffer);
			}
		}

	setviewport(9,9, 630,470, 0);

	settextstyle(SMALL_FONT, HORIZ_DIR, 5);
	outtextxy(525,400, "Courtesy of");
	outtextxy(525,415, "Bill West");
	outtextxy(525,430, "10/11/92");

	delay(1500);
	clearviewport();
	}

/***********************************************************************************************************************
* Let's play snakebite!                                                                                                *
***********************************************************************************************************************/

void fun_scr()
	{
	int snake_x[1000], snake_y[1000],		//snake coordinates
		treat_x, treat_y,	           		//object (snake treat) coordinates
		poison_x, poison_y,					//poison object coordinates
		full[80][60],		            	//hazardous object matrix ([x][y])
		key, prev_key,						//last key and previous key pressed
		done=0,								//esc key presses, exit program
		len,								//current snake length
		lives, max_life=3, 					//snake lives left, max lives
		dly,								//delay - controls game speed
		flicker=0,							//flicker "Your Dead!!!"
		cnt,								//loop counter
		init1, init2,						//array init counters
		treats,								//number of treats eaten
		again;								//play again = yes

	char snake_length[80], length[10];

	do
		{
		/*initialize parameters*/
		treat_x=0; treat_y=0;	        //object (snake treat) coordinates
		poison_x=0; poison_y=0;			//poison object coordinates
		treats=0;						//number of treats eaten
		dly=100;						//delay - controls game speed
		key=0x4800;						//last key and previous key pressed

		/*initialize full position registers*/
		for(init1=0; init1<80; init1++)
			{
			for(init2=0; init2<60; init2++)
				{
				if(init1==0 || init1==79 || init2==0 || init2==59)
					full[init1][init2]=1;
				else full[init1][init2]=0;
				}
			}

		/*initialize full sreen*/
		setviewport(0,0, 639,479, 0);
		clearviewport();

		/*initialize border*/
		setcolor(hi_fore);
		rectangle(7,7, 632,472);
		setfillstyle(SOLID_FILL, hi_fore);
		floodfill(1,1, hi_fore);

		for(lives=1; lives<=max_life; lives++)
			{
			/*initialize snake length*/
			len=5;							//current snake length

			/*initialize x and y snake registers*/
			for(init1=1; init1<=1000; init1++)
				{
				snake_x[init1]=0;
				snake_y[init1]=0;
				}

			/*set snake start position*/
			snake_x[1] = 40;
			snake_y[1] = 30;

			/*move snake*/
			do
				{
				/*cover up snake tracks*/
				if(snake_x[len])
					{
					setfillstyle(SOLID_FILL, back_color);
					setcolor(back_color);
					rectangle(snake_x[len]*8,snake_y[len]*8,
						snake_x[len]*8+7,snake_y[len]*8+7);
					floodfill((snake_x[len]*8+3),(snake_y[len]*8+3), back_color);
					full[snake_x[len]][snake_y[len]]=0;
					}

				/*draw new object (snake treat) and poison*/
				if(!treat_x)
					{
					/*define and draw snake treat*/
					do
						{
						srand((unsigned)time(NULL)*9);	//random number
						treat_x=random(77)+1;           //for treat coordinates
						treat_y=random(57)+1;
						}while(full[treat_x][treat_y]);	//coordinates not full
					setcolor(treat_color);
					circle(treat_x*8+4,treat_y*8+4, 3);
					setfillstyle(SOLID_FILL, treat_color);
					floodfill(treat_x*8+4,treat_y*8+4, treat_color);

					/*define and draw poison*/
					for(cnt=0; cnt<2; cnt++)
						{
						do
							{
							poison_x=random(77)+1;
							poison_y=random(57)+1;
							}while(full[poison_x][poison_y] ||
								(treat_x==poison_x && treat_y==poison_y));
						setcolor(poison_color);
						settextstyle(SMALL_FONT, HORIZ_DIR, 6);
						settextjustify(CENTER_TEXT, CENTER_TEXT);
						outtextxy(poison_x*8+4,poison_y*8+2, "*");
						full[poison_x][poison_y]=1;
						}
					}

				/*get next key when pressed*/
				if(bioskey(1))				//if key pressed
					{
					prev_key = key;         //save previous key
					key = bioskey(0);		//read new key
					}

				/*control direction of snake*/
				switch(key)
					{
					case 0x4800:			//up arrow key
						if(prev_key!=0x5000) snake_y[1]=snake_y[1]-1;
						else
							{
							key = 0x5000;
							snake_y[1] = snake_y[1] + 1;
							}
						break;

					case 0x5000:			//down arrow key
						if(prev_key!=0x4800) snake_y[1]=snake_y[1]+1;
						else
							{
							key = 0x4800;
							snake_y[1] = snake_y[1] - 1;
							}
						break;

					case 0x4b00:			//left arrow key
						if(prev_key!=0x4d00) snake_x[1]=snake_x[1]-1;
						else
							{
							key = 0x4d00;
							snake_x[1] = snake_x[1] + 1;
							}
						break;

					case 0x4d00:			//right arrow key
						if(prev_key!=0x4b00) snake_x[1]=snake_x[1]+1;
						else
							{
							key = 0x4b00;
							snake_x[1] = snake_x[1] - 1;
							}
						break;

					case 0x11b:				//esc key
						done=1;
						break;
					}

				/*increase length of snake and speed after meals*/
				if(treat_x==snake_x[1] && treat_y==snake_y[1])
					{
					/*treat sound*/
					sound(2000);
					delay(50);
					nosound();

					/*increase length*/
					len=len+20;

					/*zero treat coordinates*/
					treat_x=0;
					treat_y=0;

					/*increase delay*/
					if(dly>=5) dly=dly-5;

					/*increase number of treats*/
					treats=treats+1;
					}

				/*snake ran into something*/
				if(full[snake_x[1]][snake_y[1]] && !done)
					{
					/*death sound*/
					sound(40);
					delay(250);
					nosound();

					/*has snake used all his lives?*/
					if(lives==max_life)
						{
						/*Display treats eaten*/
						clearviewport();
						setcolor(hi_fore);
						rectangle(8,8, 632,472);
						settextjustify(CENTER_TEXT, CENTER_TEXT);
						settextstyle(TRIPLEX_FONT, HORIZ_DIR, 2);
						strcpy(snake_length, "Treats Eaten = ");
						itoa(treats, length, 10);
						strcat(snake_length, length);
						outtextxy(320,240, snake_length);
						delay(1500);

						/*flicker display "Your Dead!!!" - all lives are gone*/
						clearviewport();
						rectangle(8,8, 632,472);
						settextstyle(TRIPLEX_FONT, HORIZ_DIR, 8);
						for(cnt=0; cnt<30; cnt++)
							{
							if(flicker)
								{
								setcolor(snake_color);
								flicker=0;
								}
							else
								{
								setcolor(poison_color);
								flicker=1;
								}
							outtextxy(320,240, "YOUR DEAD!!!");
							delay(50);
							}
						}

					/*erase snake when he dies - and has more lives*/
					else
						{
						for(cnt=2; cnt<len; cnt++)
							{
							if(snake_x[cnt])
								{
								setfillstyle(SOLID_FILL, back_color);
								setcolor(back_color);
								rectangle(snake_x[cnt]*8,snake_y[cnt]*8,
									snake_x[cnt]*8+7,snake_y[cnt]*8+7);
								floodfill((snake_x[cnt]*8+3),(snake_y[cnt]*8+3),
									back_color);
								full[snake_x[cnt]][snake_y[cnt]]=0;
								}
							}
						}
					break;
					}
				/*advance snake - he's moved to a safe position*/
				else
					{
					setfillstyle(SOLID_FILL, snake_color);
					setcolor(snake_color);
					rectangle(snake_x[1]*8,snake_y[1]*8,
						snake_x[1]*8+7,snake_y[1]*8+7);
					floodfill(snake_x[1]*8+3,snake_y[1]*8+3, snake_color);
					full[snake_x[1]][snake_y[1]]=1;
					}

				/*update remaining length of snake - shift snake segments*/
				for(cnt=len-1; cnt>0; cnt--)
					{
					snake_x[cnt+1]=snake_x[cnt];
					snake_y[cnt+1]=snake_y[cnt];
					}

				/*delay to acheive human speed*/
				delay(dly);
				}while(!done);
			if(done) break;
			}

		/*play again?*/
		if(!done)
			{
			while(kbhit()) getch();					//clear keyboard buffer
			clearviewport();
			setcolor(hi_fore);
			rectangle(8,8, 632,472);
			settextjustify(CENTER_TEXT, CENTER_TEXT);
			settextstyle(TRIPLEX_FONT, HORIZ_DIR, 2);
			outtextxy(320,240, "Would you like to play again?");
			while(bioskey(1) == 0);					//wait for key press
			again = bioskey(0) & 0xff00;			//read key scancode
			}
		}while((again == 0x1500) && (!done));      	//key = Y or y
	}

