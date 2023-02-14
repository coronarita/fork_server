#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netdb.h>
#include <stdio.h>

// error routine 
void error(char *msg){
    perror(msg);
    exit(0);
}

int main(int argc, char *argv[]){
    int sock, length, fromlen, n;

    struct sockaddr_in server;
    struct sockaddr_in from;

    char buf[1024];

    if (argc < 2){
        fprintf(stderr, "ERROR no port provided\n");
        exit(0);
    }

    sock = socket(AF_INET, SOCK_DGRAM, 0);
    if (sock<0) error("opening sockcet error");

    length = sizeof(server);

    bzero(&server, length);
    server.sin_family = AF_INET;
    server.sin_addr.s_addr = INADDR_ANY; // for any UDP Clients
    server.sin_port = htons(atoi(argv[1]));

    if (bind(sock, (struct sockaddr *)&server, length) < 0) {
        error("Binding Error");

    }
    fromlen = sizeof(struct sockaddr_in);

    while (1){
        n = recvfrom(
            sock,
            buf, 1024,
            0,
            (struct sockaddr *)&from,
            &fromlen
        ); // fd, buf, size of buf, flag, add of serv, size of addof serv
    // no handshake, comparing with TCP
        
        if (n<0) error("Receive Error");
        write(1, "Received ad datagram: ", 21);
        write(1, buf, n); // consol check

        n = sendto(
            sock, 
            "Server: Helloworld Datagram\n", 20, 
            0,
            (struct sockaddr *)&from,
        fromlen
        );
        
        if (n<0) error("Send Error");
    

    }
}   