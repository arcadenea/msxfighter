#include "VDP_TMS9918A.h"
#include "sprite.h"
#include "tilemap.h"
#include "input.h"
#include "tiles.h"
#include "fighter.h"


#define  HALT __asm halt __endasm
#define DEBUG_COLLISIONS 1


#define PLAYER_STAND 0
//#define PLAYER_STAND_2 99
#define PLAYER_JUMP 1
#define PLAYER_JUMP_RIGHT 2
#define PLAYER_JUMP_LEFT 8
#define PLAYER_MOVE_LEFT 7
#define PLAYER_MOVE_RIGHT 3
#define PLAYER_CROUCH 5
#define PLAYER_LP 10
#define PLAYER_LP_CROUCH 11
#define PLAYER_LP_JUMP 12
#define PLAYER_LP_JUMP_LEFT 13
#define PLAYER_LP_JUMP_RIGHT 14
#define PLAYER_HP 15
#define PLAYER_HP_CROUCH 16
#define PLAYER_HP_JUMP 17
#define PLAYER_HP_JUMP_LEFT 18
#define PLAYER_HP_JUMP_RIGHT 19
#define PLAYER_LK 20
#define PLAYER_LK_CROUCH 21
#define PLAYER_LK_JUMP 22
#define PLAYER_LK_JUMP_LEFT 23
#define PLAYER_LK_JUMP_RIGHT 24
#define PLAYER_HK 25
#define PLAYER_HK_CROUCH 26
#define PLAYER_HK_JUMP 27
#define PLAYER_HK_JUMP_LEFT 28
#define PLAYER_HK_JUMP_RIGHT 29

unsigned char flicker; //flicker variable
__at 0xFC9E unsigned int jiffy; //the damn jiffy variable

struct players {
	unsigned char posx;
	unsigned char posy;
	unsigned char action;
	unsigned char joystick;
	unsigned char joy_trigp; //trigger counter for low/high buttons
	unsigned char joy_trigk; //trigger counter for low/high buttons
	unsigned char frame; //frame counter
	unsigned char animation; //
	unsigned char animation_load; //
	unsigned char prevframe; //frame counter backup for jumps
	unsigned char flipx; //flip position
	unsigned char color;
	unsigned char spr_index1; //start position of sprite order
	unsigned char spr_index2; //start position of sprite order
	unsigned char spr_index3; //start position of sprite order
	unsigned char spr_index4; //start position of sprite order
};

struct players player[2];
unsigned char i;

unsigned char debug_sprite=0;


void VPRINT(char column, char line, char* text);  //print in screen 1 or 2

void VPOKEARRAY(unsigned int vaddr, char* text)
{
  while(*(text)) VPOKE(vaddr++,*(text++));
}

void VPRINT(char column, char line, char* text)
{
  unsigned int vaddr = BASE10 + (line*32)+column; // calcula la posicion en la VRAM
  VPOKEARRAY(vaddr, text);
}

void WAIT(unsigned int cicles)
{
	int jiffyref;
	jiffyref = jiffy;
	while(jiffy < 1 || jiffyref == jiffy) 
	{ 
		HALT; 	
	}
//  int i;
//  for(i=0;i<cicles;i++) HALT;
}

void POKE(unsigned int address, char value)
{
address;value;
__asm
  push IX
  ld   IX,#0
  add  IX,SP 
    
  ld   L,4(ix)
  ld   H,5(ix)
  ld   A,6(ix)
  ld   (HL),A

  pop  IX  
__endasm;
}

void fillOrdered()
{
  unsigned int i;
  for(i=0;i<255;i++) VPOKE(BASE11+i,i);
}


char checkCollision(char posx, char posy, char direction)
{

	//unsigned int vaddr1 = (((posy&0xF8)+16)*4)+((posx&0xf8)/8); // calcula la posicion en la VRAM
	//unsigned int vaddr2 = (((posy&0xF8)+16)*4)+(((posx&0xf8)+8)/8); // calcula la posicion en la VRAM

	return 0;
} 


void load_sprites()
{

/*sprite order
Player 1	Player 2
0	2		4	6
1	3		5	7
*/

	if(player[0].animation!=player[0].animation_load)
	{

		player[0].spr_index1 = load_sprite((unsigned int) fighters[0].frames[player[0].animation_load].spr0, player[0].flipx);
		player[0].spr_index2 = load_sprite((unsigned int) fighters[0].frames[player[0].animation_load].spr1, player[0].flipx);
		player[0].spr_index3 = load_sprite((unsigned int) fighters[0].frames[player[0].animation_load].spr2, player[0].flipx);
		player[0].spr_index4 = load_sprite((unsigned int) fighters[0].frames[player[0].animation_load].spr3, player[0].flipx);
		player[0].animation=player[0].animation_load;
	}

	if(player[1].animation!=player[1].animation_load)
	{
		player[1].spr_index1 = load_sprite((unsigned int) fighters[0].frames[player[1].animation_load].spr0, player[1].flipx);
		player[1].spr_index2 = load_sprite((unsigned int) fighters[0].frames[player[1].animation_load].spr1, player[1].flipx);
		player[1].spr_index3 = load_sprite((unsigned int) fighters[0].frames[player[1].animation_load].spr2, player[1].flipx);
		player[1].spr_index4 = load_sprite((unsigned int) fighters[0].frames[player[1].animation_load].spr3, player[1].flipx);
		player[1].animation=player[1].animation_load;
	}

}


void draw_sprites()
{

		if(player[0].flipx==0)
		{
			draw_sprite(0, player[0].spr_index1, player[0].posx, player[0].posy-32, player[0].color);
			draw_sprite(1, player[0].spr_index2, player[0].posx, player[0].posy, player[0].color);
			draw_sprite(4, player[1].spr_index1, player[1].posx, player[1].posy-32, player[1].color);
			draw_sprite(5, player[1].spr_index2, player[1].posx, player[1].posy, player[1].color);
		}else{
			draw_sprite(0, player[0].spr_index1, player[0].posx, player[0].posy-32, player[0].color);
			draw_sprite(1, player[0].spr_index2, player[0].posx, player[0].posy, player[0].color);
			draw_sprite(4, player[1].spr_index1, player[1].posx, player[1].posy-32, player[1].color);
			draw_sprite(5, player[1].spr_index2, player[1].posx, player[1].posy, player[1].color);
		}

		draw_sprite(29, debug_sprite, 20, 20, BLACK); //debug

		if(flicker == 0){
			draw_sprite(30, 61, player[0].posx, player[0].posy-32, CYAN); //collision box
			draw_sprite(31, 62, player[0].posx, player[0].posy, CYAN); //collision box

			draw_sprite(31, 63, player[0].posx, 180, BLACK); //shadow


//			draw_sprite(2, player[0].spr_index2, 255, 255, player[0].color);
//			draw_sprite(3, player[0].spr_index3, 255, 255, player[0].color);

//			draw_sprite(6, player[1].spr_index2, 255, 255, player[1].color);
//			draw_sprite(7, player[1].spr_index3, 255, 255, player[1].color);

			flicker=1;
		}else{
			draw_sprite(30, 61, player[1].posx, player[1].posy-32, CYAN); //collision box
			draw_sprite(31, 62, player[1].posx, player[1].posy, CYAN); //collision box

			draw_sprite(31, 63, player[1].posx, 180, BLACK); //shadow


/*			if(player[0].flipx==0)
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

void main(void)
{

unsigned char i=0;
flicker = 0;
//initialize screen mode
//POKE(0xF3AF,32); // set 32 columns per line
COLOR(15,15,15);

setup_sprites(SPRITE16X16, SPRITE_ZOOM);
SCREEN(GRAPH1);

player[i].flipx = 0;
player[0].posx = 40;
player[0].posy = 148;
player[0].animation_load=0;
player[0].prevframe=0;
player[0].frame=FIGHTER_STAND_FRAMES;
player[0].action=PLAYER_STAND;
player[0].joystick = 0;
player[0].joy_trigp = 0;
player[0].joy_trigk = 0;
player[0].color=BLACK;
player[0].spr_index1=64;
player[0].spr_index2=64;
player[0].spr_index3=64;
player[0].spr_index4=64;
player[0].animation=64;

player[1].flipx = 1;
player[1].posx = 110;
player[1].posy = 148;
player[1].animation_load=255;
player[1].prevframe=0;
player[1].frame=FIGHTER_STAND_FRAMES;
player[1].action=PLAYER_STAND;
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
load_tileset((unsigned int) TILESET_0, 2048, BANK0);
load_tileset((unsigned int) TILESET_1, 2048, BANK1);
load_tileset((unsigned int) TILESET_2, 2048, BANK2);
load_colormap((unsigned int) COLORMAP_0, 2048, BANK0);
load_colormap((unsigned int) COLORMAP_1, 2048, BANK1);
load_colormap((unsigned int) COLORMAP_2, 2048, BANK2); 
load_tilemap((unsigned int) TILEMAP, 768); //32*24 tiles


init_sprite_manager();
//load static sprites
load_sprite_unmanaged(61, (unsigned int) collision_up);
load_sprite_unmanaged(62, (unsigned int) collision_down);
load_sprite_unmanaged(63, (unsigned int) shadow);

debug_sprite = 0;

while(1){

jiffy = 0;
//read joystick(s) input
for(i=0;i<2;i++)
{
	player[i].joystick = joy_read(i+1);
	if(i==0 && player[0].joystick==0) player[0].joystick = joy_read(0);

	if(player[i].action == PLAYER_STAND) //if not between an animation
	{
		if(player[i].joystick&JOYSTICK_RIGHT)//&&(player[i].posx<232))
		{ 
			player[i].action = PLAYER_MOVE_RIGHT;
			player[i].frame=FIGHTER_WALK_FRAMES;
			if(debug_sprite < 255) debug_sprite++;
		}else if(player[i].joystick&JOYSTICK_LEFT)//&&(player[i].posx>=10))
		{	
			player[i].action = PLAYER_MOVE_LEFT; 
			player[i].frame=FIGHTER_WALK_FRAMES;
			//player[0].animation_load=255;
			if(debug_sprite > 0) debug_sprite--;
		} 
		
		if((player[i].joystick&JOYSTICK_DOWN))
		{
			player[i].action = PLAYER_CROUCH;
			player[i].frame=FIGHTER_DEFAULT_FRAMES;
	
		}else if((player[i].joystick&JOYSTICK_UP))
		{
			player[i].frame=FIGHTER_JUMP_FRAMES*2;
	
			if(player[i].action == PLAYER_MOVE_LEFT)
			{
				player[i].action = PLAYER_JUMP_LEFT;
			}else if(player[i].action == PLAYER_MOVE_RIGHT)
			{
				player[i].action = PLAYER_JUMP_RIGHT;
			}else{
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
			switch(player[i].action) 
			{
				case PLAYER_CROUCH: player[i].action = PLAYER_HP_CROUCH;
				break;
				case PLAYER_JUMP: player[i].action = PLAYER_HP_JUMP;
					player[i].prevframe = player[i].frame; //backup frames
				break;
				case PLAYER_JUMP_LEFT: 
					player[i].action = PLAYER_HP_JUMP_LEFT;
					player[i].prevframe = player[i].frame; //backup frames
				break;
				case PLAYER_JUMP_RIGHT: 
					player[i].action = PLAYER_HP_JUMP_RIGHT;
					player[i].prevframe = player[i].frame; //backup frames
				break;
				case PLAYER_STAND: player[i].action = PLAYER_HP;
				break;
			}
			player[i].frame=FIGHTER_H_FRAMES;
		}else if (player[i].joy_trigp>0)
		{
			switch(player[i].action) 
			{
				case PLAYER_CROUCH: player[i].action = PLAYER_LP_CROUCH;
					break;
				case PLAYER_JUMP: 
					player[i].action = PLAYER_LP_JUMP;
					player[i].prevframe = player[i].frame; //backup frames
					break;
				case PLAYER_JUMP_LEFT: 
					player[i].action = PLAYER_LP_JUMP_LEFT;
					player[i].prevframe = player[i].frame; //backup frames
					break;
				case PLAYER_JUMP_RIGHT: 
					player[i].action = PLAYER_LP_JUMP_RIGHT;
					player[i].prevframe = player[i].frame; //backup frames
					break;
				case PLAYER_STAND: player[i].action = PLAYER_LP;
					break;
			}
			player[i].frame=FIGHTER_DEFAULT_FRAMES;
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
			player[i].prevframe = player[i].frame-FIGHTER_DEFAULT_FRAMES; //backup frames
			player[i].frame=FIGHTER_DEFAULT_FRAMES;
		}else if (player[i].joy_trigk>0)
		{
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
			player[i].prevframe = player[i].frame-FIGHTER_H_FRAMES; //backup frames
			player[i].frame=FIGHTER_H_FRAMES;
		}
		player[i].joy_trigk=0;	
	}

}

for(i=0;i<2;i++)
{
	switch(player[i].action)
	{
		case PLAYER_STAND:
			if(player[i].frame<12)
			{
					player[i].animation_load=FIGHTER_STAND_ANIMATION1;
			}else{
					player[i].animation_load=FIGHTER_STAND_ANIMATION2;
			}
		break;		
		case PLAYER_MOVE_LEFT:
			player[i].posx=player[i].posx-FIGHTER_WALK_SPEED;
			if(player[i].frame<7){
					player[i].animation_load=FIGHTER_WALK_ANIMATION1;
			}else {
					player[i].animation_load=FIGHTER_WALK_ANIMATION2;
			}
		break;
		case PLAYER_MOVE_RIGHT:
			player[i].posx=player[i].posx+FIGHTER_WALK_SPEED; //derecha
			if(player[i].frame<7){
					player[i].animation_load=FIGHTER_WALK_ANIMATION1;
			}else {
					player[i].animation_load=FIGHTER_WALK_ANIMATION2;
			}
		break;
		case PLAYER_LP_CROUCH:
			player[i].animation_load=FIGHTER_LP_CROUCH;
			break;
		case PLAYER_LP:
			player[i].animation_load=FIGHTER_LP;
			break;
		case PLAYER_HP:
			player[i].animation_load=FIGHTER_HP;
			break;
		case PLAYER_HP_CROUCH:
			player[i].animation_load=FIGHTER_HP_CROUCH;
			break;
		case PLAYER_LK_CROUCH:
			player[i].animation_load=FIGHTER_LK_CROUCH;
			break;
		case PLAYER_LK:
			player[i].animation_load=FIGHTER_LK;
			break;
		case PLAYER_HK:
			player[i].animation_load=FIGHTER_HK;
			break;
		case PLAYER_HK_CROUCH:
			player[i].animation_load=FIGHTER_HK_CROUCH;
			break;
		case PLAYER_CROUCH:
			player[i].animation_load=FIGHTER_CROUCH;
			break;
		case PLAYER_JUMP_RIGHT:
			player[i].animation_load=FIGHTER_JUMP_RIGHT;
			break;
		case PLAYER_LP_JUMP_RIGHT:
			player[i].animation_load=FIGHTER_LP_JUMP_RIGHT;
			break;
		case PLAYER_LK_JUMP_RIGHT:
			player[i].animation_load=FIGHTER_LK_JUMP_RIGHT;
			break;
		case PLAYER_HP_JUMP_RIGHT:
			player[i].animation_load=FIGHTER_HP_JUMP_RIGHT;
			break;
		case PLAYER_HK_JUMP_RIGHT:	
			player[i].animation_load=FIGHTER_HK_JUMP_RIGHT;
			break;		
		case PLAYER_JUMP_LEFT:
			player[i].animation_load=FIGHTER_JUMP_LEFT;
			break;
		case PLAYER_LP_JUMP_LEFT:
			player[i].animation_load=FIGHTER_LP_JUMP_LEFT;
			break;
		case PLAYER_LK_JUMP_LEFT:
			player[i].animation_load=FIGHTER_LK_JUMP_LEFT;
			break;
		case PLAYER_HP_JUMP_LEFT:
			player[i].animation_load=FIGHTER_HP_JUMP_LEFT;
			break;
		case PLAYER_HK_JUMP_LEFT:			
			player[i].animation_load=FIGHTER_HK_JUMP_LEFT;
			break;
		case PLAYER_JUMP:
			player[i].animation_load=FIGHTER_JUMP;
			break;
		case PLAYER_LP_JUMP:
			player[i].animation_load=FIGHTER_LP_JUMP;
			break;
		case PLAYER_LK_JUMP:
			player[i].animation_load=FIGHTER_LK_JUMP;
			break;
		case PLAYER_HP_JUMP:
			player[i].animation_load=FIGHTER_HP_JUMP;
			break;
		case PLAYER_HK_JUMP:			
			player[i].animation_load=FIGHTER_HK_JUMP;
			break;

	}

	player[i].frame--;

	//treat jumps
	if( player[i].action == PLAYER_JUMP || player[i].action == PLAYER_JUMP_LEFT || player[i].action == PLAYER_JUMP_RIGHT 
		|| player[i].action == PLAYER_LP_JUMP_LEFT || player[i].action == PLAYER_LP_JUMP_RIGHT || player[i].action == PLAYER_LP_JUMP
		|| player[i].action == PLAYER_LK_JUMP_LEFT || player[i].action == PLAYER_LK_JUMP_RIGHT || player[i].action == PLAYER_LK_JUMP
		|| player[i].action == PLAYER_HP_JUMP_LEFT || player[i].action == PLAYER_HP_JUMP_RIGHT || player[i].action == PLAYER_HP_JUMP
		|| player[i].action == PLAYER_HK_JUMP_LEFT || player[i].action == PLAYER_HK_JUMP_RIGHT || player[i].action == PLAYER_HK_JUMP)
	{

		if(player[i].action == PLAYER_JUMP_LEFT || player[i].action == PLAYER_LP_JUMP_LEFT || player[i].action == PLAYER_LK_JUMP_LEFT
		|| player[i].action == PLAYER_HP_JUMP_LEFT || player[i].action == PLAYER_HK_JUMP_LEFT)
			player[i].posx=player[i].posx-FIGHTER_WALK_SPEED;
		else if(player[i].action == PLAYER_JUMP_RIGHT || player[i].action == PLAYER_LP_JUMP_RIGHT || player[i].action == PLAYER_LK_JUMP_RIGHT
		     || player[i].action == PLAYER_HP_JUMP_RIGHT || player[i].action == PLAYER_HK_JUMP_RIGHT)
			player[i].posx=player[i].posx+FIGHTER_WALK_SPEED;

		 if(player[i].frame>FIGHTER_JUMP_FRAMES){ //up
			player[i].posy=player[i].posy-FIGHTER_JUMP_SPEED;
		}else if(player[i].frame<=FIGHTER_JUMP_FRAMES){ //end raising, start to falling down
			player[i].posy=player[i].posy+FIGHTER_JUMP_SPEED;
		} 

		if((player[i].frame==0) && 
		  ( player[i].action == PLAYER_LP_JUMP_LEFT || player[i].action == PLAYER_LP_JUMP_RIGHT || player[i].action == PLAYER_LP_JUMP
		 || player[i].action == PLAYER_LK_JUMP_LEFT || player[i].action == PLAYER_LK_JUMP_RIGHT || player[i].action == PLAYER_LK_JUMP
		 || player[i].action == PLAYER_HP_JUMP_LEFT || player[i].action == PLAYER_HP_JUMP_RIGHT || player[i].action == PLAYER_HP_JUMP
		 || player[i].action == PLAYER_HK_JUMP_LEFT || player[i].action == PLAYER_HK_JUMP_RIGHT || player[i].action == PLAYER_HK_JUMP))
		{ 
			player[i].frame=player[i].prevframe;
			player[i].prevframe=0;
			player[i].action==PLAYER_JUMP;
		}

		if(player[i].posy==148){ 
			player[i].action = PLAYER_STAND;
		}
	}

	player[i].joystick = 0;

}


for(i=0;i<2;i++)
{
	//revert to default animation
	if(player[i].frame==0)
	{
		player[i].action = PLAYER_STAND;
		player[i].frame=FIGHTER_STAND_FRAMES;
		//player[0].animation_load=0;
	}
}


for(i=0;i<2;i++)
{
	//check collisions
	switch(player[i].action)
	{
		case PLAYER_MOVE_RIGHT:
		case PLAYER_JUMP_RIGHT:
		case PLAYER_STAND:
			if(player[0].posx+32>=player[1].posx+16)
			{ 
				if(player[0].flipx==0)
				{
					player[0].flipx = 1;
					player[1].flipx = 0;
					player[0].animation=255;
					player[1].animation=255;
				}
			}else
			{
				if(player[0].flipx==1)
				{
					player[0].flipx = 0;
					player[1].flipx = 1;
					player[0].animation=255;
					player[1].animation=255;
				}
			}
			//if(player[i].posx+32>=pos2x) pos2x+=2;
		break;
		case PLAYER_HP:
			if(player[0].posx+64>=player[1].posx) 
			{			
				//player[0].posx+=2;
				//load_sprite(6, (unsigned int) sprfighter_hit0, player[1].flipx);
				//load_sprite(7, (unsigned int) sprfighter_hit2, player[1].flipx);
				//player[i].frame=4;
			}
		break;
	}
}


//load & draw sprites
load_sprites();
draw_sprites();

	

	WAIT(1);

}


}
