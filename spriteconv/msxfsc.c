/*
 * A simple libpng example program
 * http://zarb.org/~gc/html/libpng.html
 *
 * Modified by Yoshimasa Niwa to make it much simpler
 * and support all defined color_type.
 *
 * To build, use the next instruction on OS X.
 * $ brew install libpng
 * $ clang -lz -lpng16 libpng_test.c
 *
 * Copyright 2002-2010 Guillaume Cottenceau.
 *
 * This software may be freely redistributed under the terms
 * of the X11 license.
 *
 */

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <png.h>

int width, height;
png_byte color_type;
png_byte bit_depth;
png_bytep *row_pointers = NULL;

void read_png_file(char *filename) {
  FILE *fp = fopen(filename, "rb");

  png_structp png = png_create_read_struct(PNG_LIBPNG_VER_STRING, NULL, NULL, NULL);
  if(!png) abort();

  png_infop info = png_create_info_struct(png);
  if(!info) abort();

  if(setjmp(png_jmpbuf(png))) abort();

  png_init_io(png, fp);

  png_read_info(png, info);

  width      = png_get_image_width(png, info);
  height     = png_get_image_height(png, info);
  color_type = png_get_color_type(png, info);
  bit_depth  = png_get_bit_depth(png, info);

  printf("width:%d height:%d color type:%d bit depth:%d row bytes:%d\n", width, height, color_type, bit_depth, (int) png_get_rowbytes(png,info));

  if (row_pointers) abort();

  row_pointers = (png_bytep*)malloc(sizeof(png_bytep) * height);
  for(int y = 0; y < height; y++) {
    row_pointers[y] = (png_byte*)malloc(png_get_rowbytes(png,info));
  }

  png_read_image(png, row_pointers);

  fclose(fp);

  png_destroy_read_struct(&png, &info, NULL);
}


void process_png_file(char *filename, char *arrayname) {

  int emptyspr = 0;
  FILE *fp = fopen(filename, "ab");
  char* substr = (char *) malloc(sizeof(char)*100);//malloc(strlen(arrayname)*sizeof(char));
  memset(substr, 0, sizeof(char)*100);
  strncpy(substr, arrayname, strlen(arrayname)-4);



  //check if sprite is empty
  for(int y = 0; y < height; y++) {
    png_bytep row = row_pointers[y];
      png_bytep px0 = &(row[0]);
	  png_bytep px1 = &(row[1]);
      if (px0[0] > 0 || px1[1] > 0) emptyspr++;  
  }

  if(emptyspr) //if sprite is NOT empty, generate header
  {
  	  fprintf(fp, "const unsigned char %s []={\n", substr);

	  for(int y = 0; y < height; y++) {
		png_bytep row = row_pointers[y];
		  png_bytep px = &(row[0]);
		  fprintf(fp, "0x%02x,", px[0]);
	  }

	  for(int y = 0; y < height; y++) {
		  png_bytep row = row_pointers[y];
		  png_bytep px = &(row[1]);
		  if(y==height-1) fprintf(fp, "0x%02x", px[0]);
			else fprintf(fp, "0x%02x,", px[0]);
	  }

	  fprintf(fp, "};\n");
  }

  fclose(fp);
}


int main(int argc, char *argv[]) {
  if(argc != 3) abort(); //printf("algo %s\n", argv[0]);


	printf("Creating sprite to file %s from file %s\n", argv[2], argv[1]);
  	read_png_file(argv[1]);
  	process_png_file(argv[2], argv[1]);


  return 0;
}

