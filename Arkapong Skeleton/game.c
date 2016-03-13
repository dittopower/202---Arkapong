#include "game.h"
bool pause = FALSE;
bool end = FALSE;
double speed = 1;

void setup_game() {
	auto_refresh_sprites = FALSE;
	auto_sprite_delay = FALSE;
	auto_wrap_sprites = FALSE;

	setup_screen();
	
	//
	setup_score();
	setup_right_paddle();
	setup_left_paddle();
	setup_ball();
	setup_block();
	setup_splitter();
	update_speed(10*speed);
	setup_muncher();
	
	refresh();
}


void reset_game() {
	reset_screen();
	
	pause = FALSE;
	end = FALSE;
	reset_right_paddle();
	reset_left_paddle();
	reset_score();
	reset_ball();
	reset_block();
	reset_splitter();
	update_speed(10*speed);
	reset_muncher();

	refresh( );
}


int play_turn() {
	if ( update_screen() ) {
		reset_game();
		return TURN_OK;
	}

	/* If we have a key, process it immediately. */
	int key_code = getch();

	if ( key_code == 'q' || key_code == 'Q' ) {
		return TURN_GAME_OVER;
	}
	else if ( key_code == 'r' || key_code == 'R' ) {
		reset_game();
		return TURN_OK;
	}
	
	//Custom Extras
	if (key_code == ' '){
		pause = !pause;
	}
	if (pause || end){
		return TURN_OK;
	}
	
	if (key_code == 's' || key_code == 'S'){//speed affects you as well to be fair
		if(speed == 0.1){//mainly for testing purposes
			speed = 0.5;
		}else if(speed == 0.5){
			speed = 1;
		}else if(speed == 1){
			speed = 1.5;
		}else if(speed == 1.5){
			speed = 2;
		}else if(speed == 2){
			speed = 0.1;
		}
		update_speed(10*speed);
	}
	timer_pause( 50*speed );
	
	if (key_code == 'g' || key_code == 'G'){
		blockside();
	}
	
	//Extra functions
	switch(key_code){
		case 49://1
			update_extra(1,toggle_ai());
			break;
		case 50://2
			
			break;
		case 51://3
			update_extra(3,toggle_blocks());
			break;
		case 52://4
			update_extra(4,toggle_extender());
			break;
		case 53://5
			update_extra(5,toggle_shrinker());
			break;
		case 54://6
			update_extra(6,toggle_splitters());
			break;
		case 55://7
			update_extra(7,toggle_wind());
			break;
		case 56://8
			update_extra(8,toggle_muncher());
			break;
	}
	
	//Moving Things
	int retur = TURN_OK;
	
	if ( update_right_paddle( key_code ) ) {
		retur = TURN_SCREEN_CHANGED;
	}
	if ( update_left_paddle()){
		retur = TURN_SCREEN_CHANGED;
	}
	if(update_ball()){
		retur = TURN_SCREEN_CHANGED;
	}
	if(update_muncher()){
		retur = TURN_SCREEN_CHANGED;
	}
	
	if(get_lives() < 1){
		gameover();
		return TURN_OK;
	}else if(get_no_balls() < 1){
		reset_ball();
		retur = TURN_SCREEN_CHANGED;
	}

	return retur;
}

void gameover(){
	reset_screen();
	end = TRUE;
	print_centre_string("Game Over",40,8);
	mvprintw(12,31,"Your Score was %i",get_score());
	
	print_centre_string("Press 'r' to Restart",40,16);
	print_centre_string("Press 'q' to Quit",40,17);
	
	print_centre_string("Ps. 'S' toggle the Game's Speed",40,22);
	print_centre_string("Space to Pause",40,23);
}
