#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#define DYNAMIC_ARRAY_GROW_FACTOR 2

struct dynamic_array {
	size_t object_length;

	size_t size;
	size_t capacity;

	void * storage;
};

bool dynamic_array_create ( struct dynamic_array * self, size_t _object_length, size_t _initial_capacity ) {
	self->object_length = _object_length;

	self->size = 0;
	self->capacity = _initial_capacity;
	
	self->storage = malloc ( self->capacity * self->object_length );

	return self->storage != NULL;
}

void dynamic_array_destroy ( struct dynamic_array * self ) {
	free ( self->storage );
}

bool dynamic_array_grow ( struct dynamic_array * self ) {
	void * new_storage = realloc ( self->storage, DYNAMIC_ARRAY_GROW_FACTOR * self->capacity * self->object_length );
	
	if ( new_storage == NULL )
		return false;

	self->capacity *= DYNAMIC_ARRAY_GROW_FACTOR;
	self->storage = new_storage;

	return true;
}

bool dynamic_array_alloc_back ( struct dynamic_array * self ) {
	if ( self->size == self->capacity )
		if ( ! dynamic_array_grow ( self ) )
			return false;

	++ self->size;

	return true;
}

void dynamic_array_dealloc_back ( struct dynamic_array * self ) {
	--self->size;
}

void * dynamic_array_get_object_at ( struct dynamic_array * self, size_t _index ) {
	return self->storage + _index * self->object_length;
}

void * dynamic_array_back ( struct dynamic_array * self ) {
	return dynamic_array_get_object_at ( self, self->size - 1 );
}

size_t dynamic_array_get_size ( struct dynamic_array * self ) {
	return self->size;
}

void print_string ( struct dynamic_array * _string ) {
	for ( size_t i = 0; i < dynamic_array_get_size ( _string ); ++i )
		putchar ( * ( char * ) dynamic_array_get_object_at ( _string, i ) );

	putchar ( '\n' );
}

bool read_string ( struct dynamic_array * _string_storage ) {
	if ( ! dynamic_array_create ( _string_storage, sizeof ( char ), 32 ) ) 
		return false;

	for ( char input_char = getchar (); input_char != '\n' && input_char != EOF; input_char = getchar () ) {
		if ( ! dynamic_array_alloc_back ( _string_storage ) ) {
			dynamic_array_destroy ( _string_storage );
			return false;
		}

		* ( char * ) dynamic_array_back ( _string_storage ) = input_char;
	}

	return true;
}

bool read_string_array ( struct dynamic_array * _string_array_storage ) {
	if ( ! dynamic_array_create ( _string_array_storage, sizeof ( struct dynamic_array ), 1 )
		return false;

	while ( ! feof ( STDIN ) ) {
		if ( ! dynamic_array_alloc_back ( _string_array_storage ) ) {
			for ( size_t i = 0; i < dynamic_array_get_size ( _string_array_storage ); ++i ) 
				dynamic_array_destroy ( dynamic_array_get_object_at ( _string_array_storage, i ) );

			dynamic_array_destroy ( _string_array_storage );

			return false;
		}

		if ( ! read_string ( dynamic_array_back ( _string_array_storage ) ) ) {
			dynamic_array_dealloc_back ( _string_array_storage );

			for ( size_t i = 0; i < dynamic_array_get_size ( _string_array_storage ); ++i ) 
				dynamic_array_destroy ( dynamic_array_get_object_at ( _string_array_storage, i ) );

			dynamic_array_destroy ( _string_array_storage );

			return false;
		}
	}

	return true;
}

void delete_spaces ( struct dynamic_array * _source_string_array, struct dynamic_array * _target_string_array ) {
	for ( size_t i = 0; i < dynamic_array_get_size ( _source_string_array ); ++i ) {
		if ( !)
	}
}

void print_string_array ( struct dynamic_array * _string_array ) {
	for ( size_t i = 0; i < dynamic_array_get_size ( _string_array ); ++i )
		print_string ( ( struct dynamic_array * ) dynamic_array_get_object_at ( _string_array, i ) );
}

void destroy_string_array ( struct dynamic_array * _string_array ) {
	for ( size_t i = 0; i < dynamic_array_get_size ( _string_array ); ++i )
		dynamic_array_destroy ( ( struct dynamic_array * ) dynamic_array_get_object_at ( _string_array, i ) );

	dynamic_array_destroy ( _string_array );
}

int main ( void ) {
	struct dynamic_array input_string_array;
	struct dynamic_array output_string_array;

	read_string_array ( & input_string_array );
	delete_spaces ( & input_string_array, & output_string_array );
	
	print_string_array ( & output_string_array );

	destroy_string_array ( & input_string_array );
	destroy_string_array ( & output_string_array );

	return 0;
}
