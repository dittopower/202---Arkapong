#include "cab202_simple_sprite.h"
#include "cab202_screen.h"

#include "ball.h"



#include <time.h>

// INSERT GLOBAL VARIABLES HERE
sprite_id balls[10];
bool active[10];
int last_paddle[10];
int no_balls = 0;
char ball_img = 'O';
char paddle = '$';


//-----------------------------------------------------------------------------
//  Function declarations.
//-----------------------------------------------------------------------------

// INSERT DECLARATIONS FOR HELPER FUNCTIONS HERE


//-----------------------------------------------------------------------------
//  Function implementations.
//-----------------------------------------------------------------------------


void setup_ball() {
time_t t;
srand((unsigned) time(&t));

	// INSERT SETUP CODE HERE
	 balls[0] = create_sprite((79/2),(23/2+2),ball_img,0);
	 active[0] = TRUE;
	 for(int i = 1; i < 10;i++){
		 balls[i] = create_sprite(-2,-2,ball_img,0);
		 active[i] = FALSE;
		 last_paddle[i] = 0;
	 }
	// double dy = (rand() % 180);
//	 set_sprite_angle(balls[0],dy);
	 double dy = (rand() % 3) -1;
	 set_sprite_direction(balls[0], -1, dy);
	 no_balls++;
}

void reset_ball() {

	// INSERT RESET CODE HERE
	 move_sprite_to(balls[0],(79/2),(23/2+2));
	 active[0] = TRUE;
	last_paddle[0] = 0;
	 for(int i = 1; i < 10;i++){
		 move_sprite_to(balls[i],-2,-2);
		 active[i] = FALSE;
		 last_paddle[i] = 0;
	 }
	 set_sprite_direction(balls[0], -1, (rand() % 6)/2 -1);
	 no_balls = 1;

}


bool update_ball() {
	bool ball_updated = FALSE;
	
	sprite_direction windy = get_wind();
	for(int i = 0; i < 10;i++){
		if(active[i]){
			simple_sprite_t ball = get_sprite(balls[i]);
			double x = get_sprite_position(balls[i]).x;
			double dx = ball.direction.dx + windy.dx;
			double y = get_sprite_position(balls[i]).y;
			double dy = ball.direction.dy + windy.dy;
			bool bscore = FALSE;
			char next;
			
			if(dx > 1){
				dx = 1;
			}else if(dx < -1){
				dx = -1;
			}
			if(dy > 1){
				dy = 1;
			}else if(dy < -1){
				dy = -1;
			}
			
			//X Axis
			if(dx != 0){
			next = mvinch(y,x+dx);
			if(x+dx > 79 || x+dx < 0){//Screen bounds
				update_score(1);//lose life
				no_balls--;
				active[i] = FALSE;
				move_sprite_to(balls[i],-2,-2);
			}else if(next == '@'){//splitter
				switch(activate_splitter(x+dx,y)){
					case 0://splitter
						activate_ball(x+dx,y,dx*-1,dy*-1);
						bscore = TRUE;
						break;
					case 1://extender
						if(last_paddle[i] == 1){
							grow_right();
						}else if(last_paddle[i] == 2){
							grow_left();
						}
						bscore = TRUE;
						break;
					case 2://shrinker
						if(last_paddle[i] == 1){
							shrink_right();
						}else if(last_paddle[i] == 2){
							shrink_left();
						}
						bscore = TRUE;
						break;
				}
			}else if (next != ' '){//Blocks & paddles
				activate_block(x+dx,y);
				dx=dx*-1;
				bscore = TRUE;
			}
			if(next == paddle){
			//mvprintw(0,20,"%i",x+dx);
				if(x < 40){
					last_paddle[i] = 2;
				}else if(x > 40){
					last_paddle[i] = 1;
				}
			}}
			
			
			//Y Axis
			if(dy != 0){
			next = mvinch(y+dy,x);
			if(y+dy < 3 || y+dy > 23){//screen bounds
				dy=dy*-1;
			}else if(next == '@'){//special blocks
				switch(activate_splitter(x,y+dy)){
					case 0://splitter
						activate_ball(x,y+dy,dx*-1,dy*-1);
						bscore = TRUE;
						break;
					case 1://extender
						if(last_paddle[i] == 1){
							grow_right();
						}else if(last_paddle[i] == 2){
							grow_left();
						}
						bscore = TRUE;
						break;
					case 2://shrinker
						if(last_paddle[i] == 1){
							shrink_right();
						}else if(last_paddle[i] == 2){
							shrink_left();
						}
						bscore = TRUE;
						break;
				}
			}else if (next == '#' || next == paddle){//blocks and paddles
				activate_block(x,y+dy);
				dy=dy*-1;
				bscore = TRUE;
			}
			if(next == paddle){
			//mvprintw(0,15,"%i",x);
				if(x < 40){
					last_paddle[i] = 2;
				}else if(x > 40){
					last_paddle[i] = 1;
				}
			}}
			
			
			set_sprite_direction(balls[i],dx, dy);
			//mvprintw(0,25,"p%i",last_paddle[i]);
			
			//Diagonal
			next = mvinch(y+dy,x+dx);
			if( next != '#' && next != paddle){
				move_sprite_forward(balls[i]);
				ball_updated = TRUE;
			}else{
				activate_block(x+dx,y+dy);
				set_sprite_direction(balls[i],dx, dy*-1);
			}
			if(bscore){
				update_score(3);//Gain Score
			}
		}
	}
	return ball_updated;
}

bool activate_ball(double x, double y, double dx, double dy) {
	for(int i = 0; i < 10;i++){
		if(!active[i]){
			move_sprite_to(balls[i],x,y);
			active[i] = TRUE;
			no_balls++;
			set_sprite_direction(balls[i], dx, dy);
			return TRUE;
		}
	}
	return FALSE;
}

int get_no_balls(){
	return no_balls;
}

sprite_id get_inbound_ball(int x){//get the next ball head to location. X axis only
	sprite_id last = -1;
	int dis = 1000;
	for(int i = 0; i <10;i++){
		if(active[i]){
			simple_sprite_t ball = get_sprite(balls[i]);
			double bx = get_sprite_position(balls[i]).x;
			double dx = ball.direction.dx;
			if((bx-x)>(bx-x+dx)){
				if(bx-x < dis){
					dis = bx-x;
					last = balls[i];
				}
			}
		}
	}
	return last;
}

bool eat_ball(double x, double y) {
	if(mvinch(y,x) == 'O'){
		sprite_id target = get_sprite_at(x,y,100);
		for(int i = 0; i <10;i++){
			if(balls[i] == target){
				update_score(1);//lose life
				no_balls--;
				active[i] = FALSE;
				move_sprite_to(balls[i],-2,-2);
				return TRUE;
			}
		}
	}
	return FALSE;
}
// INSERT HELPER FUNCIONS HERE
