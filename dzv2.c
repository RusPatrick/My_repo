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


/*void print_strings( char** strings, int num_strings ) {
	for ( int i = 0; i < num_strings; ++i ) {
		printf ( "%s\n", strings[i] );
	}
}*/


int main() {
	const size_t buff_size = 32;
	int num_strings = 1;
	char** strings;

	if ( !(strings = mem_alloc(num_strings, buff_size) ) ) {
		printf( "[error]\n" );
		return 0;
	}

	size_t *size_strings;
	if ( !( size_strings = ( size_t* )malloc( num_strings * sizeof( size_t ) ) ) ) {
		printf( "[error]\n" );
		return 0;
	}
	
	int i = 0;
	int j = 0;
	char c;
	size_strings[i] = buff_size;
	while ( (c = getchar() ) != EOF ) {
		if (c != '\n') {
			strings[i][j] = c;
			if ( j == buff_size - 1 ) {
				size_strings[i] += 32;
				strings[i] = ( char* )realloc( strings[i], size_strings[i] * sizeof( char ) );
				// printf ( "buff_size = %zi\n", buff_size );
			}
			j++;
		} else {
			strings[i][j] = '\0';
			num_strings++;
			size_strings = realloc( size_strings, num_strings * sizeof( size_t ) );
			strings = realloc( strings, num_strings * sizeof( char* ) );
			size_strings[num_strings - 1] = buff_size;
			strings[num_strings - 1] = ( char* )malloc( size_strings[num_strings - 1] * sizeof( char ) );
			i++;
			j = 0;
		}
	}

	char **new_strings = (char**)malloc(num_strings * sizeof(char*));

	for ( int i = 0; i < num_strings; ++i) {
		new_strings[i] = (char*)malloc(size_strings[i] * sizeof(char));
		// printf("%zd(size_strings[%d]\n", size_strings[i], i);
	}

	if (!(delete_spaces( strings, num_strings, new_strings )) ){
		printf("[error]\n");
		return 0;
	}

	// print_strings( new_strings, num_strings );

	for ( int i = 0; i < num_strings; ++i ) {
		printf ( "%s\n", new_strings[i] );
	}

	for ( int i = 0; i < num_strings; ++i ) {
		free( strings[i] );
		free( new_strings[i] );
	}
	free( strings );
	free( new_strings );
	free( size_strings );


	return 0;
}
