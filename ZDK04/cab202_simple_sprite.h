#ifndef __SIMPLE_SPRITE_H__
#define __SIMPLE_SPRITE_H__

#include "curses.h"
#include "cab202_coordinates.h"
#include "cab202_timer.h"

#define SS_MAX 1000
#define SS_ERROR -1
#define SS_WIDTH 32
#define SS_HEIGHT 32

/* 
 *	Data type to uniquely identify all registered sprites. 
 */

typedef int sprite_id;

/*
 *	Data structure used to manage and render moving sprites.
 *
 *	Members:
 *		id: The unique ID of the sprite.
 *
 *		location: The location of the sprite, represented as double to allow
 *			fractional positioning.
 *
 *		screen_location: The current position of the sprite on the screen.
 *
 *		width:	The width of the sprite. This must be less than or equal to 
 *				SS_WIDTH.
 *
 *		height:	The height of the sprite. This must be less than or equal to 
 *				SS_HEIGHT.
 *
 *		display_data:	A 2-dimensional array containing the image of the sprite.
 *
 *		background: A 2-dimensional array containing the background which is 
 *					concealed by the sprite.
 *
 *		direction: The step that will be taken each time the sprite moves forward.
 *
 *		is_visible: Current visibility of the sprite. TRUE == visible; FALSE == invisible.
 *
 *		z_index: The height of the sprite above the background. The visible sprite having
 *			the greatest z_index at the current location is displayed.
 *		
 *		timer: The ID of a timer which (if non-negative) is used to automatically
 *			move the sprite.
 *		
 *		trail: The character (if non-zero) to leave behind in cells when moving. This
 *			replaces the background at the current position when the sprite leaves.
 */

typedef struct simple_sprite {
	sprite_id id;
	sprite_position location;
	screen_position screen_location;
	int width;
	int height;
	sprite_direction direction;
	bool is_visible;
	int z_index;
	timer_id timer;
	chtype trail;
	chtype display_data[SS_HEIGHT][SS_WIDTH];
	chtype background[SS_HEIGHT][SS_WIDTH];
} simple_sprite_t;

/*
 *	auto_refresh_sprites:
 *	
 *	Set this to TRUE to cause the screen to be updated immediately
 * whenever a sprite moves. Default value: TRUE.
 */

extern bool auto_refresh_sprites;

/*
 *	auto_sprite_delay:
 *
 *	Set this to a positive value to force a delay whenever a sprite 
 *	moves. Default value: 100 milliseconds.
 */

extern int auto_sprite_delay;

/*
 *	auto_wrap_sprites:
 *	
 *	Set this to TRUE to cause sprites to wrap around when the move off the 
 *	screen. Default value = FALSE;
 *
 *	THIS FUNCTIONALITY ISDISABLED IN THE PRESENT VERSION.
 */

extern bool auto_wrap_sprites;

/*
 *	create_sprite:
 *
 *	Initialise a sprite, appending it into the z buffer and saving its initial background.
 *	The sprite is then displayed at the coordinates specified by (x,y).
 *
 *	Input:
 *		x, y:	The initial location of the sprite. Floating point values are
 *				used to allow sub-pixel resolution (in a chunky display),
 *				making it easier to achieve "smooth" movement.
 *
 *		display_char:	The character to show.
 *
 *		attributes:	The display attributes for the sprite. This includes
 *					foreground and background colour, plus other attributes.
 *
 *	Output:
 *		Returns the ID of an initialised simple sprite object.
 */

sprite_id create_sprite( double x, double y, char display_char, int attributes );

/*
 *	create_big_sprite:
 *
 *	Initialise a sprite, appending it into the z buffer and saving its initial background.
 *	The sprite is then displayed at the coordinates specified by (x,y).
 *
 *	Input:
 *		x, y:	The initial location of the sprite. Floating point values are
 *				used to allow sub-pixel resolution (in a chunky display),
 *				making it easier to achieve "smooth" movement.
 *
 *		display_char:	A 1-d array containing the characters to show. There 
 *						should be at least width * height characters, with 
 *						'width' characters for the first row, followed immediately 
 *						by the same number of chars for the second row, etc.
 *
 *	Output:
 *		Returns the ID of an initialised simple sprite object.
 */

sprite_id create_big_sprite( double x, double y, int width, int height, char image[] );

/*
 *	create_big_sprite_attributes:
 *
 *	Initialise a sprite, appending it into the z buffer and saving its initial background.
 *	The sprite is then displayed at the coordinates specified by (x,y).
 *
 *	Input:
 *		x, y:	The initial location of the sprite. Floating point values are
 *				used to allow sub-pixel resolution (in a chunky display),
 *				making it easier to achieve "smooth" movement.
 *
 *		display_char:	A 1-d array containing the characters to show. There 
 *						should be at least width * height characters, with 
 *						'width' characters for the first row, followed immediately 
 *						by the same number of chars for the second row, etc.
 *
 *		attributes:	A 1-d array containing character attributes to show. There 
 *						should be at least width * height characters, with 
 *						'width' characters for the first row, followed immediately 
 *						by the same number of chars for the second row, etc.
 *
 *	Output:
 *		Returns the ID of an initialised simple sprite object.
 */

sprite_id create_big_sprite_attributes( double x, double y, int width, int height, char image[], int attributes[] );

/*
 *	move_sprite_to:
 *
 *	Move a sprite to an absolute location, restoring and saving the background,
 *	as necessary.
 *
 *	Input:
 *		id: The ID of the sprite which is to be moved.
 *
 *		x, y:	The coordinates of new location at which the sprite will be displayed.
 *
 *	Output:
 *		n/a.
 */

void move_sprite_to( sprite_id id, double x, double y );

/*
 *	move_sprite:
 *
 *	Move a sprite relative to its current location.
 *
 *	Input:
 *		id:	The sprite which is to be moved.
 *
 *		dx, dy: The distance by which the sprite is to be moved in the x,y
 *				plane.
 *
 *	Output:
 *		Returns an updated copy of the sprite.
 */

void move_sprite( sprite_id id, double dx, double dy );

/*
 *	show_sprite:
 *
 *	Turn an invisible sprite visible.
 *
 *	Input:
 *		id: The ID of the sprite which is to be made visible.
 *
 *	Output:
 *		n/a
 */

void show_sprite( sprite_id id );

/*
 *	hide_sprite:
 *
 *	Turn an invisible sprite invisible.
 *
 *	Input:
 *		id:	The ID of the sprite which is to be hidden.
 *
 *	Output:
 *		n/a.
 */

void hide_sprite( sprite_id id );

/*
 *	get_sprite_at:
 *
 *	Finds the visible sprite (if any) which is covering the specified location.
 *
 *	Input:
 *		x, y:		The screen location to be checked.
 *
 *		max_index:	The upper limit of the z-index range to be searched.
 *
 *	Output:
 *		If there is at least one visible sprite at the specified location,  
 *		a non-negative sprite ID is returned.
 *	
 *		If there is no visible sprite at the location, the function returns 
 *		a negative integer.
 */

sprite_id get_sprite_at( double x, double y, int max_index );

/*
 *	get_sprite:
 *
 *	Gets a copy of the sprite data associated with a particular sprite id.
 *	NB: changing the contents of the return object WILL NOT AFFECT the original.
 *
 *	Input:
 *		sprite: The ID of a registered sprite.
 *
 *	Output:
 *		Returns a copy of the data associated with the sprite.
 */

simple_sprite_t get_sprite( sprite_id id );

/*
 *	get_sprite_position:
 *
 *	Gets the location of a sprite in the sprite reference frame.
 *
 *	Input:
 *		id:	The ID of the sprite for which the location is desired.
 *
 *	Output:
 *		A sprite_position which holds the current location of the
 *		sprite in the sprite coordinate system.
 */

sprite_position get_sprite_position( sprite_id id );

/*
 *	get_sprite_size:
 *
 *	Gets the location of a sprite in the sprite reference frame.
 *
 *	Input:
 *		id:	The ID of the sprite for which the location is desired.
 *
 *	Output:
 *		A screen_dimensions object that holds the current size of the
 *		sprite.
 */

screen_dimensions get_sprite_size( sprite_id id );

/*
 *	get_sprite_screen_loc:
 *
 *	Gets the location on the curses screen (integer coordinate system)
 *	of a sprite.
 *
 *	Input:
 *		id:	The ID of the sprite for which the location is desired.
 *
 *	Output:
 *		The integer pair referenced by (*x, *y) will be updated to hold the current
 *		screen coordinates of the sprite.
 */

screen_position get_sprite_screen_loc( sprite_id id );

/* 
 *	set_sprite_background:
 *
 *	Replaces the saved background in any sprites at a particular point on the screen.
 *	Use this to prevent new drawing in the background from being wiped out when a sprite 
 *	moves away from the point.
 */

void set_sprite_background( screen_position location, chtype background_data );

/* 
 *	set_sprite_image:
 *
 *	Replaces the foreground image of a specified sprite and updates the screen.
 */

void set_sprite_image( sprite_id id, int width, int height, char image[] );

/* 
 *	set_sprite_image:
 *
 *	Replaces the foreground image of a specified sprite and updates the screen.
 */

void set_sprite_image_attributes( sprite_id id, int width, int height, char image[], int attributes[] );

/* Get the 'true' curses screen background at the specified screen location.
 *	
 *	Input:
 *	-	x, y: The horizontal and vertical offset to the location for which the
 *	screen coordinates are required.
 *	
 *	Output:
 *	-	Returns an integer containing (in encoded form) the character and
 *	screen attributes at the specified location.
 */

chtype get_sprite_background( double x, double y );

/*
 *	set_sprite_timer:
 *
 *	Attaches a timer to a sprite for use by the move_sprites_by_timer 
 *	function.
 *	
 *	Input:
 *		sprite_id: The ID of the sprite to which the timer is to be attached.
 *
 *		timer: The ID of a timer.
 */

void set_sprite_timer( sprite_id id, timer_id timer );

/*
 *	move_sprites_by_timer:
 *
 *	If the timer has expired, moves all sprites attached to the timer. Otherwise,
 *	no action is taken.
 *
 *	Input:
 *		timer_id:	The ID of a timer.
 *
 *	Output:
 *		Returns true if and only if at least one sprite moved. 
 */

bool move_sprites_by_timer( timer_id timer );

/*
 *	move_sprite_forward:
 *
 *	Moves a sprite one step in the direction saved within the sprite.
 *
 *	Input:
 *		sprite_id: The ID of a sprite.
 */

void move_sprite_forward( sprite_id id );

/*
 *	move_sprite_backward:
 *
 *	Moves a sprite one step backward in the direction saved within the sprite.
 *
 *	Input:
 *		sprite_id: The ID of a sprite.
 */

void move_sprite_backward( sprite_id id );

/*
 *	set_sprite_direction:
 *
 *	Sets the internally stored direction. This is the steps that is taken when 
 *	the sprite moves forward or backward.
 *
 *	Setting this to 0, 0 will stop movement, even if the sprite is connected
 *	to a timer.
 *
 *	Input:
 *		sprite_id: The ID of a sprite.
 *		dx: The distance to move horizontally.
 *		dy: The distance to move vertically.
 */

void set_sprite_direction( sprite_id id, double dx, double dy );

/*
 *	set_sprite_angle:
 *
 *	Sets the internally stored direction. This is the steps that is taken when 
 *	the sprite moves forward or backward.
 *
 *	Equivalent to set_sprite_direction( cos( degrees * PI / 180 ), sin( degrees * PI / 180 ) )
 *
 *	Input:
 *		sprite_id: The ID of a sprite.
 *		degrees: The angle to move.
 */

void set_sprite_angle( sprite_id id, double degrees );

/*
 *	turn_sprite:
 *
 *	Sets the internally stored direction. This is the steps that is taken when 
 *	the sprite moves forward or backward.
 *
 *	The new direction is relative to the old one. If the old direction is 0,0 then
 *	the new one will also be 0,0.
 *
 *	Input:
 *		sprite_id: The ID of a sprite.
 *		degrees: The angle to turn.
 */

void turn_sprite( sprite_id id, double degrees );

/*
 *	turn_sprite_left:
 *
 *	Turn sprite 90° left.
 *
 *	The new direction is relative to the old one. If the old direction is 0,0 then
 *	the new one will also be 0,0.
 *
 *	Input:
 *		sprite_id: The ID of a sprite.
 */

void turn_sprite_left( sprite_id id );

/*
 *	turn_sprite_right:
 *
 *	Turn sprite 90° right.
 *
 *	The new direction is relative to the old one. If the old direction is 0,0 then
 *	the new one will also be 0,0.
 *
 *	Input:
 *		sprite_id: The ID of a sprite.
 */

void turn_sprite_right( sprite_id id );

/*
 *	bounce_sprite_horizontal:
 *
 *	Bounces the sprite off a horizontal 'wall'.
 *
 *	Input:
 *		sprite_id: The ID of a sprite.
 *		degrees: The angle to turn.
 */

void bounce_sprite_horizontal( sprite_id id );

/*
 *	bounce_sprite_horizontal:
 *
 *	Bounces the sprite off a vertical 'wall'.
 *
 *	Input:
 *		sprite_id: The ID of a sprite.
 *		degrees: The angle to turn.
 */

void bounce_sprite_vertical( sprite_id id );

/*
 *	set_sprite_trail:
 *
 *	Sets the trail character (if any) left by the sprite sprite when 
 *	it leaves its current cell. This overwrites the background of the 
 *	cell.
 *
 *	Input:
 *		sprite_id:	The ID of a sprite.
 *
 *		trail:	The character to leave behind, or 0 to cancel the 
 *					breadcrumb functionality.
 */

void set_sprite_trail( sprite_id id, chtype trail );

#endif
