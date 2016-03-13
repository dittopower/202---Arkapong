#ifndef __MUNCHER_H__
#define __MUNCHER_H__

#include "curses.h"
#include "cab202_simple_sprite.h"
#include "ball.h"
#include "splitter.h"
#include "left_paddle.h"
#include "right_paddle.h"

// INSERT DECLARATIONS OF ANY NEW FUNCTIONS OR GLOBAL VARIABLES HERE

/*
 *	setup_muncher:
 *
 *	Initialises the muncher-related aspects of the game,
 *	creating the icon for the muncher and initialising other state related 
 *	to the muncher.
 */

void setup_muncher();

/*
 *	reset_muncher:
 *
 *	Restores the muncher to its original position and appearance.
 */

void reset_muncher();

/*
 *	Interprets the key code and updates the position of the muncher sprite 
 *	accordingly. 
 *
 *	Input:
 *		key_code:	an integer that represents a key code.
 *
 *	Output:
 *		Returns TRUE if and only if the muncher moved, indicating that the screen
 *		needs to be refreshed.
 */

bool update_muncher();

bool toggle_muncher();

#endif
