CC=sdcc
ASM=sdasz80
CFLAGS+= --code-loc 0x4020 --data-loc 0xc000 -mz80 --no-std-crt0
#CFLAGS+= --nogcse 
#CFLAGS+= --noinvariant 
#CFLAGS+= --noinduction 
#CFLAGS+= --nojtbound
#CFLAGS+= --noloopreverse --nolabelopt --no-xinit-opt --nooverlay --no-peep --no-peep-return
OBJS=VDP_TMS9918A_ROM.rel main.rel sprite.rel input.rel tilemap.rel
CRTOBJ=crt/crt0msx.16k.4000.rel
CRTSRC=crt/crt0msx.16k.4000.s
MAKEBIN=makebin
ROM16KBLOCKS=1
ROM16KSKIP=1
ROM=test.rom

all: build

build: $(ROM)

$(ROM): main.ihx
	$(MAKEBIN) -s 65536 < main.ihx >64k.mem
	dd if=64k.mem of=$(ROM) bs=16384 skip=$(ROM16KSKIP) count=$(ROM16KBLOCKS)
	awk 'BEGIN { FS=" "; } /DEF.*/ { print $$2 ": equ 0" substr($$3,3) "h"; }' < main.noi | grep -v "_end: equ " > main.tniasm.sym

%.rel: %.c
	$(CC) -c $(CFLAGS) $<

%.rel: %.s
	$(ASM) -o $<

$(CRTOBJ): $(CRTSRC)
	sdasz80 -o $(CRTOBJ) $(CRTSRC)

main.ihx: $(OBJS) $(CRTOBJ)
	$(CC) $(CFLAGS) $(LDFLAGS) -omain.ihx $(CRTOBJ) $(OBJS)

clean:
	$(RM) -v $(ROM) *.sym *.lnk *.ihx *.map *.lst $(OBJS) main.rel *.asm *.bin *.lk *.noi 64k.mem

help:
	echo Usage:
	echo make          = builds all except main.c
	echo make clean    = clean intermediate files

