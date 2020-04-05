#ifndef  __SPRITE_H__
#define  __SPRITE_H__

#define SPRITE8X8      8
#define SPRITE16X16   32

#define SPRITE_NO_ZOOM 0
#define SPRITE_ZOOM    1

void setup_sprites(char spritesize, char zoom);

void load_sprite(unsigned char index, unsigned int sprite, unsigned char flipx);

void draw_sprite(unsigned char index, unsigned char posx, unsigned char posy, unsigned char color);

void invert_sprite_x(unsigned int source, unsigned int dest);

#endif
