#include "cab202_simple_sprite.h"
#include "cab202_screen.h"

#include "right_paddle.h"


// INSERT GLOBAL VARIABLES HERE
sprite_id right_Paddle_id;
char right_paddle = '$';
int r_startx = 75;
int r_starty = (24-3-5)/2+3;
int r_area_top = 3;
int r_area_bot = 24;

//-----------------------------------------------------------------------------
//  Function declarations.
//-----------------------------------------------------------------------------

// INSERT DECLARATIONS FOR HELPER FUNCTIONS HERE


//-----------------------------------------------------------------------------
//  Function implementations.
//-----------------------------------------------------------------------------


void setup_right_paddle() {

	// INSERT SETUP CODE HERE
	char img[5];
	for(int i = 0; i < 5;i++){
		img[i] = right_paddle;
	}
	right_Paddle_id = create_big_sprite(r_startx,r_starty,1,5,img);

}

void reset_right_paddle() {

	// INSERT RESET CODE HERE
	move_sprite_to(right_Paddle_id,r_startx,r_starty);
	char img[5];
	for(int i = 0; i < (5);i++){
		img[i] = right_paddle;
	}
	set_sprite_image(right_Paddle_id,1,5,img);

}


bool update_right_paddle( int key_code ) {
	bool right_paddle_moved = FALSE;

	switch(key_code){
		case KEY_UP:
			if (get_sprite_position(right_Paddle_id).y > r_area_top){
				move_sprite(right_Paddle_id, 0, -1);
				right_paddle_moved = TRUE;
			}
			break;
		case KEY_DOWN:
			if (get_sprite_position(right_Paddle_id).y < (r_area_bot-get_sprite_size(right_Paddle_id).height)){
				move_sprite(right_Paddle_id, 0, 1);
				right_paddle_moved = TRUE;
			}
			break;
	}

	return right_paddle_moved;
}

void blockside(){
	if(get_sprite_size(right_Paddle_id).height < 21){
		char img[21];
		for(int i = 0; i < (21);i++){
			img[i] = right_paddle;
		}
		move_sprite_to(right_Paddle_id,r_startx,3);
		set_sprite_image(right_Paddle_id,1,21,img);
	}
}

void grow_right(){
	if(get_sprite_size(right_Paddle_id).height < 21){
		char img[get_sprite_size(right_Paddle_id).height+2];
		for(int i = 0; i < (get_sprite_size(right_Paddle_id).height+2);i++){
			img[i] = right_paddle;
		}
		set_sprite_image(right_Paddle_id,1,get_sprite_size(right_Paddle_id).height+2,img);
	}
}

void shrink_right(){
	if(get_sprite_size(right_Paddle_id).height > 3){
		char img[get_sprite_size(right_Paddle_id).height-2];
		for(int i = 0; i < (get_sprite_size(right_Paddle_id).height-2);i++){
			img[i] = right_paddle;
		}
		set_sprite_image(right_Paddle_id,1,get_sprite_size(right_Paddle_id).height-2,img);
	}
}

// INSERT HELPER FUNCIONS HERE
