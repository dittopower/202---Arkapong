#ifndef __SCORE_H__
#define __SCORE_H__

#include "curses.h"
#include "cab202_simple_sprite.h"

// INSERT DECLARATIONS OF ANY NEW FUNCTIONS OR GLOBAL VARIABLES HERE

/*
 *	setup_score:
 *
 *	Initialises the score-related aspects of the game,
 *	creating the icon for the score and initialising other state related 
 *	to the score.
 */

void setup_score();

/*
 *	reset_score:
 *
 *	Restores the score to its original position and appearance.
 */

void reset_score();

/*
 *	Interprets the key code and updates the position of the score sprite 
 *	accordingly. 
 *
 *	Input:
 *		key_code:	an integer that represents a key code.
 *
 *	Output:
 *		Returns TRUE if and only if the score moved, indicating that the screen
 *		needs to be refreshed.
 */

bool update_score( char what );

int get_lives();
int get_score();
void update_extra(int num, bool state);
void update_wind(int num);
void update_speed(int num);

#endif
