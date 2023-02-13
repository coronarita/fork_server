#include <stdio.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>

#define SERV_UDP_PORT 1919
#define SERV_TCP_PORT 1919
// SERVER : VIRTUALBOX UBUNTU -->WSL
// #define SERV_HOST_ADDR "192.168.45.59"
// SERVER : WSL - UBUNTU 20.04 
#define SERV_HOST_ADDR "192.168.45.95"

char *pname;