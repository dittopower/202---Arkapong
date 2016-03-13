#include "cab202_simple_sprite.h"
#include "cab202_screen.h"

#include "splitter.h"



#include <time.h>

// INSERT GLOBAL VARIABLES HERE
sprite_id splitter;
sprite_id extender;
sprite_id shrink;
sprite_id wind;
int wind_dir = 0;
bool splitteractive = FALSE;
bool extenderactive = FALSE;
bool shrinkactive = FALSE;
bool windactive = FALSE;
char splitter_img[15] = " @@@ @@@@@ @@@ ";

//-----------------------------------------------------------------------------
//  Function declarations.
//-----------------------------------------------------------------------------

// INSERT DECLARATIONS FOR HELPER FUNCTIONS HERE


//-----------------------------------------------------------------------------
//  Function implementations.
//-----------------------------------------------------------------------------


void setup_splitter() {
time_t t;
srand((unsigned) time(&t));

	if (splitteractive){
		splitter = create_big_sprite(ran_x(),ran_y(),5,3,splitter_img);
	}else{
		splitter = create_big_sprite(-3,-3,5,3,splitter_img);
	}
	if (extenderactive){
		extender = create_big_sprite(ran_x(),ran_y(),5,3,splitter_img);
	}else{
		extender = create_big_sprite(-3,-3,5,3,splitter_img);
	}
	if (shrinkactive){
		shrink = create_big_sprite(ran_x(),ran_y(),5,3,splitter_img);
	}else{
		shrink = create_big_sprite(-3,-3,5,3,splitter_img);
	}
	if (windactive){
		wind = create_big_sprite(ran_x(),ran_y(),5,3,splitter_img);
	}else{
		wind = create_big_sprite(-3,-3,5,3,splitter_img);
	}
}

void reset_splitter() {
	if (splitteractive){
		move_sprite_to(splitter,ran_x(),ran_y());
	}else{
		move_sprite_to(splitter,-3,-3);
	}
	if (extenderactive){
		move_sprite_to(extender,ran_x(),ran_y());
	}else{
		move_sprite_to(extender,-3,-3);
	}
	if (shrinkactive){
		move_sprite_to(shrink,ran_x(),ran_y());
	}else{
		move_sprite_to(shrink,-3,-3);
	}
	wind_dir = 0;
	if (windactive){
		move_sprite_to(wind,ran_x(),ran_y());
		update_wind(wind_dir);
	}else{
		move_sprite_to(wind,-3,-3);
	}
	
}

int activate_splitter(double x, double y) {
	int blocktype = -1;
	if(mvinch(y,x) == '@'){
		sprite_id target = get_sprite_at(x,y,100);
		if(target == splitter){
			blocktype = 0;
		}else if(target == extender){
			blocktype = 1;
		}else if(target == shrink){
			blocktype = 2;
		}else if(target == wind){
			blocktype = 3;
			wind_dir = (wind_dir + 1) % 5;
			update_wind(wind_dir);
		}
		move_sprite_to(target, ran_x(),ran_y());
	}
	return blocktype;
}

bool toggle_splitters(){
	splitteractive = !splitteractive;
	reset_splitter();
	return splitteractive;
}
bool toggle_extender(){
	extenderactive = !extenderactive;
	reset_splitter();
	return extenderactive;
}
bool toggle_shrinker(){
	shrinkactive = !shrinkactive;
	reset_splitter();
	return shrinkactive;
}
bool toggle_wind(){
	windactive = !windactive;
	reset_splitter();
	if(!windactive){
		update_wind(5);
	}else{
		update_wind(wind_dir);
	}
	return windactive;
}

sprite_direction get_wind(){
	int ran = rand();
	sprite_direction new;
	new.dx = 0;
	new.dy = 0;
	switch(wind_dir){
		case 1:
			if(ran % 16 < 1){//80/10 =8 *2 =16
				new.dx = 1;
			}
			break;
		case 2:
			if(ran % 16 < 1){
				new.dx = -1;
			}
			break;
		case 3:
			if(ran % 5 < 1){//24/10 =2.4 *2 ~5
				new.dy = -1;
			}
			break;
		case 4:
			if(ran % 5 < 1){
				new.dy = 1;
			}
			break;
	}
	return new;
}

sprite_direction true_wind(){
	sprite_direction new;
	new.dx = 0;
	new.dy = 0;
	switch(wind_dir){
		case 1:
			new.dx = 1;
			break;
		case 2:
			new.dx = -1;
			break;
		case 3:
			new.dy = -1;
			break;
		case 4:
			new.dy = 1;
			break;
	}
	return new;
}

bool windy(){
	if(wind_dir == 0){
		return FALSE;
	}else{
		return TRUE;
	}
}
// INSERT HELPER FUNCIONS HERE


