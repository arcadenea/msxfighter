#ifndef  __SPRITE_H__
#define  __SPRITE_H__

#define SPRITE8X8      8
#define SPRITE16X16   32

#define SPRITE_NO_ZOOM 0
#define SPRITE_ZOOM    1


void setup_sprites(char spritesize, char zoom);

unsigned char load_sprite(unsigned int sprite, unsigned char flipx);
unsigned char load_sprite_unmanaged(unsigned char index, unsigned int sprite);

void draw_sprite(unsigned char index, unsigned char spr_index, unsigned char posx, unsigned char posy, unsigned char color);

void invert_sprite_x(unsigned int source, unsigned int dest);

void init_sprite_manager();


#endif
