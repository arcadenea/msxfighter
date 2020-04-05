

#include "input.h"

char joystick(char n) __naked {
	/*
		GTSTCK (00D5H)		*1
		Function:	returns the joystick status
		Input:	A for the joystick number to be tested
		Output:	A for the joystick direction
		Registers:	all
	*/
    __asm
  	push	ix  	; prologue
	ld	ix,#0
	add	ix,sp

	push af         ; body
    ld a,4(ix)
    call 0x00d5
    ld l,a
    pop af

	pop	ix          ; epilogue
	ret
	__endasm;
}

char joytrig(char n) __naked {

	/*
		GTTRIG (00D8H)		*1
		Function:	returns the trigger button status
		Input:	A for the trigger button number to be tested
		Output:	When A is 0, the trigger button is not being pressed.
		When A is FFH, the trigger button is being pressed.
		Registers:	AF
	*/

	__asm
  	push	ix  	; prologue
	ld	ix,#0
	add	ix,sp

	push af         ; body
    ld a,4(ix)
    call 0x00d8
    ld h,#0x00
    ld l,a
    pop af

    pop	ix          ; epilogue
	ret
  __endasm;
}

//read joystick input, return
char joy_read(char n)
{
	char status=0;
	
	switch(joystick(n))
	{
		case DIRECTION_UP: //1
			status |= JOYSTICK_UP;
			break;
		case DIRECTION_UPRIGHT: //2
			status |= (JOYSTICK_UP|JOYSTICK_RIGHT);
			break;
		case DIRECTION_RIGHT: //3
			status |= JOYSTICK_RIGHT;
			break;
		case DIRECTION_DOWNRIGHT: //4
			status |= (JOYSTICK_DOWN|JOYSTICK_RIGHT);			
			break;
		case DIRECTION_DOWN: //5
			status |= JOYSTICK_DOWN;
			break;
		case DIRECTION_DOWNLEFT: //6
			status |= (JOYSTICK_DOWN|JOYSTICK_LEFT);
			break;
		case DIRECTION_LEFT: //7
			status |= JOYSTICK_LEFT;
			break;
		case DIRECTION_UPLEFT: //8
			status |= (JOYSTICK_UP|JOYSTICK_LEFT);
			break;
	}

	//read buttons

	if(n==1)
	{
		if(joytrig(1)) status |= JOYSTICK_TRIGA; //joy1 button 1
		if(joytrig(3)) status |= JOYSTICK_TRIGB;	//joy1 button 2
	}else if (n==2)
	{
		if(joytrig(2)) status |= JOYSTICK_TRIGA; //joy2 button 1
		if(joytrig(4)) status |= JOYSTICK_TRIGB;	//joy2 button 2

	}

	return status;

}

