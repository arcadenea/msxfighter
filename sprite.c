

#include "VDP_TMS9918A.h"
#include "sprite.h"

struct sprite_element {
	unsigned char usage;
	unsigned char index;
	unsigned int  sprite;
	unsigned char flip;
	unsigned char character; //fighter number
};

struct sprite_element sprite_list_vram[60]; //sprites in vram

void setup_sprites(char spritesize, char zoom) __naked {

	/*
		CLRSPR (0069H)		*3
		Function:	initialises all sprites. The sprite pattern is cleared to
		null, the sprite number to the sprite plane number, the
		sprite colour to the foregtound colour. The vertical location
		of the sprite is set to 209 (mode 0 to 3) or 217
		(mode 4 to 8).
		Input:	SCRMOD (FCAFH) for the screen mode
		Output:	none
		Registers:	all

		SETT32 (007BH)		*3
		Function:	set only VDP in GRAPHIC1 mode (32x24)
		Input:	same as INIT32
		Output:	none
		Registers:	all
	*/

	__asm

	push ix  	; prologue
	ld	ix,#0
	add	ix,sp

	push de
	push hl
  
	ld b,#0x00
	ld a,4(ix)
	and #0x0f
	cp #0x08
	jr z,$1
	set 1,b ; --- if 16x16 sprites => set bit 1
$1:
	ld a,5(ix)
	cp #0x00
	jr z, $2
	set 0,b ; --- if zoom sprites => set bit 0
$2:
	ld hl,#0xf3e0 ; --- read vdp(1) from mem
	ld a,(hl)
	and #0xfc
	or b
	ld (hl),a
	call 0x007b ; --- change vdp(1) bits

	ld a,#0x01
	ld hl,#0xfcaf
	ld (hl),a
	call 0x0069 ; --- reset sprite attributes

	pop hl
	pop de

	pop	ix           ;epilogue
	ret

	__endasm;
}

void invert_sprite_x(unsigned int source, unsigned int dest) __naked {

	__asm

	push ix  	; prologue
	ld	ix,#0
	add	ix,sp

	;push af    ; body
	;push bc
	push de
	push hl
	;push iy

	ld l,4(ix)
	ld h,5(ix)
	ld e,6(ix)
	ld d,7(ix)

	push hl
	push de
   
	exx
		    ; we keep pointers to the other columns of the sprite on the shadow registers
		    pop de
		    pop hl
		    ld bc,#16
		    add hl,bc

		exx
		ld bc,#16
		ex de,hl
		add hl,bc
		ex de,hl    ; at this point, we have de pointing to the destination byte for (hl)
		ld b,#16

	$invert_sprite_in_x_external_loop:
		push bc
		ld c,(hl)
		; reverses byte c into a
		ld b,#8
	$invert_sprite_in_x_loop1:
		sra c
		rl a
		djnz $invert_sprite_in_x_loop1
		ex de,hl
		call #0x004D
		ex de,hl		
		inc hl
		inc de
		exx
		    ld c,(hl)
		    ; reverses byte c into a
		    ld b,#8
	$invert_sprite_in_x_loop2:
		    sra c
		    rl a
		    djnz $invert_sprite_in_x_loop2
		    ;ld (de),a
			ex de,hl
			call #0x004D
			ex de,hl
		    inc hl
		    inc de
		exx    
		pop bc    
		djnz $invert_sprite_in_x_external_loop

	;pop iy
	pop hl
	pop de
	;pop bc
	;pop af

	pop ix
	ret

	__endasm;

}

//raw, fast load of sprite without flipping
unsigned char load_sprite_unmanaged(unsigned char index, unsigned int sprite)
{
		//if(flipx) invert_sprite_x((unsigned int) sprite, BASE14+(((unsigned int)index)<<5));
		//else 
		CopyToVRAM((unsigned int) sprite, BASE14+(((unsigned int)index)<<5), 32);
}

unsigned char load_sprite(unsigned int sprite, unsigned char flipx)
{
	unsigned char i;
	unsigned char less_usage = 0; //sprite with less usage in vram


	for(i = 0; i<=60; i++)
	{

		if((sprite_list_vram[i].sprite == sprite) 	&&
			(sprite_list_vram[i].flip == flipx)		&&
			(sprite_list_vram[i].character == 0))
		{
			if(sprite_list_vram[i].usage < 255) sprite_list_vram[i].usage++;	
			return sprite_list_vram[i].index; //sprite is in vram, return index
		}

		if(sprite_list_vram[less_usage].usage > sprite_list_vram[i].usage) less_usage = i;
		if(sprite_list_vram[i].usage > 0) sprite_list_vram[i].usage--;
	}

		sprite_list_vram[less_usage].character = 0;
		sprite_list_vram[less_usage].usage = 255;
		sprite_list_vram[less_usage].index = less_usage;
		sprite_list_vram[less_usage].sprite = sprite;
		sprite_list_vram[less_usage].flip = flipx;

		if(flipx) invert_sprite_x((unsigned int) sprite, BASE14+(((unsigned int)less_usage)<<5));
		else CopyToVRAM((unsigned int) sprite, BASE14+(((unsigned int)less_usage)<<5), 32);

		return sprite_list_vram[less_usage].index;

}


/*The lower 4 bits of ``colour sprite'' define the colour. Bit 7 is the EC.
Bits 6 - 4 should be zero officially, but they are ignored. If the colour is 
0, the sprite is transparent (not visible).*/

void draw_sprite(unsigned char index, unsigned char spr_index, unsigned char posx, unsigned char posy, unsigned char color)
{
	VPOKE(BASE13+(index<<2), posy); //sprite1y
	VPOKE(BASE13+(index<<2)+1, posx); //sprite1x
	VPOKE(BASE13+(index<<2)+2, spr_index<<2); //sprite1index
	VPOKE(BASE13+(index<<2)+3, color); //sprite1color
}


int is_sprite_in_vram(unsigned int sprite)
{


}


void init_sprite_manager()
{

unsigned char i;
	for(i = 0; i<=60; i++)
	{
		sprite_list_vram[i].character = 0;
		sprite_list_vram[i].usage = 0;
		sprite_list_vram[i].index = 63;
		sprite_list_vram[i].sprite = 0;
		sprite_list_vram[i].flip = 0;

	}
}

