#include "cab202_simple_sprite.h"
#include "cab202_screen.h"

#include "left_paddle.h"


// INSERT GLOBAL VARIABLES HERE
sprite_id left_Paddle_id;
char left_paddle = '$';
int l_startx = 4;
int l_starty = 3;
int l_area_top = 3;
int l_area_bot = 24;
int height = 5;
bool ai = false;

//-----------------------------------------------------------------------------
//  Function declarations.
//-----------------------------------------------------------------------------

// INSERT DECLARATIONS FOR HELPER FUNCTIONS HERE


//-----------------------------------------------------------------------------
//  Function implementations.
//-----------------------------------------------------------------------------


void setup_left_paddle() {
	height = l_area_bot-l_area_top;
	
	char img[height];
	for(int i = 0; i < (height);i++){
		img[i] = left_paddle;
	}
	left_Paddle_id = create_big_sprite(l_startx,l_starty,1,(l_area_bot-l_area_top),img);

}

void reset_left_paddle() {

	char img[height];
	for(int i = 0; i < (height);i++){
		img[i] = left_paddle;
	}
	move_sprite_to(left_Paddle_id,l_startx,l_starty);
	set_sprite_image(left_Paddle_id,1,height,img);
}


bool update_left_paddle() {
	bool left_paddle_moved = FALSE;
	if (ai){
	sprite_id target = get_inbound_ball(l_startx);
	if(target > 0){
		simple_sprite_t ball = get_sprite(target);
		
		double y = get_sprite_position(left_Paddle_id).y;
		double by = ball.location.y;
		double dy = ball.direction.dy;
		
		if (by+dy > y && by+dy > y+get_sprite_size(left_Paddle_id).height-1 && y+get_sprite_size(left_Paddle_id).height-1 < 23){
			move_sprite(left_Paddle_id,0,1);
			left_paddle_moved = TRUE;
		}else if (by+dy <= y && y > 3){
			move_sprite(left_Paddle_id,0,-1);
			left_paddle_moved = TRUE;
		}
	}}
	return left_paddle_moved;
}

bool toggle_ai(){
	ai = !ai;
	if(ai){
		height = 5;
		l_starty = (24-3-5)/2+3;
	}else{
		height = l_area_bot-l_area_top;
		l_starty = 3;
	}
	reset_left_paddle();
	return ai;
}


void grow_left(){
	if(get_sprite_size(left_Paddle_id).height < 21){
		char img[get_sprite_size(left_Paddle_id).height+2];
		for(int i = 0; i < (get_sprite_size(left_Paddle_id).height+2);i++){
			img[i] = left_paddle;
		}
		set_sprite_image(left_Paddle_id,1,get_sprite_size(left_Paddle_id).height+2,img);
	}
}

void shrink_left(){
	if(get_sprite_size(left_Paddle_id).height > 3){
		char img[get_sprite_size(left_Paddle_id).height-2];
		for(int i = 0; i < (get_sprite_size(left_Paddle_id).height-2);i++){
			img[i] = left_paddle;
		}
		set_sprite_image(left_Paddle_id,1,get_sprite_size(left_Paddle_id).height-2,img);
	}
}

// INSERT HELPER FUNCIONS HERE
