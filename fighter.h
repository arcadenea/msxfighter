#ifndef  __FIGHTER_H__
#define  __FIGHTER_H__


#define FIGHTER_WALK_FRAMES 12
#define FIGHTER_JUMP_FRAMES 20
#define FIGHTER_STAND_FRAMES 24
#define FIGHTER_H_FRAMES 10
#define FIGHTER_DEFAULT_FRAMES 4

#define FIGHTER_WALK_SPEED 2
#define FIGHTER_JUMP_SPEED 4

//sprite frames
#define FIGHTER_STAND_ANIMATION1 	 30
#define FIGHTER_STAND_ANIMATION2 	 1
#define FIGHTER_WALK_ANIMATION1 	 2
#define FIGHTER_WALK_ANIMATION2 	 3
#define FIGHTER_CROUCH				 4
#define FIGHTER_LP					 5
#define FIGHTER_HP					 6
#define FIGHTER_LK					 7
#define FIGHTER_HK					 8
#define FIGHTER_LP_CROUCH			 9
#define FIGHTER_HP_CROUCH			10
#define FIGHTER_LK_CROUCH			11
#define FIGHTER_HK_CROUCH			12
#define FIGHTER_JUMP				13
#define FIGHTER_LP_JUMP				14
#define FIGHTER_LK_JUMP				15
#define FIGHTER_HP_JUMP				16
#define FIGHTER_HK_JUMP				17
#define FIGHTER_JUMP_RIGHT			18
#define FIGHTER_LP_JUMP_RIGHT		19
#define FIGHTER_LK_JUMP_RIGHT		20
#define FIGHTER_HP_JUMP_RIGHT		21
#define FIGHTER_HK_JUMP_RIGHT		22
#define FIGHTER_JUMP_LEFT			23
#define FIGHTER_LP_JUMP_LEFT		24
#define FIGHTER_LK_JUMP_LEFT	    25
#define FIGHTER_HP_JUMP_LEFT	    26
#define FIGHTER_HK_JUMP_LEFT	    27


//sprite blocks
#define blkfighter_block0 			  0
#define blkfighter_block2 			  1
#define blkfighter_crouch2 			  2
#define blkfighter_crouch_block2 	  3
#define blkfighter_crouch_hit0 		  4
#define blkfighter_crouch_hit2 		  5
#define blkfighter_crouch_hk2 		  6
#define blkfighter_crouch_hk3 		  7
#define blkfighter_crouch_hp0 		  8
#define blkfighter_crouch_hp1 		  9	
#define blkfighter_crouch_hp2 		 10
#define blkfighter_crouch_hp3 		 11
#define blkfighter_crouch_lk2 		 12
#define blkfighter_crouch_lk3 		 13
#define blkfighter_crouch_lp2 		 14
#define blkfighter_crouch_lp3 		 15
#define blkfighter_crouch_old2 		 16
#define blkfighter_floor2 			 17
#define blkfighter_floor3 			 18
#define blkfighter_hit0 			 19
#define blkfighter_hit2 			 20
#define blkfighter_hk0 				 21
#define blkfighter_hk2 				 22
#define blkfighter_hk3 				 23
#define blkfighter_hp0 				 24
#define blkfighter_hp1 				 25
#define blkfighter_hp2 				 26
#define blkfighter_jump0 			 27 
#define blkfighter_jump2 			 28
#define blkfighter_jump_hk0 		 29 
#define blkfighter_jump_hk2 		 30
#define blkfighter_jump_hk3 		 31
#define blkfighter_jump_lk0 		 32
#define blkfighter_jump_lk2 		 33
#define blkfighter_jump_lp0 		 34
#define blkfighter_jump_lp1 		 35
#define blkfighter_jump_lp2 		 36
#define blkfighter_jump_lp3 		 37
#define blkfighter_lk0 		 		 38
#define blkfighter_lk2 		 		 39
#define blkfighter_lk3 		 		 40
#define blkfighter_lp0 		 		 41
#define blkfighter_lp1 		 		 42
#define blkfighter_lp2 		 	 	 43
#define blkfighter_magic0 		     44 
#define blkfighter_magic1 		 	 45
#define blkfighter_magic2 		 	 46
#define blkfighter_stand_00 		 47
#define blkfighter_stand_01 		 48 
#define blkfighter_stand_10 		 49
#define blkfighter_stand_11 		 50
#define blkfighter_walk_00 			 51
#define blkfighter_walk_01 			 52
#define blkfighter_walk_10 			 53
#define blkfighter_walk_11 			 54
#define blkfighter_win0 			 55
#define blkfighter_win2 			 56

struct frame {
	unsigned int *spr0;
	unsigned int *spr1;
	unsigned int *spr2;
	unsigned int *spr3;
	unsigned char hit_x1, hit_y1, hit_x2, hit_y2; //hit box
	unsigned char att_x1, att_y1, att_x2, att_y2; //attack box
	unsigned char name; //frame name
};

struct fighter {
	struct frame frames[30];	
	unsigned char fc; //frame count 
};

extern struct fighter fighters[];

extern const unsigned char empty_sprite[];
extern const unsigned char collision_up[];
extern const unsigned char collision_down[];
extern const unsigned char shadow[];

/*
NOTAS: 
sprfighter_walk_10 y sprfighter_walk_11 no se utilizan
sprfighter_hp1 es el mismo frame que sprfighter_stand_01 (o debería)
sprfighter_hk0 y sprfighter_lk0 son los mismos frames (o deberían)
falta sprite de salto con piña fuerte
*/


extern const unsigned char sprfighter_block0 [];
extern const unsigned char sprfighter_block2 [];
extern const unsigned char sprfighter_crouch2 [];
extern const unsigned char sprfighter_crouch_block2 [];
extern const unsigned char sprfighter_crouch_hit0 [];
extern const unsigned char sprfighter_crouch_hit2 [];
extern const unsigned char sprfighter_crouch_hk2 [];
extern const unsigned char sprfighter_crouch_hk3 [];
extern const unsigned char sprfighter_crouch_hp0 [];
extern const unsigned char sprfighter_crouch_hp1 [];
extern const unsigned char sprfighter_crouch_hp2 [];
extern const unsigned char sprfighter_crouch_hp3 [];
extern const unsigned char sprfighter_crouch_lk2 [];
extern const unsigned char sprfighter_crouch_lk3 [];
extern const unsigned char sprfighter_crouch_lp2 [];
extern const unsigned char sprfighter_crouch_lp3 [];
extern const unsigned char sprfighter_crouch_old2 [];
extern const unsigned char sprfighter_floor2 [];
extern const unsigned char sprfighter_floor3 [];
extern const unsigned char sprfighter_hit0 [];
extern const unsigned char sprfighter_hit2 [];
extern const unsigned char sprfighter_hk0 [];
extern const unsigned char sprfighter_hk2 [];
extern const unsigned char sprfighter_hk3 [];
extern const unsigned char sprfighter_hp0 [];
extern const unsigned char sprfighter_hp1 [];
extern const unsigned char sprfighter_hp2 [];
extern const unsigned char sprfighter_jump0 [];
extern const unsigned char sprfighter_jump2 [];
extern const unsigned char sprfighter_jump_hk0 [];
extern const unsigned char sprfighter_jump_hk2 [];
extern const unsigned char sprfighter_jump_hk3 [];
extern const unsigned char sprfighter_jump_lk0 [];
extern const unsigned char sprfighter_jump_lk2 [];
extern const unsigned char sprfighter_jump_lp0 [];
extern const unsigned char sprfighter_jump_lp1 [];
extern const unsigned char sprfighter_jump_lp2 [];
extern const unsigned char sprfighter_jump_lp3 [];
extern const unsigned char sprfighter_lk0 [];
extern const unsigned char sprfighter_lk2 [];
extern const unsigned char sprfighter_lk3 [];
extern const unsigned char sprfighter_lp0 [];
extern const unsigned char sprfighter_lp1 [];
extern const unsigned char sprfighter_lp2 [];
extern const unsigned char sprfighter_magic0 [];
extern const unsigned char sprfighter_magic1 [];
extern const unsigned char sprfighter_magic2 [];
extern const unsigned char sprfighter_stand_00 [];
extern const unsigned char sprfighter_stand_01 [];
extern const unsigned char sprfighter_stand_10 [];
extern const unsigned char sprfighter_stand_11 [];
extern const unsigned char sprfighter_walk_00 [];
extern const unsigned char sprfighter_walk_01 [];
extern const unsigned char sprfighter_walk_10 [];
extern const unsigned char sprfighter_walk_11 [];
extern const unsigned char sprfighter_win0 [];
extern const unsigned char sprfighter_win2 [];


void load_fighter();

#endif
