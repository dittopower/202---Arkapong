#ifndef __BALL_H__
#define __BALL_H__

#include "curses.h"
#include "cab202_simple_sprite.h"
#include "score.h"
#include "block.h"
#include "splitter.h"
#include "left_paddle.h"
#include "right_paddle.h"

// INSERT DECLARATIONS OF ANY NEW FUNCTIONS OR GLOBAL VARIABLES HERE

/*
 *	setup_ball:
 *
 *	Initialises the ball-related aspects of the game,
 *	creating the icon for the ball and initialising other state related 
 *	to the ball.
 */

void setup_ball();

/*
 *	reset_ball:
 *
 *	Restores the ball to its original position and appearance.
 */

void reset_ball();

/*
 *	Interprets the key code and updates the position of the ball sprite 
 *	accordingly. 
 *
 *	Input:
 *		key_code:	an integer that represents a key code.
 *
 *	Output:
 *		Returns TRUE if and only if the ball moved, indicating that the screen
 *		needs to be refreshed.
 */

bool update_ball();


bool activate_ball(double x, double y, double dx, double dy);

int get_no_balls();

sprite_id get_inbound_ball(int x);

bool eat_ball(double x, double y);

#endif
