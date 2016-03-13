#include <math.h>
#include "curses.h"
#include "cab202_coordinates.h"

#define PI 3.14159265358979323846

screen_position xy_to_screen( double x, double y ) {
	screen_position pos;
	pos.x = (int) round( x );
	pos.y = (int) round( y );
	return pos;
}

sprite_position xy_to_sprite( double x, double y ) {
	sprite_position pos;
	pos.x = x;
	pos.y = y;
	return pos;
}

screen_position sprite_to_screen( sprite_position sprite_pos ) {
	return xy_to_screen( sprite_pos.x, sprite_pos.y );
}


sprite_direction angle_to_direction( double degrees ) {
	double radians = degrees * PI / 180;
	sprite_direction dir;
	dir.dx = cos( radians );
	dir.dy = sin( radians );
	return dir;
}

sprite_direction dir_rotate( sprite_direction dir, double degrees ) {
	double radians = degrees * PI / 180;
	double c = cos( radians );
	double s = sin( radians );
	sprite_direction new_dir;
	new_dir.dx = c * dir.dx - s * dir.dy;
	new_dir.dy = s * dir.dx + c * dir.dy;
	return new_dir;
}

sprite_direction dir_left( sprite_direction dir ) {
	return dir_rotate( dir, -90 );
}

sprite_direction dir_right( sprite_direction dir ) {
	return dir_rotate( dir, 90 );
}

sprite_direction reflect_horizontal( sprite_direction dir ) {
	dir.dy = -dir.dy;
	return dir;
}

sprite_direction reflect_vertical( sprite_direction dir ) {
	dir.dx = -dir.dx;
	return dir;
}


