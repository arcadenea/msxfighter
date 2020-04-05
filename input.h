#ifndef  __INPUT_H__
#define  __INPUT_H__

//msx values for joystick
#define DIRECTION_UP 1
#define DIRECTION_UPRIGHT 2
#define DIRECTION_RIGHT 3
#define DIRECTION_DOWNRIGHT 4
#define DIRECTION_DOWN 5
#define DIRECTION_DOWNLEFT 6
#define DIRECTION_LEFT 7
#define DIRECTION_UPLEFT 8

//internal values
#define JOYSTICK_UP        (1<<0)
#define JOYSTICK_DOWN      (1<<1)
#define JOYSTICK_LEFT      (1<<2)
#define JOYSTICK_RIGHT     (1<<3)
#define JOYSTICK_TRIGA     (1<<4)
#define JOYSTICK_TRIGB     (1<<5)


char joystick(char n);
char joytrig(char n);
char joy_read(char n);


#endif
