#include "VDP_TMS9918A.h"
#include "sprite.h"
#include "tilemap.h"
#include "input.h"
#include "tiles.h"
#include "fighter.h"


#define  HALT __asm halt __endasm
#define DEBUG_COLLISIONS 1

#define DIRECTION_UP 1
#define DIRECTION_UPRIGHT 2
#define DIRECTION_RIGHT 3
#define DIRECTION_DOWNRIGHT 4
#define DIRECTION_DOWN 5
#define DIRECTION_DOWNLEFT 6
#define DIRECTION_LEFT 7
#define DIRECTION_UPLEFT 8

#define PLAYER_STAND 0
#define PLAYER_JUMP 1
#define PLAYER_JUMP_RIGHT 2
#define PLAYER_JUMP_LEFT 8
#define PLAYER_MOVE_LEFT 7
#define PLAYER_MOVE_RIGHT 3
#define PLAYER_CROUCH 5
#define PLAYER_LP 10
#define PLAYER_LP_CROUCH 11
#define PLAYER_LP_JUMP 12
#define PLAYER_LK 20
#define PLAYER_LK_CROUCH 21
#define PLAYER_LK_JUMP 22



unsigned char pos1x;
unsigned char pos1y;
unsigned char pos2x;
unsigned char pos2y;
unsigned char jump1;
unsigned char land1;
unsigned char walk1;
unsigned char stand1;
unsigned char sprite1;
unsigned char player1_action;
unsigned char player1_joystick;
unsigned char player1_frame; //frame counter
unsigned char i;


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

	unsigned int vaddr1 = (((posy&0xF8)+16)*4)+((posx&0xf8)/8); // calcula la posicion en la VRAM
	unsigned int vaddr2 = (((posy&0xF8)+16)*4)+(((posx&0xf8)+8)/8); // calcula la posicion en la VRAM

	return 0;
} 


void main(void)
{


//initialize screen mode
//POKE(0xF3AF,32); // set 32 columns per line
COLOR(15,15,15);

setup_sprites(SPRITE16X16, SPRITE_ZOOM);
SCREEN(GRAPH1);



pos1x = 40;
pos1y = 148;
pos2x = 110;
pos2y = 148;
jump1 = 0;
land1 = 1;
walk1 = 0; //estado de la animación de caminar
stand1 = 0;
sprite1=0;

player1_action = PLAYER_STAND;
player1_frame = 0;
player1_joystick = 0;


//cargamos sprites
/*load_sprite(0, (unsigned int) fighter_stand_0, 16, 0);
load_sprite(1, (unsigned int) fighter_stand_1, 16, 0);
load_sprite(0, (unsigned int) fighter_stand_0, 16, 1);
load_sprite(2, (unsigned int) fighter_stand_1, 16, 0);*/
//load_sprite(4, (unsigned int) nick_r3, 16);

load_sprite(0, (unsigned int) sprfighter_stand_00, 16, 0);
load_sprite(1, (unsigned int) sprfighter_stand_01, 16, 0);

load_sprite(6, (unsigned int) sprfighter_stand_00, 16, 1);
load_sprite(7, (unsigned int) sprfighter_stand_01, 16, 1);

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


//FillVRAM(BASE12, 768, 0xA5); //character table
while(1){

//load empty sprites
load_sprite(2, (unsigned int) empty_sprite, 16, 0);
load_sprite(3, (unsigned int) empty_sprite, 16, 0);

	if(walk1>0 && walk1<12){
		load_sprite(0, (unsigned int) sprfighter_stand_00, 16, 0);
		load_sprite(1, (unsigned int) sprfighter_stand_01, 16, 0);
	}else if(walk1>12){
		load_sprite(0, (unsigned int) sprfighter_walk_00, 16, 0);
		load_sprite(1, (unsigned int) sprfighter_walk_01, 16, 0);

	}else if(stand1>0 && stand1<12){
		load_sprite(0, (unsigned int) sprfighter_stand_00, 16, 0);
		load_sprite(1, (unsigned int) sprfighter_stand_01, 16, 0);
	}else{
		load_sprite(0, (unsigned int) sprfighter_stand_10, 16, 0);
		load_sprite(1, (unsigned int) sprfighter_stand_11, 16, 0);

	}


	switch(player1_action)
	{
		case PLAYER_LP_CROUCH:
			load_sprite(0, (unsigned int) empty_sprite, 16, 0);		
			load_sprite(1, (unsigned int) sprfighter_crouch_lp2, 16, 0);
			load_sprite(3, (unsigned int) sprfighter_crouch_lp3, 16, 0);
			break;
		case PLAYER_LP:
			//load_sprite(0, (unsigned int) empty_sprite, 16, 0);		
			load_sprite(0, (unsigned int) sprfighter_lp0, 16, 0);
			load_sprite(1, (unsigned int) sprfighter_lp2, 16, 0);
			load_sprite(2, (unsigned int) sprfighter_lp1, 16, 0);
			break;
		case PLAYER_LK_CROUCH:
			load_sprite(0, (unsigned int) empty_sprite, 16, 0);		
			load_sprite(1, (unsigned int) sprfighter_crouch_lk2, 16, 0);
			load_sprite(3, (unsigned int) sprfighter_crouch_lk3, 16, 0);
			break;
		case PLAYER_LK:
			load_sprite(0, (unsigned int) sprfighter_lk0, 16, 0);		
			load_sprite(1, (unsigned int) sprfighter_lk2, 16, 0);
			load_sprite(3, (unsigned int) sprfighter_lk3, 16, 0);
			break;
		case PLAYER_CROUCH:
			load_sprite(0, (unsigned int) empty_sprite, 16, 0);
			load_sprite(1, (unsigned int) sprfighter_crouch_hit2, 16, 0);
			break;
		case PLAYER_JUMP:
			
			 if(player1_frame<20){ //up
				pos1y=pos1y-4;
				player1_frame++;	
			}else if(player1_frame>=20){ //end raising, start to falling down
				pos1y=pos1y+4;
				player1_frame++;
			} 

			if(pos1y==148){ 
				player1_action = PLAYER_STAND;
				player1_frame=0;
			} 
			
			load_sprite(0, (unsigned int) sprfighter_jump0, 16, 0);
			load_sprite(1, (unsigned int) sprfighter_jump2, 16, 0);
			break;
		case PLAYER_JUMP_RIGHT:
			
			 if(player1_frame<20){ //up
				pos1y=pos1y-4;
				pos1x=pos1x+2;
				player1_frame++;	
			}else if(player1_frame>=20){ //end raising, start to falling down
				pos1y=pos1y+4;
				pos1x=pos1x+2;
				player1_frame++;
			} 

			if(pos1y==148){ 
				player1_action = PLAYER_STAND;
				player1_frame=0;
			} 
			
			load_sprite(0, (unsigned int) sprfighter_jump0, 16, 0);
			load_sprite(1, (unsigned int) sprfighter_jump2, 16, 0);
			break;
		case PLAYER_JUMP_LEFT:
			
			 if(player1_frame<20){ //up
				pos1y=pos1y-4;
				pos1x=pos1x-2;
				player1_frame++;	
			}else if(player1_frame>=20){ //end raising, start to falling down
				pos1y=pos1y+4;
				pos1x=pos1x-2;
				player1_frame++;
			} 

			if(pos1y==148){ 
				player1_action = PLAYER_STAND;
				player1_frame=0;
			} 
			
			load_sprite(0, (unsigned int) sprfighter_jump0, 16, 0);
			load_sprite(1, (unsigned int) sprfighter_jump2, 16, 0);
			break;

	}


	//draw sprites player 1
	draw_sprite(0, pos1x, pos1y-32, BLACK);
	draw_sprite(4, pos1x, pos1y, BLACK);
	draw_sprite(8, pos1x+32, pos1y-32, BLACK);
	draw_sprite(12, pos1x+32, pos1y, BLACK);

	//draw sprites player 2
	draw_sprite(16, pos2x, pos2y-32, DARK_RED);
	draw_sprite(20, pos2x, pos2y, DARK_RED);
	draw_sprite(24, pos2x, pos2y-32, DARK_RED);
	draw_sprite(28, pos2x, pos2y, DARK_RED);

	//read joystick(s) input
	player1_joystick=joystick(0);

	if(player1_frame==0) //if not between a movement
	{
		if((player1_joystick==DIRECTION_RIGHT)&&(pos1x<232))
		{ 
			player1_action = PLAYER_MOVE_RIGHT;
			pos1x=pos1x+2; //derecha
			walk1++;
			stand1=0;
			if(walk1==24) walk1=0;
			switch (checkCollision(pos1x, pos1y, DIRECTION_RIGHT)) 
			{	
				case 0: land1=0;
				break;
				case 2: pos1y=pos1y-2;
				break;
			}
		}else if((player1_joystick==DIRECTION_LEFT)&&(pos1x>=10))
		{	
			player1_action = PLAYER_MOVE_LEFT; 
			pos1x=pos1x-2;
			walk1++;
			stand1=0;
			if(walk1==24) walk1=0;
			switch (checkCollision(pos1x, pos1y, DIRECTION_LEFT)) 
			{	
				case 0: land1=0;
				break;
				case 2: pos1y=pos1y-2;
				break;
			}
		}else if((player1_joystick==DIRECTION_DOWN))
		{
			player1_action = PLAYER_CROUCH;
	
		}else if((player1_joystick==DIRECTION_UP))
		{
			player1_action = PLAYER_JUMP;
	
		}else if((player1_joystick==DIRECTION_UPLEFT))
		{
			player1_action = PLAYER_JUMP_LEFT;
	
		}else if((player1_joystick==DIRECTION_UPRIGHT))
		{
			player1_action = PLAYER_JUMP_RIGHT;
	
		}else if(player1_joystick==0)
		{

			player1_action = PLAYER_STAND;
			stand1++;
			if(stand1==24) stand1=1;
			walk1=0;
		}
	}

	if(joytrig(0))
	{
		switch(player1_action) 
		{
			case PLAYER_CROUCH: player1_action = PLAYER_LP_CROUCH;
			break;
			case PLAYER_STAND: player1_action = PLAYER_LP;
			break;
		}
	}

	if(joytrig(3))
	{
		switch(player1_action) 
		{
			case PLAYER_CROUCH: player1_action = PLAYER_LK_CROUCH;
			break;
			case PLAYER_STAND: player1_action = PLAYER_LK;
			break;
		}
	}
	




	WAIT(1);

}



}
