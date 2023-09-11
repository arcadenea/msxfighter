#include "timer.h"
#include "tilemap.h"
#include "VDP_TMS9918A.h"
#include "input.h"
#include "title_screen.h"
#include "AY38910BF.h"
#include "pt3_player.h"
#include "pt3_notetable2.h"
//#include "music/Fret.h"
#include "music/smario.h"
//#include "font.h"


extern unsigned char FONT[];
extern void PRINT_TEXT(char column, char line, char* text);
extern void TEXT_COLOR(unsigned int bank, char fcolor, char bcolor);


unsigned char condition;
unsigned char pl;
unsigned char frame_count;


unsigned char joy[2];
unsigned char posx;
unsigned char posy;






void title_screen(void)
{

clear_screen(DARK_BLUE);
const unsigned char TEXTO_PRUEBA[]={"PRESS START"};



//cargamos tilemap
load_tileset((unsigned int) FONT, 512, BANK2, 0);
//load_colormap((unsigned int) FONTCOLOR, 512, BANK2, 0); //temp fonts

load_tileset((unsigned int) TITLE_TILESET_0, 1024, BANK0, 512);
load_tileset((unsigned int) TITLE_TILESET_1, 1536, BANK1, 512);
load_tileset((unsigned int) TITLE_TILESET_2, 1536, BANK2, 512);

load_colormap((unsigned int) TITLE_COLORMAP_0, 1536, BANK0, 512);
load_colormap((unsigned int) TITLE_COLORMAP_1, 1536, BANK1, 512);
load_colormap((unsigned int) TITLE_COLORMAP_2, 1536, BANK2, 512); 
load_tilemap((unsigned int) TITLE_TILEMAP, 768, 0); //32*24 tiles


//cargamos música
Player_Init();
Player_InitSong((unsigned int) g_smario, (unsigned int) PT3_NT2, 1) ; //(unsigned char *)
Player_Resume();

TEXT_COLOR(BANK2, WHITE, DARK_BLUE);
PRINT_TEXT(11, 20, TEXTO_PRUEBA);


condition = 0;
pl=0;
posx=10;
posy=20;
frame_count = 0;


while(1){

	WAIT_VBLANK();
	PlayAY();
	Player_Decode(); 
	frame_count++;
	if(frame_count==30)
	{
		TEXT_COLOR(BANK2, DARK_BLUE, DARK_BLUE);
		
	}else if(frame_count==50)
	{
		TEXT_COLOR(BANK2, WHITE, DARK_BLUE);	
		frame_count=0;
	}


//read joy(s) input
for(pl=0;pl<2;pl++)
{
	joy[pl] = joy_read(pl+1);
	if(pl==0 && joy[pl]==0) joy[pl] = joy_read(0);


		if(joy[pl]&JOYSTICK_RIGHT)//&&(player[i].posx<232))
		{ 
            condition = 1;
            posx++;
		}else if(joy[pl]&JOYSTICK_LEFT)//&&(player[i].posx>=10))
		{	
            posx--;
		} 
		
		if((joy[pl]&JOYSTICK_DOWN))
		{
            posy++;
	
		}else if((joy[pl]&JOYSTICK_UP))
		{
            posy--;

		}

	

	if(joy[pl]&JOYSTICK_TRIGA)
	{

	}

	if(joy[pl]&JOYSTICK_TRIGB)
	{

	}

}

    //PRINT_TEXT(posy, posx, TEXTO_PRUEBA);

    if(condition) return;





}

}
