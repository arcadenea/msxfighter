#include "VDP_TMS9918A.h"
#include "timer.h"
#include "screen_fight.h"
#include "sprite.h"
#include "tilemap.h"
#include "consts.h"
#include "input.h"
//#include "font.h"
#include "AY38910BF.h"
#include "pt3_player.h"
//#include "pt3_notetable2.h"
#include "music/Fret.h"


//fighters
#include "fighter.h"

//backgrounds
#include "tiles.h" //test background
//#include "bg_beach.h"
//#include "bg_stairs.h"
/*#include "bg_stadium.h"
#include "bg_field.h"
#include "bg_train.h"
#include "bg_bsas.h"
#include "bg_taxis.h"
#include "bg_stairs.h"*/


#define DEBUG_COLLISIONS 1



extern const unsigned int PT3_NT2;
//extern unsigned char g_Fret;

struct players {
	unsigned char character;
	unsigned char posx;
	unsigned char posy;
	unsigned char action;
	unsigned char joystick;
	unsigned char joy_trigp; //trigger counter for low/high buttons
	unsigned char joy_trigk; //trigger counter for low/high buttons
	unsigned char ticks; //animation frame counter
	unsigned char current_frame; //current frame of animation 
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
	unsigned char hx, hy, hw, hh :6; //hit box
	unsigned char ax, ay, aw, ah :6; //attack box
};

struct players player[2];

unsigned char flicker; //flicker variable
unsigned char debug_sprite=0;

extern unsigned char FONT[];
extern void PRINT_TEXT(char column, char line, char* text);
extern void TEXT_COLOR(unsigned int bank, char fcolor, char bcolor);
extern void uitoa_print(char column, char line, unsigned char value, unsigned char radix);

static inline void load_sprites(unsigned char pl) //__z88dk_fastcall
{

/*sprite order
Player 1	Player 2
0	2		4	6
1	3		5	7
*/
		player[pl].spr_index1 = load_sprite((unsigned int) fighters[player[pl].character].frames[player[pl].current_frame].spr0, player[pl].flip, player[pl].character);
	    player[pl].spr_index2 = load_sprite((unsigned int) fighters[player[pl].character].frames[player[pl].current_frame].spr1, player[pl].flip, player[pl].character);
		player[pl].spr_index3 = load_sprite((unsigned int) fighters[player[pl].character].frames[player[pl].current_frame].spr2, player[pl].flip, player[pl].character);
		player[pl].spr_index4 = load_sprite((unsigned int) fighters[player[pl].character].frames[player[pl].current_frame].spr3, player[pl].flip, player[pl].character);


/*	if(player[0].animation!=player[0].animation_load)
	{
	
		player[0].spr_index1 = load_sprite((unsigned int) fighters[player[0].character].frames[player[0].animation_load].spr0, player[0].flip, CHARACTER);
	    player[0].spr_index2 = load_sprite((unsigned int) fighters[player[0].character].frames[player[0].animation_load].spr1, player[0].flip, CHARACTER);
		player[0].spr_index3 = load_sprite((unsigned int) fighters[player[0].character].frames[player[0].animation_load].spr2, player[0].flip, CHARACTER);
		player[0].spr_index4 = load_sprite((unsigned int) fighters[player[0].character].frames[player[0].animation_load].spr3, player[0].flip, CHARACTER);
		//player[0].spr_index2 = load_sprite((unsigned int) fighters[0].frames[player[0].animation_load].spr1, player[0].flip, CHARACTER);
		//player[0].spr_index3 = load_sprite((unsigned int) fighters[0].frames[player[0].animation_load].spr2, player[0].flip, CHARACTER);
		//player[0].spr_index4 = load_sprite((unsigned int) fighters[0].frames[player[0].animation_load].spr3, player[0].flip, CHARACTER);

		//player[0].spr_index1 = load_sprite((unsigned int) fighters[0].frames[player[0].animation_load].spr0, player[0].flip, CHARACTER);
		//player[0].spr_index2 = load_sprite((unsigned int) fighters[0].frames[player[0].animation_load].spr1, player[0].flip, CHARACTER);
		//player[0].spr_index3 = load_sprite((unsigned int) fighters[0].frames[player[0].animation_load].spr2, player[0].flip, CHARACTER);
		//player[0].spr_index4 = load_sprite((unsigned int) fighters[0].frames[player[0].animation_load].spr3, player[0].flip, CHARACTER);
		player[0].animation=player[0].animation_load;
	}*/
/*
	if(player[1].animation!=player[1].animation_load)
	{
		player[1].spr_index1 = load_sprite((unsigned int) fighters[player[1].character].frames[player[1].animation_load].spr0, player[1].flip, CHARACTER);
		player[1].spr_index2 = load_sprite((unsigned int) fighters[player[1].character].frames[player[1].animation_load].spr1, player[1].flip, CHARACTER);
		player[1].spr_index3 = load_sprite((unsigned int) fighters[player[1].character].frames[player[1].animation_load].spr2, player[1].flip, CHARACTER);
		player[1].spr_index4 = load_sprite((unsigned int) fighters[player[1].character].frames[player[1].animation_load].spr3, player[1].flip, CHARACTER);
		player[1].animation=player[1].animation_load;
	}*/

}


static inline void draw_sprites() //__z88dk_fastcall
{
//for(unsigned char i=0;i<2;++i) descomentar
/*
resolucion msx 256x192
0,0     32,0
0,32         32, 32
*/

for(unsigned char i=0;i<1;++i)
{
		if(player[i].flip==SPRITE_NOFLIP)
		{
			draw_sprite((i<<2), player[i].spr_index1, player[i].posx, player[i].posy, player[i].color);
			draw_sprite((i<<2)+1, player[i].spr_index2, player[i].posx, player[i].posy+32, player[i].color);
			draw_sprite((i<<2)+2, player[i].spr_index3, player[i].posx+32, player[i].posy, player[i].color);
			draw_sprite((i<<2)+3, player[i].spr_index4, player[i].posx+32, player[i].posy+32, player[i].color);
		}else if(player[i].flip==SPRITE_FLIPX){
			draw_sprite((i<<2), player[i].spr_index1, player[i].posx, player[i].posy, player[i].color);
			draw_sprite((i<<2)+1, player[i].spr_index2, player[i].posx, player[i].posy+32, player[i].color);
			draw_sprite((i<<2)+2, player[i].spr_index3, player[i].posx-32, player[i].posy, player[i].color);
			draw_sprite((i<<2)+3, player[i].spr_index4, player[i].posx-32, player[i].posy+32, player[i].color);
		}else if(player[i].flip==SPRITE_FLIPY){
			draw_sprite((i<<2), player[i].spr_index1, player[i].posx, player[i].posy+32, player[i].color);
			draw_sprite((i<<2)+1, player[i].spr_index2, player[i].posx, player[i].posy, player[i].color);
			draw_sprite((i<<2)+2, player[i].spr_index3, player[i].posx+32, player[i].posy+32, player[i].color);
			draw_sprite((i<<2)+3, player[i].spr_index4, player[i].posx+32, player[i].posy, player[i].color);	
		}else{ //SPRITE_FLIPXY
			draw_sprite((i<<2), player[i].spr_index1, player[i].posx, player[i].posy+32, player[i].color);
			draw_sprite((i<<2)+1, player[i].spr_index2, player[i].posx, player[i].posy, player[i].color);
			draw_sprite((i<<2)+2, player[i].spr_index3, player[i].posx-32, player[i].posy, player[i].color);
			draw_sprite((i<<2)+3, player[i].spr_index4, player[i].posx-32, player[i].posy, player[i].color);
		}
}		

		//draw_sprite(29, debug_sprite, 20, 20, BLACK); //debug

		if(flicker == 0){
			draw_sprite(30, 61,   player[0].posx+player[0].hx, 
			                                    player[0].posy+player[0].hy, CYAN); //collision box
			if(player[0].ax!=63) draw_sprite(31, 62,   player[0].posx-16 + player[0].ax + player[0].aw, 
			                                     player[0].posy-16 + player[0].ay + player[0].ah, RED); //attack box

			//draw_sprite(31, 63, player[0].posx, SHADOW_POSY, BLACK); //shadow


/*			draw_sprite(2, player[0].spr_index2, 255, 255, player[0].color);
			draw_sprite(3, player[0].spr_index3, 255, 255, player[0].color);

			draw_sprite(6, player[1].spr_index2, 255, 255, player[1].color);
			draw_sprite(7, player[1].spr_index3, 255, 255, player[1].color);*/

			flicker=1;
		}else{
			if(player[0].ax!=63) draw_sprite(30, 61,   
                                                            player[0].posx + player[0].ax, 
			                                    player[0].posy + player[0].ay, RED); //attack box
			draw_sprite(31, 62,   player[0].posx + player[0].hx + player[0].hw-32, 
			                                    player[0].posy -32 + player[0].hy + player[0].hh, CYAN); //collision box


			//draw_sprite(31, 63, player[1].posx, SHADOW_POSY, BLACK); //shadow

/*			if(player[0].flip==0)
			{
				draw_sprite(2, 8, player[0].posx+32, player[0].posy-32, player[0].color);
				draw_sprite(3, 12, player[0].posx+32, player[0].posy, player[0].color);

				draw_sprite(6, 24, player[1].posx-32, player[1].posy-32, player[1].color);
				draw_sprite(7, 28, player[1].posx-32, player[1].posy, player[1].color);
			}else{
				draw_sprite(2, 8, player[0].posx-32, player[0].posy-32, player[0].color);
				draw_sprite(3, 12, player[0].posx-32, player[0].posy, player[0].color);

				draw_sprite(6, 24, player[1].posx+32, player[1].posy-32, player[1].color);
				draw_sprite(7, 28, player[1].posx+32, player[1].posy, player[1].color);
			}*/

		flicker = 0;

		}

}

void load_animation(unsigned char pl, unsigned char anim)
{
	if(player[pl].anim_breakable == ANIMATION_BREAKABLE)
	{
		//PRINT_TEXT(10, 1, "AGGHHHH!");

		player[pl].animation=fighters_animations[player[pl].character][anim];
		player[pl].current_frame=fighters_animations[player[pl].character][anim];		
		player[pl].ticks=fighters[player[pl].character].frames[player[pl].current_frame].ticks;
		player[pl].flip=fighters[player[pl].character].frames[player[pl].current_frame].flip;
		player[pl].next_frame=fighters[player[pl].character].frames[player[pl].current_frame].next_frame;
                player[pl].ax=fighters[player[pl].character].frames[player[pl].current_frame].ax;
                player[pl].ay=fighters[player[pl].character].frames[player[pl].current_frame].ay;
                player[pl].aw=fighters[player[pl].character].frames[player[pl].current_frame].aw;
                player[pl].ah=fighters[player[pl].character].frames[player[pl].current_frame].ah;
                player[pl].hx=fighters[player[pl].character].frames[player[pl].current_frame].hx;
                player[pl].hy=fighters[player[pl].character].frames[player[pl].current_frame].hy;
                player[pl].hw=fighters[player[pl].character].frames[player[pl].current_frame].hw;
                player[pl].hh=fighters[player[pl].character].frames[player[pl].current_frame].hh;
		load_sprites(pl);
	}	

}


unsigned char run_animation(unsigned char i)
{
					
		if((player[i].ticks==0)&&(player[i].next_frame == 255)) //animation ended
		{
			//PRINT_TEXT(9, 1, "ENDUT");
			//player[i].action = PLAYER_STAND;
			return 0;
		}else if(player[i].ticks==0) //load next frame
		{
			//PRINT_TEXT(9, 1, "HOCH HECH!");
			player[i].ticks=fighters[player[i].character].frames[player[i].next_frame].ticks;
			player[i].flip=fighters[player[i].character].frames[player[i].next_frame].flip;
                        player[i].ax=fighters[player[i].character].frames[player[i].next_frame].ax;
                        player[i].ay=fighters[player[i].character].frames[player[i].next_frame].ay;
                        player[i].aw=fighters[player[i].character].frames[player[i].next_frame].aw;
                        player[i].ah=fighters[player[i].character].frames[player[i].next_frame].ah;
                        player[i].hx=fighters[player[i].character].frames[player[i].next_frame].hx;
                        player[i].hy=fighters[player[i].character].frames[player[i].next_frame].hy;
                        player[i].hw=fighters[player[i].character].frames[player[i].next_frame].hw;
                        player[i].hh=fighters[player[i].character].frames[player[i].next_frame].hh;
			player[i].current_frame=player[i].next_frame;
			player[i].next_frame=fighters[player[i].character].frames[player[i].current_frame].next_frame;

			load_sprites(i);
			return 1;		
		}else{
			player[i].ticks--;
			if(player[i].action == PLAYER_MOVE_LEFT)  player[i].posx-=fighters[player[i].character].frames[player[i].current_frame].mx;
			else player[i].posx+=fighters[player[i].character].frames[player[i].current_frame].mx;
			 player[i].posy+=fighters[player[i].character].frames[player[i].current_frame].my;
			player[i].flip=fighters[player[i].character].frames[player[i].current_frame].flip;			
			return 1;
		}

}

unsigned char check_collision(unsigned char r1x,  unsigned char r1w, unsigned char r1y,  unsigned char r1h,  unsigned char r2x,  unsigned char r2w, unsigned char r2y,  unsigned char r2h)
{
       if (r1x + r1w >= r2x &&    // r1 right edge past r2 left
            r1x <= r2x + r2w &&    // r1 left edge past r2 right
            r1y + r1h >= r2y &&    // r1 top edge past r2 bottom
            r1y <= r2y + r2h) {    // r1 bottom edge past r2 top
              return 1;
        }
        return 0;

}

void fight_screen(void)
{
const unsigned char TEXT_P1[]={"ONE"};
const unsigned char TEXT_P2[]={"TWO"};
const unsigned char SCORE_P1[]={"99999"};
const unsigned char SCORE_P2[]={"PRESS START"};
const unsigned char KO[]={"KO"};
unsigned char i=0;
flicker = 0;

//
clear_screen(WHITE);

unsigned char c1, c2, c3; //collision check - delete

//cargamos música
Player_Init();
Player_InitSong((unsigned int) g_Fret, (unsigned int) PT3_NT2, 1) ; //(unsigned char *)
Player_Resume();

player[0].character = 0;
player[0].flip = SPRITE_NOFLIP;
player[0].posx = PLAYER1_POSX;
player[0].posy = PLAYER_POSY;
player[0].anim_breakable=ANIMATION_BREAKABLE;
player[0].anim_state=ANIMATION_WAITING;
//player[0].prevframe=0;
//player[0].action=PLAYER_STAND;
player[0].joystick = 0;
player[0].joy_trigp = 0;
player[0].joy_trigk = 0;
player[0].color=BLACK;
player[0].spr_index1=64;
player[0].spr_index2=64;
player[0].spr_index3=64;
player[0].spr_index4=64;
player[0].animation=255;
player[0].ticks=0;

player[1].character = 0;
player[1].flip = SPRITE_FLIPX;
player[1].posx = PLAYER2_POSX;
player[1].posy = PLAYER_POSY;
player[1].anim_breakable=ANIMATION_BREAKABLE;
player[1].anim_state=ANIMATION_WAITING;
//player[1].animation_load=255;
//player[1].prevframe=0;
//player[1].frames=fighters_animations[player[0].character][FIGHTER_STAND_ANIMATION1];
//player[1].action=PLAYER_STAND;
player[1].joystick = 0;
player[1].joy_trigp = 0;
player[1].joy_trigk = 0;
player[1].color=DARK_RED;
player[1].spr_index1=64;
player[1].spr_index2=64;
player[1].spr_index3=64;
player[1].spr_index4=64;
player[1].animation=255;

//load fighter animations and collision boxes
load_fighter();


//cargamos tilemap
load_tileset((unsigned int) FONT, 512, BANK0, 0);
//load_tileset((unsigned int) TILESET_0, 1024, BANK0, 512);
//load_tileset((unsigned int) TILESET_1, 2048, BANK1, 512);
//load_tileset((unsigned int) TILESET_2, 2048, BANK2, 512);
//load_colormap((unsigned int) FONTCOLOR, 512, BANK0, 0); //temp fonts
//load_colormap((unsigned int) COLORMAP_0, 2048, BANK0, 512);
//load_colormap((unsigned int) COLORMAP_1, 2048, BANK1, 512);
//load_colormap((unsigned int) COLORMAP_2, 2048, BANK2, 512); 
load_tilemap((unsigned int) TILEMAP, 256, 0); //32*24 tiles


init_sprite_manager();
//load static sprites
load_sprite_unmanaged(61, (unsigned int) collision_up);
load_sprite_unmanaged(62, (unsigned int) collision_down);
load_sprite_unmanaged(63, (unsigned int) shadow);

load_animation(0, PLAYER_STAND);
load_animation(1, PLAYER_STAND);

debug_sprite = 0;

int t;

//load bars
//0xAA
FillVRAM(BASE10, 256, 0x40); //limpiamos la base0
FillVRAM(BASE11+512, 256, (DARK_YELLOW<<4)|LIGHT_YELLOW); //color del damero
FillVRAM(BASE12+512, 1, 0x0F); //patrón de las barras
FillVRAM(BASE12+513, 1, 0x0F); //patrón de las barras
FillVRAM(BASE12+514, 1, 0x0F); //patrón de las barras
FillVRAM(BASE12+515, 1, 0x0F); //patrón de las barras
FillVRAM(BASE12+516, 1, 0xF0); //patrón de las barras
FillVRAM(BASE12+517, 1, 0xF0); //patrón de las barras
FillVRAM(BASE12+518, 1, 0xF0); //patrón de las barras
FillVRAM(BASE12+519, 1, 0xF0); //patrón de las barras



FillVRAM(BASE11+520, 8, (RED<<4)|RED); //color de las barras
FillVRAM(BASE12+520, 8, 0xFF); //patrón de las barras
FillVRAM(BASE10+(2*32)+2, 12, 0x41); //barrap1 (linea*32+columna)
FillVRAM(BASE10+(2*32)+18, 12, 0x41); //barrap2

//super bars
FillVRAM(BASE11+528, 4, (GREEN<<4)|BLACK); //color de las barras
FillVRAM(BASE12+528, 8, 0xFF); //patrón de las barras
FillVRAM(BASE10+(3*32)+2, 12, 0x42); //barrap1 (linea*32+columna)
FillVRAM(BASE10+(3*32)+18, 12, 0x42); //barrap2

//character names
TEXT_COLOR(BANK0, BLACK, DARK_YELLOW);
PRINT_TEXT(2, 4, TEXT_P1);
PRINT_TEXT(27, 4, TEXT_P2);

//PRINT_TEXT(9, 1, player[0].ticks);
PRINT_TEXT(18, 1, SCORE_P2);

PRINT_TEXT(15, 2, KO);

for(;;)
{

WAIT_VBLANK();
//if(flicker ==0){x
		PlayAY();
		Player_Decode();
//}else{

//read joystick(s) input
for(i=0;i<2;i++)
{
	player[i].joystick = joy_read(i+1);
	//if(i==0 && player[0].joystick==0) player[0].joystick = joy_read(0);

	if(player[i].anim_breakable == ANIMATION_BREAKABLE) 
	{
		if(player[i].joystick&JOYSTICK_RIGHT)
		{ 
			//player[i].flip = SPRITE_FLIPY;
		      player[i].anim_state = ANIMATION_WAITING;			
			player[i].action = PLAYER_MOVE_RIGHT;

			if(debug_sprite < 255) debug_sprite++;
		}else if(player[i].joystick&JOYSTICK_LEFT)
		{	
		      player[i].anim_state = ANIMATION_WAITING;		
			player[i].action = PLAYER_MOVE_LEFT; 
			if(debug_sprite > 0) debug_sprite--;
		} 
		
		if((player[i].joystick&JOYSTICK_DOWN))
		{
		      player[i].anim_state = ANIMATION_WAITING;				
			player[i].action = PLAYER_CROUCH;
	
		}else if((player[i].joystick&JOYSTICK_UP))
		{

			if(player[i].action == PLAYER_MOVE_LEFT)
			{
		            player[i].anim_state = ANIMATION_WAITING;					
				player[i].action = PLAYER_JUMP_LEFT;
			}else if(player[i].action == PLAYER_MOVE_RIGHT)
			{
		             player[i].anim_state = ANIMATION_WAITING;					
				player[i].action = PLAYER_JUMP_RIGHT;
			}else{
			      player[i].anim_state = ANIMATION_WAITING;		
				player[i].action = PLAYER_JUMP;
			}
		}

	}

	if(player[i].joystick&JOYSTICK_TRIGA)
	{
		player[i].joy_trigp++;
	} else
	{
		if (player[i].joy_trigp>=10)
		{
		player[i].anim_state = ANIMATION_WAITING;		
			switch(player[i].action) 
			{
				case PLAYER_CROUCH: player[i].action = PLAYER_HP_CROUCH;
				break;
				case PLAYER_JUMP: player[i].action = PLAYER_HP_JUMP;
				break;
				case PLAYER_JUMP_LEFT: 
					player[i].action = PLAYER_HP_JUMP_LEFT;
				break;
				case PLAYER_JUMP_RIGHT: 
					player[i].action = PLAYER_HP_JUMP_RIGHT;
				break;
				case PLAYER_STAND: player[i].action = PLAYER_HP;
				break;
			}
		}else if (player[i].joy_trigp>0)
		{
		player[i].anim_state = ANIMATION_WAITING;		
			switch(player[i].action) 
			{
				case PLAYER_CROUCH: player[i].action = PLAYER_LP_CROUCH;
					break;
				case PLAYER_JUMP: 
					player[i].action = PLAYER_LP_JUMP;
					break;
				case PLAYER_JUMP_LEFT: 
					player[i].action = PLAYER_LP_JUMP_LEFT;
					break;
				case PLAYER_JUMP_RIGHT: 
					player[i].action = PLAYER_LP_JUMP_RIGHT;
					break;
				case PLAYER_STAND: player[i].action = PLAYER_LP;
					break;
			}
		}
	
		player[i].joy_trigp=0;
	}

	if(player[i].joystick&JOYSTICK_TRIGB)
	{
		player[i].joy_trigk++;
	} else
	{
		if (player[i].joy_trigk>=10)
		{
		player[i].anim_state = ANIMATION_WAITING;
			switch(player[i].action) 
			{
				case PLAYER_CROUCH: player[i].action = PLAYER_HK_CROUCH;
					break;
				case PLAYER_JUMP: player[i].action = PLAYER_HK_JUMP;
					break;
				case PLAYER_JUMP_LEFT: 
					player[i].action = PLAYER_HK_JUMP_LEFT;
					break;
				case PLAYER_JUMP_RIGHT: 
					player[i].action = PLAYER_HK_JUMP_RIGHT;
					break;
				case PLAYER_STAND: player[i].action = PLAYER_HK;
					break;
			}
		}else if (player[i].joy_trigk>0)
		{
		player[i].anim_state = ANIMATION_WAITING;
			switch(player[i].action) 
			{
				case PLAYER_CROUCH: player[i].action = PLAYER_LK_CROUCH;
					break;
				case PLAYER_JUMP: player[i].action = PLAYER_LK_JUMP;
					break;
				case PLAYER_JUMP_LEFT: 
					player[i].action = PLAYER_LK_JUMP_LEFT;
					break;
				case PLAYER_JUMP_RIGHT: 
					player[i].action = PLAYER_LK_JUMP_RIGHT;
					break;
				case PLAYER_STAND: player[i].action = PLAYER_LK;
					break;
			}
		}
		player[i].joy_trigk=0;	
	}

//ANIMATION_WAITING->ANIMATION_RUNNING->ANIMATION_FINISHED
if(player[i].anim_state == ANIMATION_WAITING)
{ 
      uitoa_print(0, 3, player[i].action, 10);
      uitoa_print(0, 4, player[i].anim_breakable, 10);
	load_animation(i, player[i].action);	
switch(player[i].action)
{
          case PLAYER_STAND: player[i].anim_breakable = ANIMATION_BREAKABLE; break;
          case PLAYER_CROUCH: player[i].anim_breakable = ANIMATION_BREAKABLE; break;
          case PLAYER_MOVE_RIGHT: player[i].anim_breakable = ANIMATION_BREAKABLE_BUTTON; break;
          case PLAYER_MOVE_LEFT: player[i].anim_breakable = ANIMATION_BREAKABLE_BUTTON; break;          
           case PLAYER_JUMP: player[i].anim_breakable = ANIMATION_BREAKABLE_BUTTON; break;
           case PLAYER_JUMP_LEFT: player[i].anim_breakable = ANIMATION_BREAKABLE_BUTTON; break;
           case PLAYER_JUMP_RIGHT: player[i].anim_breakable = ANIMATION_BREAKABLE_BUTTON; break;           
          default:  player[i].anim_breakable = ANIMATION_NONBREAKABLE;
}

	player[i].anim_state = ANIMATION_RUNNING;
}
if(run_animation(i)==0){ 
	player[i].action = PLAYER_STAND;
	player[i].anim_breakable = ANIMATION_BREAKABLE;
	player[i].anim_state = ANIMATION_WAITING;	
}	

} //for each player


draw_sprites();
if(player[0].ax!=63) c1=check_collision(player[0].ax, player[0].ay, player[0].aw, player[0].ah, player[1].hx, player[1].hy, player[1].hw, player[1].hh);  //player 1 attack player 2
if(player[1].ax!=63) c2=check_collision(player[1].ax, player[1].ay, player[1].aw, player[1].ah, player[0].hx, player[0].hy, player[0].hw, player[0].hh);  //player 2 attack player 1
c3=check_collision(player[0].hx, player[0].hy, player[0].hw, player[0].hh, player[1].hx, player[1].hy, player[1].hw, player[1].hh);  //are players colliding?

                    uitoa_print(0, 1, player[0].ticks, 10);
                    uitoa_print(0, 2, player[0].current_frame, 10);
                    uitoa_print(0, 5, c1, 10);
                    uitoa_print(0, 6, c2, 10);
                    uitoa_print(0, 7, c3, 10);


} //game loop
} //main





