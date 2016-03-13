#include "cab202_simple_sprite.h"
#include "cab202_screen.h"

#include "score.h"


// INSERT GLOBAL VARIABLES HERE
sprite_id scoreboard_id;
int lives;
int score;
int const Lose_Life = 1;
int const Gain_Life = 2;
int const Gain_Score = 3;
int const Lose_Score = 4;
bool extras[8];


//-----------------------------------------------------------------------------
//  Function declarations.
//-----------------------------------------------------------------------------

// INSERT DECLARATIONS FOR HELPER FUNCTIONS HERE


//-----------------------------------------------------------------------------
//  Function implementations.
//-----------------------------------------------------------------------------


void setup_score() {

	// INSERT SETUP CODE HERE
	mvprintw(0,0,"Score: 0");
	score = 0;
	lives = 3;
	mvprintw(0,72,"Lives: %i",lives);
	mvprintw(1,0,"1:");
	for(int i = 1; i < 8; i++){
		mvprintw(1,i*7+1,"%i: ",(i+1));
		
	}
	for(int i = 1; i <= 8; i++){
		update_extra(i,extras[i-1]);
	}
	for(int i = 0; i < 80; i++){
		mvaddch(2,i,'_');
	}
	
	mvprintw(0,20,"Speed: ");
}

void reset_score() {

	// INSERT RESET CODE HERE
	setup_score();

}


bool update_score( char what ) {
	bool score_updated = FALSE;

	switch(what){
		case 1:
			lives--;
			mvprintw(0,79,"%i",lives);
			break;
		case 2:
			lives++;
			mvprintw(0,79,"%i",lives);
			break;
		case 4:
			score--;
			mvprintw(0,7,"%i",score);
			break;
		case 3:
			score++;
			mvprintw(0,7,"%i",score);
			break;
	}

	return score_updated;
}

int get_lives(){
	return lives;
}
int get_score(){
	return score;
}

void update_extra(int number, bool newvalue){
	int n = (number-1)*7+4;
	if(newvalue){
		mvprintw(1,n,"ON ");
		extras[number-1] = TRUE;
	}else{
		mvprintw(1,n,"OFF");
		extras[number-1] = FALSE;
	}
}

void update_wind(int num){
	switch(num){
		case 0:
			mvprintw(0,30,"Wind:  ");
			break;
		case 1:
			mvprintw(0,30,"Wind: >");
			break;
		case 2:
			mvprintw(0,30,"Wind: <");
			break;
		case 3:
			mvprintw(0,30,"Wind: ^");
			break;
		case 4:
			mvprintw(0,30,"Wind: V");
			break;
		case 5:
			mvprintw(0,30,"       ");
			break;
	}
}

void update_speed(int num){
	switch(num){
		case 1:
			mvprintw(0,27,"VF");
			break;
		case 5:
			mvprintw(0,27,"F ");
			break;
		case 10:
			mvprintw(0,27,"N ");
			break;
		case 15:
			mvprintw(0,27,"S ");
			break;
		case 20:
			mvprintw(0,27,"VS");
			break;
	}
}

// INSERT HELPER FUNCIONS HERE
