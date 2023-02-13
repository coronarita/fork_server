#include "inet.h"
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

int main (int argc, char* argv[]){
    // identifier
    int sockfd, newsockfd, clilen;

    struct sockaddr_in cli_addr;
    struct sockaddr_in serv_addr;

    int pid;

    char buff[30];
    pname = argv[0];
    
    int option;

    if ((sockfd = socket(AF_INET, SOCK_STREAM, 0)) < 0) {
        // ERROR
        puts("Server: Error");
        exit(1);
    }
    option = 1;
    setsockopt(sockfd, SOL_SOCKET, SO_REUSEADDR, &option, sizeof(option));

    // Server Address
    // bzero(공간, 사이즈) : 첫번째 지정된 공간을 두번째 인자의 사이즈 만큼 0으로 채우면 초기화
    // memset(공간, 값, 사이즈) : 지정된 메모리 공간을 두번째 값으로 세번째 사이즈만큼 채우기
    bzero((char *) &serv_addr, sizeof(serv_addr));
    serv_addr.sin_family = AF_INET;
    serv_addr.sin_addr.s_addr = htonl(INADDR_ANY);
    serv_addr.sin_port = htons(SERV_TCP_PORT);


    if (bind(sockfd, (struct sockaddr *)&serv_addr, sizeof(serv_addr))<0) {
        puts("Server: bind error!");
        exit(1);
    }

    listen(sockfd, 5);
    clilen = sizeof(cli_addr);

    for(;;){
        newsockfd = accept(sockfd, (struct sockaddr *)&cli_addr, &clilen);
        if((pid = fork()) == 0){
            // CHILD
            if (newsockfd <0){
                puts("Server: accept error!");
                exit(1);
            }
            close(sockfd);
            
            if(read(newsockfd, buff, 20) <= 0){
                puts("Server: read error!");
                exit(1);
            }
            printf("Server: Received String = %s\n", buff);
            close(newsockfd);
            exit(0);  // end of CHILD
        }
        close(newsockfd);
        if(pid == -1){
            // ERROR
            perror("fork error");
        }
    } // loop end
    close(sockfd);

    return 0;
}