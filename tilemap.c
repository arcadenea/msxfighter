#include "VDP_TMS9918A.h"
#include "tilemap.h"



void load_tileset(unsigned int tileset, int size, int bank)
{
	CopyToVRAM((unsigned int) tileset, BASE12+bank, size); //character table
}


void load_colormap(unsigned int tileset, int size, int bank)
{
	CopyToVRAM((unsigned int) tileset, BASE11+bank, size);
}


void load_tilemap(unsigned int tileset, int size)
{
	CopyToVRAM((unsigned int) tileset, BASE10, size);
}
