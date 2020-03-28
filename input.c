

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
