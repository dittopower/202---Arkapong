#ifndef __LEFT_PADDLE_H__
#define __LEFT_PADDLE_H__

#include "curses.h"
#include "cab202_simple_sprite.h"
#include "ball.h"

// INSERT DECLARATIONS OF ANY NEW FUNCTIONS OR GLOBAL VARIABLES HERE

/*
 *	setup_left_paddle:
 *
 *	Initialises the left_paddle-related aspects of the game,
 *	creating the icon for the left_paddle and initialising other state related 
 *	to the left_paddle.
 */

void setup_left_paddle();

/*
 *	reset_left_paddle:
 *
 *	Restores the left_paddle to its original position and appearance.
 */

void reset_left_paddle();

/*
 *	Interprets the key code and updates the position of the left_paddle sprite 
 *	accordingly. 
 *
 *	Input:
 *		key_code:	an integer that represents a key code.
 *
 *	Output:
 *		Returns TRUE if and only if the left_paddle moved, indicating that the screen
 *		needs to be refreshed.
 */

bool update_left_paddle();

bool toggle_ai();

void grow_left();
void shrink_left();

#endif
