#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define BUFFER_SIZE 1024

struct DATA
{
  int a;
  double d;
  char text[128];
};
typedef struct DATA Data;

void fill_buffer( void *buffer, int size )
{
  char *internal = (char *)buffer;
  int max = size / sizeof( char );
  
  for ( int i=0 ; i<max ; i+=2 )
  {
    strcpy( internal, "hi" );
    internal += 2;
  }
}

void process_buffer( void *buffer, int size )
{
  Data *internal = (Data *)buffer;
  int max = size / sizeof(Data);
  
  for ( int i=0 ; i<max ; i++ )
    printf( "%d\n%6.2f\n%s\n\n", internal[i].a, internal[i].d, internal[i].text );
}

int main( int argc, char *argv[] )
{
  char *buffer;
  
  buffer = malloc( BUFFER_SIZE );
  
  fill_buffer( buffer, BUFFER_SIZE );
  process_buffer( buffer, BUFFER_SIZE );
  
  free( buffer );
  
  return EXIT_SUCCESS;
}
