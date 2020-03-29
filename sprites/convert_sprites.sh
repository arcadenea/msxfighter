#!/bin/bash

rm *.h

for f in *.png
do
  echo "Procesando el archivo $f..."
  # take action on each file. $f store current file name
  #convert $f -crop 16x16 -type palette -depth 1 -colors 2 png8:spr${f%.*}%d.png
  convert $f -crop 16x16 -negate spr${f%.*}%d.png
done

for f in spr*.png
do
  echo "Insertando $f en header..."
  ../spriteconv/msxfsc $f fighter.h
  rm $f
done
