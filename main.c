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
	unsigned char spr_index; //start position of sprite order
};

struct players player[2];
unsigned char i;

unsigned int * frames[256];


const unsigned char empty_sprite[]={
0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00
};


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
  int i;
  for(i=0;i<cicles;i++) HALT;
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


void main(void)
{

unsigned char i=0;
//initialize screen mode
//POKE(0xF3AF,32); // set 32 columns per line
COLOR(15,15,15);

setup_sprites(SPRITE16X16, SPRITE_ZOOM);
SCREEN(GRAPH1);

player[i].flipx = 0;
player[0].posx = 40;
player[0].posy = 148;
player[0].animation_load=255;
player[0].prevframe=0;
player[0].frame=FIGHTER_STAND_FRAMES;
player[0].action=PLAYER_STAND;
player[0].joystick = 0;
player[0].joy_trigp = 0;
player[0].joy_trigk = 0;
player[0].color=BLACK;
player[0].spr_index=0;
player[0].animation=255;

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
player[1].spr_index=4;
player[1].animation=255;

//FIGHTER_STAND_ANIMATION1 	
frames[0] = (unsigned int *) sprfighter_stand_00;
frames[1] = (unsigned int *) sprfighter_stand_01;
frames[2] = (unsigned int *) empty_sprite;
frames[3] = (unsigned int *) empty_sprite;
// FIGHTER_STAND_ANIMATION2 	 
frames[4] = (unsigned int *) sprfighter_stand_10;
frames[5] = (unsigned int *) sprfighter_stand_11;
frames[6] = (unsigned int *) empty_sprite;
frames[7] = (unsigned int *) empty_sprite;
// FIGHTER_WALK_ANIMATION1 	 
frames[8] = (unsigned int *) sprfighter_stand_10;
frames[9] = (unsigned int *) sprfighter_stand_11;
frames[10] = (unsigned int *) empty_sprite;
frames[11] = (unsigned int *) empty_sprite;
// FIGHTER_WALK_ANIMATION2 
frames[12] = (unsigned int *) sprfighter_walk_00;
frames[13] = (unsigned int *) sprfighter_walk_01;
frames[14] = (unsigned int *) empty_sprite;
frames[15] = (unsigned int *) empty_sprite;
// FIGHTER_CROUCH				
frames[16] = (unsigned int *) empty_sprite;
frames[17] = (unsigned int *) sprfighter_crouch2;
frames[18] = (unsigned int *) empty_sprite;
frames[19] = (unsigned int *) empty_sprite;
// FIGHTER_LP					
frames[20] = (unsigned int *) sprfighter_lp0;
frames[21] = (unsigned int *) sprfighter_lp2;
frames[22] = (unsigned int *) sprfighter_lp1;
frames[23] = (unsigned int *) empty_sprite;
// FIGHTER_HP					
frames[24] = (unsigned int *) sprfighter_hp0;
frames[25] = (unsigned int *) sprfighter_hp2;
frames[26] = (unsigned int *) sprfighter_hp1;
frames[27] = (unsigned int *) empty_sprite;
// FIGHTER_LK					
frames[28] = (unsigned int *) sprfighter_lk0;
frames[29] = (unsigned int *) sprfighter_lk2;
frames[30] = (unsigned int *) empty_sprite;
frames[31] = (unsigned int *) sprfighter_lk3;
// FIGHTER_HK					
frames[32] = (unsigned int *) sprfighter_hk0;
frames[33] = (unsigned int *) sprfighter_hk2;
frames[34] = (unsigned int *) empty_sprite;
frames[35] = (unsigned int *) sprfighter_hk3;
// FIGHTER_LP_CROUCH			
frames[36] = (unsigned int *) empty_sprite;
frames[37] = (unsigned int *) sprfighter_crouch_lp2;
frames[38] = (unsigned int *) empty_sprite;
frames[39] = (unsigned int *) sprfighter_crouch_lp3;
// FIGHTER_HP_CROUCH			
frames[40] = (unsigned int *) sprfighter_crouch_hp0;
frames[41] = (unsigned int *) sprfighter_crouch_hp2;
frames[42] = (unsigned int *) sprfighter_crouch_hp1;
frames[43] = (unsigned int *) sprfighter_crouch_hp3;
// FIGHTER_LK_CROUCH			
frames[44] = (unsigned int *) empty_sprite;
frames[45] = (unsigned int *) sprfighter_crouch_lk2;
frames[46] = (unsigned int *) empty_sprite;
frames[47] = (unsigned int *) sprfighter_crouch_lk3;
// FIGHTER_HK_CROUCH			
frames[48] = (unsigned int *) empty_sprite;
frames[49] = (unsigned int *) sprfighter_crouch_hk2;
frames[50] = (unsigned int *) empty_sprite;
frames[51] = (unsigned int *) sprfighter_crouch_hk3;
// FIGHTER_JUMP				
frames[52] = (unsigned int *) sprfighter_jump0;
frames[53] = (unsigned int *) sprfighter_jump2;
frames[54] = (unsigned int *) empty_sprite;
frames[55] = (unsigned int *) empty_sprite;
// FIGHTER_LP_JUMP				
frames[56] = (unsigned int *) sprfighter_jump_lp0;
frames[57] = (unsigned int *) sprfighter_jump_lp2;
frames[58] = (unsigned int *) sprfighter_jump_lp1;
frames[59] = (unsigned int *) sprfighter_jump_lp3;
// FIGHTER_LK_JUMP				
frames[60] = (unsigned int *) sprfighter_jump_lk0;
frames[61] = (unsigned int *) sprfighter_jump_lk2;
frames[62] = (unsigned int *) empty_sprite;
frames[63] = (unsigned int *) empty_sprite;
// FIGHTER_HP_JUMP				
frames[64] = (unsigned int *) sprfighter_jump_lp0;
frames[65] = (unsigned int *) sprfighter_jump_lp2;
frames[66] = (unsigned int *) sprfighter_jump_lp1;
frames[67] = (unsigned int *) sprfighter_jump_lp3;
// FIGHTER_HK_JUMP				
frames[68] = (unsigned int *) sprfighter_jump_hk0;
frames[69] = (unsigned int *) sprfighter_jump_hk2;
frames[70] = (unsigned int *) empty_sprite;
frames[71] = (unsigned int *) sprfighter_jump_hk3;
// FIGHTER_JUMP_RIGHT			
frames[72] = (unsigned int *) sprfighter_jump0;
frames[73] = (unsigned int *) sprfighter_jump2;
frames[74] = (unsigned int *) empty_sprite;
frames[75] = (unsigned int *) empty_sprite;
// FIGHTER_LP_JUMP_RIGHT		
frames[76] = (unsigned int *) sprfighter_jump_lp0;
frames[77] = (unsigned int *) sprfighter_jump_lp2;
frames[78] = (unsigned int *) sprfighter_jump_lp1;
frames[79] = (unsigned int *) sprfighter_jump_lp3;
// FIGHTER_LK_JUMP_RIGHT		
frames[80] = (unsigned int *) sprfighter_jump_lk0;
frames[81] = (unsigned int *) sprfighter_jump_lk2;
frames[82] = (unsigned int *) empty_sprite;
frames[83] = (unsigned int *) empty_sprite;
// FIGHTER_HP_JUMP_RIGHT		
frames[84] = (unsigned int *) sprfighter_walk_00;
frames[85] = (unsigned int *) sprfighter_walk_01;
frames[86] = (unsigned int *) empty_sprite;
frames[87] = (unsigned int *) empty_sprite;
// FIGHTER_HK_JUMP_RIGHT		
frames[88] = (unsigned int *) sprfighter_jump_hk0;
frames[89] = (unsigned int *) sprfighter_jump_hk2;
frames[90] = (unsigned int *) empty_sprite;
frames[91] = (unsigned int *) sprfighter_jump_hk3;
// FIGHTER_JUMP_LEFT			
frames[92] = (unsigned int *) sprfighter_jump0;
frames[93] = (unsigned int *) sprfighter_jump2;
frames[94] = (unsigned int *) empty_sprite;
frames[95] = (unsigned int *) empty_sprite;
// FIGHTER_LP_JUMP_LEFT		
frames[96] = (unsigned int *) sprfighter_jump_lp0;
frames[97] = (unsigned int *) sprfighter_jump_lp2;
frames[98] = (unsigned int *) sprfighter_jump_lp1;
frames[99] = (unsigned int *) sprfighter_jump_lp3;
// FIGHTER_LK_JUMP_LEFT		
frames[100] = (unsigned int *) sprfighter_jump_lk0;
frames[101] = (unsigned int *) sprfighter_jump_lk2;
frames[102] = (unsigned int *) empty_sprite;
frames[103] = (unsigned int *) empty_sprite;
// FIGHTER_HP_JUMP_LEFT	   
frames[104] = (unsigned int *) sprfighter_walk_00;
frames[105] = (unsigned int *) sprfighter_walk_01;
frames[106] = (unsigned int *) empty_sprite;
frames[107] = (unsigned int *) empty_sprite;
// FIGHTER_HK_JUMP_LEFT	   
frames[108] = (unsigned int *) sprfighter_jump_hk0;
frames[109] = (unsigned int *) sprfighter_jump_hk2;
frames[110] = (unsigned int *) empty_sprite;
frames[111] = (unsigned int *) sprfighter_jump_hk3;



//cargamos tilemap
load_tileset((unsigned int) TILESET_0, 2048, BANK0);
load_tileset((unsigned int) TILESET_1, 2048, BANK1);
load_tileset((unsigned int) TILESET_2, 2048, BANK2);
load_colormap((unsigned int) COLORMAP_0, 2048, BANK0);
load_colormap((unsigned int) COLORMAP_1, 2048, BANK1);
load_colormap((unsigned int) COLORMAP_2, 2048, BANK2); 
load_tilemap((unsigned int) TILEMAP, 768); //32*24 tiles


/*sprite order
Player 1	Player 2
0	2		4	6
1	3		5	7
*/


while(1){


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
			//player[0].animation_load=255;
		}else if(player[i].joystick&JOYSTICK_LEFT)//&&(player[i].posx>=10))
		{	
			player[i].action = PLAYER_MOVE_LEFT; 
			player[i].frame=FIGHTER_WALK_FRAMES;
			//player[0].animation_load=255;
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
				//	player[i].prevframe = player[i].frame; //backup frames
				break;
				case PLAYER_JUMP_LEFT: 
					player[i].action = PLAYER_HK_JUMP_LEFT;
				//	player[i].prevframe = player[i].frame; //backup frames
				break;
				case PLAYER_JUMP_RIGHT: 
					player[i].action = PLAYER_HK_JUMP_RIGHT;
				//	player[i].prevframe = player[i].frame; //backup frames
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
					//player[i].prevframe = player[i].frame; //backup frames
				break;
				case PLAYER_JUMP_LEFT: 
					player[i].action = PLAYER_LK_JUMP_LEFT;
					//player[i].prevframe = player[i].frame; //backup frames
				break;
				case PLAYER_JUMP_RIGHT: 
					player[i].action = PLAYER_LK_JUMP_RIGHT;
					//player[i].prevframe = player[i].frame; //backup frames
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


//draw sprites
	
	if(player[0].animation!=player[0].animation_load)
	{
		load_sprite(player[0].spr_index, (unsigned int) frames[player[0].animation_load], player[0].flipx);
		load_sprite(player[0].spr_index+1, (unsigned int) frames[player[0].animation_load+1], player[0].flipx);	
		load_sprite(player[0].spr_index+2, (unsigned int) frames[player[0].animation_load+2], player[0].flipx);
		load_sprite(player[0].spr_index+3, (unsigned int) frames[player[0].animation_load+3], player[0].flipx);
		player[0].animation=player[0].animation_load;
	}

	if(player[1].animation!=player[1].animation_load)
	{
		load_sprite(player[1].spr_index, (unsigned int) frames[player[1].animation_load], player[1].flipx);
		load_sprite(player[1].spr_index+1, (unsigned int) frames[player[1].animation_load+1], player[1].flipx);	
		load_sprite(player[1].spr_index+2, (unsigned int) frames[player[1].animation_load+2], player[1].flipx);
		load_sprite(player[1].spr_index+3, (unsigned int) frames[player[1].animation_load+3], player[1].flipx);
		player[1].animation=player[1].animation_load;
	}

	if(player[0].flipx==0)
	{
		draw_sprite(0, player[0].posx, player[0].posy-32, player[0].color);
		draw_sprite(4, player[0].posx, player[0].posy, player[0].color);
		draw_sprite(8, player[0].posx+32, player[0].posy-32, player[0].color);
		draw_sprite(12, player[0].posx+32, player[0].posy, player[0].color);

		draw_sprite(16, player[1].posx, player[1].posy-32, player[1].color);
		draw_sprite(20, player[1].posx, player[1].posy, player[1].color);
		draw_sprite(24, player[1].posx-32, player[1].posy-32, player[1].color);
		draw_sprite(28, player[1].posx-32, player[1].posy, player[1].color);
	}else{
		draw_sprite(0, player[0].posx, player[0].posy-32, player[0].color);
		draw_sprite(4, player[0].posx, player[0].posy, player[0].color);
		draw_sprite(8, player[0].posx-32, player[0].posy-32, player[0].color);
		draw_sprite(12, player[0].posx-32, player[0].posy, player[0].color);

		draw_sprite(16, player[1].posx, player[1].posy-32, player[1].color);
		draw_sprite(20, player[1].posx, player[1].posy, player[1].color);
		draw_sprite(24, player[1].posx+32, player[1].posy-32, player[1].color);
		draw_sprite(28, player[1].posx+32, player[1].posy, player[1].color);
	}


	WAIT(1);

}


}
