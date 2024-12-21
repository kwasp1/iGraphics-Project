#include "iGraphics.h"
#include <windows.h>
#include <mmsystem.h>
#include <stdlib.h>
#include <time.h>

int x = 100, y = 200, r = 60;
/*
	function iDraw() is called again and again by the system.
*/
int click_shuru = 0;
int highscoreEasy = 0;
int highscoreMedium = 0;
int highscoreHard = 0;

void drawHomepage();
void drawEasyPage();
void drawMediumPage();
void drawHardPage();
void drawInstructionPage();
void drawScorePage();
void drawSettingsPage();
void updateScore();
void InstructionClickController();
void scoreClickController();
void settingsClickController();
void easyClickController();
void mediumClickController();
void hardClickController();
void backClickController();
void backClickController2();

int pichabe = 1;
int pipeWidth = 100;
int pipeGap = 60;
int score = 0;
int game_over = 0;
int pause = 0;
int resume = 0;
int homepage = 1;
int startPage = 0;
int InstructionPage = 0;
int scorePage = 0;
int settingsPage = 0;
int easyPage = 0;
int mediumPage = 0;
int hardPage = 0;
int easy = 1;
int medium = 0;
int hard = 0;
int Bird = 1;
int Bird1 = 0;
int Bird2 = 0;
int BirdX = 30, BirdY = 281;
int pipe1X = 700, pipe1Y = 380;
int pipe2X = 900, pipe2Y = 0;
int pipe3X = pipe1X + 320 + rand() % 150, pipe3Y = 380 + rand() % 100;
int pipe4X = pipe2X + 320 + rand() % 150, pipe4Y = 0;
int pipe5X = pipe3X + 320 + rand() % 150, pipe5Y = 380 + rand() % 100;
int pipe6X = pipe4X + 320 + rand() % 150, pipe6Y = 0; 
int music_shuru = 1;

void iDraw()
{
	// place your drawing codes here
	iClear();

	if (homepage == 1)
	{
		drawHomepage();
	}

	else if (InstructionPage == 1)
	{
		drawInstructionPage();
	}
	else if (scorePage == 1)
	{
		drawScorePage();
	}
	else if (settingsPage == 1)
	{
		drawSettingsPage();
	}
	else if (easyPage == 1)
	{
		drawEasyPage();
	}
	else if (mediumPage == 1)
	{
		drawMediumPage();
	}
	else if (hardPage == 1)
	{
		drawHardPage();
	}
}

void iMouseMove(int mx, int my)
{
	printf("x = %d, y= %d\n", mx, my);

}

void iMouse(int button, int state, int mx, int my)
{
	if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN)
	{
		// place your codes here
		printf("x = %d, y= %d\n", mx, my);
		if (homepage == 1 && (mx >= 138 && mx <= 280) && (my >= 83 && my <= 125))
		{
			if (easy == 1)
			{
				easyClickController();
			}
			else if (medium == 1)
			{
				mediumClickController();
			}
			else if (hard == 1)
			{
				hardClickController();
			}
		}
		else if (homepage == 1 && (mx >= 528 && mx <= 674) && (my >= 83 && my <= 125))
		{

			InstructionClickController();
		}
		else if (homepage == 1 && (mx >= 720 && mx <= 870) && (my >= 83 && my <= 125))
		{

			scoreClickController();
		}
		else if (homepage == 1 && (mx >= 330 && mx <= 480) && (my >= 83 && my <= 125))
		{

			settingsClickController();
		}

				else if ((easyPage == 1 || mediumPage == 1 || hardPage == 1) && (mx >= 3 && mx <= 45) && (my >= 485 && my <= 525))
		{

			backClickController();
		}
		
		else if (settingsPage == 1 && (mx >= 476 && mx <= 540) && (my >= 431 && my <= 447))
		{
			Bird = 1;
			Bird1 = 0;
			Bird2 = 0;
		}
		else if (settingsPage == 1 && (mx >= 476 && mx <= 576) && (my >= 395 && my <= 415))
		{
			Bird = 0;
			Bird1 = 1;
			Bird2 = 0;
		}
		else if (settingsPage == 1 && (mx >= 476 && mx <= 553) && (my >= 370 && my <= 380))
		{
			Bird = 0;
			Bird1 = 0;
			Bird2 = 1;
		}
		else if (settingsPage == 1 && (mx >= 756 && mx <= 800) && (my >= 395 && my <= 412))
		{
			easy = 1;
			medium = 0;
			hard = 0;
		}
		else if (settingsPage == 1 && (mx >= 748 && mx <= 828) && (my >= 347 && my <= 362))
		{
			easy = 0;
			medium = 1;
			hard = 0;
		}
		else if (settingsPage == 1 && (mx >= 756 && mx <= 800) && (my >= 296 && my <= 312))
		{
			easy = 0;
			medium = 0;
			hard = 1;
		}
		else if (startPage == 1 && (mx >= 26 && mx <= 66) && (my >= 505 && my <= 550))
		{

			backClickController();
		}
		else if (settingsPage == 1 && (mx >= 26 && mx <= 66) && (my >= 505 && my <= 550))
		{

			backClickController();
		}
		else if (InstructionPage == 1 && (mx >= 26 && mx <= 66) && (my >= 505 && my <= 550))
		{

			backClickController();
		}
		else if (scorePage == 1 && (mx >= 26 && mx <= 66) && (my >= 505 && my <= 550))
		{

			backClickController();
		}
	}
	if (button == GLUT_RIGHT_BUTTON && state == GLUT_DOWN)
	{
		// place your codes here
		x -= 10;
		y -= 10;
	}
}

/*
	function iKeyboard() is called whenever the user hits a key in keyboard.
	key- holds the ASCII value of the key pressed.
	*/
void iKeyboard(unsigned char key)
{
	if (key == 'q')
	{
		exit(0);
	}
	// Restart the game when enter is pressed
	if (game_over && (key == '\r' || key == '\n'))
	{
		BirdX = 100;
		BirdY = 281;
		pipe1X = 700;
		pipe1Y = 320;
		pipe2X = 900;
		pipe2Y = 0;
		pipe3X = 1050, pipe3Y = 380;
		pipe4X = 1250, pipe4Y = 0;
		pipe5X = 1400, pipe5Y = 380;
		pipe6X = 1600, pipe6Y = 0;
		// pipe7X = 1750, pipe7Y = 380;
		score = 0;
		game_over = 0;
	}
	// place your codes for other keys here
}

void iSpecialKeyboard(unsigned char key)
{

	if (key == GLUT_KEY_UP)
	{
		BirdY += 25;
	}
	if (key == GLUT_KEY_DOWN)
	{
		BirdY -= 25;
	}
	else if (key == GLUT_KEY_RIGHT)
	{
		BirdX += 30;
	}
	
}

void drawPipes()
{
	iShowBMP2(pipe1X, pipe1Y, "image\\pipe1.bmp", 0);
	iShowBMP2(pipe2X, pipe2Y, "image\\pipe2.bmp", 0);
	iShowBMP2(pipe3X, pipe3Y, "image\\pipe1.bmp", 0);
	iShowBMP2(pipe4X, pipe4Y, "image\\pipe2.bmp", 0);
	iShowBMP2(pipe5X, pipe5Y, "image\\pipe1.bmp", 0);
	iShowBMP2(pipe6X, pipe6Y, "image\\pipe2.bmp", 0);
}

void drawHomepage()
{

	iSetColor(128, 128, 128);
	iFilledRectangle(0, 0, 1000, 562);
	iShowBMP(0, 0, "image\\Home.bmp");
	iShowBMP2(130, 65, "image\\Button.bmp", 0);
	iShowBMP2(325, 65, "image\\Button.bmp", 0);
	iShowBMP2(520, 65, "image\\Button.bmp", 0);
	iShowBMP2(715, 65, "image\\Button.bmp", 0);

	iSetColor(0, 0, 0);
	iText(190, 100, "Start", GLUT_BITMAP_HELVETICA_18);
	iText(370, 100, "Settings", GLUT_BITMAP_HELVETICA_18);
	iText(550, 100, "Instructions", GLUT_BITMAP_HELVETICA_18);
	iText(770, 100, "Score", GLUT_BITMAP_HELVETICA_18);
	iShowBMP2(705, 440, "image\\credit.bmp", 0);
}

void drawInstructionPage()
{
	iFilledRectangle(0, 0, 1000, 562);
	iShowBMP(0, 0, "image\\instruction.bmp");
	iShowBMP2(20, 500, "image\\back.bmp", 0);

	iSetColor(0, 0, 0);
	iShowBMP2(180, 60, "image\\struct.bmp", 255);

	// iRectangle(240, 210, 500, 300);
	iText(250, 420, "2.Stay in the middle of screen until the first set of pipes", GLUT_BITMAP_HELVETICA_18);
	iText(250, 400, "appears.", GLUT_BITMAP_HELVETICA_18);
	iText(250, 370, "3.Stay in the middle of the pipes. This is the main objective ", GLUT_BITMAP_HELVETICA_18);
	iText(250, 350, "of the game. If you hit a pipe or the ground, the game ends.", GLUT_BITMAP_HELVETICA_18);
	iText(250, 320, "4.Find your rhythm for higher and lower pipes.", GLUT_BITMAP_HELVETICA_18);
	iText(250, 300, "This is important when you need to go higher or drop, or ", GLUT_BITMAP_HELVETICA_18);
	iText(250, 280, "else you will hit a pipe.", GLUT_BITMAP_HELVETICA_18);

	iText(250, 450, "1.Press the start button and then select difficulty.", GLUT_BITMAP_HELVETICA_18);
	
	iShowBMP2(360, 0, "image\\teach.bmp", 255);
}
void drawScorePage()
{
	iFilledRectangle(0, 0, 1000, 562);
	iShowBMP(0, 0, "image\\score.bmp");
	iShowBMP2(20, 500, "image\\back.bmp", 0);
	iShowBMP2(0, 0, "image\\scoreBird.bmp", 255);
	char strEasy[80];
	sprintf(strEasy, "%d", highscoreEasy);
	char strMedium[80];
	sprintf(strMedium, "%d", highscoreMedium);
	char strHard[80];
	sprintf(strHard, "%d", highscoreHard);

	iText(460, 390, "HIGHEST SCOREBOARD", GLUT_BITMAP_HELVETICA_18);
	iShowBMP(370, 230, "image\\table.bmp");
	iText(430, 325, "Easy", GLUT_BITMAP_HELVETICA_18);
	iText(660, 325, strEasy, GLUT_BITMAP_HELVETICA_18);
	iText(425, 285, "Medium", GLUT_BITMAP_HELVETICA_18);
	iText(660, 285, strMedium, GLUT_BITMAP_HELVETICA_18);
	iText(430, 245, "Hard", GLUT_BITMAP_HELVETICA_18);
	iText(660, 245, strHard, GLUT_BITMAP_HELVETICA_18);
}

void drawEasyPage()
{
	iClear();

	// Draw background
	iShowBMP(0, 0, "image\\start.bmp");

	// Draw bird
	if (Bird == 1)
	{
		iShowBMP2(BirdX, BirdY, "image\\Bird.bmp", 255);
	}
	else if (Bird1 == 1)
	{
		iShowBMP2(BirdX, BirdY, "image\\Bird1.bmp", 0);
	}
	else if (Bird2 == 1)
	{
		iShowBMP2(BirdX, BirdY, "image\\Bird2.bmp", 0);
	}
	iShowBMP2(0, 480, "image\\back.bmp", 0);

	drawPipes();

	// Display score
	iSetColor(255, 255, 255);
	iText(10, 540, "Score: ", GLUT_BITMAP_TIMES_ROMAN_24);
	char scoreStr[10];
	sprintf(scoreStr, "%d", score);
	iText(80, 540, scoreStr, GLUT_BITMAP_TIMES_ROMAN_24);

	// Check collision with pipes or ground or ceiling
	if ((BirdY <= 0 || BirdY >= 562 - 60) || ((BirdX + 52 >= pipe1X && BirdX <= pipe1X + 100) && !(BirdY + 32 < pipe1Y || BirdY > pipe1Y + 320)) || ((BirdX + 45 >= pipe2X && BirdX <= pipe2X + 100) && !(BirdY + 50 < pipe2Y || BirdY > pipe2Y + 312)) || ((BirdX + 52 >= pipe3X && BirdX <= pipe3X + 100) && !(BirdY + 32 < pipe3Y || BirdY > pipe3Y + 320)) || (((BirdX + 45 >= pipe4X && BirdX <= pipe4X + 100) && !(BirdY + 50 < pipe4Y || BirdY > pipe4Y + 312))) || (((BirdX + 52 >= pipe5X && BirdX <= pipe5X + 100) && !(BirdY + 32 < pipe5Y || BirdY > pipe5Y + 320))) || (((BirdX + 45 >= pipe6X && BirdX <= pipe6X + 100) && !(BirdY + 50 < pipe6Y || BirdY > pipe6Y + 312))))
	{
		game_over = 1;
		
		iFilledRectangle(0, 0, 1000, 562);
		if (highscoreEasy < score)
		{
			highscoreEasy = score;
			FILE *fp;
			fp = fopen("easyscore.txt", "w");
			fprintf(fp, "%d\n", highscoreEasy);
			fclose(fp);
		}
		iShowBMP(0, 0, "image\\show.bmp");
		iShowBMP2(180, 0, "image\\tiredBird.bmp", 255);
		iText(400, 270, "Score:  ", GLUT_BITMAP_TIMES_ROMAN_24);
		iText(400, 240, "Highscore: ", GLUT_BITMAP_TIMES_ROMAN_24);
		iText(400, 300, "Game Over!", GLUT_BITMAP_TIMES_ROMAN_24);
		iText(400, 210, "Press Enter key to restart", GLUT_BITMAP_TIMES_ROMAN_24);
		iText(470, 270, scoreStr, GLUT_BITMAP_TIMES_ROMAN_24);
		char strEasy[80];
		sprintf(strEasy, "%d", highscoreEasy);
		iText(525, 240, strEasy, GLUT_BITMAP_TIMES_ROMAN_24);
	}

	if (!game_over)
	{
		// Move pipes to the left
		pipe1X -= 3;
		pipe2X -= 3;
		pipe3X -= 3;
		pipe4X -= 3;
		pipe5X -= 3;
		pipe6X -= 3;

		// Check if pipes are off the screen, then reset their position and add new pipes in 100 x-coordinate intervals
		if (pipe1X <= 0)
		{
			pipe1X += 1000;
			srand(time(NULL));
			pipe1Y = 380 + rand() % 100;
		}

		if (pipe2X <= 0)
		{
			pipe2X += 1000;
			pipe2Y = 0;
		}
		if (pipe3X <= 0)
		{
			pipe3X += 1000;
			srand(time(NULL));
			pipe3Y = 380 + rand() % 100;
		}
		if (pipe4X <= 0)
		{
			pipe4X += 1000;
			pipe4Y = 0;
		}
		if (pipe5X <= 0)
		{
			pipe5X += 1000;
			srand(time(NULL));
			pipe5Y = 380 + rand() % 100;
		}
		if (pipe6X <= 0)
		{
			pipe6X += 1000;
			pipe6Y = 0;
		}
		
		updateScore();

		// Bird's gravity
		BirdY -= 2;
	}
}

void drawMediumPage()
{
	iClear();

	// Draw background
	iShowBMP(0, 0, "image\\start.bmp");

	// Draw bird
	if (Bird == 1)
	{
		iShowBMP2(BirdX, BirdY, "image\\Bird.bmp", 255);
	}
	else if (Bird1 == 1)
	{
		iShowBMP2(BirdX, BirdY, "image\\Bird1.bmp", 0);
	}
	else if (Bird2 == 1)
	{
		iShowBMP2(BirdX, BirdY, "image\\Bird2.bmp", 0);
	}
	iShowBMP2(0, 480, "image\\back.bmp", 0);

	drawPipes();

	// Display score
	iSetColor(255, 255, 255);
	iText(10, 540, "Score: ", GLUT_BITMAP_TIMES_ROMAN_24);
	char scoreStr[10];
	sprintf(scoreStr, "%d", score);
	iText(80, 540, scoreStr, GLUT_BITMAP_TIMES_ROMAN_24);

	// Check collision with pipes, ground or ceiling
	if ((BirdY <= 0 || BirdY >= 562 - 60) || ((BirdX + 52 >= pipe1X && BirdX <= pipe1X + 100) && !(BirdY + 32 < pipe1Y || BirdY > pipe1Y + 320)) || ((BirdX + 45 >= pipe2X && BirdX <= pipe2X + 100) && !(BirdY + 50 < pipe2Y || BirdY > pipe2Y + 312)) || ((BirdX + 52 >= pipe3X && BirdX <= pipe3X + 100) && !(BirdY + 32 < pipe3Y || BirdY > pipe3Y + 320)) || (((BirdX + 45 >= pipe4X && BirdX <= pipe4X + 100) && !(BirdY + 50 < pipe4Y || BirdY > pipe4Y + 312))) || (((BirdX + 52 >= pipe5X && BirdX <= pipe5X + 100) && !(BirdY + 32 < pipe5Y || BirdY > pipe5Y + 320))) || (((BirdX + 45 >= pipe6X && BirdX <= pipe6X + 100) && !(BirdY + 50 < pipe6Y || BirdY > pipe6Y + 312))))
	{
		game_over = 1;
		iFilledRectangle(0, 0, 1000, 562);
		if (highscoreMedium < score)
		{
			highscoreMedium = score;
			FILE *fp;
			fp = fopen("mediumscore.txt", "w");
			fprintf(fp, "%d\n", highscoreMedium);
			fclose(fp);
		}
		iShowBMP(0, 0, "image\\show.bmp");
		iShowBMP2(180, 0, "image\\tiredBird.bmp", 255);

		iText(400, 270, "Score:  ", GLUT_BITMAP_TIMES_ROMAN_24);
		iText(400, 240, "Highscore: ", GLUT_BITMAP_TIMES_ROMAN_24);
		iText(400, 300, "Game Over!", GLUT_BITMAP_TIMES_ROMAN_24);
		iText(400, 210, "Press Enter key to restart", GLUT_BITMAP_TIMES_ROMAN_24);
		iText(470, 270, scoreStr, GLUT_BITMAP_TIMES_ROMAN_24);
		char strMedium[80];
		sprintf(strMedium, "%d", highscoreMedium);
		iText(525, 240, strMedium, GLUT_BITMAP_TIMES_ROMAN_24);
	}

	if (!game_over)
	{
		// Move pipes to the left
		pipe1X -= 4;
		pipe2X -= 4;
		pipe3X -= 4;
		pipe4X -= 4;
		pipe5X -= 4;
		pipe6X -= 4;
		/* pipe8X -= 2;
		pipe7X -= 2; */

		// Check if pipes are off the screen, then reset their position and add new pipes in 100 x-coordinate intervals
		if (pipe1X <= 0)
		{
			pipe1X += 1000;
			srand(time(NULL));
			pipe1Y = 380 + rand() % 100;
		}

		if (pipe2X <= 0)
		{
			pipe2X += 1000;
			pipe2Y = 0;
		}
		if (pipe3X <= 0)
		{
			pipe3X += 1000;
			srand(time(NULL));
			pipe3Y = 380 + rand() % 100;
		}
		if (pipe4X <= 0)
		{
			pipe4X += 1000;
			pipe4Y = 0;
		}
		if (pipe5X <= 0)
		{
			pipe5X += 1000;
			srand(time(NULL));
			pipe5Y = 380 + rand() % 100;
		}
		if (pipe6X <= 0)
		{
			pipe6X += 1000;
			pipe6Y = 0;
		}
		updateScore();

		// Bird's gravity
		BirdY -= 3;
	}
}
void drawHardPage()
{
	iClear();

	// Draw background
	iShowBMP(0, 0, "image\\start.bmp");

	// Draw bird
	if (Bird == 1)
	{
		iShowBMP2(BirdX, BirdY, "image\\Bird.bmp", 255);
	}
	else if (Bird1 == 1)
	{
		iShowBMP2(BirdX, BirdY, "image\\Bird1.bmp", 0);
	}
	else if (Bird2 == 1)
	{
		iShowBMP2(BirdX, BirdY, "image\\Bird2.bmp", 0);
	}
	iShowBMP2(0, 480, "image\\back.bmp", 0);

	drawPipes();

	// Display score
	iSetColor(255, 255, 255);
	iText(10, 540, "Score: ", GLUT_BITMAP_TIMES_ROMAN_24);
	char scoreStr[10];
	sprintf(scoreStr, "%d", score);
	iText(80, 540, scoreStr, GLUT_BITMAP_TIMES_ROMAN_24);

	// Check collision with pipes
	if ((BirdY <= 0 || BirdY >= 562 - 60) || ((BirdX + 52 >= pipe1X && BirdX <= pipe1X + 100) && !(BirdY + 32 < pipe1Y || BirdY > pipe1Y + 320)) || ((BirdX + 45 >= pipe2X && BirdX <= pipe2X + 100) && !(BirdY + 50 < pipe2Y || BirdY > pipe2Y + 312)) || ((BirdX + 52 >= pipe3X && BirdX <= pipe3X + 100) && !(BirdY + 32 < pipe3Y || BirdY > pipe3Y + 320)) || (((BirdX + 45 >= pipe4X && BirdX <= pipe4X + 100) && !(BirdY + 50 < pipe4Y || BirdY > pipe4Y + 312))) || (((BirdX + 52 >= pipe5X && BirdX <= pipe5X + 100) && !(BirdY + 32 < pipe5Y || BirdY > pipe5Y + 320))) || (((BirdX + 45 >= pipe6X && BirdX <= pipe6X + 100) && !(BirdY + 50 < pipe6Y || BirdY > pipe6Y + 312))))
	{
		game_over = 1;
		iFilledRectangle(0, 0, 1000, 562);
		if (highscoreHard < score)
		{
			highscoreHard = score;
			FILE *fp;
			fp = fopen("hardscore.txt", "w");
			fprintf(fp, "%d\n", highscoreHard);
			fclose(fp);
		}
		iShowBMP(0, 0, "image\\show.bmp");
		iShowBMP2(180, 0, "image\\tiredBird.bmp", 255);
		iText(400, 270, "Score:  ", GLUT_BITMAP_TIMES_ROMAN_24);
		iText(400, 240, "Highscore: ", GLUT_BITMAP_TIMES_ROMAN_24);
		iText(400, 300, "Game Over!", GLUT_BITMAP_TIMES_ROMAN_24);
		iText(400, 210, "Press Enter key to restart", GLUT_BITMAP_TIMES_ROMAN_24);
		iText(470, 270, scoreStr, GLUT_BITMAP_TIMES_ROMAN_24);
		char strHard[80];
		sprintf(strHard, "%d", highscoreHard);
		iText(525, 240, strHard, GLUT_BITMAP_TIMES_ROMAN_24);
	}

	if (!game_over)
	{
		// Move pipes to the left
		pipe1X -= 5;
		pipe2X -= 5;
		pipe3X -= 5;
		pipe4X -= 5;
		pipe5X -= 5;
		pipe6X -= 5;
		/* pipe8X -= 2;
		pipe7X -= 2; */

		// Check if pipes are off the screen, then reset their position and add new pipes in 100 x-coordinate intervals
		if (pipe1X <= 0)
		{
			pipe1X += 1000;
			srand(time(NULL));
			pipe1Y = 380 + rand() % 100;
		}

		if (pipe2X <= 0)
		{
			pipe2X += 1000;
			pipe2Y = 0;
		}
		if (pipe3X <= 0)
		{
			pipe3X += 1000;
			srand(time(NULL));
			pipe3Y = 380 + rand() % 100;
		}
		if (pipe4X <= 0)
		{
			pipe4X += 1000;
			pipe4Y = 0;
		}
		if (pipe5X <= 0)
		{
			pipe5X += 1000;
			srand(time(NULL));
			pipe5Y = 380 + rand() % 100;
		}
		if (pipe6X <= 0)
		{
			pipe6X += 1000;
			pipe6Y = 0;
		}

		updateScore();

		// Bird's gravity
		BirdY -= 4;
	}
}
void drawSettingsPage()
{
	iFilledRectangle(0, 0, 1000, 562);
	iShowBMP(0, 0, "image\\settings.bmp");
	iShowBMP2(20, 500, "image\\back.bmp", 0);

	iText(450, 460, "Select Bird Color:", GLUT_BITMAP_TIMES_ROMAN_24);
	iText(474, 430, "Yellow", GLUT_BITMAP_TIMES_ROMAN_24);
	iText(474, 400, "Light Blue", GLUT_BITMAP_TIMES_ROMAN_24);
	iText(474, 369, "Orrange", GLUT_BITMAP_TIMES_ROMAN_24);
	iRectangle(452, 430, 15, 15);
	iRectangle(452, 400, 15, 15);
	iRectangle(452, 369, 15, 15);

	iText(450, 330, "Music", GLUT_BITMAP_TIMES_ROMAN_24);
	iText(464, 300, "On", GLUT_BITMAP_TIMES_ROMAN_24);
	iText(464, 269, "Off", GLUT_BITMAP_TIMES_ROMAN_24);
	iCircle(452, 309, 7);
	if (music_shuru == 1)
	{
		iFilledCircle(452, 309, 4);
	}
	else
	{
		iFilledCircle(452, 280, 4);
	}
	iCircle(452, 280, 7);
	if (Bird == 1)
	{
		iShowBMP2(450, 428, "image\\tick.bmp", 0);
	}
	else if (Bird1 == 1)
	{
		iShowBMP2(450, 395, "image\\tick.bmp", 0);
	}
	else if (Bird2 == 1)
	{
		iShowBMP2(450, 365, "image\\tick.bmp", 0);
	}
	iShowBMP2(0, 0, "image\\settingsBird.bmp", 255);

	iText(700, 460, "Select Difficulty Level:", GLUT_BITMAP_TIMES_ROMAN_24);

	iText(755, 395, "Easy", GLUT_BITMAP_TIMES_ROMAN_24);
	iText(745, 345, "Medium", GLUT_BITMAP_TIMES_ROMAN_24);
	iText(755, 295, "Hard", GLUT_BITMAP_TIMES_ROMAN_24);
	iRectangle(730, 390, 20, 20);
	iRectangle(720, 344, 20, 20);
	iRectangle(730, 293, 20, 20);
	if (easy == 1)
	{
		iShowBMP2(730, 388, "image\\tick.bmp", 0);
	}
	if (medium == 1)
	{
		iShowBMP2(720, 340, "image\\tick.bmp", 0);
	}
	if (hard == 1)
	{
		iShowBMP2(730, 290, "image\\tick.bmp", 0);
	}
}
// int pipeX[6] = {pipe1X, pipe2X, pipe3X, pipe4X, pipe5X, pipe6X};
int flag[6] = {0};
void updateScore()
{
	if (flag[0] == 0 && BirdX > pipe1X + 104)
	{
		score++;
		flag[0] = 1;
	}
	else if (flag[0] == 1 && BirdX < pipe1X)
	{
		flag[0] = 0;
	}

	if (flag[1] == 0 && BirdX > pipe2X + 104)
	{
		score++;
		flag[1] = 1;
	}
	else if (flag[1] == 1 && BirdX < pipe2X)
	{
		flag[1] = 0;
	}

	if (flag[2] == 0 && BirdX > pipe3X + 104)
	{
		score++;
		flag[2] = 1;
	}
	else if (flag[2] == 1 && BirdX < pipe3X)
	{
		flag[2] = 0;
	}
	if (flag[3] == 0 && BirdX > pipe4X + 104)
	{
		score++;
		flag[3] = 1;
	}
	else if (flag[3] == 1 && BirdX < pipe4X)
	{
		flag[3] = 0;
	}
	if (flag[4] == 0 && BirdX > pipe5X + 104)
	{
		score++;
		flag[4] = 1;
	}
	else if (flag[4] == 1 && BirdX < pipe5X)
	{
		flag[4] = 0;
	}
	if (flag[5] == 0 && BirdX > pipe6X + 104)
	{
		score++;
		flag[5] = 1;
	}
	else if (flag[5] == 1 && BirdX < pipe6X)
	{
		flag[5] = 0;
	}
}


void InstructionClickController()
{
	homepage = 0;
	startPage = 0;
	InstructionPage = 1;
}
void scoreClickController()
{
	homepage = 0;
	startPage = 0;
	InstructionPage = 0;
	scorePage = 1;
}
void settingsClickController()
{
	homepage = 0;
	startPage = 0;
	InstructionPage = 0;
	scorePage = 0;
	settingsPage = 1;
}
void easyClickController()
{
	homepage = 0;
	startPage = 0;
	InstructionPage = 0;
	scorePage = 0;
	settingsPage = 0;
	easyPage = 1;
}
void mediumClickController()
{
	homepage = 0;
	startPage = 0;
	InstructionPage = 0;
	scorePage = 0;
	settingsPage = 0;
	mediumPage = 1;
}
void hardClickController()
{
	homepage = 0;
	startPage = 0;
	InstructionPage = 0;
	scorePage = 0;
	settingsPage = 0;
	hardPage = 1;
}
void backClickController()
{
	homepage = 1;
	settingsPage = 0;
	InstructionPage = 0;
	scorePage = 0;
}
int main()
{
	// place your own initialization codes here.
	// iSetTimer(5, changepipe);
	// iSetTimer(5000, accelerate);
	srand(time(NULL));
	int pipe2X = 900, pipe2Y = 0;
	srand(time(NULL));
	int pipe3X = pipe1X + 320, pipe3Y = 380 + rand() % 100;
	srand(time(NULL));
	int pipe4X = pipe2X + 320, pipe4Y = 0;
	srand(time(NULL));
	int pipe5X = pipe3X + 320, pipe5Y = 380 + rand() % 100;
	srand(time(NULL));
	int pipe6X = pipe4X + 320, pipe6Y = 0;
	// iSetTimer(1000, print);

	FILE *fp;
	fp = fopen("easyscore.txt", "r");
	fscanf(fp, "%d", &highscoreEasy);
	fclose(fp);
	FILE *fq;
	fq = fopen("mediumscore.txt", "r");
	fscanf(fq, "%d", &highscoreMedium);
	fclose(fq);
	FILE *fr;
	fr = fopen("hardscore.txt", "r");
	fscanf(fr, "%d", &highscoreHard);
	fclose(fr);
	iInitialize(1000, 562, "Flappy Bird Clone");
	return 0;
}