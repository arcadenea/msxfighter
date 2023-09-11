#ifndef  __CONSTS_H__
#define  __CONSTS_H__

//initial positions
#define PLAYER1_POSX  40
#define PLAYER2_POSX  110
#define PLAYER_POSY  118 //both players got the same initial positions

#define SHADOW_POSY  180

#define PLAYER_STAND 0
#define PLAYER_MOVE_LEFT 1
#define PLAYER_MOVE_RIGHT 2
#define PLAYER_CROUCH 3
#define PLAYER_LP 4
#define PLAYER_HP 5
#define PLAYER_LK 6
#define PLAYER_HK 7
#define PLAYER_LP_CROUCH 8
#define PLAYER_HP_CROUCH 9
#define PLAYER_LK_CROUCH 10
#define PLAYER_HK_CROUCH 11
#define PLAYER_JUMP 12
#define PLAYER_JUMP_RIGHT 13
#define PLAYER_JUMP_LEFT 14
#define PLAYER_LP_JUMP 15
#define PLAYER_LP_JUMP_LEFT 16
#define PLAYER_LP_JUMP_RIGHT 17
#define PLAYER_HP_JUMP 18
#define PLAYER_HP_JUMP_LEFT 19
#define PLAYER_HP_JUMP_RIGHT 20
#define PLAYER_LK_JUMP 21
#define PLAYER_LK_JUMP_LEFT 22
#define PLAYER_LK_JUMP_RIGHT 23
#define PLAYER_HK_JUMP 24
#define PLAYER_HK_JUMP_LEFT 25
#define PLAYER_HK_JUMP_RIGHT 26
#define PLAYER_BLOCK_HIGH 27
#define PLAYER_BLOCK_LOW 28
#define PLAYER_MAGIC1 29
#define PLAYER_MAGIC2 30
#define PLAYER_MAGIC3 31
#define PLAYER_MAGIC4 32
#define PLAYER_SPECIAL1 33
#define PLAYER_SPECIAL2 34
#define PLAYER_FALL 35
#define PLAYER_RISE 36
#define PLAYER_WIN 37
#define PLAYER_LOSE 38
#define PLAYER_DRAW 39

#define ANIMATION_NONBREAKABLE 0 //animation can´t be stopped, ex. fall
#define ANIMATION_BREAKABLE 1 //animation can be stopped by any event
#define ANIMATION_BREAKABLE_BUTTON 2 //animation can be stopped by a button press (punch, kick)
#define ANIMATION_BREAKABLE_ATTACK 3 //animation can be stopped by a hit of the opponent


#define ANIMATION_WAITING 0
#define ANIMATION_RUNNING 1
#define ANIMATION_FINISHED 2


#endif
