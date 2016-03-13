#include "cab202_simple_sprite.h"
#include "cab202_screen.h"

#include "block.h"

#include <time.h>

// INSERT GLOBAL VARIABLES HERE
sprite_id blocks[10];
bool blockactive = FALSE;
char block_img[4] = "####";


//-----------------------------------------------------------------------------
//  Function declarations.
//-----------------------------------------------------------------------------

// INSERT DECLARATIONS FOR HELPER FUNCTIONS HERE


//-----------------------------------------------------------------------------
//  Function implementations.
//-----------------------------------------------------------------------------


void setup_block() {
time_t t;
srand((unsigned) time(&t));

	if (blockactive){
		int Xs[10];
		int Ys[10];
		for(int i = 0; i < 10;i++){
			bool unused_coord = true;
			while(unused_coord){
				Xs[i] = ran_x();
				Ys[i] = ran_y();
				for(int a = 0;a < 10;a++){
					if(Xs[i] == Xs[a] && Ys[i] == Ys[a] && i != a){
						break;
					}
				}
				unused_coord = FALSE;
			}
			blocks[i] = create_big_sprite(Xs[i],Ys[i],2,2,block_img);
		}
	}else{
		for(int i = 0;i<10;i++){
			blocks[i] = create_big_sprite(-3,-3,2,2,block_img);
		}
	}
}

void reset_block() {
	if (blockactive){
		int Xs[10];
		int Ys[10];
		for(int i = 0; i < 10;i++){
			bool unused_coord = true;
			while(unused_coord){
				Xs[i] = ran_x();
				Ys[i] = ran_y();
				for(int a = 0;a < 10;a++){
					if(Xs[i] == Xs[a] && Ys[i] == Ys[a] && i != a){
						break;
					}
				}
				unused_coord = FALSE;
			}
			move_sprite_to(blocks[i],Xs[i],Ys[i]);
		}
		
	}else{
		for(int i = 0;i<10;i++){
			move_sprite_to(blocks[i],-3,-3);
		}
	}

}

bool activate_block(double x, double y) {
	if(mvinch(y,x) == '#'){
		sprite_id target = get_sprite_at(x,y,100);
		move_sprite_to(target, ran_x(),ran_y());
		//mvprintw(0,12,"%i",x);
		//mvprintw(1,12,"%i",y);
		return TRUE;
	}
	return FALSE;
}

bool toggle_blocks(){
	blockactive = !blockactive;
	reset_block();
	return blockactive;
}

// INSERT HELPER FUNCIONS HERE
int ran_x(){
	int ran = (rand() % (80-14)) + 6;
	return ran;
}
int ran_y(){
	int ran = (rand() % (24-5)) + 3;
	return ran;
}

