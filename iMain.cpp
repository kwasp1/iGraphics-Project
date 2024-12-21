#include "iGraphics.h"
#include <windows.h>
#include "game_data.h"

#define screenheight 450*2
#define screenwidth 850*2

struct center{
	int pic_x, pic_y;
	int playerx;
	int playery;
	int playeridx_x;
	int playeridx_y;
	int prev_x, prev_y;
	int next_x, next_y;
	int next_move;
	int pacmanbuff;
};

struct chase{
	int pac_x;
	int pac_y;
	int pacidx_x;
	int pacidx_y;
	int reached;
};

center pacman;
center redghost;
center blueghost;
center pinkghost;
center orangeghost;
chase target_red;
chase target_blue;
chase target_pink;
chase target_orange;

int map[90][170];
int len = 0;
char str1[100];
bool newscore = true;

struct hscore
{
	char name[30];
	int Score = 0;
};
hscore High_score[5];

bool faster = 0;
bool chomp=0;
bool start = 1;
int rndm=0;
int menuidx=0;
int health = 3;
int points=0;
int recover=0;
int powerstatus=0;
bool loading=0;
int tem=0;
int timerID1, timerID2, timerID3, timerID4, timerID5, timerID6, timerID7, timerID8, timerID9, timerID10, timerID11;
int elapsedTime1 = 0, elapsedTime2 = 0; // Time elapsed in milliseconds
int timerActive1 = 0, timerActive2 = 0;
int a,b,c,d,e,f,g,h,i,j;
int timerStartTime = 0; // To store when the timer started
int timerRunning = 0;   // Flag to indicate if the timer is running
int gridx=34*5, gridy=18*5;
int idle_idx=0;
int menu=0;
int red_idx=0, blue_idx=0, orange_idx=0, pink_idx=0;
int red_frightened_idx=0, blue_frightened_idx=0, pink_frightened_idx=0, orange_frightened_idx=0; 
int red_recovering_idx=0, blue_recovering_idx=0, pink_recovering_idx=0, orange_recovering_idx=0;
int state = 0, red_state =0, prev_red_state=0, blue_state=0, prev_blue_state, orange_state=0, prev_orange_state,pink_state=0, prev_pink_state;
int redable=0, blueable=0, pinkable=0, orangeable=0;
int redres=0, blueres=0, pinkres=0, orangeres=0;
char* mainmenugif;
char* loadingscrn;
char* pacman_walk;
char* red_walk;
char* orange_walk;
char* blue_walk;
char* pink_walk;
 bool dead = 0;
bool pause=0;
struct menu{
	bool startgame;
	bool control;
	bool options;
	bool sound;
	bool aboutgame;
	bool leaderboard;
}pacman_menu;

char menugif[151][200];
void loadingsgif(){
for(i=0; i<151; i++){
		sprintf(menugif[i], "loadingscreen//677f4673097e44abaf006f31cc7eb4a2TxXTvXvVnwINxITO-%d.bmp", i);
	}
}
char mainmenu[1][100] = {"pacman//mainmenu.bmp"};

char sound[2][100] = {"pacman\\soundoff.bmp", "pacman\\soundon.bmp"};
char loading_screen[44][100] = {"pacman\\frame1.bmp","pacman\\frame1.bmp","pacman\\frame1.bmp","pacman\\frame1.bmp","pacman\\frame1.bmp","pacman\\frame1.bmp","pacman\\frame2.bmp","pacman\\frame2.bmp","pacman\\frame2.bmp","pacman\\frame2.bmp","pacman\\frame2.bmp","pacman\\frame2.bmp","pacman\\frame3.bmp","pacman\\frame3.bmp","pacman\\frame3.bmp","pacman\\frame4.bmp","pacman\\frame4.bmp","pacman\\frame4.bmp","pacman\\frame5.bmp","pacman\\frame5.bmp","pacman\\frame5.bmp","pacman\\frame6.bmp","pacman\\frame6.bmp","pacman\\frame6.bmp",
								"pacman\\frame7.bmp","pacman\\frame7.bmp","pacman\\frame7.bmp","pacman\\frame8.bmp","pacman\\frame8.bmp","pacman\\frame8.bmp","pacman\\frame9.bmp","pacman\\frame9.bmp","pacman\\frame9.bmp","pacman\\frame10.bmp","pacman\\frame10.bmp","pacman\\frame10.bmp","pacman\\frame10.bmp","pacman\\frame11.bmp","pacman\\frame11.bmp","pacman\\frame11.bmp","pacman\\frame11.bmp","pacman\\frame12.bmp","pacman\\frame12.bmp", "pacman\\frame12.bmp"};

char pacman_right[3][100] = {"spritedemo\\death0.bmp","spritedemo\\tile000.bmp", "spritedemo\\tile001.bmp"};
char pacman_left[3][100] = {"spritedemo\\death0.bmp","spritedemo\\tile002.bmp", "spritedemo\\tile003.bmp"};
char pacman_up[3][100] = {"spritedemo\\death0.bmp","spritedemo\\tile004.bmp", "spritedemo\\tile005.bmp"};
char pacman_down[3][100] = {"spritedemo\\death0.bmp","spritedemo\\tile006.bmp", "spritedemo\\tile007.bmp"};
char red_right[4][100]= {"spritedemo\\red1.bmp", "spritedemo\\red1.bmp", "spritedemo\\red2.bmp", "spritedemo\\red2.bmp"};
char red_left[4][100]= {"spritedemo\\red3.bmp", "spritedemo\\red3.bmp", "spritedemo\\red4.bmp", "spritedemo\\red4.bmp"};
char red_up[4][100]= {"spritedemo\\red5.bmp", "spritedemo\\red5.bmp", "spritedemo\\red6.bmp", "spritedemo\\red6.bmp"};
char red_down[4][100]= {"spritedemo\\red7.bmp", "spritedemo\\red7.bmp", "spritedemo\\red8.bmp", "spritedemo\\red8.bmp"};
char blue_right[4][100]= {"spritedemo\\blue1.bmp", "spritedemo\\blue1.bmp", "spritedemo\\blue2.bmp", "spritedemo\\blue2.bmp"};
char blue_left[4][100]= {"spritedemo\\blue3.bmp", "spritedemo\\blue3.bmp", "spritedemo\\blue4.bmp", "spritedemo\\blue4.bmp"};
char blue_up[4][100]= {"spritedemo\\blue5.bmp", "spritedemo\\blue5.bmp", "spritedemo\\blue6.bmp", "spritedemo\\blue6.bmp"};
char blue_down[4][100]= {"spritedemo\\blue7.bmp", "spritedemo\\blue7.bmp", "spritedemo\\blue8.bmp", "spritedemo\\blue8.bmp"};
char pink_right[4][100]= {"spritedemo\\pink1.bmp", "spritedemo\\pink1.bmp", "spritedemo\\pink2.bmp", "spritedemo\\pink2.bmp"};
char pink_left[4][100]= {"spritedemo\\pink3.bmp", "spritedemo\\pink3.bmp", "spritedemo\\pink4.bmp", "spritedemo\\pink4.bmp"};
char pink_up[4][100]= {"spritedemo\\pink5.bmp", "spritedemo\\pink5.bmp", "spritedemo\\pink6.bmp", "spritedemo\\pink6.bmp"};
char pink_down[4][100]= {"spritedemo\\pink7.bmp", "spritedemo\\pink7.bmp", "spritedemo\\pink8.bmp", "spritedemo\\pink8.bmp"};
char orange_right[4][100]= {"spritedemo\\orange1.bmp", "spritedemo\\orange1.bmp", "spritedemo\\orange2.bmp", "spritedemo\\orange2.bmp"};
char orange_left[4][100]= {"spritedemo\\orange3.bmp", "spritedemo\\orange3.bmp", "spritedemo\\orange4.bmp", "spritedemo\\orange4.bmp"};
char orange_up[4][100]= {"spritedemo\\orange5.bmp", "spritedemo\\orange5.bmp", "spritedemo\\orange6.bmp", "spritedemo\\orange6.bmp"};
char orange_down[4][100]= {"spritedemo\\orange7.bmp", "spritedemo\\orange7.bmp", "spritedemo\\orange8.bmp", "spritedemo\\orange8.bmp"};
char red_frightened[4][100]= {"spritedemo\\frightened1.bmp", "spritedemo\\frightened1.bmp", "spritedemo\\frightened2.bmp", "spritedemo\\frightened2.bmp"};
char pink_frightened[4][100]= {"spritedemo\\frightened1.bmp", "spritedemo\\frightened1.bmp","spritedemo\\frightened2.bmp", "spritedemo\\frightened2.bmp"};
char orange_frightened[4][100]= {"spritedemo\\frightened1.bmp", "spritedemo\\frightened1.bmp", "spritedemo\\frightened2.bmp", "spritedemo\\frightened2.bmp"};
char blue_frightened[4][100]= {"spritedemo\\frightened1.bmp", "spritedemo\\frightened1.bmp", "spritedemo\\frightened2.bmp", "spritedemo\\frightened2.bmp"};
char red_recovering[8][100]= {"spritedemo\\frightened1.bmp", "spritedemo\\frightened3.bmp", "spritedemo\\frightened6.bmp", "spritedemo\\frightened8.bmp" , "spritedemo\\frightened2.bmp", "spritedemo\\frightened4.bmp", "spritedemo\\frightened5.bmp", "spritedemo\\frightened7.bmp"};
char pink_recovering[8][100]= {"spritedemo\\frightened1.bmp", "spritedemo\\frightened3.bmp", "spritedemo\\frightened6.bmp", "spritedemo\\frightened8.bmp" , "spritedemo\\frightened2.bmp", "spritedemo\\frightened4.bmp", "spritedemo\\frightened5.bmp", "spritedemo\\frightened7.bmp"};
char orange_recovering[8][100]= {"spritedemo\\frightened1.bmp", "spritedemo\\frightened3.bmp", "spritedemo\\frightened6.bmp", "spritedemo\\frightened8.bmp" , "spritedemo\\frightened2.bmp", "spritedemo\\frightened4.bmp", "spritedemo\\frightened5.bmp", "spritedemo\\frightened7.bmp"};
char blue_recovering[8][100]= {"spritedemo\\frightened1.bmp", "spritedemo\\frightened3.bmp", "spritedemo\\frightened6.bmp", "spritedemo\\frightened8.bmp" , "spritedemo\\frightened2.bmp", "spritedemo\\frightened4.bmp", "spritedemo\\frightened5.bmp", "spritedemo\\frightened7.bmp"};
char pacmandying[20][100]= {"spritedemo\\death0.bmp", "spritedemo\\death0.bmp","spritedemo\\death1.bmp","spritedemo\\death1.bmp", "spritedemo\\death2.bmp","spritedemo\\death2.bmp",
							 "spritedemo\\death3.bmp","spritedemo\\death3.bmp", "spritedemo\\death4.bmp","spritedemo\\death4.bmp", "spritedemo\\death5.bmp", "spritedemo\\death5.bmp",
							  "spritedemo\\death6.bmp",  "spritedemo\\death6.bmp", "spritedemo\\death7.bmp","spritedemo\\death7.bmp",
							   "spritedemo\\death8.bmp", "spritedemo\\death8.bmp", "spritedemo\\death9.bmp", "spritedemo\\death9.bmp"};

int x = 50, y = 50, r = 50, Gup=0, Gdown=0, Gleft=0, Gright=0;
int dots=0;
int negpoints=423;

void iDraw();
void iMouseMove(int mx, int my);
void iMouse(int button, int state, int mx, int my);
void iKeyboard(unsigned char key);
void iSpecialKeyboard(unsigned char key);
void update_pacman_ghosts();
void pacmanmove();
void ghostwalk();
void redwalk();
void redmove();
void bluewalk();
void bluemove();
void pinkwalk();
void pinkmove();
void orangewalk();
void orangemove();
void death();
void scatter();
void pacmanbuffed();
void disable();
void again();





void readScore()
{
	FILE *fp;
	fp = fopen("Score.txt", "r");

	char show_name[5][30], show_score[5][5];
	for (int i = 0; i < 5; i++)
	{
		fscanf(fp, "%s %d\n", High_score[i].name, &High_score[i].Score);
	}

	fclose(fp);

	for (int i = 0; i < 5; i++)
	{
		sprintf(show_name[i], "%s", High_score[i].name);
		sprintf(show_score[i], "%d", High_score[i].Score);
		iSetColor(0,0,0);
		iText(732, 550 - 50 * i, show_name[i], GLUT_BITMAP_HELVETICA_18);
		iText(932, 550 - 50 * i, show_score[i], GLUT_BITMAP_HELVETICA_18);
	}
}

void newHighscore()
{
	newscore = true;
	FILE *fp;
	fp = fopen("Score.txt", "r");
	for (int i = 0; i < 5; i++)
	{
		fscanf(fp, "%s %d\n", High_score[i].name, &High_score[i].Score);
	}
	fclose(fp);

	if (newscore) {
	//printf("%d ",points);
        if (points > High_score[4].Score) {
			//printf("score = %d",points);
            High_score[4].Score = points;
            strcpy(High_score[4].name, str1);

            for (int j = 0; j < 5; j++) {
                for (int k = 4; k > j; k--) {
                    if (High_score[k].Score > High_score[k - 1].Score) {
                        int tempScore = High_score[k - 1].Score;
                        High_score[k - 1].Score = High_score[k].Score;
                        High_score[k].Score = tempScore;

                        char tempName[30];
                        strcpy(tempName, High_score[k - 1].name);
                        strcpy(High_score[k - 1].name, High_score[k].name);
                        strcpy(High_score[k].name, tempName);
                    }
                }
            }

            fp = fopen("Score.txt", "w");
            for (int i = 0; i < 5; i++) {
                fprintf(fp, "%s %d\n", High_score[i].name, High_score[i].Score);
            }
            fclose(fp);

            newscore = false;
		}
	}
}

void takeInput(unsigned key)
{
	if (dots==0&&pacman_menu.startgame==1)
	{
		if (key == '\r')
		{
			newHighscore();
		}
		else if (key == '\b')
		{
			if (len > 0)
				len--;
			str1[len] = '\0';
		}
		else
		{
			if (len < 29)
			{
				str1[len] = key;
				len++;
				str1[len] = '\0';
			}
		}
	}
}

void show_char()
{
	iSetColor(255,255,255);
	iText(860, 115, str1, GLUT_BITMAP_TIMES_ROMAN_24);
}


void mazeupdate(){
	for(i=0; i<18*5; i++){
			for(j=0; j<34*5; j++){
				map[i][j] = maze[i][j];
			}
		}
	points = 0;
}

void updatedots(){
		for(i=0; i<18*5; i++){
		for(j=0; j<34*5; j++){
			if(map[i][j]==8||map[i][j]==7)
				dots++;
		}
	}
}

void musicplay(){
	//printf("hpl");
	if(pacman_menu.sound==0){
		PlaySound(0,0,0);
	}
	if(pacman_menu.sound==1){
		if(menu==0){
			PlaySound("music//pacman_intermission.wav", NULL, SND_LOOP | SND_ASYNC);
		}
		if(pacman_menu.startgame ==1 && loading==0 && chomp==0){
			PlaySound("music//pacman_beginning.wav", NULL, SND_LOOP | SND_ASYNC);
		
		}
		if(pacman_menu.startgame ==1 && loading==0 && chomp==1 && health>=0 && (blueghost.pacmanbuff==0 && redghost.pacmanbuff==0 && pinkghost.pacmanbuff==0 && orangeghost.pacmanbuff==0 && faster==0)){
			PlaySound("music//pacman_chomp.wav", NULL, SND_LOOP | SND_ASYNC);
		}
		if(pacman_menu.startgame ==1 && loading==0 && chomp==1 && health>=0 && (blueghost.pacmanbuff==1 || redghost.pacmanbuff==1 || pinkghost.pacmanbuff==1 || orangeghost.pacmanbuff==1)){
			PlaySound("music//pacman_frightened.wav", NULL, SND_LOOP | SND_ASYNC);
		}
		if(pacman_menu.startgame ==1 && loading==0 && chomp==1 && health>=0 && (blueghost.pacmanbuff==0 && redghost.pacmanbuff==0 && pinkghost.pacmanbuff==0 && orangeghost.pacmanbuff==0 && faster==1)){
			PlaySound("music//pacman_faster.wav", NULL, SND_LOOP | SND_ASYNC);
		}
	}

}
void update_pacman_ghosts(){

		mainmenugif = menugif[menuidx];
		menuidx = (menuidx+1)%151;

	switch (state)
	{
	case 1:
		pacman_walk = pacman_right[idle_idx];
		idle_idx = (idle_idx+1)%3;
		break;
	case 2:
		pacman_walk = pacman_left[idle_idx];
		idle_idx = (idle_idx+1)%3;
		break;
	case 3:
		pacman_walk = pacman_up[idle_idx];
		idle_idx = (idle_idx+1)%3;
		break;
	case 4:
		pacman_walk = pacman_down[idle_idx];
		idle_idx = (idle_idx+1)%3;
		break;
	case 5:
		if(idle_idx<20){		
		pacman_walk = pacmandying[idle_idx];
		idle_idx = (idle_idx+1);
		}
		if(idle_idx==20){
			
			idle_idx=0;
			Sleep(1000);
			again();
			musicplay();
			if(health<0){
			dots=0;
			}
		}
		break;
	default:
		idle_idx = 0;
		pacman_walk = pacmandying[0];
		break;
	}

	if(redghost.pacmanbuff==0){
		if(faster==0){
		iResumeTimer(timerID3);
		iPauseTimer(timerID6);
		}
		if(faster==1){
			//printf("happened");
		iPauseTimer(timerID3);
		iResumeTimer(timerID6);
		}
		iPauseTimer(timerID4);
			switch(red_state)
		{
		case 1:
			red_walk = red_right[red_idx];
			red_idx = (red_idx+1)%4;
			break;
		case 2:
			red_walk = red_left[red_idx];
			red_idx = (red_idx+1)%4;
			break;
		case 3:
			red_walk = red_up[red_idx];
			red_idx = (red_idx+1)%4;
			break;
		case 4:
			red_walk = red_down[red_idx];
			red_idx = (red_idx+1)%4;
			break;
		default:
			red_walk = red_right[red_idx];
			red_idx = (red_idx+1)%4;
			break;
		}
	}

	if(pinkghost.pacmanbuff==0){
		if(faster==0){
		iResumeTimer(timerID3);
		iPauseTimer(timerID6);
		}
		if(faster==1){
		iResumeTimer(timerID6);
		iPauseTimer(timerID3);

		}
		iPauseTimer(timerID4);
			switch(pink_state)
		{
		case 1:
			pink_walk = pink_right[pink_idx];
			pink_idx = (pink_idx+1)%4;
			break;
		case 2:
			pink_walk = pink_left[pink_idx];
			pink_idx = (pink_idx+1)%4;
			break;
		case 3:
			pink_walk = pink_up[pink_idx];
			pink_idx = (pink_idx+1)%4;
			break;
		case 4:
			pink_walk = pink_down[pink_idx];
			pink_idx = (pink_idx+1)%4;
			break;
		default:
			pink_walk = pink_right[pink_idx];
			pink_idx = (pink_idx+1)%4;
			break;
		}
	}

	if(orangeghost.pacmanbuff==0){
		if(faster==0){
		iResumeTimer(timerID3);
		iPauseTimer(timerID6);

		}
		if(faster==1){
		iPauseTimer(timerID3);
		iResumeTimer(timerID6);
		}
		iPauseTimer(timerID4);

			switch(orange_state)
		{
		case 1:
			orange_walk = orange_right[orange_idx];
			orange_idx = (orange_idx+1)%4;
			break;
		case 2:
			orange_walk = orange_left[orange_idx];
			orange_idx = (orange_idx+1)%4;
			break;
		case 3:
			orange_walk = orange_up[orange_idx];
			orange_idx = (orange_idx+1)%4;
			break;
		case 4:
			orange_walk = orange_down[orange_idx];
			orange_idx = (orange_idx+1)%4;
			break;
		default:
			orange_walk = orange_right[orange_idx];
			orange_idx = (orange_idx+1)%4;
			break;
		}
	}

	if(blueghost.pacmanbuff==0){
		if(faster==0){
		iResumeTimer(timerID3);
		iPauseTimer(timerID6);
		}
		if(faster==1){
		iResumeTimer(timerID6);
		iPauseTimer(timerID3);
		}
		iPauseTimer(timerID4);

			switch(blue_state)
		{
		case 1:
			blue_walk = blue_right[blue_idx];
			blue_idx = (blue_idx+1)%4;
			break;
		case 2:
			blue_walk = blue_left[blue_idx];
			blue_idx = (blue_idx+1)%4;
			break;
		case 3:
			blue_walk = blue_up[blue_idx];
			blue_idx = (blue_idx+1)%4;
			break;
		case 4:
			blue_walk = blue_down[blue_idx];
			blue_idx = (blue_idx+1)%4;
			break;
		default:
			blue_walk = blue_right[blue_idx];
			blue_idx = (blue_idx+1)%4;
			break;
		}
	}

	if(redghost.pacmanbuff==1){
		iResumeTimer(timerID4);
		iPauseTimer(timerID3);
		iPauseTimer(timerID6);

		if(!recover){
			switch(red_state)
		{
		case 1:
			red_walk = red_frightened[red_frightened_idx];
			red_frightened_idx = (red_frightened_idx+1)%4;
			break;
		case 2:
			red_walk = red_frightened[red_frightened_idx];
			red_frightened_idx = (red_frightened_idx+1)%4;
			break;
		case 3:
			red_walk = red_frightened[red_frightened_idx];
			red_frightened_idx = (red_frightened_idx+1)%4;
			break;
		case 4:
			red_walk = red_frightened[red_frightened_idx];
			red_frightened_idx = (red_frightened_idx+1)%4;
			break;
		default:
			red_walk = red_frightened[red_frightened_idx];
			red_frightened_idx = (red_frightened_idx+1)%4;
			break;
		}
		}
		else if(recover){
			switch(red_state)
		{
		case 1:
			red_walk = red_recovering[red_recovering_idx];
			red_recovering_idx = (red_recovering_idx+1)%8;
			break;
		case 2:
			red_walk = red_recovering[red_recovering_idx];
			red_recovering_idx = (red_recovering_idx+1)%8;
			break;
		case 3:
			red_walk = red_recovering[red_recovering_idx];
			red_recovering_idx = (red_recovering_idx+1)%8;
			break;
		case 4:
			red_walk = red_recovering[red_recovering_idx];
			red_recovering_idx = (red_recovering_idx+1)%8;
			break;
		default:
			red_walk = red_recovering[red_recovering_idx];
			red_recovering_idx = (red_recovering_idx+1)%8;
			break;
		}
	}
	}

	if(pinkghost.pacmanbuff==1){
		iResumeTimer(timerID4);
		iPauseTimer(timerID3);
		iPauseTimer(timerID6);

		if(!recover){
			switch(pink_state)
		{
		case 1:
			pink_walk = pink_frightened[pink_frightened_idx];
			pink_frightened_idx = (pink_frightened_idx+1)%4;
			break;
		case 2:
			pink_walk = pink_frightened[pink_frightened_idx];
			pink_frightened_idx = (pink_frightened_idx+1)%4;
			break;
		case 3:
			pink_walk = pink_frightened[pink_frightened_idx];
			pink_frightened_idx = (pink_frightened_idx+1)%4;
			break;
		case 4:
			pink_walk = pink_frightened[pink_frightened_idx];
			pink_frightened_idx = (pink_frightened_idx+1)%4;
			break;
		default:
			pink_walk = pink_frightened[pink_frightened_idx];
			pink_frightened_idx = (pink_frightened_idx+1)%4;
			break;
		}
		}
		else if(recover){
			switch(pink_state)
		{
		case 1:
			pink_walk = pink_recovering[pink_recovering_idx];
			pink_recovering_idx = (pink_recovering_idx+1)%8;
			break;
		case 2:
			pink_walk = pink_recovering[pink_recovering_idx];
			pink_recovering_idx = (pink_recovering_idx+1)%8;
			break;
		case 3:
			pink_walk = pink_recovering[pink_recovering_idx];
			pink_recovering_idx = (pink_recovering_idx+1)%8;
			break;
		case 4:
			pink_walk = pink_recovering[pink_recovering_idx];
			pink_recovering_idx = (pink_recovering_idx+1)%8;
			break;
		default:
			pink_walk = pink_recovering[pink_recovering_idx];
			pink_recovering_idx = (pink_recovering_idx+1)%8;
			break;
		}
		}
	}

	if(orangeghost.pacmanbuff==1){
		iResumeTimer(timerID4);
		iPauseTimer(timerID3);
		iPauseTimer(timerID6);

		if(!recover){
			switch(orange_state)
		{
		case 1:
			orange_walk = orange_frightened[orange_frightened_idx];
			orange_frightened_idx = (orange_frightened_idx+1)%4;
			break;
		case 2:
			orange_walk = orange_frightened[orange_frightened_idx];
			orange_frightened_idx = (orange_frightened_idx+1)%4;
			break;
		case 3:
			orange_walk = orange_frightened[orange_frightened_idx];
			orange_frightened_idx = (orange_frightened_idx+1)%4;
			break;
		case 4:
			orange_walk = orange_frightened[orange_frightened_idx];
			orange_frightened_idx = (orange_frightened_idx+1)%4;
			break;
		default:
			orange_walk = orange_frightened[orange_frightened_idx];
			orange_frightened_idx = (orange_frightened_idx+1)%4;
			break;
		}
		}
		if(recover){
			switch(orange_state)
		{
		case 1:
			orange_walk = orange_recovering[orange_recovering_idx];
			orange_recovering_idx = (orange_recovering_idx+1)%8;
			break;
		case 2:
			orange_walk = orange_recovering[orange_recovering_idx];
			orange_recovering_idx = (orange_recovering_idx+1)%8;
			break;
		case 3:
			orange_walk = orange_recovering[orange_recovering_idx];
			orange_recovering_idx = (orange_recovering_idx+1)%8;
			break;
		case 4:
			orange_walk = orange_recovering[orange_recovering_idx];
			orange_recovering_idx = (orange_recovering_idx+1)%8;
			break;
		default:
			orange_walk = orange_recovering[orange_recovering_idx];
			orange_recovering_idx = (orange_recovering_idx+1)%8;
			break;
		}
		}
	}

	if(blueghost.pacmanbuff==1){
		iResumeTimer(timerID4);
		iPauseTimer(timerID3);
		iPauseTimer(timerID6);
		if(!recover){
			switch(blue_state)
		{
		case 1:
			blue_walk = blue_frightened[blue_frightened_idx];
			blue_frightened_idx = (blue_frightened_idx+1)%4;
			break;
		case 2:
			blue_walk = blue_frightened[blue_frightened_idx];
			blue_frightened_idx = (blue_frightened_idx+1)%4;
			break;
		case 3:
			blue_walk = blue_frightened[blue_frightened_idx];
			blue_frightened_idx = (blue_frightened_idx+1)%4;
			break;
		case 4:
			blue_walk = blue_frightened[blue_frightened_idx];
			blue_frightened_idx = (blue_frightened_idx+1)%4;
			break;
		default:
			blue_walk = blue_frightened[blue_frightened_idx];
			blue_frightened_idx = (blue_frightened_idx+1)%4;
			break;
		}
		}
		if(recover){
			switch(blue_state)
		{
		case 1:
			blue_walk = blue_recovering[blue_recovering_idx];
			blue_recovering_idx = (blue_recovering_idx+1)%8;
			break;
		case 2:
			blue_walk = blue_recovering[blue_recovering_idx];
			blue_recovering_idx = (blue_recovering_idx+1)%8;
			break;
		case 3:
			blue_walk = blue_recovering[blue_recovering_idx];
			blue_recovering_idx = (blue_recovering_idx+1)%8;
			break;
		case 4:
			blue_walk = blue_recovering[blue_recovering_idx];
			blue_recovering_idx = (blue_recovering_idx+1)%8;
			break;
		default:
			blue_walk = blue_recovering[blue_recovering_idx];
			blue_recovering_idx = (blue_recovering_idx+1)%8;
			break;
		}
		}
	}
}

void animation(){
			mainmenugif = menugif[menuidx];
			menuidx = (menuidx+1)%151;
}

void iDraw() {
	iClear();
	
	if(menu==0 && pacman_menu.startgame==0){
			iShowBMP(0, 0, "pacman\\mainmenu.bmp");
			iShowBMP2(670, 315, mainmenugif, 0);
	}
	if(pacman_menu.aboutgame==1){
			iShowBMP(0,0, "pacman\\aboutgame.bmp");
	}
	if(pacman_menu.control==1){
			iShowBMP(0,0, "pacman\\instructions.bmp");
	}
	if(pacman_menu.leaderboard==1){
			iShowBMP(0,0, "pacman\\leaderboard.bmp");
		
				readScore();
	}
	if(pacman_menu.startgame==1){
		if(menu==1){
			again();
		}
		iLine(720,450,720,400);
		iLine(720,350,720,300);
		iLine(980,500,980,550);
		iLine(980,600,980,650);
	for(j=0, y=0; j<gridy; j++, y=y+10){
		for(i=0, x=0; i<gridx; i++, x=x+10){
			iSetColor(33, 33, 222);
			if(map[j][i] == 1){
				iFilledRectangle(x,y, 10, 10);
			}
			if(map[j][i] == 2){
				iRectangle(x,y, 10, 10);
			}
			if(dots){
			if(map[j][i] == 7 || map[j][i] == 8){
				//dots++;
				iSetColor(255, 255, 0);
				iPoint(x,y,2);
			}
			if(map[j][i] == 6){
				//dots++;
				iSetColor(255, 255, 0);
				iPoint(x,y,7);
			}
			}
		}
	}
	//printf("%d\n", dots);
	if(dots){
	iShowBMP2(redghost.pic_x, redghost.pic_y, red_walk, 0);
	iShowBMP2(blueghost.pic_x, blueghost.pic_y, blue_walk, 0);
	iShowBMP2(pinkghost.pic_x, pinkghost.pic_y, pink_walk, 0);
	iShowBMP2(orangeghost.pic_x, orangeghost.pic_y, orange_walk, 0);
	iShowBMP2(pacman.pic_x, pacman.pic_y, pacman_walk, 0);
	if (timerRunning) {
		
        int currentTime = glutGet(GLUT_ELAPSED_TIME);
        int elapsed = (currentTime - timerStartTime) / 1000; 

        if (elapsed < 1) {
			state = 0;
        } else {
			
			state = 5;
            timerRunning = 0;
			idle_idx = 0;
        }
		}
		char scoreText[20];
		sprintf(scoreText, "SCORE: %d", points);
		iSetColor(255, 255, 0);
		iText(10, 20, scoreText, GLUT_BITMAP_TIMES_ROMAN_24);
		switch (health)
		{
		case 3:
			iShowBMP2(1550, 1, "spritedemo\\tile001.bmp", 0);
		case 2:	
			iShowBMP2(1600, 1, "spritedemo\\tile001.bmp", 0);
		case 1:
			iShowBMP2(1650, 1, "spritedemo\\tile001.bmp", 0);
			break;
		case 0:
			break;
		}

		
		}
		if(dots==0&&pacman_menu.startgame==1){
			PlaySound(0,0,0);
			iShowBMP2(508,203, "spritedemo\\endscreen.bmp", 0);
			char scoreText[20];
			if(health>=0){
				printf("%d", health);
				points += health * 500;
				printf("%d", points);
				points += 1000;
				health=-1;
			}
			sprintf(scoreText, "SCORE: %d", points);
			iSetColor(255, 255, 0);
			iText(787, 20, scoreText, GLUT_BITMAP_TIMES_ROMAN_24);

			iSetColor(255, 255, 255);
			iText(10, 20, "Press 'ENTER' to put your score and to go to mainmenu.", GLUT_BITMAP_TIMES_ROMAN_24);
			iText(770, 115, "NAME: ", GLUT_BITMAP_TIMES_ROMAN_24);
			show_char();
		}
		if(pause){
		iShowBMP(0,0, "pacman\\pausedimage.bmp");
		//printf("paused");
		}
	}

	if(pacman_menu.sound==1){
		iShowBMP2(1620,840, sound[1], 0);
	}
	if(pacman_menu.sound==0){
		iShowBMP2(1620,840, sound[0], 0);
	}
	if(loading==1){
		iShowBMP(0,0, loadingscrn);
	}
}

void iMouseMove(int mx, int my) {
	printf("x = %d, y= %d\n",mx,my);
}

void iMouse(int button, int state, int mx, int my) {
	if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN) {
		
		if(pacman_menu.startgame==0){
		if(mx>700&&mx<975){
			if(my>330&&my<375){
				if(pacman_menu.sound==1){
				PlaySound(0,0,0);
				PlaySound("music//pacman_extra.wav", NULL, SND_LOOP | SND_ASYNC);
				}
				pacman_menu.startgame=1;
				menu=1;
				iResumeTimer(timerID5);
				iResumeTimer(timerID8);
				iResumeTimer(timerID10);
				iPauseTimer(timerID3);
				iPauseTimer(timerID6);
				loading = 1;
				a=1;
			}
		}
		if(mx>730&&mx<940){
			if(my>265&&my<315){
				pacman_menu.control=1;
			}
		}

		if(mx>680&&mx<1000){
			if(my>155&&my<200){
				pacman_menu.aboutgame=1;
			}
		}

		if(mx>665 && mx <1000){
				if((my>210 && my<250)){
					pacman_menu.leaderboard=1;
				}
			}


		if(pacman_menu.control==1 || pacman_menu.aboutgame==1 || pacman_menu.leaderboard==1){
			if(mx>25&&mx<125){
				if(my>770&& my<845){
					pacman_menu.control=0;
					pacman_menu.aboutgame=0;
					pacman_menu.leaderboard=0;
				}
			}
		}
		}
			
		


		if(mx>1620&&mx<1695){
			if(my>830&&my<895){			
				if(pacman_menu.sound==1){
		PlaySound(0,0,0);
		pacman_menu.sound=0;
		
	}
	else{
		pacman_menu.sound=1;
		if(menu==0){
		PlaySound("music//pacman_intermission.wav", NULL, SND_LOOP | SND_ASYNC);
			}
			}
				musicplay();
		}
		}
	}
		
	
	if (button == GLUT_RIGHT_BUTTON && state == GLUT_DOWN) {
		
	}
	
}


void iKeyboard(unsigned char key) {
	if((pacman_menu.startgame==1 && dots!=0)||menu==0){
	if (key == 'q') {
		exit(0);
	}
	}
	if(pacman_menu.startgame==1 && dots!=0){
		if (key == 'o' && pause==1){
			musicplay();
			iResumeTimer(timerID5);
			iResumeTimer(timerID8);
			iResumeTimer(timerID10);
			if(faster==1){
			iPauseTimer(timerID6);
			}
			else if(faster==0){
			iResumeTimer(timerID3);
			}
			pause = 0;
		}
		if (key == 'p' && pause==0){
			pause = 1;	
				PlaySound(0,0,0);
				iPauseTimer(timerID5);
				iPauseTimer(timerID8);
				iPauseTimer(timerID10);
				iPauseTimer(timerID3);
				iPauseTimer(timerID6);

		}
		if (key == 'x' && pause==1){
			if(pause==1||dots==0){
				iResumeTimer(timerID5);
				iPauseTimer(timerID8);
				iPauseTimer(timerID10);
				iPauseTimer(timerID3);
				iPauseTimer(timerID6);
				pacman_menu.startgame=0;
				redable=0;
				blueable=0;
				pinkable=0;
				orangeable=0;
				menu = 0;
				pause = 0;
				musicplay();
			}
			}
		
	}
	if(pacman_menu.startgame==1 && dots==0){
		takeInput(key);
		if(key == '\r'){
			pacman_menu.startgame=0;
				menu=0;
				pause = 0;
				musicplay();
		}
	}

}

void iSpecialKeyboard(unsigned char key) {

	if (key == GLUT_KEY_END) {
		exit(0);
	}
	if(dead==0)
	{
	if (key == GLUT_KEY_UP) {
		iClear();
		if(map[(pacman.playery+10)/10][(pacman.playerx)/10]==5||map[(pacman.playery+10)/10][(pacman.playerx)/10]==7||map[(pacman.playery+10)/10][(pacman.playerx)/10]==8||map[(pacman.playery+10)/10][(pacman.playerx)/10]==4||map[(pacman.playery+10)/10][(pacman.playerx)/10]==3||map[(pacman.playery+10)/10][(pacman.playerx)/10]==6){
		state = 3;
		pacman.next_move = 3;
		}
		else
		{
		pacman.next_move = 3;
		}
		if(dots!=0 && pacman_menu.startgame==1){
		if(chomp==0){
			chomp=1;
			musicplay();
		}
		}
	}

	if (key == GLUT_KEY_LEFT) {
		iClear();
		if(map[(pacman.playery)/10][(pacman.playerx-10)/10]==5||map[(pacman.playery)/10][(pacman.playerx-10)/10]==7||map[(pacman.playery)/10][(pacman.playerx-10)/10]==8||map[(pacman.playery)/10][(pacman.playerx-10)/10]==4||map[(pacman.playery)/10][(pacman.playerx-10)/10]==3||map[(pacman.playery)/10][(pacman.playerx-10)/10]==6){
		state = 2;
		pacman.next_move = 2;
		}
		else
		{
		pacman.next_move = 2;
		}
		if(dots!=0 && pacman_menu.startgame==1){
		if(chomp==0){
			chomp=1;
			musicplay();
		}
		}
	}

	if (key == GLUT_KEY_RIGHT) {
		iClear();
		if(map[(pacman.playery)/10][(pacman.playerx+10)/10]==5||map[(pacman.playery)/10][(pacman.playerx+10)/10]==7||map[(pacman.playery)/10][(pacman.playerx+10)/10]==8||map[(pacman.playery)/10][(pacman.playerx+10)/10]==4||map[(pacman.playery)/10][(pacman.playerx+10)/10]==6){
		state = 1;
		pacman.next_move = 1;
		}
		else
		{
		pacman.next_move = 1;
		}
		if(dots!=0 && pacman_menu.startgame==1){
		if(chomp==0){
			chomp=1;
			musicplay();
		}
		}
	}

	if (key == GLUT_KEY_DOWN) {
		iClear();
		if(map[(pacman.playery-10)/10][(pacman.playerx)/10]==5||map[(pacman.playery-10)/10][(pacman.playerx)/10]==7||map[(pacman.playery-10)/10][(pacman.playerx)/10]==8||map[(pacman.playery-10)/10][(pacman.playerx)/10]==4||map[(pacman.playery-10)/10][(pacman.playerx)/10]==3||map[(pacman.playery-10)/10][(pacman.playerx)/10]==6){
		state = 4;
		pacman.next_move = 4;
		}
		else{
		pacman.next_move = 4;
		}
		if(dots!=0 && pacman_menu.startgame==1){
		if(chomp==0){
			chomp=1;
			musicplay();
		}
		}
	}
	}

}

void clearstate(){
	//pacman.next_move=state;
	if(pinkable!=0 && tem==0 && redghost.pacmanbuff==0&&pinkghost.pacmanbuff==0&&orangeghost.pacmanbuff==0&&blueghost.pacmanbuff==0){
			if (!timerActive2) { 
				elapsedTime2 = 0; 
				timerActive2 = 1;    
				tem = 1;
				iResumeTimer(timerID2); 
				//printf("Timer started. Waiting 25 seconds...\n");
			}
		}
}

void pacmanmove(){
	if(state==1){	
		if(map[(pacman.playery)/10][(pacman.playerx+10)/10]==5||map[(pacman.playery)/10][(pacman.playerx+10)/10]==7||map[(pacman.playery)/10][(pacman.playerx+10)/10]==8||map[(pacman.playery)/10][(pacman.playerx+10)/10]==4||map[(pacman.playery)/10][(pacman.playerx+10)/10]==6){
		pacman.pic_x += 10;
		if(map[(pacman.playery)/10][(pacman.playerx+10)/10]==8){
	 			points+=10;
				dots--;
				map[(pacman.playery)/10][(pacman.playerx+10)/10]=5;
		}
		if(map[(pacman.playery)/10][(pacman.playerx+10)/10]==7){
	 			points+=10;
				dots--;
				map[(pacman.playery)/10][(pacman.playerx+10)/10]=4;
		}
		if(map[(pacman.playery)/10][(pacman.playerx+10)/10]==6){
			map[(pacman.playery)/10][(pacman.playerx+10)/10]=4;
			if(powerstatus==0||powerstatus==1){
			redghost.pacmanbuff=1;
			pinkghost.pacmanbuff=1;
			orangeghost.pacmanbuff=1;
			blueghost.pacmanbuff=1;
			powerstatus=1;
			}	
			musicplay();
			if(powerstatus==1){
				recover=0;
			}
			disable();
			timerActive1 = 0;  
			if (!timerActive1) { 
            elapsedTime1 = 0;     
            timerActive1 = 1;     
            iResumeTimer(timerID1); 
			}
		}
		pacman.playeridx_y=(pacman.playery)/10;
		pacman.playeridx_x=(pacman.playerx+10)/10;
		pacman.next_x=pacman.playerx+10;
		pacman.next_y=pacman.playery;
		}
	}

	if(state==2){
		if(map[(pacman.playery)/10][(pacman.playerx-10)/10]==5||map[(pacman.playery)/10][(pacman.playerx-10)/10]==7||map[(pacman.playery)/10][(pacman.playerx-10)/10]==8||map[(pacman.playery)/10][(pacman.playerx-10)/10]==4||map[(pacman.playery)/10][(pacman.playerx-10)/10]==3||map[(pacman.playery)/10][(pacman.playerx-10)/10]==6){
		pacman.pic_x -= 10;
		if(map[(pacman.playery)/10][(pacman.playerx-10)/10]==8){
	 			points+=10;
				dots--;

			map[(pacman.playery)/10][(pacman.playerx-10)/10]=5;
		}
		if(map[(pacman.playery)/10][(pacman.playerx-10)/10]==7){
	 			points+=10;
				dots--;

			map[(pacman.playery)/10][(pacman.playerx-10)/10]=4;
	 	}
		if(map[(pacman.playery)/10][(pacman.playerx-10)/10]==6){
			map[(pacman.playery)/10][(pacman.playerx-10)/10]=4;
			if(powerstatus==0||powerstatus==1){
			redghost.pacmanbuff=1;
			pinkghost.pacmanbuff=1;
			orangeghost.pacmanbuff=1;
			blueghost.pacmanbuff=1;
			powerstatus=1;
			}
			musicplay();
			if(powerstatus==1){
				recover=0;
			}
			disable();
			timerActive1 = 0;  
			if (!timerActive1) { 
            elapsedTime1 = 0;
            timerActive1 = 1;   
            iResumeTimer(timerID1);
			}
		}
		pacman.playeridx_y=(pacman.playery)/10;
		pacman.playeridx_x=(pacman.playerx-10)/10;
		pacman.next_x=pacman.playerx-10;
		pacman.next_y=pacman.playery;
		}
	}

	if(state==3){
		if(map[(pacman.playery+10)/10][(pacman.playerx)/10]==5||map[(pacman.playery+10)/10][(pacman.playerx)/10]==7||map[(pacman.playery+10)/10][(pacman.playerx)/10]==8||map[(pacman.playery+10)/10][(pacman.playerx)/10]==4||map[(pacman.playery+10)/10][(pacman.playerx)/10]==6){
		pacman.pic_y += 10;
		if(map[(pacman.playery+10)/10][(pacman.playerx)/10]==8){
	 			points+=10;
				dots--;
				map[(pacman.playery+10)/10][(pacman.playerx)/10]=5;
	 	}
		if(map[(pacman.playery+10)/10][(pacman.playerx)/10]==7){
	 			points+=10;
				dots--;
				map[(pacman.playery+10)/10][(pacman.playerx)/10]=4;
		}
		if(map[(pacman.playery+10)/10][(pacman.playerx)/10]==6){
			map[(pacman.playery+10)/10][(pacman.playerx)/10]=4;
			if(powerstatus==0||powerstatus==1){
			redghost.pacmanbuff=1;
			pinkghost.pacmanbuff=1;
			orangeghost.pacmanbuff=1;
			blueghost.pacmanbuff=1;
			powerstatus=1;
			}
			musicplay();
			if(powerstatus==1){
				recover=0;
			}
			disable();
			timerActive1 = 0; 
			if(!timerActive1) { // Only start if not already active
            elapsedTime1 = 0;     // Reset elapsed time
            timerActive1 = 1;     // Activate the timer
            iResumeTimer(timerID1); // Resume the timer
			}
		}
		pacman.playeridx_y=(pacman.playery+10)/10;
		pacman.playeridx_x=(pacman.playerx)/10;
		pacman.next_x=pacman.playerx;
		pacman.next_y=pacman.playery+10;
		}
	}

	if(state==4){
		if(map[(pacman.playery-10)/10][(pacman.playerx)/10]==5||map[(pacman.playery-10)/10][(pacman.playerx)/10]==7||map[(pacman.playery-10)/10][(pacman.playerx)/10]==8||map[(pacman.playery-10)/10][(pacman.playerx)/10]==4||map[(pacman.playery-10)/10][(pacman.playerx)/10]==6){
		pacman.pic_y -= 10;
		if(map[(pacman.playery-10)/10][(pacman.playerx)/10]==8){
	 				points+=10;
					dots--;

				map[(pacman.playery-10)/10][(pacman.playerx)/10]=5;
		}
		if(map[(pacman.playery-10)/10][(pacman.playerx)/10]==7){
	 				points+=10;
					dots--;

				map[(pacman.playery-10)/10][(pacman.playerx)/10]=4;
		}
		if(map[(pacman.playery-10)/10][(pacman.playerx)/10]==6){
			map[(pacman.playery-10)/10][(pacman.playerx)/10]=4;
			if(powerstatus==0||powerstatus==1){
			redghost.pacmanbuff=1;
			pinkghost.pacmanbuff=1;
			orangeghost.pacmanbuff=1;
			blueghost.pacmanbuff=1;
			powerstatus=1;
			}
			musicplay();
			if(powerstatus==1){
				recover=0;
			}
			disable();
			timerActive1 = 0;
			if (!timerActive1) {
            elapsedTime1 = 0;    
            timerActive1 = 1;     
            iResumeTimer(timerID1); 
			}
		}
		pacman.playeridx_y=(pacman.playery-10)/10;
		pacman.playeridx_x=(pacman.playerx)/10;
		pacman.next_x=pacman.playerx;
		pacman.next_y=pacman.playery-10;
		}
	}

	pacman.playerx = pacman.pic_x + 25;
	pacman.playery = pacman.pic_y + 25;
	redghost.playerx = redghost.pic_x + 25;
	redghost.playery = redghost.pic_y + 25;
	pacman.prev_x=pacman.playerx;
	pacman.prev_y=pacman.playery;
		
	
	switch (pacman.next_move)
	{
	case 1:
		if(map[(pacman.playery)/10][(pacman.playerx+10)/10]==5||map[(pacman.playery)/10][(pacman.playerx+10)/10]==7||map[(pacman.playery)/10][(pacman.playerx+10)/10]==8||map[(pacman.playery)/10][(pacman.playerx+10)/10]==4){
		state = 1;
		}
		break;
	case 2:
		if(map[(pacman.playery)/10][(pacman.playerx-10)/10]==5||map[(pacman.playery)/10][(pacman.playerx-10)/10]==7||map[(pacman.playery)/10][(pacman.playerx-10)/10]==8||map[(pacman.playery)/10][(pacman.playerx-10)/10]==4||map[(pacman.playery)/10][(pacman.playerx-10)/10]==3){
		state = 2;
		}
		break;
	case 3:
		if(map[(pacman.playery+10)/10][(pacman.playerx)/10]==5||map[(pacman.playery+10)/10][(pacman.playerx)/10]==7||map[(pacman.playery+10)/10][(pacman.playerx)/10]==8||map[(pacman.playery+10)/10][(pacman.playerx)/10]==4){
		state = 3;
		}
		break;
	case 4:
		if(map[(pacman.playery-10)/10][(pacman.playerx)/10]==5||map[(pacman.playery-10)/10][(pacman.playerx)/10]==7||map[(pacman.playery-10)/10][(pacman.playerx)/10]==8||map[(pacman.playery-10)/10][(pacman.playerx)/10]==4){
		state = 4;
		}
		break;
	}
	
	if(pacman.pic_x<0&&pacman.pic_y==450){
		pacman.pic_x=1660;
		pacman.pic_y=450;
	}
	if(pacman.pic_x>1660&&pacman.pic_y==450){
		pacman.pic_x=0;
		pacman.pic_y=450;
	}
	if(pacman.pic_x==830&&pacman.pic_y<60){
		pacman.pic_x=830;
		pacman.pic_y=860;
	}
	if(pacman.pic_x==830&&pacman.pic_y>860){
		pacman.pic_x=830;
		pacman.pic_y=60;
	}
}

void redwalk(){
if(dead==0){
	if(redable==0||redable==9){
		if(target_red.reached==0){
		target_red.pac_x=1350+25;
		target_red.pac_y=200+25;
		target_red.reached=1;
		}
		else if((redghost.pic_x==1350&&redghost.pic_y==200&&target_red.reached==1)){
		target_red.pac_x=1600+25;
		target_red.pac_y=100+25;
		target_red.reached=2;
		}
		else if((redghost.pic_x==1600&&redghost.pic_y==100&&target_red.reached==2)){
		redable=1;
		target_red.reached=0;
	//	printf("red chasing you\n");
		}
	}
	else{
	target_red.pac_x=pacman.prev_x;
	target_red.pac_y=pacman.prev_y;
	}
	redghost.playeridx_x=redghost.playerx/10;
	redghost.playeridx_y=redghost.playery/10;
	if(map[redghost.playeridx_y][redghost.playeridx_x]==7||(map[redghost.playeridx_y][redghost.playeridx_x]==4)||(map[redghost.playeridx_y][redghost.playeridx_x]==6)){
	target_red.pacidx_x=target_red.pac_x/10;
	target_red.pacidx_y=target_red.pac_y/10;
	}


	if(state!=0){
	if((map[(redghost.playery)/10][(redghost.playerx)/10]==7)||(map[(redghost.playery)/10][(redghost.playerx)/10]==4)||(map[redghost.playeridx_y][redghost.playeridx_x]==6)){
		if(target_red.pacidx_x<redghost.playeridx_x){
			if(target_red.pacidx_y<redghost.playeridx_y){
				if(((map[(redghost.playery-10)/10][redghost.playerx/10]==5)||(map[(redghost.playery-10)/10][(redghost.playerx)/10]==7)||(map[(redghost.playery-10)/10][(redghost.playerx)/10]==4)||(map[(redghost.playery-10)/10][(redghost.playerx)/10]==8)||(map[(redghost.playery-10)/10][(redghost.playerx)/10]==6))&&(prev_red_state!=3)){
				red_state = 4;
				prev_red_state = red_state;
				}
				else if(((map[redghost.playery/10][(redghost.playerx-10)/10]==5)||(map[redghost.playery/10][(redghost.playerx-10)/10]==7)||(map[redghost.playery/10][(redghost.playerx-10)/10]==4)||(map[redghost.playery/10][(redghost.playerx-10)/10]==8)|(map[redghost.playery/10][(redghost.playerx-10)/10]==6))&&(prev_red_state!=1)){
				red_state = 2;
				prev_red_state = red_state;
				}
				else if(((map[redghost.playery/10][(redghost.playerx+10)/10]==5)||(map[redghost.playery/10][(redghost.playerx+10)/10]==7)||(map[redghost.playery/10][(redghost.playerx+10)/10]==4)||(map[redghost.playery/10][(redghost.playerx+10)/10]==8)||(map[redghost.playery/10][(redghost.playerx+10)/10]==6))&&(prev_red_state!=2)){
				red_state = 1;
				prev_red_state = red_state;
				}
				else if(((map[(redghost.playery+10)/10][redghost.playerx/10]==5)||(map[(redghost.playery+10)/10][(redghost.playerx)/10]==7)||(map[(redghost.playery+10)/10][redghost.playerx/10]==4)||(map[(redghost.playery+10)/10][(redghost.playerx)/10]==8)||(map[(redghost.playery+10)/10][(redghost.playerx)/10]==6))&&(prev_red_state!=4)){
				red_state = 3;
				prev_red_state = red_state;
				}
			}
			else if(target_red.pacidx_y>redghost.playeridx_y){
				if(((map[(redghost.playery+10)/10][redghost.playerx/10]==5)||(map[(redghost.playery+10)/10][(redghost.playerx)/10]==7)||(map[(redghost.playery+10)/10][redghost.playerx/10]==4)||(map[(redghost.playery+10)/10][(redghost.playerx)/10]==8)||(map[(redghost.playery+10)/10][(redghost.playerx)/10]==6))&&(prev_red_state!=4)){
				red_state = 3;
				prev_red_state = red_state;
				}
				else if(((map[redghost.playery/10][(redghost.playerx-10)/10]==5)||(map[redghost.playery/10][(redghost.playerx-10)/10]==7)||(map[redghost.playery/10][(redghost.playerx-10)/10]==4)||(map[redghost.playery/10][(redghost.playerx-10)/10]==8)||(map[redghost.playery/10][(redghost.playerx-10)/10]==6))&&(prev_red_state!=1)){
				red_state = 2;
				prev_red_state = red_state;
				}
				else if(((map[redghost.playery/10][(redghost.playerx+10)/10]==5)||(map[redghost.playery/10][(redghost.playerx+10)/10]==7)||(map[redghost.playery/10][(redghost.playerx+10)/10]==4)||(map[redghost.playery/10][(redghost.playerx+10)/10]==8)|(map[redghost.playery/10][(redghost.playerx+10)/10]==6))&&(prev_red_state!=2)){
				red_state = 1;
				prev_red_state = red_state;
			 	}
				else if(((map[(redghost.playery-10)/10][redghost.playerx/10]==5)||(map[(redghost.playery-10)/10][(redghost.playerx)/10]==7)||(map[(redghost.playery-10)/10][(redghost.playerx)/10]==4)||(map[(redghost.playery-10)/10][(redghost.playerx)/10]==8)||(map[(redghost.playery-10)/10][(redghost.playerx)/10]==6))&&(prev_red_state!=3)){
				red_state = 4;
				prev_red_state = red_state;
				}
			}
			else if(target_red.pacidx_y==redghost.playeridx_y){
				if(((map[redghost.playery/10][(redghost.playerx-10)/10]==5)||(map[redghost.playery/10][(redghost.playerx-10)/10]==7)||(map[redghost.playery/10][(redghost.playerx-10)/10]==4)||(map[redghost.playery/10][(redghost.playerx-10)/10]==8)||(map[redghost.playery/10][(redghost.playerx-10)/10]==6))&&(prev_red_state!=1)){
				red_state = 2;
				prev_red_state = red_state;
				}
				else if(((map[(redghost.playery-10)/10][redghost.playerx/10]==5)||(map[(redghost.playery-10)/10][(redghost.playerx)/10]==7)||(map[(redghost.playery-10)/10][(redghost.playerx)/10]==4)||(map[(redghost.playery-10)/10][(redghost.playerx)/10]==8)||(map[(redghost.playery-10)/10][(redghost.playerx)/10]==6))&&(prev_red_state!=3)){
				red_state = 4;
				prev_red_state = red_state;
				}
				else if(((map[(redghost.playery+10)/10][redghost.playerx/10]==5)||(map[(redghost.playery+10)/10][(redghost.playerx)/10]==7)||(map[(redghost.playery+10)/10][redghost.playerx/10]==4)||(map[(redghost.playery+10)/10][(redghost.playerx)/10]==8)||(map[(redghost.playery+10)/10][(redghost.playerx)/10]==6))&&(prev_red_state!=4)){
				red_state = 3;
				prev_red_state = red_state;
				}
				else if(((map[redghost.playery/10][(redghost.playerx+10)/10]==5)||(map[redghost.playery/10][(redghost.playerx+10)/10]==7)||(map[redghost.playery/10][(redghost.playerx+10)/10]==4)||(map[redghost.playery/10][(redghost.playerx+10)/10]==8)||(map[redghost.playery/10][(redghost.playerx+10)/10]==6))&&(prev_red_state!=2)){
				red_state = 1;
				prev_red_state = red_state;
				}
			}
		}

		if(target_red.pacidx_x>redghost.playeridx_x){
			if(target_red.pacidx_y<redghost.playeridx_y){
				if(((map[redghost.playery/10][(redghost.playerx+10)/10]==5)||(map[redghost.playery/10][(redghost.playerx+10)/10]==7)||(map[redghost.playery/10][(redghost.playerx+10)/10]==4)||(map[redghost.playery/10][(redghost.playerx+10)/10]==8)||(map[redghost.playery/10][(redghost.playerx+10)/10]==6))&&(prev_red_state!=2)){
				red_state = 1;
				prev_red_state = red_state;
				}
				else if(((map[(redghost.playery-10)/10][redghost.playerx/10]==5)||(map[(redghost.playery-10)/10][(redghost.playerx)/10]==7)||(map[(redghost.playery-10)/10][(redghost.playerx)/10]==4)||(map[(redghost.playery-10)/10][(redghost.playerx)/10]==8)||(map[(redghost.playery-10)/10][(redghost.playerx)/10]==6))&&(prev_red_state!=3)){
				red_state = 4;
				prev_red_state = red_state;
				}
				else if((((map[(redghost.playery+10)/10][redghost.playerx/10]==5)||(map[(redghost.playery+10)/10][(redghost.playerx)/10]==7)||map[(redghost.playery+10)/10][redghost.playerx/10]==4)||(map[(redghost.playery+10)/10][(redghost.playerx)/10]==8)||(map[(redghost.playery+10)/10][(redghost.playerx)/10]==6))&&(prev_red_state!=4)){
				red_state = 3;
				prev_red_state = red_state;
				}
				else if(((map[redghost.playery/10][(redghost.playerx-10)/10]==5)||(map[redghost.playery/10][(redghost.playerx-10)/10]==7)||(map[redghost.playery/10][(redghost.playerx-10)/10]==4)||(map[redghost.playery/10][(redghost.playerx-10)/10]==8)||(map[redghost.playery/10][(redghost.playerx-10)/10]==6))&&(prev_red_state!=1)){
				red_state = 2;
				prev_red_state = red_state;
				}
			}

			else if(target_red.pacidx_y>redghost.playeridx_y){
				if(((map[(redghost.playery+10)/10][redghost.playerx/10]==5)||(map[(redghost.playery+10)/10][(redghost.playerx)/10]==7)||map[(redghost.playery+10)/10][redghost.playerx/10]==4||(map[(redghost.playery+10)/10][(redghost.playerx)/10]==8)||(map[(redghost.playery+10)/10][(redghost.playerx)/10]==6))&&(prev_red_state!=4)){
				red_state = 3;
				prev_red_state = red_state;
				}
				else if(((map[redghost.playery/10][(redghost.playerx+10)/10]==5)||(map[redghost.playery/10][(redghost.playerx+10)/10]==7)||(map[redghost.playery/10][(redghost.playerx+10)/10]==4)||(map[redghost.playery/10][(redghost.playerx+10)/10]==8)||(map[redghost.playery/10][(redghost.playerx+10)/10]==6))&&(prev_red_state!=2)){
				red_state = 1;
				prev_red_state = red_state;
				}
				else if(((map[redghost.playery/10][(redghost.playerx-10)/10]==5)||(map[redghost.playery/10][(redghost.playerx-10)/10]==7)||(map[redghost.playery/10][(redghost.playerx-10)/10]==4)||(map[redghost.playery/10][(redghost.playerx-10)/10]==8)||(map[redghost.playery/10][(redghost.playerx-10)/10]==6))&&(prev_red_state!=1)){
				red_state = 2;
				prev_red_state = red_state;	
				}
				else if(((map[(redghost.playery-10)/10][redghost.playerx/10]==5)||(map[(redghost.playery-10)/10][(redghost.playerx)/10]==7)||(map[(redghost.playery-10)/10][(redghost.playerx)/10]==4)||(map[(redghost.playery-10)/10][(redghost.playerx)/10]==8)||(map[(redghost.playery-10)/10][(redghost.playerx)/10]==6))&&(prev_red_state!=3)){
				red_state = 4;
				prev_red_state = red_state;
				}	
			}

			else if(target_red.pacidx_y==redghost.playeridx_y){
				if(((map[redghost.playery/10][(redghost.playerx+10)/10]==5)||(map[redghost.playery/10][(redghost.playerx+10)/10]==7)||(map[redghost.playery/10][(redghost.playerx+10)/10]==4)||(map[redghost.playery/10][(redghost.playerx+10)/10]==8)||(map[redghost.playery/10][(redghost.playerx+10)/10]==6))&&(prev_red_state!=2)){
				red_state = 1;
				prev_red_state = red_state;
				}
				else if(((map[(redghost.playery-10)/10][redghost.playerx/10]==5)||(map[(redghost.playery-10)/10][(redghost.playerx)/10]==7)||(map[(redghost.playery-10)/10][(redghost.playerx)/10]==4)||(map[(redghost.playery-10)/10][(redghost.playerx)/10]==8)||(map[(redghost.playery-10)/10][(redghost.playerx)/10]==6))&&(prev_red_state!=3)){
				red_state = 4;
				prev_red_state = red_state;
				}
				else if(((map[(redghost.playery+10)/10][redghost.playerx/10]==5)||(map[(redghost.playery+10)/10][(redghost.playerx)/10]==7)||(map[(redghost.playery+10)/10][redghost.playerx/10]==4)||(map[(redghost.playery+10)/10][(redghost.playerx)/10]==8)||(map[(redghost.playery+10)/10][(redghost.playerx)/10]==6))&&(prev_red_state!=4)){
				red_state = 3;
				prev_red_state = red_state;
				}
				else if(((map[redghost.playery/10][(redghost.playerx-10)/10]==5)||(map[redghost.playery/10][(redghost.playerx-10)/10]==7)||(map[redghost.playery/10][(redghost.playerx-10)/10]==4)||(map[redghost.playery/10][(redghost.playerx-10)/10]==8)||(map[redghost.playery/10][(redghost.playerx-10)/10]==6))&&(prev_red_state!=1)){
				red_state = 2;
				prev_red_state = red_state;
				}
			}	
		}

		if(target_red.pacidx_x==redghost.playeridx_x){
			if(target_red.pacidx_y<redghost.playeridx_y){
				if(((map[(redghost.playery-10)/10][redghost.playerx/10]==5)||(map[(redghost.playery-10)/10][(redghost.playerx)/10]==7)||(map[(redghost.playery-10)/10][(redghost.playerx)/10]==4)||(map[(redghost.playery-10)/10][(redghost.playerx)/10]==8)||(map[(redghost.playery-10)/10][(redghost.playerx)/10]==6))&&(prev_red_state!=3)){
				red_state = 4;
				prev_red_state = red_state;
				}
				else if(((map[redghost.playery/10][(redghost.playerx-10)/10]==5)||(map[redghost.playery/10][(redghost.playerx-10)/10]==7)||(map[redghost.playery/10][(redghost.playerx-10)/10]==4)||(map[redghost.playery/10][(redghost.playerx-10)/10]==8)|(map[redghost.playery/10][(redghost.playerx-10)/10]==6))&&(prev_red_state!=1)){
				red_state = 2;
				prev_red_state = red_state;
				}
				else if(((map[redghost.playery/10][(redghost.playerx+10)/10]==5)||(map[redghost.playery/10][(redghost.playerx+10)/10]==7)||(map[redghost.playery/10][(redghost.playerx+10)/10]==4)||(map[redghost.playery/10][(redghost.playerx+10)/10]==8)||(map[redghost.playery/10][(redghost.playerx+10)/10]==6))&&(prev_red_state!=2)){
				red_state = 1;
				prev_red_state = red_state;
				}
				else if(((map[(redghost.playery+10)/10][redghost.playerx/10]==5)||(map[(redghost.playery+10)/10][(redghost.playerx)/10]==7)||(map[(redghost.playery+10)/10][redghost.playerx/10]==4)||(map[(redghost.playery+10)/10][(redghost.playerx)/10]==8)||(map[(redghost.playery+10)/10][(redghost.playerx)/10]==6))&&(prev_red_state!=4)){
				red_state = 3;
				prev_red_state = red_state;
				}
			}
			else if(target_red.pacidx_y>redghost.playeridx_y){
				if(((map[(redghost.playery+10)/10][redghost.playerx/10]==5)||(map[(redghost.playery+10)/10][(redghost.playerx)/10]==7)||(map[(redghost.playery+10)/10][redghost.playerx/10]==4)||(map[(redghost.playery+10)/10][(redghost.playerx)/10]==8)||(map[(redghost.playery+10)/10][(redghost.playerx)/10]==6))&&(prev_red_state!=4)){
				red_state = 3;
				prev_red_state = red_state;
				}
				else if(((map[redghost.playery/10][(redghost.playerx-10)/10]==5)||(map[redghost.playery/10][(redghost.playerx-10)/10]==7)||(map[redghost.playery/10][(redghost.playerx-10)/10]==4)||(map[redghost.playery/10][(redghost.playerx-10)/10]==8)||(map[redghost.playery/10][(redghost.playerx-10)/10]==6))&&(prev_red_state!=1)){
				red_state = 2;
				prev_red_state = red_state;
				}
				else if(((map[redghost.playery/10][(redghost.playerx+10)/10]==5)||(map[redghost.playery/10][(redghost.playerx+10)/10]==7)||(map[redghost.playery/10][(redghost.playerx+10)/10]==4)||(map[redghost.playery/10][(redghost.playerx+10)/10]==8)|(map[redghost.playery/10][(redghost.playerx+10)/10]==6))&&(prev_red_state!=2)){
				red_state = 1;
				prev_red_state = red_state;
			 	}
				else if(((map[(redghost.playery-10)/10][redghost.playerx/10]==5)||(map[(redghost.playery-10)/10][(redghost.playerx)/10]==7)||(map[(redghost.playery-10)/10][(redghost.playerx)/10]==4)||(map[(redghost.playery-10)/10][(redghost.playerx)/10]==8)||(map[(redghost.playery-10)/10][(redghost.playerx)/10]==6))&&(prev_red_state!=3)){
				red_state = 4;
				prev_red_state = red_state;
				}
			}
			else if(target_red.pacidx_y==redghost.playeridx_y){
				if(((map[redghost.playery/10][(redghost.playerx-10)/10]==5)||(map[redghost.playery/10][(redghost.playerx-10)/10]==7)||(map[redghost.playery/10][(redghost.playerx-10)/10]==4)||(map[redghost.playery/10][(redghost.playerx-10)/10]==8)||(map[redghost.playery/10][(redghost.playerx-10)/10]==6))&&(prev_red_state!=1)){
				red_state = 2;
				prev_red_state = red_state;
				}
				else if(((map[(redghost.playery-10)/10][redghost.playerx/10]==5)||(map[(redghost.playery-10)/10][(redghost.playerx)/10]==7)||(map[(redghost.playery-10)/10][(redghost.playerx)/10]==4)||(map[(redghost.playery-10)/10][(redghost.playerx)/10]==8)||(map[(redghost.playery-10)/10][(redghost.playerx)/10]==6))&&(prev_red_state!=3)){
				red_state = 4;
				prev_red_state = red_state;
				}
				else if(((map[(redghost.playery+10)/10][redghost.playerx/10]==5)||(map[(redghost.playery+10)/10][(redghost.playerx)/10]==7)||(map[(redghost.playery+10)/10][redghost.playerx/10]==4)||(map[(redghost.playery+10)/10][(redghost.playerx)/10]==8)||(map[(redghost.playery+10)/10][(redghost.playerx)/10]==6))&&(prev_red_state!=4)){
				red_state = 3;
				prev_red_state = red_state;
				}
				else if(((map[redghost.playery/10][(redghost.playerx+10)/10]==5)||(map[redghost.playery/10][(redghost.playerx+10)/10]==7)||(map[redghost.playery/10][(redghost.playerx+10)/10]==4)||(map[redghost.playery/10][(redghost.playerx+10)/10]==8)||(map[redghost.playery/10][(redghost.playerx+10)/10]==6))&&(prev_red_state!=2)){
				red_state = 1;
				prev_red_state = red_state;
				}
			}
		}
	}
	}
	}
}

void redmove(){
	// if(map[redghost.playery/10][redghost.playery/10]==7){
	// 	redres=1;
	// }
	if(red_state==1){	
		if((map[redghost.playery/10][(redghost.playerx+10)/10]==5)||(map[redghost.playery/10][(redghost.playerx+10)/10]==7)||(map[redghost.playery/10][(redghost.playerx+10)/10]==4)||(map[redghost.playery/10][(redghost.playerx+10)/10]==8)||(map[redghost.playery/10][(redghost.playerx+10)/10]==6)){
		redghost.pic_x += 10;
		redghost.next_x=redghost.playerx+10;
		redghost.next_y=redghost.playery;
		}	
		else if((map[redghost.playery/10][(redghost.playerx+10)/10]==9)){
		redghost.pic_x += 10;
		redghost.next_x=redghost.playerx+10;
		redghost.next_y=redghost.playery;
		}
	}
	if(red_state==2){
		if((map[redghost.playery/10][(redghost.playerx-10)/10]==5)||(map[redghost.playery/10][(redghost.playerx-10)/10]==7)||(map[redghost.playery/10][(redghost.playerx-10)/10]==4)||(map[redghost.playery/10][(redghost.playerx-10)/10]==8)||(map[redghost.playery/10][(redghost.playerx-10)/10]==6)){
		redghost.pic_x -= 10;
		redghost.next_x=redghost.playerx-10;
		redghost.next_y=redghost.playery;
		}	
		// else if((map[redghost.playery/10][(redghost.playerx-10)/10]==9)){
		// redghost.pic_x -= 10;
		// redghost.next_x=redghost.playerx-10;
		// redghost.next_y=redghost.playery;
		// }
	}
	if(red_state==3){
		if((map[(redghost.playery+10)/10][redghost.playerx/10]==5)||(map[(redghost.playery+10)/10][(redghost.playerx)/10]==7)||map[(redghost.playery+10)/10][redghost.playerx/10]==4||(map[(redghost.playery+10)/10][(redghost.playerx)/10]==8)||(map[(redghost.playery+10)/10][(redghost.playerx)/10]==6)){
		redghost.pic_y += 10;
		redghost.next_x=redghost.playerx;
		redghost.next_y=redghost.playery+10;
		}
		else if((map[(redghost.playery+10)/10][redghost.playerx/10]==9)){
		redghost.pic_y += 10;
		redghost.next_x=redghost.playerx;
		redghost.next_y=redghost.playery+10;
		}
	}
	if(red_state==4){
		if((map[(redghost.playery-10)/10][redghost.playerx/10]==5)||(map[(redghost.playery-10)/10][(redghost.playerx)/10]==7)||(map[(redghost.playery-10)/10][(redghost.playerx)/10]==4)||(map[(redghost.playery-10)/10][(redghost.playerx)/10]==8)||(map[(redghost.playery-10)/10][(redghost.playerx)/10]==6)){
		redghost.pic_y -= 10;
		redghost.next_x=redghost.playerx;
		redghost.next_y=redghost.playery-10;
		}
		else if((map[(redghost.playery-10)/10][redghost.playerx/10]==9)){
		redghost.pic_y -= 10;
		redghost.next_x=redghost.playerx;
		redghost.next_y=redghost.playery-10;
		}
	}
	redghost.playerx = redghost.pic_x + 25;
	redghost.playery = redghost.pic_y + 25;

}




void bluewalk(){
if(dead==0){
	if(blueable==0){
		if(target_blue.reached==0){
		target_blue.pac_x=300+25;
		target_blue.pac_y=700+25;
		target_blue.reached=1;
		}
		if((blueghost.pic_x==300&&blueghost.pic_y==700)&&target_blue.reached==1){
		target_blue.pac_x=50+25;
		target_blue.pac_y=800+25;
		target_blue.reached=2;
		}
		if((blueghost.pic_x==50&&blueghost.pic_y==800)&&target_blue.reached==2){
		blueable=1;
		target_blue.reached=0;
		}
	}
	else if(blueable==1){
		if(target_blue.reached==0){
		target_blue.pac_x=1350+25;
		target_blue.pac_y=700+25;
		target_blue.reached=1;
		}
	if((blueghost.pic_x==1350&&blueghost.pic_y==700)&&target_blue.reached==1){
		target_blue.pac_x=1600+25;
		target_blue.pac_y=800+25;
		target_blue.reached=2;
	}
		if((blueghost.pic_x==1600&&blueghost.pic_y==800)&&target_blue.reached==2){
		blueable=2;
		target_blue.reached=0;
	//	printf("blue chasing you\n");
		}
	}
	else{
	target_blue.pac_x=pacman.prev_x;
	target_blue.pac_y=pacman.prev_y;
	}

	blueghost.playeridx_x=blueghost.playerx/10;
	blueghost.playeridx_y=blueghost.playery/10;
	if(map[blueghost.playeridx_y][blueghost.playeridx_x]==7||(map[blueghost.playeridx_y][blueghost.playeridx_x]==4)||(map[blueghost.playeridx_y][blueghost.playeridx_x]==6)){
	target_blue.pacidx_x=target_blue.pac_x/10;
	target_blue.pacidx_y=target_blue.pac_y/10;
	}


	if(state!=0){
	if((map[(blueghost.playery)/10][(blueghost.playerx)/10]==7)||(map[(blueghost.playery)/10][(blueghost.playerx)/10]==4)||(map[blueghost.playeridx_y][blueghost.playeridx_x]==6)){
		if(target_blue.pacidx_x<blueghost.playeridx_x){
			if(target_blue.pacidx_y<blueghost.playeridx_y){
				if(((map[blueghost.playery/10][(blueghost.playerx-10)/10]==5)||(map[blueghost.playery/10][(blueghost.playerx-10)/10]==7)||(map[blueghost.playery/10][(blueghost.playerx-10)/10]==4)||(map[blueghost.playery/10][(blueghost.playerx-10)/10]==8)||(map[blueghost.playery/10][(blueghost.playerx-10)/10]==6))&&(prev_blue_state!=1)){
				blue_state = 2;
				prev_blue_state = blue_state;
				}
				else if(((map[(blueghost.playery-10)/10][blueghost.playerx/10]==5)||(map[(blueghost.playery-10)/10][(blueghost.playerx)/10]==7)||(map[(blueghost.playery-10)/10][(blueghost.playerx)/10]==4)||(map[(blueghost.playery-10)/10][(blueghost.playerx)/10]==8)||(map[(blueghost.playery-10)/10][(blueghost.playerx)/10]==6))&&(prev_blue_state!=3)){
				blue_state = 4;
				prev_blue_state = blue_state;
				}
				else if(((map[(blueghost.playery+10)/10][blueghost.playerx/10]==5)||(map[(blueghost.playery+10)/10][(blueghost.playerx)/10]==7)||(map[(blueghost.playery+10)/10][blueghost.playerx/10]==4)||(map[(blueghost.playery+10)/10][(blueghost.playerx)/10]==8)||(map[(blueghost.playery+10)/10][(blueghost.playerx)/10]==6))&&(prev_blue_state!=4)){
				blue_state = 3;
				prev_blue_state = blue_state;
				}
				else if(((map[blueghost.playery/10][(blueghost.playerx+10)/10]==5)||(map[blueghost.playery/10][(blueghost.playerx+10)/10]==7)||(map[blueghost.playery/10][(blueghost.playerx+10)/10]==4)||(map[blueghost.playery/10][(blueghost.playerx+10)/10]==8)||(map[blueghost.playery/10][(blueghost.playerx+10)/10]==6))&&(prev_blue_state!=2)){
				blue_state = 1;
				prev_blue_state = blue_state;
				}
			}
			else if(target_blue.pacidx_y>blueghost.playeridx_y){
				if(((map[blueghost.playery/10][(blueghost.playerx-10)/10]==5)||(map[blueghost.playery/10][(blueghost.playerx-10)/10]==7)||(map[blueghost.playery/10][(blueghost.playerx-10)/10]==4)||(map[blueghost.playery/10][(blueghost.playerx-10)/10]==8)||(map[blueghost.playery/10][(blueghost.playerx-10)/10]==6))&&(prev_blue_state!=1)){
				blue_state = 2;
				prev_blue_state = blue_state;
				}
				else if(((map[(blueghost.playery+10)/10][blueghost.playerx/10]==5)||(map[(blueghost.playery+10)/10][(blueghost.playerx)/10]==7)||(map[(blueghost.playery+10)/10][blueghost.playerx/10]==4)||(map[(blueghost.playery+10)/10][(blueghost.playerx)/10]==8)||(map[(blueghost.playery+10)/10][(blueghost.playerx)/10]==6))&&(prev_blue_state!=4)){
				blue_state = 3;
				prev_blue_state = blue_state;
				}
				else if(((map[(blueghost.playery-10)/10][blueghost.playerx/10]==5)||(map[(blueghost.playery-10)/10][(blueghost.playerx)/10]==7)||(map[(blueghost.playery-10)/10][(blueghost.playerx)/10]==4)||(map[(blueghost.playery-10)/10][(blueghost.playerx)/10]==8))&&(prev_blue_state!=3)||(map[(blueghost.playery-10)/10][(blueghost.playerx)/10]==6)){
				blue_state = 4;
				prev_blue_state = blue_state;
				}
				else if(((map[blueghost.playery/10][(blueghost.playerx+10)/10]==5)||(map[blueghost.playery/10][(blueghost.playerx+10)/10]==7)||(map[blueghost.playery/10][(blueghost.playerx+10)/10]==4)||(map[blueghost.playery/10][(blueghost.playerx+10)/10]==8)||(map[blueghost.playery/10][(blueghost.playerx+10)/10]==6))&&(prev_blue_state!=2)){
				blue_state = 1;
				prev_blue_state = blue_state;
			 	}
				
			}
			else if(target_blue.pacidx_y==blueghost.playeridx_y){
				if(((map[(blueghost.playery-10)/10][blueghost.playerx/10]==5)||(map[(blueghost.playery-10)/10][(blueghost.playerx)/10]==7)||(map[(blueghost.playery-10)/10][(blueghost.playerx)/10]==4)||(map[(blueghost.playery-10)/10][(blueghost.playerx)/10]==8))&&(prev_blue_state!=3)||(map[(blueghost.playery-10)/10][(blueghost.playerx)/10]==6)){
				blue_state = 4;
				prev_blue_state = blue_state;
				}
				else if(((map[blueghost.playery/10][(blueghost.playerx-10)/10]==5)||(map[blueghost.playery/10][(blueghost.playerx-10)/10]==7)||(map[blueghost.playery/10][(blueghost.playerx-10)/10]==4)||(map[blueghost.playery/10][(blueghost.playerx-10)/10]==8)||(map[blueghost.playery/10][(blueghost.playerx-10)/10]==6))&&(prev_blue_state!=1)){
				blue_state = 2;
				prev_blue_state = blue_state;
				} 
				else if(((map[blueghost.playery/10][(blueghost.playerx+10)/10]==5)||(map[blueghost.playery/10][(blueghost.playerx+10)/10]==7)||(map[blueghost.playery/10][(blueghost.playerx+10)/10]==4)||(map[blueghost.playery/10][(blueghost.playerx+10)/10]==8)||(map[blueghost.playery/10][(blueghost.playerx+10)/10]==6))&&(prev_blue_state!=2)){
				blue_state = 1;
				prev_blue_state = blue_state;
				}
				else if(((map[(blueghost.playery+10)/10][blueghost.playerx/10]==5)||(map[(blueghost.playery+10)/10][(blueghost.playerx)/10]==7)||(map[(blueghost.playery+10)/10][blueghost.playerx/10]==4)||(map[(blueghost.playery+10)/10][(blueghost.playerx)/10]==8)||(map[(blueghost.playery+10)/10][(blueghost.playerx)/10]==6))&&(prev_blue_state!=4)){
				blue_state = 3;
				prev_blue_state = blue_state;
				}
			}
		}

		if(target_blue.pacidx_x>blueghost.playeridx_x){
			if(target_blue.pacidx_y<blueghost.playeridx_y){
				if(((map[(blueghost.playery-10)/10][blueghost.playerx/10]==5)||(map[(blueghost.playery-10)/10][(blueghost.playerx)/10]==7)||(map[(blueghost.playery-10)/10][(blueghost.playerx)/10]==4)||(map[(blueghost.playery-10)/10][(blueghost.playerx)/10]==8)||(map[(blueghost.playery-10)/10][(blueghost.playerx)/10]==6))&&(prev_blue_state!=3)){
				blue_state = 4;
				prev_blue_state = blue_state;
				}
				else if(((map[blueghost.playery/10][(blueghost.playerx+10)/10]==5)||(map[blueghost.playery/10][(blueghost.playerx+10)/10]==7)||(map[blueghost.playery/10][(blueghost.playerx+10)/10]==4)||(map[blueghost.playery/10][(blueghost.playerx+10)/10]==8)||(map[blueghost.playery/10][(blueghost.playerx+10)/10]==6))&&(prev_blue_state!=2)){
				blue_state = 1;
				prev_blue_state = blue_state;
				}
				else if(((map[blueghost.playery/10][(blueghost.playerx-10)/10]==5)||(map[blueghost.playery/10][(blueghost.playerx-10)/10]==7)||(map[blueghost.playery/10][(blueghost.playerx-10)/10]==4)||(map[blueghost.playery/10][(blueghost.playerx-10)/10]==8)||(map[blueghost.playery/10][(blueghost.playerx-10)/10]==6))&&(prev_blue_state!=1)){
				blue_state = 2;
				prev_blue_state = blue_state;
				}
				else if((((map[(blueghost.playery+10)/10][blueghost.playerx/10]==5)||(map[(blueghost.playery+10)/10][(blueghost.playerx)/10]==7)||map[(blueghost.playery+10)/10][blueghost.playerx/10]==4)||(map[(blueghost.playery+10)/10][(blueghost.playerx)/10]==8)||(map[(blueghost.playery+10)/10][(blueghost.playerx)/10]==6))&&(prev_blue_state!=4)){
				blue_state = 3;
				prev_blue_state = blue_state;
				}	
			}

			else if(target_blue.pacidx_y>blueghost.playeridx_y){
				if(((map[blueghost.playery/10][(blueghost.playerx+10)/10]==5)||(map[blueghost.playery/10][(blueghost.playerx+10)/10]==7)||(map[blueghost.playery/10][(blueghost.playerx+10)/10]==4)||(map[blueghost.playery/10][(blueghost.playerx+10)/10]==8)||(map[blueghost.playery/10][(blueghost.playerx+10)/10]==6))&&(prev_blue_state!=2)){
				blue_state = 1;
				prev_blue_state = blue_state;
				}
				else if(((map[(blueghost.playery+10)/10][blueghost.playerx/10]==5)||(map[(blueghost.playery+10)/10][(blueghost.playerx)/10]==7)||map[(blueghost.playery+10)/10][blueghost.playerx/10]==4||(map[(blueghost.playery+10)/10][(blueghost.playerx)/10]==8)||(map[(blueghost.playery+10)/10][(blueghost.playerx)/10]==6))&&(prev_blue_state!=4)){
				blue_state = 3;
				prev_blue_state = blue_state;
				}
				else if(((map[(blueghost.playery-10)/10][blueghost.playerx/10]==5)||(map[(blueghost.playery-10)/10][(blueghost.playerx)/10]==7)||(map[(blueghost.playery-10)/10][(blueghost.playerx)/10]==4)||(map[(blueghost.playery-10)/10][(blueghost.playerx)/10]==8)||(map[(blueghost.playery-10)/10][(blueghost.playerx)/10]==6))&&(prev_blue_state!=3)){
				blue_state = 4;
				prev_blue_state = blue_state;
				}	
				else if(((map[blueghost.playery/10][(blueghost.playerx-10)/10]==5)||(map[blueghost.playery/10][(blueghost.playerx-10)/10]==7)||(map[blueghost.playery/10][(blueghost.playerx-10)/10]==4)||(map[blueghost.playery/10][(blueghost.playerx-10)/10]==8)||(map[blueghost.playery/10][(blueghost.playerx-10)/10]==6))&&(prev_blue_state!=1)){
				blue_state = 2;
				prev_blue_state = blue_state;	
				}
				
			}

			else if(target_blue.pacidx_y==blueghost.playeridx_y){
				if(((map[(blueghost.playery-10)/10][blueghost.playerx/10]==5)||(map[(blueghost.playery-10)/10][(blueghost.playerx)/10]==7)||(map[(blueghost.playery-10)/10][(blueghost.playerx)/10]==4)||(map[(blueghost.playery-10)/10][(blueghost.playerx)/10]==8)||(map[(blueghost.playery-10)/10][(blueghost.playerx)/10]==6))&&(prev_blue_state!=3)){
				blue_state = 4;
				prev_blue_state = blue_state;
				}
				else if(((map[blueghost.playery/10][(blueghost.playerx+10)/10]==5)||(map[blueghost.playery/10][(blueghost.playerx+10)/10]==7)||(map[blueghost.playery/10][(blueghost.playerx+10)/10]==4)||(map[blueghost.playery/10][(blueghost.playerx+10)/10]==8)||(map[blueghost.playery/10][(blueghost.playerx+10)/10]==6))&&(prev_blue_state!=2)){
				blue_state = 1;
				prev_blue_state = blue_state;
				}
				else if(((map[blueghost.playery/10][(blueghost.playerx-10)/10]==5)||(map[blueghost.playery/10][(blueghost.playerx-10)/10]==7)||(map[blueghost.playery/10][(blueghost.playerx-10)/10]==4)||(map[blueghost.playery/10][(blueghost.playerx-10)/10]==8)||(map[blueghost.playery/10][(blueghost.playerx-10)/10]==6))&&(prev_blue_state!=1)){
				blue_state = 2;
				prev_blue_state = blue_state;
				}
				else if(((map[(blueghost.playery+10)/10][blueghost.playerx/10]==5)||(map[(blueghost.playery+10)/10][(blueghost.playerx)/10]==7)||(map[(blueghost.playery+10)/10][blueghost.playerx/10]==4)||(map[(blueghost.playery+10)/10][(blueghost.playerx)/10]==8)||(map[(blueghost.playery+10)/10][(blueghost.playerx)/10]==6))&&(prev_blue_state!=4)){
				blue_state = 3;
				prev_blue_state = blue_state;
				}
			}	
		}
		if(target_blue.pacidx_x==blueghost.playeridx_x){
			if(target_blue.pacidx_y<blueghost.playeridx_y){
				if(((map[(blueghost.playery-10)/10][blueghost.playerx/10]==5)||(map[(blueghost.playery-10)/10][(blueghost.playerx)/10]==7)||(map[(blueghost.playery-10)/10][(blueghost.playerx)/10]==4)||(map[(blueghost.playery-10)/10][(blueghost.playerx)/10]==8)||(map[(blueghost.playery-10)/10][(blueghost.playerx)/10]==6))&&(prev_blue_state!=3)){
				blue_state = 4;
				prev_blue_state = blue_state;
				}
				else if(((map[blueghost.playery/10][(blueghost.playerx-10)/10]==5)||(map[blueghost.playery/10][(blueghost.playerx-10)/10]==7)||(map[blueghost.playery/10][(blueghost.playerx-10)/10]==4)||(map[blueghost.playery/10][(blueghost.playerx-10)/10]==8)||(map[blueghost.playery/10][(blueghost.playerx-10)/10]==6))&&(prev_blue_state!=1)){
				blue_state = 2;
				prev_blue_state = blue_state;
				}
				else if(((map[(blueghost.playery+10)/10][blueghost.playerx/10]==5)||(map[(blueghost.playery+10)/10][(blueghost.playerx)/10]==7)||(map[(blueghost.playery+10)/10][blueghost.playerx/10]==4)||(map[(blueghost.playery+10)/10][(blueghost.playerx)/10]==8)||(map[(blueghost.playery+10)/10][(blueghost.playerx)/10]==6))&&(prev_blue_state!=4)){
				blue_state = 3;
				prev_blue_state = blue_state;
				}
				else if(((map[blueghost.playery/10][(blueghost.playerx+10)/10]==5)||(map[blueghost.playery/10][(blueghost.playerx+10)/10]==7)||(map[blueghost.playery/10][(blueghost.playerx+10)/10]==4)||(map[blueghost.playery/10][(blueghost.playerx+10)/10]==8)||(map[blueghost.playery/10][(blueghost.playerx+10)/10]==6))&&(prev_blue_state!=2)){
				blue_state = 1;
				prev_blue_state = blue_state;
				}
			}
			else if(target_blue.pacidx_y>blueghost.playeridx_y){ 
				if(((map[(blueghost.playery+10)/10][blueghost.playerx/10]==5)||(map[(blueghost.playery+10)/10][(blueghost.playerx)/10]==7)||(map[(blueghost.playery+10)/10][blueghost.playerx/10]==4)||(map[(blueghost.playery+10)/10][(blueghost.playerx)/10]==8)||(map[(blueghost.playery+10)/10][(blueghost.playerx)/10]==6))&&(prev_blue_state!=4)){
				blue_state = 3;
				prev_blue_state = blue_state;
				}
				else if(((map[blueghost.playery/10][(blueghost.playerx-10)/10]==5)||(map[blueghost.playery/10][(blueghost.playerx-10)/10]==7)||(map[blueghost.playery/10][(blueghost.playerx-10)/10]==4)||(map[blueghost.playery/10][(blueghost.playerx-10)/10]==8)||(map[blueghost.playery/10][(blueghost.playerx-10)/10]==6))&&(prev_blue_state!=1)){
				blue_state = 2;
				prev_blue_state = blue_state;
				}
				else if(((map[(blueghost.playery-10)/10][blueghost.playerx/10]==5)||(map[(blueghost.playery-10)/10][(blueghost.playerx)/10]==7)||(map[(blueghost.playery-10)/10][(blueghost.playerx)/10]==4)||(map[(blueghost.playery-10)/10][(blueghost.playerx)/10]==8))&&(prev_blue_state!=3)||(map[(blueghost.playery-10)/10][(blueghost.playerx)/10]==6)){
				blue_state = 4;
				prev_blue_state = blue_state;
				}
				else if(((map[blueghost.playery/10][(blueghost.playerx+10)/10]==5)||(map[blueghost.playery/10][(blueghost.playerx+10)/10]==7)||(map[blueghost.playery/10][(blueghost.playerx+10)/10]==4)||(map[blueghost.playery/10][(blueghost.playerx+10)/10]==8)||(map[blueghost.playery/10][(blueghost.playerx+10)/10]==6))&&(prev_blue_state!=2)){
				blue_state = 1;
				prev_blue_state = blue_state;
			 	}
				
			}
			else if(target_blue.pacidx_y==blueghost.playeridx_y){
				if(((map[(blueghost.playery+10)/10][blueghost.playerx/10]==5)||(map[(blueghost.playery+10)/10][(blueghost.playerx)/10]==7)||(map[(blueghost.playery+10)/10][blueghost.playerx/10]==4)||(map[(blueghost.playery+10)/10][(blueghost.playerx)/10]==8)||(map[(blueghost.playery+10)/10][(blueghost.playerx)/10]==6))&&(prev_blue_state!=4)){
				blue_state = 3;
				prev_blue_state = blue_state;
				}
				else if(((map[(blueghost.playery-10)/10][blueghost.playerx/10]==5)||(map[(blueghost.playery-10)/10][(blueghost.playerx)/10]==7)||(map[(blueghost.playery-10)/10][(blueghost.playerx)/10]==4)||(map[(blueghost.playery-10)/10][(blueghost.playerx)/10]==8))&&(prev_blue_state!=3)||(map[(blueghost.playery-10)/10][(blueghost.playerx)/10]==6)){
				blue_state = 4;
				prev_blue_state = blue_state;
				}
				else if(((map[blueghost.playery/10][(blueghost.playerx-10)/10]==5)||(map[blueghost.playery/10][(blueghost.playerx-10)/10]==7)||(map[blueghost.playery/10][(blueghost.playerx-10)/10]==4)||(map[blueghost.playery/10][(blueghost.playerx-10)/10]==8)||(map[blueghost.playery/10][(blueghost.playerx-10)/10]==6))&&(prev_blue_state!=1)){
				blue_state = 2;
				prev_blue_state = blue_state;
				} 
				else if(((map[blueghost.playery/10][(blueghost.playerx+10)/10]==5)||(map[blueghost.playery/10][(blueghost.playerx+10)/10]==7)||(map[blueghost.playery/10][(blueghost.playerx+10)/10]==4)||(map[blueghost.playery/10][(blueghost.playerx+10)/10]==8)||(map[blueghost.playery/10][(blueghost.playerx+10)/10]==6))&&(prev_blue_state!=2)){
				blue_state = 1;
				prev_blue_state = blue_state;
				}
			}
		}
	}
	}
	}
}

void bluemove(){

	if(blue_state==1){	
		if((map[blueghost.playery/10][(blueghost.playerx+10)/10]==5)||(map[blueghost.playery/10][(blueghost.playerx+10)/10]==7)||(map[blueghost.playery/10][(blueghost.playerx+10)/10]==4)||(map[blueghost.playery/10][(blueghost.playerx+10)/10]==8)||(map[blueghost.playery/10][(blueghost.playerx+10)/10]==6)){
		blueghost.pic_x += 10;
		blueghost.next_x=blueghost.playerx+10;
		blueghost.next_y=blueghost.playery;
		}	
		else if((map[blueghost.playery/10][(blueghost.playerx+10)/10]==9)){
		blueghost.pic_x += 10;
		blueghost.next_x=blueghost.playerx+10;
		blueghost.next_y=blueghost.playery;
		}
	}
	if(blue_state==2){
		if((map[blueghost.playery/10][(blueghost.playerx-10)/10]==5)||(map[blueghost.playery/10][(blueghost.playerx-10)/10]==7)||(map[blueghost.playery/10][(blueghost.playerx-10)/10]==4)||(map[blueghost.playery/10][(blueghost.playerx-10)/10]==8)||(map[blueghost.playery/10][(blueghost.playerx-10)/10]==6)){
		blueghost.pic_x -= 10;
		blueghost.next_x=blueghost.playerx-10;
		blueghost.next_y=blueghost.playery;
		}	

	}
	if(blue_state==3){
		if((map[(blueghost.playery+10)/10][blueghost.playerx/10]==5)||(map[(blueghost.playery+10)/10][(blueghost.playerx)/10]==7)||map[(blueghost.playery+10)/10][blueghost.playerx/10]==4||(map[(blueghost.playery+10)/10][(blueghost.playerx)/10]==8)||(map[(blueghost.playery+10)/10][(blueghost.playerx)/10]==6)){
		blueghost.pic_y += 10;
		blueghost.next_x=blueghost.playerx;
		blueghost.next_y=blueghost.playery+10;
		}
		else if((map[(blueghost.playery+10)/10][blueghost.playerx/10]==9)){
		blueghost.pic_y += 10;
		blueghost.next_x=blueghost.playerx;
		blueghost.next_y=blueghost.playery+10;
		}
	}
	if(blue_state==4){
		if((map[(blueghost.playery-10)/10][blueghost.playerx/10]==5)||(map[(blueghost.playery-10)/10][(blueghost.playerx)/10]==7)||(map[(blueghost.playery-10)/10][(blueghost.playerx)/10]==4)||(map[(blueghost.playery-10)/10][(blueghost.playerx)/10]==8)||(map[(blueghost.playery-10)/10][(blueghost.playerx)/10]==6)){
		blueghost.pic_y -= 10;
		blueghost.next_x=blueghost.playerx;
		blueghost.next_y=blueghost.playery-10;
		}
		else if((map[(blueghost.playery-10)/10][blueghost.playerx/10]==9)){
		blueghost.pic_y -= 10;
		blueghost.next_x=blueghost.playerx;
		blueghost.next_y=blueghost.playery-10;
		}
	}
	blueghost.playerx = blueghost.pic_x + 25;
	blueghost.playery = blueghost.pic_y + 25;

}


void pinkwalk(){
if(dead==0){
	if(pinkable==0){
		if(target_pink.reached==0){
		target_pink.pac_x=1350+25;
		target_pink.pac_y=700+25;
		target_pink.reached=1;
		}
		if((pinkghost.pic_x==1350&&pinkghost.pic_y==700&&target_pink.reached==1)){
		target_pink.pac_x=1600+25;
		target_pink.pac_y=800+25;
		target_pink.reached=2;
	}
		if((pinkghost.pic_x==1600&&pinkghost.pic_y==800&&target_pink.reached==2)){
		pinkable=1;
		target_pink.reached=0;
		}
	}
	else if(pinkable==1){
		if(target_pink.reached==0){
		target_pink.pac_x=300+25;
		target_pink.pac_y=200+25;
		target_pink.reached=1;
		}
	if((pinkghost.pic_x==300&&pinkghost.pic_y==200&&target_pink.reached==1)){
		target_pink.pac_x=50+25;
		target_pink.pac_y=100+25;
		target_pink.reached=2;
	}
		if((pinkghost.pic_x==50&&pinkghost.pic_y==100&&target_pink.reached==2)){
		pinkable=2;
		target_pink.reached=0;
		// printf("pink chasing you\n");
		}
	}

	else{
	target_pink.pac_x=pacman.prev_x+40;
	target_pink.pac_y=pacman.prev_y+40;
	}
	pinkghost.playeridx_x=pinkghost.playerx/10;
	pinkghost.playeridx_y=pinkghost.playery/10;
	if(map[pinkghost.playeridx_y][pinkghost.playeridx_x]==7||(map[pinkghost.playeridx_y][pinkghost.playeridx_x]==4)||(map[pinkghost.playeridx_y][pinkghost.playeridx_x]==6)){
	target_pink.pacidx_x=target_pink.pac_x/10;
	target_pink.pacidx_y=target_pink.pac_y/10;
	}


	if(state!=0){
	if((map[(pinkghost.playery)/10][(pinkghost.playerx)/10]==7)||(map[(pinkghost.playery)/10][(pinkghost.playerx)/10]==4)||(map[pinkghost.playeridx_y][pinkghost.playeridx_x]==6)){
		if(target_pink.pacidx_x<pinkghost.playeridx_x){
			if(target_pink.pacidx_y<pinkghost.playeridx_y){
				if(((map[(pinkghost.playery-10)/10][pinkghost.playerx/10]==5)||(map[(pinkghost.playery-10)/10][(pinkghost.playerx)/10]==7)||(map[(pinkghost.playery-10)/10][(pinkghost.playerx)/10]==4)||(map[(pinkghost.playery-10)/10][(pinkghost.playerx)/10]==8)||(map[(pinkghost.playery-10)/10][(pinkghost.playerx)/10]==6))&&(prev_pink_state!=3)){
				pink_state = 4;
				prev_pink_state = pink_state;
				}
				else if(((map[pinkghost.playery/10][(pinkghost.playerx-10)/10]==5)||(map[pinkghost.playery/10][(pinkghost.playerx-10)/10]==7)||(map[pinkghost.playery/10][(pinkghost.playerx-10)/10]==4)||(map[pinkghost.playery/10][(pinkghost.playerx-10)/10]==8)||(map[pinkghost.playery/10][(pinkghost.playerx-10)/10]==6))&&(prev_pink_state!=1)){
				pink_state = 2;
				prev_pink_state = pink_state;
				}
				else if(((map[(pinkghost.playery+10)/10][pinkghost.playerx/10]==5)||(map[(pinkghost.playery+10)/10][(pinkghost.playerx)/10]==7)||(map[(pinkghost.playery+10)/10][pinkghost.playerx/10]==4)||(map[(pinkghost.playery+10)/10][(pinkghost.playerx)/10]==8)||(map[(pinkghost.playery+10)/10][(pinkghost.playerx)/10]==6))&&(prev_pink_state!=4)){
				pink_state = 3;
				prev_pink_state = pink_state;
				}
				else if(((map[pinkghost.playery/10][(pinkghost.playerx+10)/10]==5)||(map[pinkghost.playery/10][(pinkghost.playerx+10)/10]==7)||(map[pinkghost.playery/10][(pinkghost.playerx+10)/10]==4)||(map[pinkghost.playery/10][(pinkghost.playerx+10)/10]==8))&&(prev_pink_state!=2)){
				pink_state = 1;
				prev_pink_state = pink_state;
				}
			}
			else if(target_pink.pacidx_y>pinkghost.playeridx_y){
				if(((map[(pinkghost.playery+10)/10][pinkghost.playerx/10]==5)||(map[(pinkghost.playery+10)/10][(pinkghost.playerx)/10]==7)||(map[(pinkghost.playery+10)/10][pinkghost.playerx/10]==4)||(map[(pinkghost.playery+10)/10][(pinkghost.playerx)/10]==8)||(map[(pinkghost.playery+10)/10][(pinkghost.playerx)/10]==8))&&(prev_pink_state!=4)){
				pink_state = 3;
				prev_pink_state = pink_state;
				}
				else if(((map[pinkghost.playery/10][(pinkghost.playerx-10)/10]==5)||(map[pinkghost.playery/10][(pinkghost.playerx-10)/10]==7)||(map[pinkghost.playery/10][(pinkghost.playerx-10)/10]==4)||(map[pinkghost.playery/10][(pinkghost.playerx-10)/10]==8)||(map[pinkghost.playery/10][(pinkghost.playerx-10)/10]==6))&&(prev_pink_state!=1)){
				pink_state = 2;
				prev_pink_state = pink_state;
				}
				else if(((map[(pinkghost.playery-10)/10][pinkghost.playerx/10]==5)||(map[(pinkghost.playery-10)/10][(pinkghost.playerx)/10]==7)||(map[(pinkghost.playery-10)/10][(pinkghost.playerx)/10]==4)||(map[(pinkghost.playery-10)/10][(pinkghost.playerx)/10]==8)||(map[(pinkghost.playery-10)/10][(pinkghost.playerx)/10]==6))&&(prev_pink_state!=3)){
				pink_state = 4;
				prev_pink_state = pink_state;
				}
				else if(((map[pinkghost.playery/10][(pinkghost.playerx+10)/10]==5)||(map[pinkghost.playery/10][(pinkghost.playerx+10)/10]==7)||(map[pinkghost.playery/10][(pinkghost.playerx+10)/10]==4)||(map[pinkghost.playery/10][(pinkghost.playerx+10)/10]==8)||(map[pinkghost.playery/10][(pinkghost.playerx+10)/10]==6))&&(prev_pink_state!=2)){
				pink_state = 1;
				prev_pink_state = pink_state;
			 	}
			}
			else if(target_pink.pacidx_y==pinkghost.playeridx_y){
				if(((map[pinkghost.playery/10][(pinkghost.playerx-10)/10]==5)||(map[pinkghost.playery/10][(pinkghost.playerx-10)/10]==7)||(map[pinkghost.playery/10][(pinkghost.playerx-10)/10]==4)||(map[pinkghost.playery/10][(pinkghost.playerx-10)/10]==8)||(map[pinkghost.playery/10][(pinkghost.playerx-10)/10]==6))&&(prev_pink_state!=1)){
				pink_state = 2;
				prev_pink_state = pink_state;
				}
				else if(((map[(pinkghost.playery-10)/10][pinkghost.playerx/10]==5)||(map[(pinkghost.playery-10)/10][(pinkghost.playerx)/10]==7)||(map[(pinkghost.playery-10)/10][(pinkghost.playerx)/10]==4)||(map[(pinkghost.playery-10)/10][(pinkghost.playerx)/10]==8)||(map[(pinkghost.playery-10)/10][(pinkghost.playerx)/10]==6))&&(prev_pink_state!=3)){
				pink_state = 4;
				prev_pink_state = pink_state;
				}
				else if(((map[pinkghost.playery/10][(pinkghost.playerx+10)/10]==5)||(map[pinkghost.playery/10][(pinkghost.playerx+10)/10]==7)||(map[pinkghost.playery/10][(pinkghost.playerx+10)/10]==4)||(map[pinkghost.playery/10][(pinkghost.playerx+10)/10]==8)||(map[pinkghost.playery/10][(pinkghost.playerx+10)/10]==6))&&(prev_pink_state!=2)){
				pink_state = 1;
				prev_pink_state = pink_state;
				}
				else if(((map[(pinkghost.playery+10)/10][pinkghost.playerx/10]==5)||(map[(pinkghost.playery+10)/10][(pinkghost.playerx)/10]==7)||(map[(pinkghost.playery+10)/10][pinkghost.playerx/10]==4)||(map[(pinkghost.playery+10)/10][(pinkghost.playerx)/10]==8)||(map[(pinkghost.playery+10)/10][(pinkghost.playerx)/10]==8))&&(prev_pink_state!=4)){
				pink_state = 3;
				prev_pink_state = pink_state;
				}
			}
		}

		if(target_pink.pacidx_x>pinkghost.playeridx_x){
			if(target_pink.pacidx_y<pinkghost.playeridx_y){
				if(((map[(pinkghost.playery-10)/10][pinkghost.playerx/10]==5)||(map[(pinkghost.playery-10)/10][(pinkghost.playerx)/10]==7)||(map[(pinkghost.playery-10)/10][(pinkghost.playerx)/10]==4)||(map[(pinkghost.playery-10)/10][(pinkghost.playerx)/10]==8)||(map[(pinkghost.playery-10)/10][(pinkghost.playerx)/10]==6))&&(prev_pink_state!=3)){
				pink_state = 4;
				prev_pink_state = pink_state;
				}
				else if(((map[pinkghost.playery/10][(pinkghost.playerx+10)/10]==5)||(map[pinkghost.playery/10][(pinkghost.playerx+10)/10]==7)||(map[pinkghost.playery/10][(pinkghost.playerx+10)/10]==4)||(map[pinkghost.playery/10][(pinkghost.playerx+10)/10]==8)||(map[pinkghost.playery/10][(pinkghost.playerx+10)/10]==6))&&(prev_pink_state!=2)){
				pink_state = 1;
				prev_pink_state = pink_state;
				}
				else if((((map[(pinkghost.playery+10)/10][pinkghost.playerx/10]==5)||(map[(pinkghost.playery+10)/10][(pinkghost.playerx)/10]==7)||map[(pinkghost.playery+10)/10][pinkghost.playerx/10]==4)||(map[(pinkghost.playery+10)/10][(pinkghost.playerx)/10]==8)||(map[(pinkghost.playery+10)/10][(pinkghost.playerx)/10]==8))&&(prev_pink_state!=4)){
				pink_state = 3;
				prev_pink_state = pink_state;
				}
				else if(((map[pinkghost.playery/10][(pinkghost.playerx-10)/10]==5)||(map[pinkghost.playery/10][(pinkghost.playerx-10)/10]==7)||(map[pinkghost.playery/10][(pinkghost.playerx-10)/10]==4)||(map[pinkghost.playery/10][(pinkghost.playerx-10)/10]==8)||(map[pinkghost.playery/10][(pinkghost.playerx-10)/10]==6))&&(prev_pink_state!=1)){
				pink_state = 2;
				prev_pink_state = pink_state;
				}
			}

			else if(target_pink.pacidx_y>pinkghost.playeridx_y){
				if(((map[(pinkghost.playery+10)/10][pinkghost.playerx/10]==5)||(map[(pinkghost.playery+10)/10][(pinkghost.playerx)/10]==7)||map[(pinkghost.playery+10)/10][pinkghost.playerx/10]==4||(map[(pinkghost.playery+10)/10][(pinkghost.playerx)/10]==8)||(map[(pinkghost.playery+10)/10][(pinkghost.playerx)/10]==8))&&(prev_pink_state!=4)){
				pink_state = 3;
				prev_pink_state = pink_state;
				}
				else if(((map[pinkghost.playery/10][(pinkghost.playerx+10)/10]==5)||(map[pinkghost.playery/10][(pinkghost.playerx+10)/10]==7)||(map[pinkghost.playery/10][(pinkghost.playerx+10)/10]==4)||(map[pinkghost.playery/10][(pinkghost.playerx+10)/10]==8)||(map[pinkghost.playery/10][(pinkghost.playerx+10)/10]==6))&&(prev_pink_state!=2)){
				pink_state = 1;
				prev_pink_state = pink_state;
				}
				else if(((map[(pinkghost.playery-10)/10][pinkghost.playerx/10]==5)||(map[(pinkghost.playery-10)/10][(pinkghost.playerx)/10]==7)||(map[(pinkghost.playery-10)/10][(pinkghost.playerx)/10]==4)||(map[(pinkghost.playery-10)/10][(pinkghost.playerx)/10]==8)||(map[(pinkghost.playery-10)/10][(pinkghost.playerx)/10]==6))&&(prev_pink_state!=3)){
				pink_state = 4;
				prev_pink_state = pink_state;
				}
				else if(((map[pinkghost.playery/10][(pinkghost.playerx-10)/10]==5)||(map[pinkghost.playery/10][(pinkghost.playerx-10)/10]==7)||(map[pinkghost.playery/10][(pinkghost.playerx-10)/10]==4)||(map[pinkghost.playery/10][(pinkghost.playerx-10)/10]==8)||(map[pinkghost.playery/10][(pinkghost.playerx-10)/10]==6))&&(prev_pink_state!=1)){
				pink_state = 2;
				prev_pink_state = pink_state;	
				}	
			}

			else if(target_pink.pacidx_y==pinkghost.playeridx_y){
				if(((map[pinkghost.playery/10][(pinkghost.playerx+10)/10]==5)||(map[pinkghost.playery/10][(pinkghost.playerx+10)/10]==7)||(map[pinkghost.playery/10][(pinkghost.playerx+10)/10]==4)||(map[pinkghost.playery/10][(pinkghost.playerx+10)/10]==8)||(map[pinkghost.playery/10][(pinkghost.playerx+10)/10]==6))&&(prev_pink_state!=2)){
				pink_state = 1;
				prev_pink_state = pink_state;
				}
				else if(((map[(pinkghost.playery-10)/10][pinkghost.playerx/10]==5)||(map[(pinkghost.playery-10)/10][(pinkghost.playerx)/10]==7)||(map[(pinkghost.playery-10)/10][(pinkghost.playerx)/10]==4)||(map[(pinkghost.playery-10)/10][(pinkghost.playerx)/10]==8)||(map[(pinkghost.playery-10)/10][(pinkghost.playerx)/10]==6))&&(prev_pink_state!=3)){
				pink_state = 4;
				prev_pink_state = pink_state;
				}
				else if(((map[pinkghost.playery/10][(pinkghost.playerx-10)/10]==5)||(map[pinkghost.playery/10][(pinkghost.playerx-10)/10]==7)||(map[pinkghost.playery/10][(pinkghost.playerx-10)/10]==4)||(map[pinkghost.playery/10][(pinkghost.playerx-10)/10]==8)||(map[pinkghost.playery/10][(pinkghost.playerx-10)/10]==6))&&(prev_pink_state!=1)){
				pink_state = 2;
				prev_pink_state = pink_state;
				}
				else if(((map[(pinkghost.playery+10)/10][pinkghost.playerx/10]==5)||(map[(pinkghost.playery+10)/10][(pinkghost.playerx)/10]==7)||(map[(pinkghost.playery+10)/10][pinkghost.playerx/10]==4)||(map[(pinkghost.playery+10)/10][(pinkghost.playerx)/10]==8)||(map[(pinkghost.playery+10)/10][(pinkghost.playerx)/10]==8))&&(prev_pink_state!=4)){
				pink_state = 3;
				prev_pink_state = pink_state;
				}
			}	
		}
		if(target_pink.pacidx_x==pinkghost.playeridx_x){
			if(target_pink.pacidx_y<pinkghost.playeridx_y){
				if(((map[(pinkghost.playery-10)/10][pinkghost.playerx/10]==5)||(map[(pinkghost.playery-10)/10][(pinkghost.playerx)/10]==7)||(map[(pinkghost.playery-10)/10][(pinkghost.playerx)/10]==4)||(map[(pinkghost.playery-10)/10][(pinkghost.playerx)/10]==8)||(map[(pinkghost.playery-10)/10][(pinkghost.playerx)/10]==6))&&(prev_pink_state!=3)){
				pink_state = 4;
				prev_pink_state = pink_state;
				}
				else if(((map[pinkghost.playery/10][(pinkghost.playerx-10)/10]==5)||(map[pinkghost.playery/10][(pinkghost.playerx-10)/10]==7)||(map[pinkghost.playery/10][(pinkghost.playerx-10)/10]==4)||(map[pinkghost.playery/10][(pinkghost.playerx-10)/10]==8)||(map[pinkghost.playery/10][(pinkghost.playerx-10)/10]==6))&&(prev_pink_state!=1)){
				pink_state = 2;
				prev_pink_state = pink_state;
				}
				else if(((map[(pinkghost.playery+10)/10][pinkghost.playerx/10]==5)||(map[(pinkghost.playery+10)/10][(pinkghost.playerx)/10]==7)||(map[(pinkghost.playery+10)/10][pinkghost.playerx/10]==4)||(map[(pinkghost.playery+10)/10][(pinkghost.playerx)/10]==8)||(map[(pinkghost.playery+10)/10][(pinkghost.playerx)/10]==6))&&(prev_pink_state!=4)){
				pink_state = 3;
				prev_pink_state = pink_state;
				}
				else if(((map[pinkghost.playery/10][(pinkghost.playerx+10)/10]==5)||(map[pinkghost.playery/10][(pinkghost.playerx+10)/10]==7)||(map[pinkghost.playery/10][(pinkghost.playerx+10)/10]==4)||(map[pinkghost.playery/10][(pinkghost.playerx+10)/10]==8))&&(prev_pink_state!=2)){
				pink_state = 1;
				prev_pink_state = pink_state;
				}
			}
			else if(target_pink.pacidx_y>pinkghost.playeridx_y){
				if(((map[(pinkghost.playery+10)/10][pinkghost.playerx/10]==5)||(map[(pinkghost.playery+10)/10][(pinkghost.playerx)/10]==7)||(map[(pinkghost.playery+10)/10][pinkghost.playerx/10]==4)||(map[(pinkghost.playery+10)/10][(pinkghost.playerx)/10]==8)||(map[(pinkghost.playery+10)/10][(pinkghost.playerx)/10]==8))&&(prev_pink_state!=4)){
				pink_state = 3;
				prev_pink_state = pink_state;
				}
				else if(((map[pinkghost.playery/10][(pinkghost.playerx-10)/10]==5)||(map[pinkghost.playery/10][(pinkghost.playerx-10)/10]==7)||(map[pinkghost.playery/10][(pinkghost.playerx-10)/10]==4)||(map[pinkghost.playery/10][(pinkghost.playerx-10)/10]==8)||(map[pinkghost.playery/10][(pinkghost.playerx-10)/10]==6))&&(prev_pink_state!=1)){
				pink_state = 2;
				prev_pink_state = pink_state;
				}
				else if(((map[(pinkghost.playery-10)/10][pinkghost.playerx/10]==5)||(map[(pinkghost.playery-10)/10][(pinkghost.playerx)/10]==7)||(map[(pinkghost.playery-10)/10][(pinkghost.playerx)/10]==4)||(map[(pinkghost.playery-10)/10][(pinkghost.playerx)/10]==8)||(map[(pinkghost.playery-10)/10][(pinkghost.playerx)/10]==6))&&(prev_pink_state!=3)){
				pink_state = 4;
				prev_pink_state = pink_state;
				}
				else if(((map[pinkghost.playery/10][(pinkghost.playerx+10)/10]==5)||(map[pinkghost.playery/10][(pinkghost.playerx+10)/10]==7)||(map[pinkghost.playery/10][(pinkghost.playerx+10)/10]==4)||(map[pinkghost.playery/10][(pinkghost.playerx+10)/10]==8)||(map[pinkghost.playery/10][(pinkghost.playerx+10)/10]==6))&&(prev_pink_state!=2)){
				pink_state = 1;
				prev_pink_state = pink_state;
			 	}
			}
			else if(target_pink.pacidx_y==pinkghost.playeridx_y){
				if(((map[(pinkghost.playery-10)/10][pinkghost.playerx/10]==5)||(map[(pinkghost.playery-10)/10][(pinkghost.playerx)/10]==7)||(map[(pinkghost.playery-10)/10][(pinkghost.playerx)/10]==4)||(map[(pinkghost.playery-10)/10][(pinkghost.playerx)/10]==8)||(map[(pinkghost.playery-10)/10][(pinkghost.playerx)/10]==6))&&(prev_pink_state!=3)){
				pink_state = 4;
				prev_pink_state = pink_state;
				}
				else if(((map[pinkghost.playery/10][(pinkghost.playerx-10)/10]==5)||(map[pinkghost.playery/10][(pinkghost.playerx-10)/10]==7)||(map[pinkghost.playery/10][(pinkghost.playerx-10)/10]==4)||(map[pinkghost.playery/10][(pinkghost.playerx-10)/10]==8)||(map[pinkghost.playery/10][(pinkghost.playerx-10)/10]==6))&&(prev_pink_state!=1)){
				pink_state = 2;
				prev_pink_state = pink_state;
				}
				else if(((map[pinkghost.playery/10][(pinkghost.playerx+10)/10]==5)||(map[pinkghost.playery/10][(pinkghost.playerx+10)/10]==7)||(map[pinkghost.playery/10][(pinkghost.playerx+10)/10]==4)||(map[pinkghost.playery/10][(pinkghost.playerx+10)/10]==8)||(map[pinkghost.playery/10][(pinkghost.playerx+10)/10]==6))&&(prev_pink_state!=2)){
				pink_state = 1;
				prev_pink_state = pink_state;
				}
				else if(((map[(pinkghost.playery+10)/10][pinkghost.playerx/10]==5)||(map[(pinkghost.playery+10)/10][(pinkghost.playerx)/10]==7)||(map[(pinkghost.playery+10)/10][pinkghost.playerx/10]==4)||(map[(pinkghost.playery+10)/10][(pinkghost.playerx)/10]==8)||(map[(pinkghost.playery+10)/10][(pinkghost.playerx)/10]==8))&&(prev_pink_state!=4)){
				pink_state = 3;
				prev_pink_state = pink_state;
				}
			}
		}
	}
	}
	}
}

void pinkmove(){
	if(pink_state==1){	
		if((map[pinkghost.playery/10][(pinkghost.playerx+10)/10]==5)||(map[pinkghost.playery/10][(pinkghost.playerx+10)/10]==7)||(map[pinkghost.playery/10][(pinkghost.playerx+10)/10]==4)||(map[pinkghost.playery/10][(pinkghost.playerx+10)/10]==8)||(map[pinkghost.playery/10][(pinkghost.playerx+10)/10]==6)){
		pinkghost.pic_x += 10;
		pinkghost.next_x=pinkghost.playerx+10;
		pinkghost.next_y=pinkghost.playery;
		}	
		else if((map[pinkghost.playery/10][(pinkghost.playerx+10)/10]==9)){
		pinkghost.pic_x += 10;
		pinkghost.next_x=pinkghost.playerx+10;
		pinkghost.next_y=pinkghost.playery;
		}
	}
	if(pink_state==2){
		if((map[pinkghost.playery/10][(pinkghost.playerx-10)/10]==5)||(map[pinkghost.playery/10][(pinkghost.playerx-10)/10]==7)||(map[pinkghost.playery/10][(pinkghost.playerx-10)/10]==4)||(map[pinkghost.playery/10][(pinkghost.playerx-10)/10]==8||(map[pinkghost.playery/10][(pinkghost.playerx-10)/10]==6))){
		pinkghost.pic_x -= 10;
		pinkghost.next_x=pinkghost.playerx-10;
		pinkghost.next_y=pinkghost.playery;
		}	

	}
	if(pink_state==3){
		if((map[(pinkghost.playery+10)/10][pinkghost.playerx/10]==5)||(map[(pinkghost.playery+10)/10][(pinkghost.playerx)/10]==7)||map[(pinkghost.playery+10)/10][pinkghost.playerx/10]==4||(map[(pinkghost.playery+10)/10][(pinkghost.playerx)/10]==8)||(map[(pinkghost.playery+10)/10][(pinkghost.playerx)/10]==6)){
		pinkghost.pic_y += 10;
		pinkghost.next_x=pinkghost.playerx;
		pinkghost.next_y=pinkghost.playery+10;
		}
		else if((map[(pinkghost.playery+10)/10][pinkghost.playerx/10]==9)){
		pinkghost.pic_y += 10;
		pinkghost.next_x=pinkghost.playerx;
		pinkghost.next_y=pinkghost.playery+10;
		}
	}
	if(pink_state==4){
		if((map[(pinkghost.playery-10)/10][pinkghost.playerx/10]==5)||(map[(pinkghost.playery-10)/10][(pinkghost.playerx)/10]==7)||(map[(pinkghost.playery-10)/10][(pinkghost.playerx)/10]==4)||(map[(pinkghost.playery-10)/10][(pinkghost.playerx)/10]==8)||(map[(pinkghost.playery-10)/10][(pinkghost.playerx)/10]==6)){
		pinkghost.pic_y -= 10;
		pinkghost.next_x=pinkghost.playerx;
		pinkghost.next_y=pinkghost.playery-10;
		}
		else if((map[(pinkghost.playery-10)/10][pinkghost.playerx/10]==9)){
		pinkghost.pic_y -= 10;
		pinkghost.next_x=pinkghost.playerx;
		pinkghost.next_y=pinkghost.playery-10;
		}
	}
	pinkghost.playerx = pinkghost.pic_x + 25;
	pinkghost.playery = pinkghost.pic_y + 25;
}


void orangewalk(){

if(dead==0){
	if(orangeable==0){
		if(target_orange.reached==0){
		target_orange.pac_x=300+25;
		target_orange.pac_y=200+25;
		target_orange.reached=1;
		}
	if((orangeghost.pic_x==300&&orangeghost.pic_y==200&&target_orange.reached==1)){
		target_orange.pac_x=50+25;
		target_orange.pac_y=100+25;
		target_orange.reached=2;

	}
	if((orangeghost.pic_x==50&&orangeghost.pic_y==100&&target_orange.reached==2)){
			orangeable=1;
			target_orange.reached=0;

	}
	}
	else if(orangeable==1){
		if(target_orange.reached==0){
		target_orange.pac_x=1350+25;
		target_orange.pac_y=700+25;
		target_orange.reached=1;
		}
	if((orangeghost.pic_x==1350&&orangeghost.pic_y==700&&target_orange.reached==1)){
		target_orange.pac_x=1600+25;
		target_orange.pac_y=800+25;
		target_orange.reached=2;

	}
		if((orangeghost.pic_x==1600&&orangeghost.pic_y==800&&target_orange.reached==2)){
			orangeable=2;
			target_orange.reached=0;

		}
	}
	else if(orangeable==2){
		if(target_orange.reached==0){
	target_orange.pac_x=300+25;
	target_orange.pac_y=700+25;
	target_orange.reached=1;
		}
	if((orangeghost.pic_x==300&&orangeghost.pic_y==700&&target_orange.reached==1)){
		target_orange.pac_x=50+25;
		target_orange.pac_y=800+25;
		target_orange.reached=2;

	}
		if((orangeghost.pic_x==50&&orangeghost.pic_y==800&&target_orange.reached==2)){
			orangeable=3;
			target_orange.reached=0;
		// printf("orange chasing you\n");

		}
	}

	else{
	target_orange.pac_x=pacman.prev_x-100;
	target_orange.pac_y=pacman.prev_y-100;
	}
	orangeghost.playeridx_x=orangeghost.playerx/10;
	orangeghost.playeridx_y=orangeghost.playery/10;
	if(map[orangeghost.playeridx_y][orangeghost.playeridx_x]==7||(map[orangeghost.playeridx_y][orangeghost.playeridx_x]==4)||(map[orangeghost.playeridx_y][orangeghost.playeridx_x]==6)){
	target_orange.pacidx_x=target_orange.pac_x/10;
	target_orange.pacidx_y=target_orange.pac_y/10;
	}


	if(state!=0){
	if((map[(orangeghost.playery)/10][(orangeghost.playerx)/10]==7)||(map[(orangeghost.playery)/10][(orangeghost.playerx)/10]==4)||(map[orangeghost.playeridx_y][orangeghost.playeridx_x]==6)){
		if(target_orange.pacidx_x<orangeghost.playeridx_x){
			if(target_orange.pacidx_y<orangeghost.playeridx_y){
				if(((map[orangeghost.playery/10][(orangeghost.playerx-10)/10]==5)||(map[orangeghost.playery/10][(orangeghost.playerx-10)/10]==7)||(map[orangeghost.playery/10][(orangeghost.playerx-10)/10]==4)||(map[orangeghost.playery/10][(orangeghost.playerx-10)/10]==8)||(map[orangeghost.playery/10][(orangeghost.playerx-10)/10]==6))&&(prev_orange_state!=1)){
				orange_state = 2;
				prev_orange_state = orange_state;
				}
				else if(((map[(orangeghost.playery-10)/10][orangeghost.playerx/10]==5)||(map[(orangeghost.playery-10)/10][(orangeghost.playerx)/10]==7)||(map[(orangeghost.playery-10)/10][(orangeghost.playerx)/10]==4)||(map[(orangeghost.playery-10)/10][(orangeghost.playerx)/10]==8)||(map[(orangeghost.playery-10)/10][(orangeghost.playerx)/10]==6))&&(prev_orange_state!=3)){
				orange_state = 4;
				prev_orange_state = orange_state;
				}
				else if(((map[orangeghost.playery/10][(orangeghost.playerx+10)/10]==5)||(map[orangeghost.playery/10][(orangeghost.playerx+10)/10]==7)||(map[orangeghost.playery/10][(orangeghost.playerx+10)/10]==4)||(map[orangeghost.playery/10][(orangeghost.playerx+10)/10]==8)||(map[orangeghost.playery/10][(orangeghost.playerx+10)/10]==6))&&(prev_orange_state!=2)){
				orange_state = 1;
				prev_orange_state = orange_state;
				}
				else if(((map[(orangeghost.playery+10)/10][orangeghost.playerx/10]==5)||(map[(orangeghost.playery+10)/10][(orangeghost.playerx)/10]==7)||(map[(orangeghost.playery+10)/10][orangeghost.playerx/10]==4)||(map[(orangeghost.playery+10)/10][(orangeghost.playerx)/10]==8)||(map[(orangeghost.playery+10)/10][(orangeghost.playerx)/10]==6))&&(prev_orange_state!=4)){
				orange_state = 3;
				prev_orange_state = orange_state;
				}
			}
			else if(target_orange.pacidx_y>orangeghost.playeridx_y){
				if(((map[orangeghost.playery/10][(orangeghost.playerx-10)/10]==5)||(map[orangeghost.playery/10][(orangeghost.playerx-10)/10]==7)||(map[orangeghost.playery/10][(orangeghost.playerx-10)/10]==4)||(map[orangeghost.playery/10][(orangeghost.playerx-10)/10]==8||(map[orangeghost.playery/10][(orangeghost.playerx-10)/10]==6)))&&(prev_orange_state!=1)){
				orange_state = 2;
				prev_orange_state = orange_state;
				}
				else if(((map[(orangeghost.playery+10)/10][orangeghost.playerx/10]==5)||(map[(orangeghost.playery+10)/10][(orangeghost.playerx)/10]==7)||(map[(orangeghost.playery+10)/10][orangeghost.playerx/10]==4)||(map[(orangeghost.playery+10)/10][(orangeghost.playerx)/10]==8)||(map[(orangeghost.playery+10)/10][(orangeghost.playerx)/10]==6))&&(prev_orange_state!=4)){
				orange_state = 3;
				prev_orange_state = orange_state;
				}
				else if(((map[orangeghost.playery/10][(orangeghost.playerx+10)/10]==5)||(map[orangeghost.playery/10][(orangeghost.playerx+10)/10]==7)||(map[orangeghost.playery/10][(orangeghost.playerx+10)/10]==4)||(map[orangeghost.playery/10][(orangeghost.playerx+10)/10]==8)||(map[orangeghost.playery/10][(orangeghost.playerx+10)/10]==6))&&(prev_orange_state!=2)){
				orange_state = 1;
				prev_orange_state = orange_state;
			 	}
				else if(((map[(orangeghost.playery-10)/10][orangeghost.playerx/10]==5)||(map[(orangeghost.playery-10)/10][(orangeghost.playerx)/10]==7)||(map[(orangeghost.playery-10)/10][(orangeghost.playerx)/10]==4)||(map[(orangeghost.playery-10)/10][(orangeghost.playerx)/10]==8)||(map[(orangeghost.playery-10)/10][(orangeghost.playerx)/10]==6))&&(prev_orange_state!=3)){
				orange_state = 4;
				prev_orange_state = orange_state;
				}
			}
			else if(target_orange.pacidx_y==orangeghost.playeridx_y){
				if(((map[orangeghost.playery/10][(orangeghost.playerx-10)/10]==5)||(map[orangeghost.playery/10][(orangeghost.playerx-10)/10]==7)||(map[orangeghost.playery/10][(orangeghost.playerx-10)/10]==4)||(map[orangeghost.playery/10][(orangeghost.playerx-10)/10]==8)||(map[orangeghost.playery/10][(orangeghost.playerx-10)/10]==6))&&(prev_orange_state!=1)){
				orange_state = 2;
				prev_orange_state = orange_state;
				}
				else if(((map[(orangeghost.playery-10)/10][orangeghost.playerx/10]==5)||(map[(orangeghost.playery-10)/10][(orangeghost.playerx)/10]==7)||(map[(orangeghost.playery-10)/10][(orangeghost.playerx)/10]==4)||(map[(orangeghost.playery-10)/10][(orangeghost.playerx)/10]==8)||(map[(orangeghost.playery-10)/10][(orangeghost.playerx)/10]==6))&&(prev_orange_state!=3)){
				orange_state = 4;
				prev_orange_state = orange_state;
				}
				else if(((map[(orangeghost.playery+10)/10][orangeghost.playerx/10]==5)||(map[(orangeghost.playery+10)/10][(orangeghost.playerx)/10]==7)||(map[(orangeghost.playery+10)/10][orangeghost.playerx/10]==4)||(map[(orangeghost.playery+10)/10][(orangeghost.playerx)/10]==8)||(map[(orangeghost.playery+10)/10][(orangeghost.playerx)/10]==6))&&(prev_orange_state!=4)){
				orange_state = 3;
				prev_orange_state = orange_state;
				}
				else if(((map[orangeghost.playery/10][(orangeghost.playerx+10)/10]==5)||(map[orangeghost.playery/10][(orangeghost.playerx+10)/10]==7)||(map[orangeghost.playery/10][(orangeghost.playerx+10)/10]==4)||(map[orangeghost.playery/10][(orangeghost.playerx+10)/10]==8)||(map[orangeghost.playery/10][(orangeghost.playerx+10)/10]==6))&&(prev_orange_state!=2)){
				orange_state = 1;
				prev_orange_state = orange_state;
				}
			}
		}

		if(target_orange.pacidx_x>orangeghost.playeridx_x){
			if(target_orange.pacidx_y<orangeghost.playeridx_y){
				if(((map[orangeghost.playery/10][(orangeghost.playerx+10)/10]==5)||(map[orangeghost.playery/10][(orangeghost.playerx+10)/10]==7)||(map[orangeghost.playery/10][(orangeghost.playerx+10)/10]==4)||(map[orangeghost.playery/10][(orangeghost.playerx+10)/10]==8)||(map[orangeghost.playery/10][(orangeghost.playerx+10)/10]==6))&&(prev_orange_state!=2)){
				orange_state = 1;
				prev_orange_state = orange_state;
				}
				else if(((map[(orangeghost.playery-10)/10][orangeghost.playerx/10]==5)||(map[(orangeghost.playery-10)/10][(orangeghost.playerx)/10]==7)||(map[(orangeghost.playery-10)/10][(orangeghost.playerx)/10]==4)||(map[(orangeghost.playery-10)/10][(orangeghost.playerx)/10]==8)||(map[(orangeghost.playery-10)/10][(orangeghost.playerx)/10]==6))&&(prev_orange_state!=3)){
				orange_state = 4;
				prev_orange_state = orange_state;
				}
				
				else if((((map[(orangeghost.playery+10)/10][orangeghost.playerx/10]==5)||(map[(orangeghost.playery+10)/10][(orangeghost.playerx)/10]==7)||map[(orangeghost.playery+10)/10][orangeghost.playerx/10]==4)||(map[(orangeghost.playery+10)/10][(orangeghost.playerx)/10]==8)||(map[(orangeghost.playery+10)/10][(orangeghost.playerx)/10]==6))&&(prev_orange_state!=4)){
				orange_state = 3;
				prev_orange_state = orange_state;
				}
				else if(((map[orangeghost.playery/10][(orangeghost.playerx-10)/10]==5)||(map[orangeghost.playery/10][(orangeghost.playerx-10)/10]==7)||(map[orangeghost.playery/10][(orangeghost.playerx-10)/10]==4)||(map[orangeghost.playery/10][(orangeghost.playerx-10)/10]==8)||(map[orangeghost.playery/10][(orangeghost.playerx-10)/10]==6))&&(prev_orange_state!=1)){
				orange_state = 2;
				prev_orange_state = orange_state;
				}
			}

			else if(target_orange.pacidx_y>orangeghost.playeridx_y){
				if(((map[(orangeghost.playery+10)/10][orangeghost.playerx/10]==5)||(map[(orangeghost.playery+10)/10][(orangeghost.playerx)/10]==7)||map[(orangeghost.playery+10)/10][orangeghost.playerx/10]==4||(map[(orangeghost.playery+10)/10][(orangeghost.playerx)/10]==8)||(map[(orangeghost.playery+10)/10][(orangeghost.playerx)/10]==6))&&(prev_orange_state!=4)){
				orange_state = 3;
				prev_orange_state = orange_state;
				}
				else if(((map[orangeghost.playery/10][(orangeghost.playerx+10)/10]==5)||(map[orangeghost.playery/10][(orangeghost.playerx+10)/10]==7)||(map[orangeghost.playery/10][(orangeghost.playerx+10)/10]==4)||(map[orangeghost.playery/10][(orangeghost.playerx+10)/10]==8)||(map[orangeghost.playery/10][(orangeghost.playerx+10)/10]==6))&&(prev_orange_state!=2)){
				orange_state = 1;
				prev_orange_state = orange_state;
				}
				else if(((map[orangeghost.playery/10][(orangeghost.playerx-10)/10]==5)||(map[orangeghost.playery/10][(orangeghost.playerx-10)/10]==7)||(map[orangeghost.playery/10][(orangeghost.playerx-10)/10]==4)||(map[orangeghost.playery/10][(orangeghost.playerx-10)/10]==8)||(map[orangeghost.playery/10][(orangeghost.playerx-10)/10]==6))&&(prev_orange_state!=1)){
				orange_state = 2;
				prev_orange_state = orange_state;	
				}
				else if(((map[(orangeghost.playery-10)/10][orangeghost.playerx/10]==5)||(map[(orangeghost.playery-10)/10][(orangeghost.playerx)/10]==7)||(map[(orangeghost.playery-10)/10][(orangeghost.playerx)/10]==4)||(map[(orangeghost.playery-10)/10][(orangeghost.playerx)/10]==8)||(map[(orangeghost.playery-10)/10][(orangeghost.playerx)/10]==6))&&(prev_orange_state!=3)){
				orange_state = 4;
				prev_orange_state = orange_state;
				}	
			}

			else if(target_orange.pacidx_y==orangeghost.playeridx_y){
				if(((map[orangeghost.playery/10][(orangeghost.playerx+10)/10]==5)||(map[orangeghost.playery/10][(orangeghost.playerx+10)/10]==7)||(map[orangeghost.playery/10][(orangeghost.playerx+10)/10]==4)||(map[orangeghost.playery/10][(orangeghost.playerx+10)/10]==8)||(map[orangeghost.playery/10][(orangeghost.playerx+10)/10]==6))&&(prev_orange_state!=2)){
				orange_state = 1;
				prev_orange_state = orange_state;
				}
				else if(((map[(orangeghost.playery-10)/10][orangeghost.playerx/10]==5)||(map[(orangeghost.playery-10)/10][(orangeghost.playerx)/10]==7)||(map[(orangeghost.playery-10)/10][(orangeghost.playerx)/10]==4)||(map[(orangeghost.playery-10)/10][(orangeghost.playerx)/10]==8)||(map[(orangeghost.playery-10)/10][(orangeghost.playerx)/10]==6))&&(prev_orange_state!=3)){
				orange_state = 4;
				prev_orange_state = orange_state;
				}
				else if(((map[(orangeghost.playery+10)/10][orangeghost.playerx/10]==5)||(map[(orangeghost.playery+10)/10][(orangeghost.playerx)/10]==7)||(map[(orangeghost.playery+10)/10][orangeghost.playerx/10]==4)||(map[(orangeghost.playery+10)/10][(orangeghost.playerx)/10]==8)||(map[(orangeghost.playery+10)/10][(orangeghost.playerx)/10]==6))&&(prev_orange_state!=4)){
				orange_state = 3;
				prev_orange_state = orange_state;
				}
				else if(((map[orangeghost.playery/10][(orangeghost.playerx-10)/10]==5)||(map[orangeghost.playery/10][(orangeghost.playerx-10)/10]==7)||(map[orangeghost.playery/10][(orangeghost.playerx-10)/10]==4)||(map[orangeghost.playery/10][(orangeghost.playerx-10)/10]==8)||(map[orangeghost.playery/10][(orangeghost.playerx-10)/10]==6))&&(prev_orange_state!=1)){
				orange_state = 2;
				prev_orange_state = orange_state;
				}
			}	
		}

		if(target_orange.pacidx_x==orangeghost.playeridx_x){
			if(target_orange.pacidx_y<orangeghost.playeridx_y){
				if(((map[(orangeghost.playery-10)/10][orangeghost.playerx/10]==5)||(map[(orangeghost.playery-10)/10][(orangeghost.playerx)/10]==7)||(map[(orangeghost.playery-10)/10][(orangeghost.playerx)/10]==4)||(map[(orangeghost.playery-10)/10][(orangeghost.playerx)/10]==8)||(map[(orangeghost.playery-10)/10][(orangeghost.playerx)/10]==6))&&(prev_orange_state!=3)){
				orange_state = 4;
				prev_orange_state = orange_state;
				}
				else if(((map[orangeghost.playery/10][(orangeghost.playerx-10)/10]==5)||(map[orangeghost.playery/10][(orangeghost.playerx-10)/10]==7)||(map[orangeghost.playery/10][(orangeghost.playerx-10)/10]==4)||(map[orangeghost.playery/10][(orangeghost.playerx-10)/10]==8)||(map[orangeghost.playery/10][(orangeghost.playerx-10)/10]==6))&&(prev_orange_state!=1)){
				orange_state = 2;
				prev_orange_state = orange_state;
				}
				else if(((map[orangeghost.playery/10][(orangeghost.playerx+10)/10]==5)||(map[orangeghost.playery/10][(orangeghost.playerx+10)/10]==7)||(map[orangeghost.playery/10][(orangeghost.playerx+10)/10]==4)||(map[orangeghost.playery/10][(orangeghost.playerx+10)/10]==8)||(map[orangeghost.playery/10][(orangeghost.playerx+10)/10]==6))&&(prev_orange_state!=2)){
				orange_state = 1;
				prev_orange_state = orange_state;
				}
				else if(((map[(orangeghost.playery+10)/10][orangeghost.playerx/10]==5)||(map[(orangeghost.playery+10)/10][(orangeghost.playerx)/10]==7)||(map[(orangeghost.playery+10)/10][orangeghost.playerx/10]==4)||(map[(orangeghost.playery+10)/10][(orangeghost.playerx)/10]==8)||(map[(orangeghost.playery+10)/10][(orangeghost.playerx)/10]==6))&&(prev_orange_state!=4)){
				orange_state = 3;
				prev_orange_state = orange_state;
				}
			}
			else if(target_orange.pacidx_y>orangeghost.playeridx_y){
				if(((map[(orangeghost.playery+10)/10][orangeghost.playerx/10]==5)||(map[(orangeghost.playery+10)/10][(orangeghost.playerx)/10]==7)||(map[(orangeghost.playery+10)/10][orangeghost.playerx/10]==4)||(map[(orangeghost.playery+10)/10][(orangeghost.playerx)/10]==8)||(map[(orangeghost.playery+10)/10][(orangeghost.playerx)/10]==6))&&(prev_orange_state!=4)){
				orange_state = 3;
				prev_orange_state = orange_state;
				}
				else if(((map[orangeghost.playery/10][(orangeghost.playerx-10)/10]==5)||(map[orangeghost.playery/10][(orangeghost.playerx-10)/10]==7)||(map[orangeghost.playery/10][(orangeghost.playerx-10)/10]==4)||(map[orangeghost.playery/10][(orangeghost.playerx-10)/10]==8||(map[orangeghost.playery/10][(orangeghost.playerx-10)/10]==6)))&&(prev_orange_state!=1)){
				orange_state = 2;
				prev_orange_state = orange_state;
				}
				else if(((map[orangeghost.playery/10][(orangeghost.playerx+10)/10]==5)||(map[orangeghost.playery/10][(orangeghost.playerx+10)/10]==7)||(map[orangeghost.playery/10][(orangeghost.playerx+10)/10]==4)||(map[orangeghost.playery/10][(orangeghost.playerx+10)/10]==8)||(map[orangeghost.playery/10][(orangeghost.playerx+10)/10]==6))&&(prev_orange_state!=2)){
				orange_state = 1;
				prev_orange_state = orange_state;
			 	}
				else if(((map[(orangeghost.playery-10)/10][orangeghost.playerx/10]==5)||(map[(orangeghost.playery-10)/10][(orangeghost.playerx)/10]==7)||(map[(orangeghost.playery-10)/10][(orangeghost.playerx)/10]==4)||(map[(orangeghost.playery-10)/10][(orangeghost.playerx)/10]==8)||(map[(orangeghost.playery-10)/10][(orangeghost.playerx)/10]==6))&&(prev_orange_state!=3)){
				orange_state = 4;
				prev_orange_state = orange_state;
				}
			}
			else if(target_orange.pacidx_y==orangeghost.playeridx_y){
				if(((map[(orangeghost.playery-10)/10][orangeghost.playerx/10]==5)||(map[(orangeghost.playery-10)/10][(orangeghost.playerx)/10]==7)||(map[(orangeghost.playery-10)/10][(orangeghost.playerx)/10]==4)||(map[(orangeghost.playery-10)/10][(orangeghost.playerx)/10]==8)||(map[(orangeghost.playery-10)/10][(orangeghost.playerx)/10]==6))&&(prev_orange_state!=3)){
				orange_state = 4;
				prev_orange_state = orange_state;
				}
				else if(((map[orangeghost.playery/10][(orangeghost.playerx-10)/10]==5)||(map[orangeghost.playery/10][(orangeghost.playerx-10)/10]==7)||(map[orangeghost.playery/10][(orangeghost.playerx-10)/10]==4)||(map[orangeghost.playery/10][(orangeghost.playerx-10)/10]==8)||(map[orangeghost.playery/10][(orangeghost.playerx-10)/10]==6))&&(prev_orange_state!=1)){
				orange_state = 2;
				prev_orange_state = orange_state;
				}
				else if(((map[(orangeghost.playery+10)/10][orangeghost.playerx/10]==5)||(map[(orangeghost.playery+10)/10][(orangeghost.playerx)/10]==7)||(map[(orangeghost.playery+10)/10][orangeghost.playerx/10]==4)||(map[(orangeghost.playery+10)/10][(orangeghost.playerx)/10]==8)||(map[(orangeghost.playery+10)/10][(orangeghost.playerx)/10]==6))&&(prev_orange_state!=4)){
				orange_state = 3;
				prev_orange_state = orange_state;
				}
				else if(((map[orangeghost.playery/10][(orangeghost.playerx+10)/10]==5)||(map[orangeghost.playery/10][(orangeghost.playerx+10)/10]==7)||(map[orangeghost.playery/10][(orangeghost.playerx+10)/10]==4)||(map[orangeghost.playery/10][(orangeghost.playerx+10)/10]==8)||(map[orangeghost.playery/10][(orangeghost.playerx+10)/10]==6))&&(prev_orange_state!=2)){
				orange_state = 1;
				prev_orange_state = orange_state;
				}
			}
		}
	}
	}
	}
}

void orangemove(){
	if(orange_state==1){	
		if((map[orangeghost.playery/10][(orangeghost.playerx+10)/10]==5)||(map[orangeghost.playery/10][(orangeghost.playerx+10)/10]==7)||(map[orangeghost.playery/10][(orangeghost.playerx+10)/10]==4)||(map[orangeghost.playery/10][(orangeghost.playerx+10)/10]==8)||(map[orangeghost.playery/10][(orangeghost.playerx+10)/10]==6)){
		orangeghost.pic_x += 10;
		orangeghost.next_x=orangeghost.playerx+10;
		orangeghost.next_y=orangeghost.playery;
		}	
		else if((map[orangeghost.playery/10][(orangeghost.playerx+10)/10]==9)){
		orangeghost.pic_x += 10;
		orangeghost.next_x=orangeghost.playerx+10;
		orangeghost.next_y=orangeghost.playery;
		}
	}
	if(orange_state==2){
		if((map[orangeghost.playery/10][(orangeghost.playerx-10)/10]==5)||(map[orangeghost.playery/10][(orangeghost.playerx-10)/10]==7)||(map[orangeghost.playery/10][(orangeghost.playerx-10)/10]==4)||(map[orangeghost.playery/10][(orangeghost.playerx-10)/10]==8)||(map[orangeghost.playery/10][(orangeghost.playerx-10)/10]==6)){
		orangeghost.pic_x -= 10;
		orangeghost.next_x=orangeghost.playerx-10;
		orangeghost.next_y=orangeghost.playery;
		}	

	}
	if(orange_state==3){
		if((map[(orangeghost.playery+10)/10][orangeghost.playerx/10]==5)||(map[(orangeghost.playery+10)/10][(orangeghost.playerx)/10]==7)||map[(orangeghost.playery+10)/10][orangeghost.playerx/10]==4||(map[(orangeghost.playery+10)/10][(orangeghost.playerx)/10]==8)||(map[(orangeghost.playery+10)/10][(orangeghost.playerx)/10]==6)){
		orangeghost.pic_y += 10;
		orangeghost.next_x=orangeghost.playerx;
		orangeghost.next_y=orangeghost.playery+10;
		}
		else if((map[(orangeghost.playery+10)/10][orangeghost.playerx/10]==9)){
		orangeghost.pic_y += 10;
		orangeghost.next_x=orangeghost.playerx;
		orangeghost.next_y=orangeghost.playery+10;
		}
	}
	if(orange_state==4){
		if((map[(orangeghost.playery-10)/10][orangeghost.playerx/10]==5)||(map[(orangeghost.playery-10)/10][(orangeghost.playerx)/10]==7)||(map[(orangeghost.playery-10)/10][(orangeghost.playerx)/10]==4)||(map[(orangeghost.playery-10)/10][(orangeghost.playerx)/10]==8)||(map[(orangeghost.playery-10)/10][(orangeghost.playerx)/10]==6)){
		orangeghost.pic_y -= 10;
		orangeghost.next_x=orangeghost.playerx;
		orangeghost.next_y=orangeghost.playery-10;
		}
		else if((map[(orangeghost.playery-10)/10][orangeghost.playerx/10]==9)){
		orangeghost.pic_y -= 10;
		orangeghost.next_x=orangeghost.playerx;
		orangeghost.next_y=orangeghost.playery-10;
		}
	}
	orangeghost.playerx = orangeghost.pic_x + 25;
	orangeghost.playery = orangeghost.pic_y + 25;
}

void ghostwalk(){
	redwalk();
	bluewalk();
	pinkwalk();
	orangewalk();
}

void ghostmove(){
	redmove();
	bluemove();
	if(blueable!=0)
	pinkmove();
	if(blueable!=0)
	orangemove();
}

void disable(){
	redable=9;
	target_red.reached=0;
	if(blueable==2){
		target_pink.reached=0;
		target_orange.reached=0;
		target_pink.reached=0;
		blueable=1;
		pinkable=1;
		orangeable=2;
	}
	// printf("Disabled through disabled\n");
}


void death(){
	
	if(dead==0){
	if(redghost.pacmanbuff==0){
		if(((redghost.pic_y-pacman.pic_y<=25)&&(redghost.pic_x-pacman.pic_x<=25))&&(((redghost.pic_x-pacman.pic_x>=0))&&(redghost.pic_y-pacman.pic_y>=0))){
			//printf("red");
			red_state = 0;
			blue_state = 0;
			pink_state = 0;
			orange_state = 0;
			pacman.next_move=0;
			redghost.next_move=0;
			pinkghost.next_move=0;
			orangeghost.next_move=0;
			blueghost.next_move=0;
			state = 0;
			if(pacman_menu.sound==1)
			PlaySound("music//pacman_death.wav", NULL, SND_LOOP | SND_ASYNC);
			timerRunning = 1;
        	timerStartTime = glutGet(GLUT_ELAPSED_TIME);
			dead=1; 
			health--;
		}
	}
	if(blueghost.pacmanbuff==0){
		if(((blueghost.pic_y-pacman.pic_y<=25)&&(blueghost.pic_x-pacman.pic_x<=25))&&(((blueghost.pic_x-pacman.pic_x>=0))&&(blueghost.pic_y-pacman.pic_y>=0))){
			//printf("blue");
			red_state = 0;
			blue_state = 0;
			pink_state = 0;
			orange_state = 0;
			pacman.next_move=0;
			redghost.next_move=0;
			pinkghost.next_move=0;
			orangeghost.next_move=0;
			blueghost.next_move=0;
			state = 0;
			if(pacman_menu.sound==1){
				PlaySound(0,0,0);
			PlaySound("music//pacman_death.wav", NULL, SND_LOOP | SND_ASYNC);
			}
			timerRunning = 1;
        	timerStartTime = glutGet(GLUT_ELAPSED_TIME); 
			dead = 1;
			health--;
		}
	}
	if(pinkghost.pacmanbuff==0){
		if(((pinkghost.pic_y-pacman.pic_y<=25)&&(pinkghost.pic_x-pacman.pic_x<=25))&&(((pinkghost.pic_x-pacman.pic_x>=0))&&(pinkghost.pic_y-pacman.pic_y>=0))){
			//printf("pink");
			red_state = 0;
			blue_state = 0;
			pink_state = 0;
			orange_state = 0;
			pacman.next_move=0;
			redghost.next_move=0;
			pinkghost.next_move=0;
			orangeghost.next_move=0;
			blueghost.next_move=0;
			state = 0;
			if(pacman_menu.sound==1)
			PlaySound("music//pacman_death.wav", NULL, SND_LOOP | SND_ASYNC);
			timerRunning = 1;
        	timerStartTime = glutGet(GLUT_ELAPSED_TIME); 
			dead=1;
			health--;
		}
	}
	if(orangeghost.pacmanbuff==0){
		if(((orangeghost.pic_y-pacman.pic_y<=25)&&(orangeghost.pic_x-pacman.pic_x<=25))&&(((orangeghost.pic_x-pacman.pic_x>=0))&&(orangeghost.pic_y-pacman.pic_y>=0))){
			//printf("orange");
			red_state = 0;
			blue_state = 0;
			pink_state = 0;
			orange_state = 0;
			pacman.next_move=0;
			redghost.next_move=0;
			pinkghost.next_move=0;
			orangeghost.next_move=0;
			blueghost.next_move=0;
			state = 0;
			if(pacman_menu.sound==1)
			PlaySound("music//pacman_death.wav", NULL, SND_LOOP | SND_ASYNC);
			timerRunning = 1;
        	timerStartTime = glutGet(GLUT_ELAPSED_TIME); 
			dead=1;
			health--;
		}
	}
	}
	if(redghost.pacmanbuff==1){
		if(((redghost.pic_y-pacman.pic_y<=25)&&(redghost.pic_x-pacman.pic_x<=25))&&(((redghost.pic_x-pacman.pic_x>=0))&&(redghost.pic_y-pacman.pic_y>=0))){
			if(pacman_menu.sound==1)
			PlaySound("music//pacman_eatghost.wav", NULL, SND_LOOP | SND_ASYNC);
			Sleep(1000);
			points+=400;
			red_state = 0;
			pacman.next_move=0;
			redghost.next_move=0;
			redghost.pic_x=810;
			redghost.pic_y=500;
			redghost.pacmanbuff=0;
			musicplay();
			}
	}

	if(blueghost.pacmanbuff==1){
		if(((blueghost.pic_y-pacman.pic_y<=25)&&(blueghost.pic_x-pacman.pic_x<=25))&&(((blueghost.pic_x-pacman.pic_x>=0))&&(blueghost.pic_y-pacman.pic_y>=0))){
			if(pacman_menu.sound==1)
			PlaySound("music//pacman_eatghost.wav", NULL, SND_LOOP | SND_ASYNC);
			Sleep(1000);
			points+=400;
			blue_state = 0;
			blueghost.next_move;
			pacman.next_move=0;
			blueghost.pic_x=810;
			blueghost.pic_y=600;
			blueghost.pacmanbuff=0;
			musicplay();
		}	
	}

	if(pinkghost.pacmanbuff==1){
		if(((pinkghost.pic_y-pacman.pic_y<=25)&&(pinkghost.pic_x-pacman.pic_x<=25))&&(((pinkghost.pic_x-pacman.pic_x>=0))&&(pinkghost.pic_y-pacman.pic_y>=0))){
			if(pacman_menu.sound==1)
			PlaySound("music//pacman_eatghost.wav", NULL, SND_LOOP | SND_ASYNC);
			Sleep(1000);
			points+=400;
			pink_state = 0;
			pacman.next_move=0;
			pinkghost.next_move=0;
			pinkghost.pic_x=810;
			pinkghost.pic_y=600;
			pinkghost.pacmanbuff=0;
			musicplay();

		}
	}

	if(orangeghost.pacmanbuff==1){
		if(((orangeghost.pic_y-pacman.pic_y<=25)&&(orangeghost.pic_x-pacman.pic_x<=25))&&(((orangeghost.pic_x-pacman.pic_x>=0))&&(orangeghost.pic_y-pacman.pic_y>=0))){
			if(pacman_menu.sound==1)
			PlaySound("music//pacman_eatghost.wav", NULL, SND_LOOP | SND_ASYNC);
			Sleep(1000);
			points+=400;
			orange_state = 0;
			pacman.next_move=0;
			orangeghost.next_move=0;
			orangeghost.pic_x=810;
			orangeghost.pic_y=500;
			orangeghost.pacmanbuff=0;
			musicplay();
			
		}		
	}
}

void pacmanbuffed(){
	if (timerActive1) {
        elapsedTime1 += 100; 
        if (elapsedTime1 >= 10000) {
			if(faster==0){
				if(dots<150){
					iPauseTimer(timerID3);
					iResumeTimer(timerID6);
					faster=1;
				}
			} 
            redghost.pacmanbuff=0;
			pinkghost.pacmanbuff=0;
			orangeghost.pacmanbuff=0;
			blueghost.pacmanbuff=0;
			recover=0;
			powerstatus=0;
            timerActive1 = 0;    
            iPauseTimer(timerID1);
			elapsedTime1 = 0; 
			musicplay();
        }
		if (elapsedTime1 >= 8000 && elapsedTime1 <= 10000) {
			recover = 1;
		}
    }
}
void scatter(){
	if(redghost.pacmanbuff==0&&pinkghost.pacmanbuff==0&&orangeghost.pacmanbuff==0&&blueghost.pacmanbuff==0){
		if(timerActive2){
			elapsedTime2 += 100; 
			if (elapsedTime2 >= 25000) { 
				disable();
				timerActive2 = 0;    
				iPauseTimer(timerID2);
				elapsedTime2 = 0; 
				tem=0;
			}
		}
	}
}

void pacmanghostwalk(){
	if(pacman_menu.startgame==1);
	pacmanmove();
	ghostwalk();


		if(a<44){
		loadingscrn = loading_screen[a];
		a = a + 1;
		}
		if(a==44){
			loading = 0;
			musicplay();
			loadingscrn = loading_screen[0];
			
			a=45;
		}
}

void again(){
		
	if(pacman_menu.startgame==0&&menu==0){
		pacman_menu.startgame=0;
		pacman_menu.leaderboard=0;
		pacman_menu.control=0;
		pacman_menu.sound=1;
		pacman_menu.aboutgame=0;
		musicplay();
		}
	if(pacman_menu.startgame==1){
		
		timerRunning=0;
		if(menu==1){
			faster=0;
			dots=0;
			mazeupdate();
			updatedots();
	//		printf("dots: %d\n", dots);
			target_blue.reached=0;
			target_red.reached=0;
			target_pink.reached=0;
			target_orange.reached=0;
			redable=0;
			blueable=0;
			orangeable=0;
			pinkable;
			health=3;
			chomp=0;
			len = 0;
			str1[0] = 0;
		}
		menu=9;
		state=0;
		pacman.next_move=0;
		pacman.pic_x=840;
		pacman.pic_y=350;
		redghost.pic_x=810;
		redghost.pic_y=500;
		blueghost.pic_x=810;
		blueghost.pic_y=600;
		pinkghost.pic_x=750;
		pinkghost.pic_y=600;
		orangeghost.pic_x=750;
		orangeghost.pic_y=500;
		red_state=0;
		orange_state=0;
		pink_state=0;
		blue_state=0;
		pacman.playerx = pacman.pic_x + 25;
		pacman.playery = pacman.pic_y + 25;
		redghost.playerx = redghost.pic_x + 25;
		redghost.playery = redghost.pic_y + 25;
		blueghost.playerx = blueghost.pic_x + 25;
		blueghost.playery = blueghost.pic_y + 25;
		pinkghost.playerx = pinkghost.pic_x + 25;
		pinkghost.playery = pinkghost.pic_y + 25;
		orangeghost.playerx = orangeghost.pic_x + 25;
		orangeghost.playery = orangeghost.pic_y + 25;
		
		redghost.pacmanbuff=0;
		blueghost.pacmanbuff=0;
		pinkghost.pacmanbuff=0;
		orangeghost.pacmanbuff=0;
		
		redghost.next_move=0;
		pinkghost.next_move=0;
		orangeghost.next_move=0;
		blueghost.next_move=0;

		target_red.reached=0;
		target_pink.reached=0;
		target_orange.reached=0;
		target_pink.reached=0;
		dead = 0;
		}
}



int main(){
	menuidx=0;
	pacman.pic_x=840;
		pacman.pic_y=350;
		redghost.pic_x=810;
		redghost.pic_y=500;
		blueghost.pic_x=810;
		blueghost.pic_y=600;
		pinkghost.pic_x=750;
		pinkghost.pic_y=600;
		orangeghost.pic_x=750;
		orangeghost.pic_y=500;

	PlaySound("music//pacman_intermission.wav", NULL, SND_LOOP | SND_ASYNC);
	
	red_walk = red_right[0];
	blue_walk = blue_right[0];
	pink_walk = pink_right[0];
	orange_walk = orange_right[0];
	pacman_walk = pacman_right[0];
	loadingscrn = loading_screen[0];

	again();
		for(i=0; i<18*5; i++){
			for(j=0; j<34*5; j++){
				map[i][j] = maze[i][j];
			}
		}
		timerID5 = iSetTimer(50, update_pacman_ghosts);
		timerID8 =	iSetTimer(50, pacmanghostwalk);
		iPauseTimer(timerID8);

		timerID9 =	iSetTimer(2000, clearstate);

		timerID6 = iSetTimer(47, ghostmove);
		iPauseTimer(timerID6);
		timerID3 = iSetTimer(50, ghostmove);
		iPauseTimer(timerID3);
		timerID4 = iSetTimer(100, ghostmove);
		iPauseTimer(timerID4);
		
		timerID10 = iSetTimer(20, death);
		iPauseTimer(timerID10);
		timerID1 = iSetTimer(100, pacmanbuffed); 
		iPauseTimer(timerID1);
		timerID2 = iSetTimer(100, scatter); 
		iPauseTimer(timerID2);
		
		loadingsgif();

		pacman_menu.startgame=0;
		pacman_menu.leaderboard=0;
		pacman_menu.control=0;
		pacman_menu.sound=1;
		pacman_menu.aboutgame=0;

	iInitialize(screenwidth, screenheight, "Pacman");
	
	return 0;
	}
