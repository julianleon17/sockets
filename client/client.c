#include <stdio.h>
#include <stdlib.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <string.h>


int main( int argc, const char *argv[] ) {

  if ( argc > 2 ) {

    const char *ip;
    int client_socket, num_bytes, port;
    char buff[100];

    port = atoi( argv[2] );
    ip = argv[1];

    struct sockaddr_in server;

    if ( inet_pton( AF_INET, argv[1], &server.sin_addr ) <= 0 ) {
      printf( "The ip %s is not valid\n", ip );

      return -1;
    }

    printf( "Opening Socket...\n" );

    if ( ( client_socket = socket( AF_INET, SOCK_STREAM, 0 ) ) == -1 ) {
      printf( "Could not open the socket\n" );

      return -2;
    }

    server.sin_family = AF_INET;
    server.sin_port = htons( port );
    bzero( &( server.sin_zero ), 8 );

    printf( "Connecting to %s : %s \n", argv[1], argv[2] );


    if ( ( connect( client_socket, (struct sockaddr *) &server, sizeof( struct sockaddr ) ) ) == -1 ) {
      printf( "Could not connect to the server\n" );

      return -3;
    }

    printf( "Receiving...\n" );

    if ( ( num_bytes = recv( client_socket, buff, 100, 0 ) ) == -1 ) {
      printf( "Reading error\n" );

      return -4;
    }

    buff[num_bytes] = '\0';

    printf( "The server sent the message : %s \n", buff );

    shutdown( client_socket, 2 );

  } else {

    printf( "Please indicate ip of server and port\n" );
    return -5;
  }
}

