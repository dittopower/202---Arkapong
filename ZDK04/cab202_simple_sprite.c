#include <stdlib.h>
#include <math.h>
#include "curses.h"
#include "cab202_simple_sprite.h"

// Public global variables, documented in .h file.

bool auto_refresh_sprites = TRUE;
int auto_sprite_delay = 100;
bool auto_wrap_sprites = FALSE;

// "Private" global variables

/*
 *  ss_z_buffer:
 *
 *	A list containing the addresses of all registered sprites.
 *	At most SS_MAX sprites may be registered.
 */

simple_sprite_t sprites[SS_MAX];

/*
 *  ss_count:
 *
 *	The number of registered sprites.
 *	At most SS_MAX sprites may be registered.
 */

int sprite_count;

//-----------------------------------------------------------------------------
// Helper functions.
//-----------------------------------------------------------------------------

/* 
 *	Removes any visible traces of a sprite from the screen, replacing those parts 
 *	that were visible with either the background, or part of any obscured sprite
 */

void remove_sprite_from_view( sprite_id id );

/* 
 *	Renders any visible parts of a sprite onto the screen, replacing those parts 
 *	that were visible with either the background, or part of any obscured sprite.
 */

void display_sprite( sprite_id id );

/* 
 *	Copies a rectangular region of background data into the background buffer of
 *	a sprite.
 */

void load_sprite_background( sprite_id id, double x, double y );

/*  
 *	Removes the character at position (row,col) within a sprite from the display
 *	and restores whatever it is concealing.
 */

void remove_char_from_view( sprite_id id, int x, int y, int row, int col );

//-----------------------------------------------------------------------------
// Implementation of public functions.
//-----------------------------------------------------------------------------

sprite_id create_sprite( double x, double y, char display_char, int attributes ) {
	char chars[1] = { display_char };
	int  attrs[1] = { attributes };

	return create_big_sprite_attributes( x, y, 1, 1, chars, attrs );
}


sprite_id create_big_sprite( double x, double y, int width, int height, char image[] ) {
	int attrs[SS_HEIGHT * SS_WIDTH] = { 0 };

	return create_big_sprite_attributes( x, y, width, height, image, attrs );
}


sprite_id create_big_sprite_attributes( double x, double y, int width, int height, char image[], int attributes[] ) {
	sprite_id id = SS_ERROR;

	if ( sprite_count >= SS_MAX ) {
		return id;
	}

	id = sprite_count;

	sprites[id].id = id;
	sprites[id].is_visible = FALSE;
	sprites[id].z_index = id;
	sprites[id].direction.dx = 0;
	sprites[id].direction.dy = 0;
	sprites[id].timer = TIMER_ERROR;

	sprites[id].location.x = 0;
	sprites[id].location.y = 0;
	sprites[id].screen_location.x = 0;
	sprites[id].screen_location.y = 0;

	set_sprite_image_attributes( id, width, height, image, attributes );

	sprite_count++;
	sprites[id].is_visible = TRUE;

	move_sprite_to( id, x, y );

	return id;
}


void set_sprite_image( sprite_id id, int width, int height, char image[] ) {
	int attrs[SS_HEIGHT * SS_WIDTH] = { 0 };

	set_sprite_image_attributes( id, width, height, image, attrs );
}


void set_sprite_image_attributes( sprite_id id, int width, int height, char image[], int attributes[] ) {
	if ( sprites[id].is_visible ) {
		remove_sprite_from_view( id );
	}

	sprites[id].width = width;
	sprites[id].height = height;

	for ( int row = 0, index = 0; row < height; row++ ) {
		for ( int col = 0; col < width; col++, index++ ) {
			sprites[id].display_data[row][col] = image[index] | attributes[index];
		}
	}

	load_sprite_background( id, sprites[id].location.x, sprites[id].location.y );

	if ( sprites[id].is_visible ) {
		display_sprite( id );
	}
}


void move_sprite_to( sprite_id id, double x, double y ) {
	if ( id < 0 || id >= sprite_count ) {
		return;
	}

	if ( sprites[id].is_visible ) {
		if ( sprites[id].trail > 0 ) {
			set_sprite_background( sprites[id].screen_location, sprites[id].trail );
		}

		remove_sprite_from_view( id );
	}

	load_sprite_background( id, x, y );

	sprites[id].location.x = x;
	sprites[id].location.y = y;
	sprites[id].screen_location = xy_to_screen( x, y );

	if ( sprites[id].is_visible ) {
		display_sprite( id );
	}

	if ( auto_refresh_sprites ) {
		refresh();
	}

	if ( auto_sprite_delay > 0 ) {
		timer_pause( auto_sprite_delay );
	}
}


void move_sprite( sprite_id id, double dx, double dy ) {
	if ( id < 0 || id >= sprite_count ) return;

	move_sprite_to( id, sprites[id].location.x + dx, sprites[id].location.y + dy );
}


void remove_sprite_from_view( sprite_id id ) {
	screen_position scr_pos = sprites[id].screen_location;
	int x = scr_pos.x;
	int y = scr_pos.y;

	for ( int row = 0; row < sprites[id].height; row++ ) {
		for ( int col = 0; col < sprites[id].width; col++ ) {
			remove_char_from_view( id, x, y, row, col );
		}
	}
}


void remove_char_from_view( sprite_id id, int x, int y, int row, int col ) {
	sprite_id visible_sprite = get_sprite_at( x + col, y + row, sprite_count );

	if ( visible_sprite != id ) {
		return;
	}

	visible_sprite = get_sprite_at( x + col, y + row, id );

	if ( visible_sprite < 0 ) {
		// No sprite --> display background
		mvaddch( y + row, x + col, sprites[id].background[row][col] );
	}
	else { 
		// Some other sprite --> display char from that sprite.
		screen_position visible_scr = sprites[visible_sprite].screen_location;
		int row2 = y + row - visible_scr.y;
		int col2 = x + col - visible_scr.x;
		mvaddch( y + row, x + col, sprites[visible_sprite].display_data[row2][col2] );
	}
}


void display_sprite( sprite_id id ) {
	int x = sprites[id].screen_location.x;
	int y = sprites[id].screen_location.y;

	for ( int row = 0; row < sprites[id].height; row++ ) {
		for ( int col = 0; col < sprites[id].width; col++ ) {
			int top_sprite = get_sprite_at( x + col, y + row, sprite_count );

			if ( top_sprite == id ) {
				mvaddch( y + row, x + col, sprites[id].display_data[row][col] );
			}
		}
	}
}


void show_sprite( sprite_id id ) {
	if ( id < 0 || id >= sprite_count ) {
		return;
	}

	sprites[id].is_visible = TRUE;
	display_sprite( id );
}


void hide_sprite( sprite_id id ) {
	if ( id < 0 || id >= sprite_count ) {
		return;
	}

	sprites[id].is_visible = FALSE;
	remove_sprite_from_view( id );
}


chtype get_sprite_background( double x, double y ) {
	screen_position scr = xy_to_screen( x, y );

	// Locate the first sprite that is covering the position.
	for ( int i = 0; i < sprite_count; i++ ) {
		int sprite_x = sprites[i].screen_location.x;
		int sprite_y = sprites[i].screen_location.y;
		int width = sprites[i].width;
		int height = sprites[i].height;
		int row = scr.y - sprite_y;
		int col = scr.x - sprite_x;

		if ( row >= 0 && row < height && col >= 0 && col < width ) {
			// Get background data from sprite.
			chtype bg = sprites[i].background[row][col];

			// If bg is zero, the sprite has no useable data at this time.
			if ( bg > 0 ) {
				return bg;
			}
		}
	}

	// Nothing found, so return the contents of the screen.
	return mvinch( scr.y, scr.x );
}


sprite_id get_sprite_at( double x, double y, int max_index ) {
	if ( max_index > sprite_count ) {
		max_index = sprite_count;
	}

	screen_position pos = xy_to_screen( x, y );

	for ( int z_index = max_index - 1; z_index >= 0; z_index-- ) {
		if ( sprites[z_index].is_visible ) {
			screen_position scr = sprites[z_index].screen_location;
			int sprite_x = scr.x;
			int sprite_y = scr.y;
			int width = sprites[z_index].width;
			int height = sprites[z_index].height;
			int row = pos.y - sprite_y;
			int col = pos.x - sprite_x;

			if ( row >= 0 && row < height && col >= 0 && col < width ) {
				chtype display_data = sprites[z_index].display_data[row][col];

				if ( ( display_data & A_CHARTEXT ) != ' ' ) {
					return z_index;
				}
			}
		}
	}

	return SS_ERROR;
}


screen_position get_sprite_screen_loc( sprite_id id ) {
	if ( id < 0 || id >= sprite_count ) {
		screen_position error = { SS_ERROR, SS_ERROR };
		return error;
	}

	return sprites[id].screen_location;
}


sprite_position get_sprite_position( sprite_id id ) {
	if ( id < 0 || id >= sprite_count ) {
		sprite_position error = { SS_ERROR, SS_ERROR };
		return error;
	}

	return sprites[id].location;
}


screen_dimensions get_sprite_size( sprite_id id ) {
	screen_dimensions size;
	size.width = sprites[id].width;
	size.height = sprites[id].height;
	return size;
}


simple_sprite_t get_sprite( sprite_id id ) {
	if ( id < 0 || id >= sprite_count ) {
		simple_sprite_t error = { 0 };
		return error;
	}

	return sprites[id];
}


bool sprite_is_visible( sprite_id id ) {
	if ( id < 0 || id >= sprite_count ) {
		return FALSE;
	}

	return sprites[id].is_visible;
}


void set_sprite_background( screen_position location, chtype background_data ) {
	bool background_is_visible = TRUE;

	for ( int i = 0; i < sprite_count; i++ ) {
		int sprite_x = sprites[i].screen_location.x;
		int sprite_y = sprites[i].screen_location.y;
		int width = sprites[i].width;
		int height = sprites[i].height;
		int row = location.y - sprite_y;
		int col = location.x - sprite_x;

		if ( row >= 0 && row < height && col >= 0 && col < width ) {
			sprites[i].background[row][col] = background_data;

			if ( ( sprites[i].display_data[row][col] & A_CHARTEXT ) != ' ' ) {
				background_is_visible = FALSE;
			}
		}
	}

	if ( background_is_visible ) {
		mvaddch( location.y, location.x, background_data );
	}
}


void set_sprite_direction( sprite_id id, double dx, double dy ) {
	if ( id < 0 || id >= sprite_count ) {
		return;
	}

	sprites[id].direction.dx = dx;
	sprites[id].direction.dy = dy;
}


void set_sprite_timer( sprite_id id, timer_id timer ) {
	if ( id < 0 || id >= sprite_count ) {
		return;
	}

	sprites[id].timer = timer;
}


bool move_sprites_by_timer( timer_id timer ) {
	if ( !timer_expired( timer ) ) {
		return FALSE;
	}

	bool something_moved = FALSE;

	for ( int i = 0; i < sprite_count; i++ ) {
		if ( sprites[i].timer == timer && sprites[i].is_visible ) {
			move_sprite_forward( i );
			something_moved = TRUE;
		}
	}

	return something_moved;
}


void move_sprite_forward( sprite_id id ) {
	if ( id < 0 || id >= sprite_count ) {
		return;
	}

	move_sprite( id, sprites[id].direction.dx, sprites[id].direction.dy );
}


void move_sprite_backward( sprite_id id ) {
	if ( id < 0 || id >= sprite_count ) {
		return;
	}

	sprite_direction dir = sprites[id].direction;
	move_sprite( id, -dir.dx, -dir.dy );
}


void turn_sprite_left( sprite_id id ) {
	if ( id < 0 || id >= sprite_count ) {
		return;
	}

	sprites[id].direction = dir_left( sprites[id].direction );
}


void turn_sprite_right( sprite_id id ) {
	if ( id < 0 || id >= sprite_count ) {
		return;
	}

	sprites[id].direction = dir_right( sprites[id].direction );
}


void turn_sprite( sprite_id id, double degrees ) {
	if ( id < 0 || id >= sprite_count ) {
		return;
	}

	sprites[id].direction = dir_rotate( sprites[id].direction, degrees );
}


void bounce_sprite_horizontal( sprite_id id ) {
	if ( id < 0 || id >= sprite_count ) {
		return;
	}

	sprite_direction dir = reflect_horizontal( sprites[id].direction );
	sprites[id].direction = dir;
}


void bounce_sprite_vertical( sprite_id id ) {
	if ( id < 0 || id >= sprite_count ) {
		return;
	}

	sprites[id].direction = reflect_vertical( sprites[id].direction );
}


void set_sprite_angle( sprite_id id, double degrees ) {
	if ( id < 0 || id >= sprite_count ) {
		return;
	}

	sprites[id].direction = angle_to_direction( degrees );
}


void set_sprite_trail( sprite_id id, chtype trail ) {
	if ( id < 0 || id >= sprite_count ) {
		return;
	}

	sprites[id].trail = trail;
}

void load_sprite_background( sprite_id id, double x, double y ) {
	// Erase the current background in the sprite
	for ( int row = 0; row < SS_HEIGHT; row++ ) {
		for ( int col = 0; col < SS_WIDTH; col++ ) {
			sprites[id].background[row][col] = 0;
		}
	}

	// Load fresh contents into temporary storage
	chtype back_buffer[SS_HEIGHT][SS_WIDTH];

	for ( int row = 0; row < sprites[id].height; row++ ) {
		for ( int col = 0; col < sprites[id].width; col++ ) {
			back_buffer[row][col] = get_sprite_background( x + col, y + row );
		}
	}

	// Copy temporary data back in to sprite background.
	for ( int row = 0; row < sprites[id].height; row++ ) {
		for ( int col = 0; col < sprites[id].width; col++ ) {
			sprites[id].background[row][col] = back_buffer[row][col];
		}
	}
}