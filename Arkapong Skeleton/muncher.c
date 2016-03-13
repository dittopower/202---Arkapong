#include "cab202_simple_sprite.h"
#include "cab202_screen.h"

#include "muncher.h"
#include <math.h>


// INSERT GLOBAL VARIABLES HERE
sprite_id muncher;
bool munching = FALSE;
int munched = 0;
int sight = 15;
char muncher_sml[9] = "/-\\|x|\\-/";
char muncher_med[24] = "//==\\\\||\\/||||/\\||\\\\==//";
char muncher_lrg[63] = "//-^-^-\\\\|<     >|<| \\|/ |><|  *  |><| /|\\ |>|<     >|\\\\-v-v-//";


//-----------------------------------------------------------------------------
//  Function declarations.
//-----------------------------------------------------------------------------

// INSERT DECLARATIONS FOR HELPER FUNCTIONS HERE


//-----------------------------------------------------------------------------
//  Function implementations.
//-----------------------------------------------------------------------------


void setup_muncher() {

	if (munching){
		muncher = create_big_sprite(36,20,3,3,muncher_sml);
	}else{
		muncher = create_big_sprite(-6,-6,3,3,muncher_sml);
	}
	set_sprite_direction(muncher,0,-1);
}

void reset_muncher() {
	if (munching){
		move_sprite_to(muncher,36,20);
	}else{
		move_sprite_to(muncher,-6,-6);
	}
	munched = 0;
	set_sprite_image(muncher,3,3,muncher_sml);
	set_sprite_direction(muncher,0,-1);
	
}

bool update_muncher() {
	bool did_something = FALSE;
	if(munching){
		simple_sprite_t mun = get_sprite(muncher);
		int x = get_sprite_position(muncher).x;
		int X = x + mun.width;
		int y = get_sprite_position(muncher).y;
		int Y = y + mun.height;
		
		for (int i = x - 1; i < X+1;i++){
			for(int k = y - 1; k < Y+1;k++){
				char food = mvinch(k,i);
				if (food == 'O'){//eat balls
					if(eat_ball(i,k)){
						munched++;
						did_something = TRUE;
					}
				}
				if(food == '@'){
					//eat special blocks
					switch(activate_splitter(i,k)){
						case 0:
							munched = 2;
							break;
						case 1:
							grow_right();
							grow_left();
							break;
						case 2:
							shrink_left();
							shrink_right();
							break;
						case 3:
							munched = 0;
							break;
					}
					did_something = TRUE;
				}
			}
		}
		
		if(munched == 0 && mun.width != 3){
			set_sprite_image(muncher,3,3,muncher_sml);
			did_something = TRUE;
		}else if(munched == 1 && mun.width != 6){
			set_sprite_image(muncher,6,4,muncher_med);
			did_something = TRUE;
		}else if(munched > 1 && mun.width != 9){
			set_sprite_image(muncher,9,7,muncher_lrg);
			did_something = TRUE;
		}
		mun = get_sprite(muncher);
		x = get_sprite_position(muncher).x;
		X = x + mun.width;
		int dx = mun.direction.dx;
		y = get_sprite_position(muncher).y;
		Y = y + mun.height;
		int dy = mun.direction.dy;
		int cx = x+ (mun.width -1)/2;
		int cy = y+ (mun.height -1)/2;
		
		if(!did_something){
			//direction
			if(windy()){
				sprite_direction dirw = true_wind();
				set_sprite_direction(muncher, dirw.dx*-1, dirw.dy*-1);
				dx = dirw.dx*-1;
				dy = dirw.dy*-1;
			}else{
				int rx = x;
				int ry = y;
				int dis = 100;
				int temp;
				for (int i = x - sight; i < X+sight;i++){
					for(int k = y - sight; k < Y+sight;k++){
						char food = mvinch(k,i);
						if (food == 'O'){
							temp = sqrt((cx-i)*(cx-i)+(cy-k)*(cy-k));
							if(temp < dis){
								dis = temp;
								rx = i;
								ry = k;
							}
						}
					}
				}//Muncher knows it has an eating problem and so runs from tasty balls
				if(dis < 100){
					dx = ((cx - rx))%2;
					dy = ((cy - ry))%2;
					set_sprite_direction(muncher,dx,dy);
					//mvprintw(20,25,"%i",(int)dx);
					//mvprintw(21,25,"%i",(int)dy);
				}
			}
			
			
			//move
				bool can_move_x = TRUE;
				bool can_move_y = TRUE;
			if(X+dx < 75 && x+dx > 4){
					if(dx > 0){
						for (int i = (y+dy); i < (Y+dy);i++){
							if(mvinch(i,(X+dx)) != ' '){
								can_move_x = FALSE;
								break;
							}
						}
					}else if(dx < 0){
						for (int i = (y+dy); i < (Y+dy);i++){
							if(mvinch(i,(x+dx)) != ' '){
								can_move_x = FALSE;
								break;
							}
						}
					}
			}else{
				can_move_x = FALSE;
			}
			
			if(y+dy > 3 && Y+dy < 24){
				if(dy > 0){
					for (int i = (x+dx); i < (X+dx);i++){
						if(mvinch((Y+dy),i) != ' '){
							can_move_y = FALSE;
							break;
						}
					}
				}else if(dy < 0){
					for (int i = (x+dx); i < (X+dx);i++){
						if(mvinch((y+dy),i) != ' '){
							can_move_y = FALSE;
							break;
						}
					}
				}
			}else{
				can_move_y = FALSE;
			}
			
			if(can_move_x){
				move_sprite(muncher,dx,0);
				did_something = TRUE;
			}else{
				dx =dx*-1;
				set_sprite_direction(muncher,dx,dy);
				move_sprite(muncher,dx,0);
				did_something = TRUE;
			}
			if(can_move_y){
				move_sprite(muncher,0,dy);
				did_something = TRUE;
			}else{
				dy=dy*-1;
				move_sprite(muncher,0,dy);
				did_something = TRUE;
			}
		}
	}
	return did_something;
}

bool toggle_muncher(){
	munching = !munching;
	reset_muncher();
	return munching;
}
// INSERT HELPER FUNCIONS HERE



