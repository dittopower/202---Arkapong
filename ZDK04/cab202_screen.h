#ifndef __SCREEN_H__
#define __SCREEN_H__

#include <stdlib.h>
#include <math.h>
#include <string.h>

#include "curses.h"
#include "cab202_coordinates.h"

/*  
 *	setup_screen:
 *
 *	Initialise the curses environment for game play.
 *	-	Keyboard buffering turned off;
 *	-	key echo turned off;
 *	-	cursor made invisible;
 *	-	special key processing (arrows, functions, numeric keypad)
 *		turned on.
 *	-	screen dimensions saved in screen_width and screen_height.
 */

void setup_screen();

/*
 *	reset_screen:
 *
 *	Restores the screen to its initial state.
 */

void reset_screen();


/*  
 *	update_screen:
 *
 *	Called once per turn (game cycle) to update the static
 *	elements of the screen. This includes determining the 
 *	current size of the display.
 *
 *	Output:
 *		Returns TRUE if and only if the screen size has changed.
 */

bool update_screen();


/*
 *	print_centre_string:
 *
 *	Helper function to display a string, centered on a specified
 *	location.
 *
 *	Input:
 *	-	s: a character sequence that will be displayed at the nominated
 *			location.
 *	-	x, y: the horizontal and vertical poistion at which the text is
 *			to be centred. 
 */

void print_centre_string( const char * s, int x, int y );

/*
 *	is_within_screen:
 *
 *	Function which determines whether the specified point is within
 *	the screen.
 *	
 *	Input:
 *	.	x, the horizontal coordinate of the point.
 *	.	y, the vertical coordinate of the point.
 *	
 *	Output:
 *	.	Returns a non-zero value if and only if 0 <= x < screen_width 
 *		and 0 <= y <= screen_height. 
 */

bool within_screen( double x, double y );

/*
 *	is_above_screen:
 *
 *	Function which determines whether the specified point is above
 *	the screen.
 *	
 *	Input:
 *	.	y, the vertical coordinate of the point.
 *	
 *	Output:
 *	.	Returns a non-zero value if and only if y < 0. 
 */

bool above_screen( double y );

/*
 *	is_below_screen:
 *
 *	Function which determines whether the specified point is above
 *	the screen.
 *	
 *	Input:
 *	.	y, the vertical coordinate of the point.
 *	
 *	Output:
 *	.	Returns a non-zero value if and only if y >= screen_height. 
 */

bool below_screen( double y );

/*
 *	is_left_of_screen:
 *
 *	Function which determines whether the specified point is to the left of the 
 *	visible area of the screen.
 *	
 *	Input:
 *	.	x, the horizontal coordinate of the point.
 *	
 *	Output:
 *	.	Returns a non-zero value if and only if x < 0. 
 */

bool left_of_screen( double x );

/*
 *	is_below_screen:
 *
 *	Function which determines whether the specified point is above
 *	the screen.
 *	
 *	Input:
 *	.	x the horizontal coordinate of the point.
 *	
 *	Output:
 *	.	Returns a non-zero value if and only if x >= screen_width. 
 */

bool right_of_screen( double x );

/*
 *	get_screen_width:
 *
 *	Returns the width of the screen.
 */

int get_screen_width();

/*
 *	get_screen_height:
 *
 *	Returns the height of the screen.
 */

int get_screen_height();

/*
 *	get_screen_size:
 *
 *	Returns the dimensions of the screen.
 *
 *	Input:
 *		x:	The address of a variable in which the current screen width will be 
 *			returned.
 *		y:	The address of a variable in which the current screen height will 
 *			be returned.
 */

screen_dimensions get_screen_size();

#endif
