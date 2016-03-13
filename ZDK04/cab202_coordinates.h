#ifndef __COORDINATES_H__
#define __COORDINATES_H__

/*
 * sprite_position:
 *
 *	A data structure which represents a (x,y) pair of floating point values.
 */

typedef struct {
	double x, y;
} sprite_position;


/*
 * screen_position:
 *
 *	A data structure which represents a (x,y) pair of integer values.
 */

typedef struct {
	int x, y;
} screen_position;

/*
 *	screen_dimensions:
 *
 *	A data structure which represents the dimensions of a rectangular object on the screen.
 */

typedef struct {
	int width;
	int height;
} screen_dimensions;

/*
 *	direction:
 *
 *	A data structure used to represent directions for sprite movement.
 */

typedef struct {
	double dx, dy;
} sprite_direction;

/*
 *	xy_to_screen:
 *
 *	Converts a pair of floating point values to a screen location.
 *
 *	Input:
 *		x, y: a pair of floating point value which represent a location in sprite space.
 *
 *	Output:
 *		Returns the screen location that corresponds to the sprite location.
 */

screen_position xy_to_screen( double x, double y );

/*
 *	xy_to_sprite:
 *
 *	Converts a pair of floating point values to a sprite location.
 */

sprite_position xy_to_sprite( double x, double y );

/*
 *	xy_to_direction:
 *
 *	Converts a pair of floating point values to a direction. 
 */

sprite_direction xy_to_direction( double x, double y );

/*
 *	angle_to_direction:
 *
 *	Creates a direction vector representing the specified angle 
 *	(measured in degrees).
 */

sprite_direction angle_to_direction( double degrees );

/*
*	sprite_to_screen:
*
*	Maps coordinates from sprite coordinate system to screen.
*
*	Input:
*		location: A coordinate pair in sprite-space.
*
*	Output:
*		Returns the screen location that corresponds to the sprite location.
*
*/

screen_position sprite_to_screen( sprite_position location );


sprite_direction dir_rotate( sprite_direction dir, double degrees );

sprite_direction dir_left( sprite_direction dir );

sprite_direction dir_right( sprite_direction dir );

sprite_direction reflect_horizontal( sprite_direction dir );

sprite_direction reflect_vertical( sprite_direction dir );

#endif
