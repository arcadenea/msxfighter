#ifndef  __FONT_H__
#define  __FONT_H__

void PRINT_TEXT(char column, char line, char* text);
void TEXT_COLOR(unsigned int bank, char fcolor, char bcolor);
void uitoa_print(char column, char line, unsigned char value, unsigned char radix);

const unsigned char FONT[]={
0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, //espacio
0xf7, 0xf7, 0xf7, 0xf7, 0xff, 0xf7, 0xff, 0xff, 
0xd7, 0xd7, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 
0xff, 0xd7, 0x7c, 0xd7, 0x7c, 0xd7, 0xff, 0xff, 
0xf7, 0xe1, 0xd7, 0xe3, 0xf5, 0xc3, 0xf7, 0xff, 
0x9f, 0x6b, 0x97, 0xe9, 0xd6, 0xf9, 0xff, 0xff, 
0xe3, 0xdf, 0xdf, 0xe6, 0xd9, 0xe6, 0xff, 0xff, 
0xf7, 0xf7, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 
0xf7, 0xef, 0xdf, 0xdf, 0xef, 0xf7, 0xff, 0xff, 
0xef, 0xf7, 0xfb, 0xfb, 0xf7, 0xef, 0xff, 0xff, 
0xd5, 0xe3, 0x3e, 0xe3, 0xd5, 0xff, 0xff, 0xff, 
0xff, 0xf7, 0xf7, 0x3e, 0xf7, 0xf7, 0xff, 0xff, 
0xff, 0xff, 0xff, 0xff, 0xff, 0xf7, 0xef, 0xff, 
0xff, 0xff, 0xff, 0xc3, 0xff, 0xff, 0xff, 0xff, 
0xff, 0xff, 0xff, 0xff, 0xff, 0xf7, 0xff, 0xff, 
0xfd, 0xfb, 0xf7, 0xef, 0xdf, 0xbf, 0xff, 0xff, 
0xe7, 0xdb, 0xbd, 0xbd, 0xdb, 0xe7, 0xff, 0xe3, 
0xff, 0xf7, 0xe7, 0xf7, 0xf7, 0xf7, 0xe3, 0xff, //1
0xff, 0xc3, 0xbd, 0xfb, 0xe7, 0xdf, 0x81, 0xff, //2
0xff, 0xc3, 0xbd, 0xfb, 0xe7, 0xbd, 0xc3, 0xff, //3
0xff, 0xf7, 0xe7, 0xd7, 0xb7, 0x83, 0xf7, 0xff, //4
0xff, 0x81, 0xbf, 0x83, 0xfd, 0xbd, 0xc3, 0xff, //5
0xff, 0xc3, 0xbf, 0x83, 0xbd, 0xbd, 0xc3, 0xff, //6
0xff, 0x81, 0xfb, 0xf7, 0xef, 0xdf, 0xbf, 0xff, //7
0xff, 0xc3, 0xbd, 0xc3, 0xbd, 0xbd, 0xc3, 0xff, //8
0xff, 0xc3, 0xbd, 0xbd, 0xc1, 0xfd, 0xc3, 0xff, //9
0xff, 0xff, 0xff, 0xf7, 0xff, 0xff, 0xf7, 0xff, 
0xff, 0xff, 0xff, 0xf7, 0xff, 0xff, 0xf7, 0xff, 
0xff, 0xff, 0xf9, 0xe7, 0x9f, 0xe7, 0xf9, 0xff, 
0xff, 0xff, 0xff, 0x7e, 0xff, 0x7e, 0xff, 0xff, 
0xff, 0xff, 0x9f, 0xe7, 0xf9, 0xe7, 0x9f, 0xff, 
0xff, 0xc7, 0xbb, 0xfb, 0xe7, 0xff, 0xef, 0xff, 
0xff, 0xff, 0xc3, 0xbb, 0x63, 0x6b, 0xa3, 0xff, 
0xe7, 0xe7, 0xdb, 0xc3, 0xbd, 0xbd, 0xff, 0xff, //A
0x87, 0xbb, 0x87, 0xbb, 0xbb, 0x87, 0xff, 0xff, //B
0xc7, 0xbb, 0x7f, 0x7f, 0xbb, 0xc7, 0xff, 0xff, //C
0x87, 0xbb, 0xbb, 0xbb, 0xbb, 0x87, 0xff, 0xff, //D
0x83, 0xbf, 0x87, 0xbf, 0xbf, 0x83, 0xff, 0xff, //E
0x83, 0xbf, 0x87, 0xbf, 0xbf, 0xbf, 0xff, 0xff, //F
0xc7, 0xbb, 0x7f, 0x63, 0xbb, 0xc7, 0xff, 0xff, //G
0xbd, 0xbd, 0x81, 0xbd, 0xbd, 0xbd, 0xff, 0xff, //H
0xc1, 0xf7, 0xf7, 0xf7, 0xf7, 0xc1, 0xff, 0xff, //I
0xe3, 0xfb, 0xfb, 0xfb, 0xbb, 0xc7, 0xff, 0xff, //J
0xbb, 0xb7, 0xaf, 0x8f, 0xb7, 0xbb, 0xff, 0xff, //K
0xbf, 0xbf, 0xbf, 0xbf, 0xbf, 0x81, 0xff, 0xff, //L
0xbe, 0x9c, 0xaa, 0xb6, 0xbe, 0xbe, 0xff, 0xff, //M
0xbd, 0x9d, 0xad, 0xb5, 0xb9, 0xbd, 0xff, 0xff, //N
0xe3, 0xdd, 0xdd, 0xdd, 0xdd, 0xe3, 0xff, 0xff, //O
0x87, 0xbb, 0x87, 0xbf, 0xbf, 0xbf, 0xff, 0xff, //P
0xe3, 0xdd, 0xdd, 0xdd, 0xdd, 0xe3, 0xfd, 0xff, //Q
0x87, 0xbb, 0x87, 0xaf, 0xb7, 0xbb, 0xff, 0xff, //R
0xe3, 0xdd, 0xef, 0xf3, 0xdd, 0xe3, 0xff, 0xff, //S
0x80, 0xf7, 0xf7, 0xf7, 0xf7, 0xf7, 0xff, 0xff, //T
0xbd, 0xbd, 0xbd, 0xbd, 0xbd, 0xc3, 0xff, 0xff, //U
0x7e, 0xbd, 0xbd, 0xdb, 0xdb, 0xe7, 0xff, 0xff, //V
0xbe, 0xbe, 0xb6, 0xaa, 0x9c, 0xbe, 0xff, 0xff, //W
0xbd, 0xdb, 0xe7, 0xe7, 0xdb, 0xbd, 0xff, 0xff, //X
0xbe, 0xdd, 0xeb, 0xf7, 0xf7, 0xf7, 0xff, 0xff, //Y
0x81, 0xfb, 0xf7, 0xef, 0xdf, 0x81, 0xff, 0xff, //Z 
0xc7, 0xdf, 0xdf, 0xdf, 0xdf, 0xc7, 0xff, 0xff, 
0xbf, 0xdf, 0xef, 0xf7, 0xfb, 0xfd, 0xff, 0xff, 
0xc7, 0xf7, 0xf7, 0xf7, 0xf7, 0xc7, 0xff, 0xff, 
0xef, 0xd7, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 
0xff, 0xff, 0xff, 0xff, 0xff, 0x7e, 0xff, 0xff, 
0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff
};

/*
const unsigned char FONTCOLOR[]={
0x10,0x10,0x10,0x10,0x10,0x10,0x10,0x10,0x10,0x10,0x10,0x10,0x10,0x10,0x10,0x10,0x10,0x10,0x10,0x10,0x10,0x10,0x10,0x10,
0x10,0x10,0x10,0x10,0x10,0x10,0x10,0x10,0x10,0x10,0x10,0x10,0x10,0x10,0x10,0x10,0x10,0x10,0x10,0x10,0x10,0x10,0x10,0x10,
0x10,0x10,0x10,0x10,0x10,0x10,0x10,0x10,0x10,0x10,0x10,0x10,0x10,0x10,0x10,0x10,0x10,0x10,0x10,0x10,0x10,0x10,0x10,0x10,
0x10,0x10,0x10,0x10,0x10,0x10,0x10,0x10,0x10,0x10,0x10,0x10,0x10,0x10,0x10,0x10,0x10,0x10,0x10,0x10,0x10,0x10,0x10,0x10,
0x10,0x10,0x10,0x10,0x10,0x10,0x10,0x10,0x10,0x10,0x10,0x10,0x10,0x10,0x10,0x10,0x10,0x10,0x10,0x10,0x10,0x10,0x10,0x10,
0x10,0x10,0x10,0x10,0x10,0x10,0x10,0x10,0x10,0x10,0x10,0x10,0x10,0x10,0x10,0x10,0x10,0x10,0x10,0x10,0x10,0x10,0x10,0x10,
0x10,0x10,0x10,0x10,0x10,0x10,0x10,0x10,0x10,0x10,0x10,0x10,0x10,0x10,0x10,0x10,0x10,0x10,0x10,0x10,0x10,0x10,0x10,0x10,
0x10,0x10,0x10,0x10,0x10,0x10,0x10,0x10,0x10,0x10,0x10,0x10,0x10,0x10,0x10,0x10,0x10,0x10,0x10,0x10,0x10,0x10,0x10,0x10,
0x10,0x10,0x10,0x10,0x10,0x10,0x10,0x10,0x10,0x10,0x10,0x10,0x10,0x10,0x10,0x10,0x10,0x10,0x10,0x10,0x10,0x10,0x10,0x10,
0x10,0x10,0x10,0x10,0x10,0x10,0x10,0x10,0x10,0x10,0x10,0x10,0x10,0x10,0x10,0x10,0x10,0x10,0x10,0x10,0x10,0x10,0x10,0x10,
0x10,0x10,0x10,0x10,0x10,0x10,0x10,0x10,0x10,0x10,0x10,0x10,0x10,0x10,0x10,0x10,0x10,0x10,0x10,0x10,0x10,0x10,0x10,0x10,
0x10,0x10,0x10,0x10,0x10,0x10,0x10,0x10,0x10,0x10,0x10,0x10,0x10,0x10,0x10,0x10,0x10,0x10,0x10,0x10,0x10,0x10,0x10,0x10,
0x10,0x10,0x10,0x10,0x10,0x10,0x10,0x10,0x10,0x10,0x10,0x10,0x10,0x10,0x10,0x10,0x10,0x10,0x10,0x10,0x10,0x10,0x10,0x10,
0x10,0x10,0x10,0x10,0x10,0x10,0x10,0x10,0x10,0x10,0x10,0x10,0x10,0x10,0x10,0x10,0x10,0x10,0x10,0x10,0x10,0x10,0x10,0x10,
0x10,0x10,0x10,0x10,0x10,0x10,0x10,0x10,0x10,0x10,0x10,0x10,0x10,0x10,0x10,0x10,0x10,0x10,0x10,0x10,0x10,0x10,0x10,0x10,
0x10,0x10,0x10,0x10,0x10,0x10,0x10,0x10,0x10,0x10,0x10,0x10,0x10,0x10,0x10,0x10,0x10,0x10,0x10,0x10,0x10,0x10,0x10,0x10,
0x10,0x10,0x10,0x10,0x10,0x10,0x10,0x10,0x10,0x10,0x10,0x10,0x10,0x10,0x10,0x10,0x10,0x10,0x10,0x10,0x10,0x10,0x10,0x10,
0x10,0x10,0x10,0x10,0x10,0x10,0x10,0x10,0x10,0x10,0x10,0x10,0x10,0x10,0x10,0x10,0x10,0x10,0x10,0x10,0x10,0x10,0x10,0x10,
0x10,0x10,0x10,0x10,0x10,0x10,0x10,0x10,0x10,0x10,0x10,0x10,0x10,0x10,0x10,0x10,0x10,0x10,0x10,0x10,0x10,0x10,0x10,0x10,
0x10,0x10,0x10,0x10,0x10,0x10,0x10,0x10,0x10,0x10,0x10,0x10,0x10,0x10,0x10,0x10,0x10,0x10,0x10,0x10,0x10,0x10,0x10,0x10,
0x10,0x10,0x10,0x10,0x10,0x10,0x10,0x10,0x10,0x10,0x10,0x10,0x10,0x10,0x10,0x10,0x10,0x10,0x10,0x10,0x10,0x10,0x10,0x10,
0x10,0x10,0x10,0x10,0x10,0x10,0x10,0x10,0x10,0x10,0x10,0x10,0x10,0x10,0x10,0x10,0x10,0x10,0x10,0x10,0x10,0x10,0x10,0x10,
0x10,0x10,0x10,0x10,0x10,0x10,0x10,0x10,0x10,0x10,0x10,0x10,0x10,0x10,0x10,0x10,0x10,0x10,0x10,0x10,0x10,0x10,0x10,0x10,
0x10,0x10,0x10,0x10,0x10,0x10,0x10,0x10,0x10,0x10,0x10,0x10,0x10,0x10,0x10,0x10,0x10,0x10,0x10,0x10,0x10,0x10,0x10,0x10,
0x10,0x10,0x10,0x10,0x10,0x10,0x10,0x10,0x10,0x10,0x10,0x10,0x10,0x10,0x10,0x10,0x10,0x10,0x10,0x10,0x10,0x10,0x10,0x10,
0x10,0x10,0x10,0x10,0x10,0x10,0x10,0x10,0x10,0x10,0x10,0x10,0x10,0x10,0x10,0x10,0x10,0x10,0x10,0x10,0x10,0x10,0x10,0x10,
0x10,0x10,0x10,0x10,0x10,0x10,0x10,0x10,0x10,0x10,0x10,0x10,0x10,0x10,0x10,0x10,0x10,0x10,0x10,0x10,0x10,0x10,0x10,0x10,
0x10,0x10,0x10,0x10,0x10,0x10,0x10,0x10,0x10,0x10,0x10,0x10,0x10,0x10,0x10,0x10,0x10,0x10,0x10,0x10,0x10,0x10,0x10,0x10,
0x10,0x10,0x10,0x10,0x10,0x10,0x10,0x10,0x10,0x10,0x10,0x10,0x10,0x10,0x10,0x10,0x10,0x10,0x10,0x10,0x10,0x10,0x10,0x10,
0x10,0x10,0x10,0x10,0x10,0x10,0x10,0x10,0x10,0x10,0x10,0x10,0x10,0x10,0x10,0x10,0x10,0x10,0x10,0x10,0x10,0x10,0x10,0x10,
0x10,0x10,0x10,0x10,0x10,0x10,0x10,0x10,0x10,0x10,0x10,0x10,0x10,0x10,0x10,0x10,0x10,0x10,0x10,0x10,0x10,0x10,0x10,0x10,
0x10,0x10,0x10,0x10,0x10,0x10,0x10,0x10,0x10,0x10,0x10,0x10,0x10,0x10,0x10,0x10,0x10,0x10,0x10,0x10,0x10,0x10,0x10,0x10,
0x10,0x10,0x10,0x10,0x10,0x10,0x10,0x10,0x10,0x10,0x10,0x10,0x10,0x10,0x10,0x10,0x10,0x10,0x10,0x10,0x10,0x10,0x10,0x10,
0x10,0x10,0x10,0x10,0x10,0x10,0x10,0x10,0x10,0x10,0x10,0x10,0x10,0x10,0x10,0x10,0x10,0x10,0x10,0x10,0x10,0x10,0x10,0x10,
0x10,0x10,0x10,0x10,0x10,0x10,0x10,0x10,0x10,0x10,0x10,0x10,0x10,0x10,0x10,0x10,0x10,0x10,0x10,0x10,0x10,0x10,0x10,0x10
};*/



#endif
