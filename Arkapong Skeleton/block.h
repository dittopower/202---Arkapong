#ifndef __BLOCK_H__
#define __BLOCK_H__

#include "curses.h"
#include "cab202_simple_sprite.h"

// INSERT DECLARATIONS OF ANY NEW FUNCTIONS OR GLOBAL VARIABLES HERE

/*
 *	setup_block:
 *
 *	Initialises the block-related aspects of the game,
 *	creating the icon for the block and initialising other state related 
 *	to the block.
 */

void setup_block();

/*
 *	reset_block:
 *
 *	Restores the block to its original position and appearance.
 */

void reset_block();

/*
 *	Interprets the key code and updates the position of the block sprite 
 *	accordingly. 
 *
 *	Input:
 *		key_code:	an integer that represents a key code.
 *
 *	Output:
 *		Returns TRUE if and only if the block moved, indicating that the screen
 *		needs to be refreshed.
 */

bool activate_block(double x, double y);

bool toggle_blocks();

int ran_x();
int ran_y();

#endif
