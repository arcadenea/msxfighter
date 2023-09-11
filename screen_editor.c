#include "VDP_TMS9918A.h"
#include "timer.h"
#include "screen_editor.h"
#include "sprite.h"
#include "tilemap.h"
#include "consts.h"
#include "input.h"
//#include "font.h"


//fighters
#include "fighter.h"




#define DEBUG_COLLISIONS 1

unsigned char cursor_x, cursor_y;

struct players {
	unsigned char character;
	unsigned char posx;
	unsigned char posy;
	unsigned char action;
	unsigned char joystick;
	unsigned char joy_trigp; //trigger counter for low/high buttons
	unsigned char joy_trigk; //trigger counter for low/high buttons
	unsigned char ticks; //animation frame counter
	unsigned char frame; //current frame of animation 
	unsigned char next_frame; //next frame of animation 	
	unsigned char animation; //current animation
	unsigned char anim_breakable; //current animation is breakable by event
	unsigned char anim_state; //current animation state
	unsigned char flip; //flip position
	unsigned char color;
	unsigned char spr_index1; //start position of sprite order
	unsigned char spr_index2; //start position of sprite order
	unsigned char spr_index3; //start position of sprite order
	unsigned char spr_index4; //start position of sprite order
};

struct players s_player[1];

unsigned char flicker_editor; //flicker_editor variable


extern unsigned char FONT[];
extern void PRINT_TEXT(char column, char line, char* text);
extern void TEXT_COLOR(unsigned int bank, char fcolor, char bcolor);
extern void uitoa_print(char column, char line, unsigned char value, unsigned char radix);

static inline void load_sprites(unsigned char index) //__z88dk_fastcall
{

/*sprite order
Player 1	Player 2
0	2		4	6
1	3		5	7
*/
		s_player[0].spr_index1 = load_sprite((unsigned int) fighters[s_player[0].character].frames[index].spr0, s_player[0].flip, s_player[0].character);
	    s_player[0].spr_index2 = load_sprite((unsigned int) fighters[s_player[0].character].frames[index].spr1, s_player[0].flip, s_player[0].character);
		s_player[0].spr_index3 = load_sprite((unsigned int) fighters[s_player[0].character].frames[index].spr2, s_player[0].flip, s_player[0].character);
		s_player[0].spr_index4 = load_sprite((unsigned int) fighters[s_player[0].character].frames[index].spr3, s_player[0].flip, s_player[0].character);


}


static inline void draw_sprites() //__z88dk_fastcall
{
for(unsigned char i=0;i<1;++i)
{
		if(s_player[i].flip==SPRITE_NOFLIP)
		{
			draw_sprite((i<<2), s_player[i].spr_index1, s_player[i].posx, s_player[i].posy-32, s_player[i].color);
			draw_sprite((i<<2)+1, s_player[i].spr_index2, s_player[i].posx, s_player[i].posy, s_player[i].color);
			draw_sprite((i<<2)+2, s_player[i].spr_index3, s_player[i].posx+32, s_player[i].posy-32, s_player[i].color);
			draw_sprite((i<<2)+3, s_player[i].spr_index4, s_player[i].posx+32, s_player[i].posy, s_player[i].color);
		}else if(s_player[i].flip==SPRITE_FLIPX){
			draw_sprite((i<<2), s_player[i].spr_index1, s_player[i].posx, s_player[i].posy-32, s_player[i].color);
			draw_sprite((i<<2)+1, s_player[i].spr_index2, s_player[i].posx, s_player[i].posy, s_player[i].color);
			draw_sprite((i<<2)+2, s_player[i].spr_index3, s_player[i].posx-32, s_player[i].posy-32, s_player[i].color);
			draw_sprite((i<<2)+3, s_player[i].spr_index4, s_player[i].posx-32, s_player[i].posy, s_player[i].color);
		}else if(s_player[i].flip==SPRITE_FLIPY){
			draw_sprite((i<<2), s_player[i].spr_index1, s_player[i].posx, s_player[i].posy, s_player[i].color);
			draw_sprite((i<<2)+1, s_player[i].spr_index2, s_player[i].posx, s_player[i].posy-32, s_player[i].color);
			draw_sprite((i<<2)+2, s_player[i].spr_index3, s_player[i].posx+32, s_player[i].posy, s_player[i].color);
			draw_sprite((i<<2)+3, s_player[i].spr_index4, s_player[i].posx+32, s_player[i].posy-32, s_player[i].color);	
		}else{ //SPRITE_FLIPXY
			draw_sprite((i<<2), s_player[i].spr_index1, s_player[i].posx, s_player[i].posy, s_player[i].color);
			draw_sprite((i<<2)+1, s_player[i].spr_index2, s_player[i].posx, s_player[i].posy-32, s_player[i].color);
			draw_sprite((i<<2)+2, s_player[i].spr_index3, s_player[i].posx-32, s_player[i].posy-32, s_player[i].color);
			draw_sprite((i<<2)+3, s_player[i].spr_index4, s_player[i].posx-32, s_player[i].posy-32, s_player[i].color);
		}
}		

			draw_sprite(30, 61,   cursor_x, 
			                                    cursor_y, RED); //collision box


}



void editor_screen(void)
{

unsigned char i=0;
flicker_editor = 0;
unsigned char accel_editor = 0;

cursor_x = 0;
cursor_y = 0;
//
clear_screen(WHITE);



s_player[0].character = 0;
s_player[0].flip = SPRITE_NOFLIP;
s_player[0].posx = 0;
s_player[0].posy = 32;
s_player[0].anim_breakable=ANIMATION_BREAKABLE;
s_player[0].anim_state=ANIMATION_WAITING;
s_player[0].frame=0;
//s_player[0].action=PLAYER_STAND;
s_player[0].joystick = 0;
s_player[0].joy_trigp = 0;
s_player[0].joy_trigk = 0;
s_player[0].color=BLACK;
s_player[0].spr_index1=64;
s_player[0].spr_index2=64;
s_player[0].spr_index3=64;
s_player[0].spr_index4=64;
s_player[0].animation=255;
s_player[0].ticks=0;



//cargamos tilemap
load_tileset((unsigned int) FONT, 512, BANK0, 0);

init_sprite_manager();
//load static sprites
load_sprite_unmanaged(61, (unsigned int) collision_up);
load_sprite_unmanaged(62, (unsigned int) collision_down);



//character names
TEXT_COLOR(BANK0, BLACK, WHITE);

PRINT_TEXT(8, 1, "X:");
PRINT_TEXT(8, 2, "Y:");
PRINT_TEXT(8, 3, "F:");


for(;;)
{


WAIT_VBLANK();


//read joystick(s) input
if(flicker_editor == 4)
{
s_player[0].joystick = joy_read(1);

		if(s_player[0].joystick&JOYSTICK_RIGHT)
		{ 
                      if(cursor_x < 255)  cursor_x+=1;
		}else if(s_player[0].joystick&JOYSTICK_LEFT)
		{	
                      if(cursor_x > 0) cursor_x-=1;
		} 
		
		if((s_player[0].joystick&JOYSTICK_DOWN))
		{
	                if(cursor_y < 255) cursor_y+=1;
		}else if((s_player[0].joystick&JOYSTICK_UP))
		{
	                if(cursor_y > 0) cursor_y-=1;
		}

	if(s_player[0].joystick&JOYSTICK_TRIGA)
	{
	  s_player[0].frame+=1;
	  load_sprites(s_player[0].frame);
	}

	if(s_player[0].joystick&JOYSTICK_TRIGB)
	{
	  s_player[0].frame-=1;
	  load_sprites(s_player[0].frame);	  
	}
flicker_editor=0;	
}
draw_sprites();
uitoa_print(10, 1, cursor_x, 10);
uitoa_print(10, 2, cursor_y, 10);
uitoa_print(10, 3, s_player[0].frame, 10);
flicker_editor++;


} //game loop
} //main





