#include <stdio.h>
#include <arpa/inet.h> // inet_ntoa() // inet = internet networking

int main()
{
    int soc, n;
    char buffer[1024], fname[50]; // buffer for data, fname for filename
    struct sockaddr_in addr; // sockaddr_in is a structure for socket address

    /*  socket creates an endpoint for communication and returns a file descriptor */
    soc = socket(PF_INET, SOCK_STREAM, 0); // AF = Address Family , PF = Protocol Family 

    /*
     * sockaddr_in is used for ip manipulation
     * we define the port and IP for the connection.
     */
    addr.sin_family = AF_INET; // AF_INET is the address family for IPv4
    addr.sin_port = htons(7891); // htons() converts the port number to network byte order
    addr.sin_addr.s_addr = inet_addr("127.0.0.1"); // inet_addr() converts the IP address to network byte order

    /*  keep trying to esatablish connection with server */
    while(connect(soc, (struct sockaddr *) &addr, sizeof(addr))) ; // connect() returns 0 on success
    printf("\nClient is connected to Server"); // if connect() returns 0, then the client is connected to the server
    printf("\nEnter file name: "); // ask for filename
    scanf("%s", fname); // get filename from user
    /*  send the filename to the server */
    send(soc, fname, sizeof(fname), 0); // send() returns the number of bytes sent

    printf("\nRecieved response\n"); // if send() returns a value greater than 0, then the filename has been sent to the server
    /*  keep printing any data received from the server */
    while ((n = recv(soc, buffer, sizeof(buffer), 0)) > 0) // recv() returns the number of bytes received
        printf("%s", buffer);

    return 0;
}
