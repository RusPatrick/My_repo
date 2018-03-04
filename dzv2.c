#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>

char** mem_alloc( int num_strings, size_t buff_size ) {
	char** strings;

	if ( !( strings = ( char** )malloc( num_strings * sizeof( char* ) ) ) ) {
		printf( "[error]\n" );
		return NULL;
	}

	for (int i = 0; i < num_strings; ++i ) {
		if ( !( strings[i] = ( char* )malloc( buff_size * sizeof( char ) ) ) ) {
			printf( "[error]\n" );
			return NULL;
		}
	}
	return strings;
}

bool delete_spaces( char** inp_strings, int val_of_strings, char** outp_strings ) {
	if ( (inp_strings == NULL) || (val_of_strings == 0) ) {
		printf( "[error]" );
		return false;
	}

	for ( int i = 0; i < val_of_strings; ++i ) {
		int k = 0;
		for ( int j = 0; inp_strings[i][j] != '\0'; ++j ) {
			if (inp_strings[i][j] == ' ') {
	            if (k == 0) continue;
	            if (inp_strings[i][j + 1] == ' ') continue;
	        }
	        outp_strings[i][k] = inp_strings[i][j];
	        k++;
		}
	}
	return true;	
}


void print_strings( char** strings, int num_strings ) {
	for ( int i = 0; i < num_strings; ++i ) {
		printf ( "%s\n", strings[i] );
	}
}


int main() {
	size_t buff_size = 16;
	int num_strings = 1;
	char** strings;
	size_t *size_strings;

	if ( !(strings = mem_alloc(num_strings, buff_size) ) ) {
		printf( "[error]\n" );
		return 0;
	}

	if ( !( size_strings = ( size_t* )malloc( num_strings * sizeof( size_t ) ) ) ) {
		printf( "[error]\n" );
		return 0;
	}
	
	int i = 0;
	int j = 0;
	char c;
	while ( (c = getchar() ) != EOF ) {
		if (c != '\n') {
			strings[i][j] = c;
			if ( j == buff_size - 1 ) {
				buff_size += 16;
				strings[i] = ( char* )realloc( strings[i], buff_size * sizeof( char ) );
				// printf ( "buff_size = %zi\n", buff_size );
			}
			j++;
		} else {
			strings[i][j] = '\0';
			num_strings++;
			size_strings[i] = buff_size;
			size_strings = realloc( size_strings, num_strings * sizeof( size_t ) );
			strings = realloc( strings, num_strings * sizeof( char* ) );
			buff_size = 16;
			strings[num_strings - 1] = ( char* )malloc( buff_size * sizeof( char ) );
			i++;
			j = 0;
		}
	}

	char **new_strings = (char**)malloc(num_strings * sizeof(char*));

	for ( int i = 0; i < num_strings; ++i) {
		new_strings[i] = (char*)malloc(size_strings[i] * sizeof(char));
	}

	new_strings = delete_spaces( strings, num_strings, new_strings );

	print_strings( new_strings, num_strings );

	for ( int i = 0; i < num_strings; ++i ) {
		free( strings[i] );
		free( new_strings[i] );
	}
	free( strings );
	free( new_strings );
	free( size_strings );


	return 0;
}
