#include <stdio.h>
#include <arpa/inet.h> // inet_ntoa()
#include <fcntl.h> // open() , file control options
#include <unistd.h> // close() , used for functions 

int main() {
    int welcome, new_soc, fd, n; // welcome is the welcome socket, new_soc is the new socket, fd is the file descriptor, n is the number of bytes
    char buffer[1024], fname[50]; // buffer for data, fname for filename
    struct sockaddr_in addr; // sockaddr_in is a structure for socket address

    welcome = socket(PF_INET, SOCK_STREAM,
                     0); // socket creates an endpoint for communication and returns a file descriptor

    addr.sin_family = AF_INET; // AF_INET is the address family for IPv4
    addr.sin_port = htons(7891); // htons() converts the port number to network byte order
    addr.sin_addr.s_addr = inet_addr("127.0.0.1"); // inet_addr() converts the IP address to network byte order

    bind(welcome, (struct sockaddr *) &addr,
         sizeof(addr)); // bind() assigns the address specified by addr to the socket referred to by the file descriptor welcome
    printf("\nServer is Online");
    /*  listen for connections from the socket */
    listen(welcome,
           5); // listen() marks the socket referred to by welcome as a passive socket, that is, as a socket that will be used to accept incoming connection requests using accept()
    /*  accept a connection, we get a file descriptor */
    // 5 is the number of queue size
    new_soc = accept(welcome, NULL,
                     NULL); // accept() extracts the first connection request on the queue of pending connections for the listening socket, welcome, creates a new connected socket, and returns a new file descriptor referring to that socket
    // The two NULLS passed in the arguments are to restrict length and to restrict some addresses
    /*  receive the filename */
    recv(new_soc, fname, 50, 0); // recv() returns the number of bytes received
    printf("\nRequesting for file: %s\n",
           fname); // if recv() returns a value greater than 0, then the filename has been received from the client

    /*  open the file and send its contents */
    fd = open(fname, O_RDONLY); // open() returns a file descriptor

    if (fd < 0) // if the file descriptor is less than 0, then the file does not exist
        send(new_soc, "\nFile not found\n", 15, 0); // send() returns the number of bytes sent
    else
        while ((n = read(fd, buffer, sizeof(buffer))) > 0) // read() returns the number of bytes read
            send(new_soc, buffer, n, 0); // send() returns the number of bytes sent
    printf("\nRequest sent\n");
    close(fd); // close() returns 0 on success

    return 0;

}
