#include <math.h>

#include "cab202_screen.h"

int screen_width, screen_height;

void setup_screen() {
	initscr();
	timeout( 0 );
	cbreak();
	noecho();
	curs_set( 0 );
	keypad( stdscr, TRUE );
	reset_screen();
}


void reset_screen() {
	clear();
	screen_width = getmaxx( stdscr );
	screen_height = getmaxy( stdscr );
}


bool update_screen() {
	int width = getmaxx( stdscr );
	int height = getmaxy( stdscr );

	bool screen_resized = ( width != screen_width || height != screen_height );

	if ( screen_resized ) {
		screen_width = width;
		screen_height = height;
		return TRUE;
	}

	return FALSE;
}


void print_centre_string( const char * s, int x, int y ) {
	mvaddstr( y, x - strlen( s ) / 2, s );
}


bool within_screen( double x, double y ) {
	return x >= 0 && y >= 0 && x < screen_width && y < screen_height;
}


bool above_screen( double y ) {
	return round( y ) < 0;
}


bool below_screen( double y ) {
	return round( y ) >= screen_height;
}


bool left_of_screen( double x ) {
	return round( x ) < 0;
}


bool right_of_screen( double x ) {
	return round( x ) >= screen_width;
}


int get_screen_width() {
	return screen_width;
}


int get_screen_height() {
	return screen_height;
}


screen_dimensions get_screen_size() {
	screen_dimensions size;
	size.width = screen_width;
	size.height = screen_height;
	return size;
}
