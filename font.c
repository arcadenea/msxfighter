#include "VDP_TMS9918A.h"



void VPOKEARRAY(unsigned int vaddr, char* text)
{
  while(*(text)){ 
  	VPOKE(vaddr++,*(text++)-32);
  }
}

void TEXT_COLOR(unsigned int bank, char fcolor, char bcolor)
{
  FillVRAM(BASE11+bank, 512, (bcolor<<4)|fcolor); 
}


void PRINT_TEXT(char column, char line, char* text)
{
  unsigned int vaddr = BASE10 + (line*32)+column; // calcula la posicion en la VRAM
  VPOKEARRAY(vaddr, text);
}

void uitoa_print(char column, char line, unsigned char value, unsigned char radix)
{
unsigned char index, i;
unsigned char string[4];

  index = 4;
  i = 0;

  do {
    string[--index] = '0' + (value % radix);
    if ( string[index] > '9') string[index] += 'A' - ':';   /* continue with A, B,.. */
    value /= radix;
  } while (value != 0);

  do {
    string[i++] = string[index++];
  } while ( index < 4 );

  string[i] = 0; /* string terminator */
 PRINT_TEXT(column, line, string);
}






