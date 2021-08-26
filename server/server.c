#include <stdio.h>
#include <stdlib.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <string.h>


int main( int argc, const char *argv[] ) {

  if ( argc > 1 ) {

    int server_socket, client_socket, client_lenght, port;

    port = atoi( argv[1] );

    struct sockaddr_in server;
    struct sockaddr_in client;

    server.sin_family = AF_INET;
    server.sin_port = htons( port );
    server.sin_addr.s_addr = INADDR_ANY;
    bzero( &( server.sin_zero ), 8 );

    if ( ( server_socket = socket( AF_INET, SOCK_STREAM, 0 ) ) == -1 ) {
      printf( "Could not open the socket\n" );

      return -1;
    }

    if ( bind( server_socket, (struct sockaddr *) &server, sizeof( struct sockaddr ) ) == -1 ) {
      printf( "Could not open the por %s\n", argv[1] );

      return -2;
    }

    if ( listen( server_socket, 5 ) == -1 ) {
      printf( "Could not get into listening mode\n" );

      return -3;
    }

    client_lenght = sizeof( struct sockaddr_in );

    printf( "Waiting for customers...\n" );

    if ( ( client_socket = accept( server_socket, (struct sockaddr*) &client, &client_lenght ) ) == -1 ) {
      printf( "Could not accept a connection\n" );

      return -4;
    }

    char str[INET_ADDRSTRLEN];
    inet_ntop( AF_INET, &( client.sin_addr ), str, INET_ADDRSTRLEN );

    printf( "A client connected from %s : %d. I greeted him\n", str, client.sin_port );
    send( client_socket, "Welcome to my server", 26, 0 );

    printf( "The greating was sent!\n" );
    shutdown( client_socket, 2 );
    shutdown( server_socket, 2 );

  } else {

    printf( "Please indicate the port\n" );
    return -5;
  }
}

