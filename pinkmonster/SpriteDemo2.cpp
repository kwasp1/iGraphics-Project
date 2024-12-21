/*
	author: S. M. Shahriar Nirjon
	last modified: August 8, 2008
*/
#include "iGraphics.h"
enum {IDLE, WALK, JUMP};
int pic_x, pic_y;
int idle_idx = 0;
int jump_idx = 0;
int walk_idx = 0;
int state = IDLE;
char monster_idle[4][100];
char monster_jump[8][100];
char monster_walk[6][100];
char* monster_image;

void populate_monster_images(){
    for(int i=0;i<4;i++){
        sprintf(monster_idle[i], "pinkmonster\\idleanim\\tile00%d.bmp", i);
    }
    for(int i=0;i<8;i++){
        sprintf(monster_jump[i], "pinkmonster\\jumpanim\\tile00%d.bmp", i);
    }
    for(int i=0;i<6;i++){
        sprintf(monster_walk[i], "pinkmonster\\walkanim\\tile00%d.bmp", i);
    }
    monster_image = monster_idle[0];
}


void update_monster(){
    switch(state){
        case IDLE:
            monster_image = monster_idle[idle_idx];
            idle_idx = (idle_idx + 1) % 4;
            break;
        case WALK:
            monster_image = monster_walk[walk_idx];
            walk_idx = (walk_idx + 1) % 6;
            break;
        case JUMP:
            monster_image = monster_jump[jump_idx];
            jump_idx = (jump_idx + 1) % 8;
            if(jump_idx == 0){
                state = IDLE;
            }
            break;
    }
}
/*
	function iDraw() is called again and again by the system.
*/
void iDraw()
{
	//place your drawing codes here

	iClear();
    iShowBMP(pic_x, pic_y, monster_image);
	// iShowBMP(pic_x, pic_y, "wheel.bmp");

}

/*
	function iMouseMove() is called when the user presses and drags the mouse.
	(mx, my) is the position where the mouse pointer is.
*/
void iMouseMove(int mx, int my)
{
	//place your codes here
}

/*
	function iMouse() is called when the user presses/releases the mouse.
	(mx, my) is the position where the mouse pointer is.
*/
void iMouse(int button, int state, int mx, int my)
{
	if(button == GLUT_LEFT_BUTTON && state == GLUT_DOWN)
	{
		//place your codes here
	}
	if(button == GLUT_RIGHT_BUTTON && state == GLUT_DOWN)
	{
		//place your codes here
	}
}

/*
	function iKeyboard() is called whenever the user hits a key in keyboard.
	key- holds the ASCII value of the key pressed.
*/
void iKeyboard(unsigned char key)
{
	if(key == 'x')
	{
		//do something with 'x'
		exit(0);
	}
	//place your codes for other keys here
}

/*
	function iSpecialKeyboard() is called whenver user hits special keys like-
	function keys, home, end, pg up, pg down, arraows etc. you have to use
	appropriate constants to detect them. A list is:
	GLUT_KEY_F1, GLUT_KEY_F2, GLUT_KEY_F3, GLUT_KEY_F4, GLUT_KEY_F5, GLUT_KEY_F6,
	GLUT_KEY_F7, GLUT_KEY_F8, GLUT_KEY_F9, GLUT_KEY_F10, GLUT_KEY_F11, GLUT_KEY_F12,
	GLUT_KEY_LEFT, GLUT_KEY_UP, GLUT_KEY_RIGHT, GLUT_KEY_DOWN, GLUT_KEY_PAGE UP,
	GLUT_KEY_PAGE DOWN, GLUT_KEY_HOME, GLUT_KEY_END, GLUT_KEY_INSERT
*/
void iSpecialKeyboard(unsigned char key)
{

	if(key == GLUT_KEY_END)
	{
		exit(0);
	}
	if(key == GLUT_KEY_LEFT)
	{
		pic_x--;
	}
	if(key == GLUT_KEY_RIGHT)
	{
		pic_x++;
        state = WALK;
	}
	if(key == GLUT_KEY_UP)
	{
		pic_y++;
        state = JUMP;
	}
	if(key == GLUT_KEY_DOWN)
	{
		pic_y--;
	}
	//place your codes for other keys here
}

int main()
{
	//place your own initialization codes here.
	pic_x = 30;
	pic_y = 20;
    populate_monster_images();
    iSetTimer(100, update_monster);
	iInitialize(500, 400, "SpriteDemo");
	return 0;
}
