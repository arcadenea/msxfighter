TARGET=cedit
DEBUG = -g
CFLAGS = -w `pkg-config gtk+-2.0 --cflags`
LFLAGS = `pkg-config gtk+-2.0 --libs` -lm


all: $(TARGET)

OBJS += main.o

rm-elf:
	-rm -f $(TARGET) $(OBJS)

$(TARGET): $(OBJS)
	$(CC)  $(OBJS) -o $(TARGET) $(LFLAGS) $(LIBS)

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -f *.o $(TARGET) $(OBJS)
