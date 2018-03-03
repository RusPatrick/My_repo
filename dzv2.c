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

char** delete_spaces( char** inp_strings, int val_of_strings ) {
	size_t buff_size = 16;
	char** outp_strings = mem_alloc(val_of_strings, buff_size );

	if ( (inp_strings == NULL) || (val_of_strings == 0) ) {
		printf( "[error]" );
		return false;
	}

	for ( int i = 0; i < val_of_strings; ++i ) {
		int j = 0;
		int k = 0;
		for (; inp_strings[i][j] != '\0'; ++j ) {
			if (inp_strings[i][j] == ' ') {
	            if (k == 0) continue;
	            if (inp_strings[i][j + 1] == ' ') continue;
	        }
	        outp_strings[i][k] = inp_strings[i][j];
	        k++;
		}
	}
	return outp_strings;	
}


void print_strings( char** strings, int num_strings ) {
	for ( int i = 0; i < num_strings; ++i ) {
		printf ( "%s\n", strings[i] );
	}
}


int main() {
	size_t buff_size = 16;
	char** strings;
	int num_strings = 1;

	/*printf( "Enter number of strings: " );
	if ( !( scanf( "%d", &num_strings ) ) ) {
		printf ( "[error]\n" );
		return 0;
	}*/

	if ( !(strings = mem_alloc(num_strings, buff_size) ) ) {
		printf( "[error]\n" );
		return 0;
	}
		
	// printf( "Input %d strings:\n", num_strings );

	/*char c = getchar();
	int j;
	for (int i = 0; i < num_strings; ++i ) {
		j = 0;
		// printf( "%d: ", i + 1 );
		while ( (c = getchar() ) != EOF ) {
			strings[i][j] = c;
			if ( j == buff_size - 2 ) {
				buff_size += 16;
				strings[i] = ( char* )realloc( strings[i], buff_size );
				//printf ( "buff_size = %zi\n", buff_size );
			}
			j++;

			if ( c == '\n' ) {
				num_strings += 1;
				strings = ( char** )realloc( strings, num_strings );
				strings[num_strings - 1] = ( char* )malloc( buff_size * sizeof(char) );
				break;
				//printf ("num_strings = %d\n", num_strings);
			}
		}
	}*/

	int i = 0;
	int j = 0;
	char c;
	strings = mem_alloc( num_strings, buff_size );
	size_t *size_strings = ( size_t* )malloc( num_strings * sizeof(size_t));
	while ( (c = getchar() ) != EOF ) {
		if (c != '\n') {
			strings[i][j] = c;
			j++;
			if ( j == buff_size - 2 ) {
				buff_size += 16;
				strings[i] = ( char* )realloc( strings[i], buff_size );
				printf ( "buff_size = %zi\n", buff_size );
			}
		} else {
			strings[i][j] = '\0';
			num_strings++;
			size_strings[i] = buff_size;
			size_strings = realloc(size_strings, num_strings);
			strings = realloc( strings, num_strings );
			strings[num_strings - 1] = ( char* )malloc( buff_size * sizeof( char ) );
			i++;
			j = 0;
			buff_size = 16;
		}
	}



	// print_strings( strings, num_strings );



	char **new_strings = (char**)malloc(num_strings * sizeof(char*));

	for ( int i = 0; i < num_strings; ++i) {
		new_strings[i] = (char*)malloc(size_strings[i] * sizeof(char));
	}

	new_strings = delete_spaces( strings, num_strings );

	print_strings( new_strings, num_strings );

	for ( int i = 0; i < num_strings; ++i ) {
		free( strings[i] );
	}

	free( strings );

	for ( int i = 0; i < num_strings; ++i ) {
		free( new_strings[i] );
	}

	free( new_strings );

	return 0;
}
