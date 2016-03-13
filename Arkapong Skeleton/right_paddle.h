#ifndef __RIGHT_PADDLE_H__
#define __RIGHT_PADDLE_H__

#include "curses.h"
#include "cab202_simple_sprite.h"

// INSERT DECLARATIONS OF ANY NEW FUNCTIONS OR GLOBAL VARIABLES HERE

/*
 *	setup_right_paddle:
 *
 *	Initialises the right_paddle-related aspects of the game,
 *	creating the icon for the right_paddle and initialising other state related 
 *	to the right_paddle.
 */

void setup_right_paddle();

/*
 *	reset_right_paddle:
 *
 *	Restores the right_paddle to its original position and appearance.
 */

void reset_right_paddle();

/*
 *	Interprets the key code and updates the position of the right_paddle sprite 
 *	accordingly. 
 *
 *	Input:
 *		key_code:	an integer that represents a key code.
 *
 *	Output:
 *		Returns TRUE if and only if the right_paddle moved, indicating that the screen
 *		needs to be refreshed.
 */

bool update_right_paddle( int key_code );

void blockside();

void grow_right();
void shrink_right();

#endif
