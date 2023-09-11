

#define  HALT __asm halt __endasm
__at 0xFC9E unsigned int jiffy; //the damn jiffy variable

void WAIT_VBLANK() __z88dk_fastcall
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
