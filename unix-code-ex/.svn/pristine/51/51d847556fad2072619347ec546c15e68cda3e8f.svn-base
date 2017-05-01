#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <unistd.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>

#define MAXLINE 80
#define SERV_PORT 8001

int main(int argc, char *argv[])
{
    struct sockaddr_in servaddr;
    struct sockaddr_in my_addr;
    char buf[MAXLINE];
    int sockfd, n, s;
    int nOptval = 1;

    if (argc != 4)
        printf("usage: %s src-ip dest-ip dest-port \n", argv[0]);

    bzero(&my_addr, sizeof(my_addr));
    my_addr.sin_family = AF_INET;
    inet_pton(AF_INET, argv[1], &my_addr.sin_addr);
    my_addr.sin_port = 0; /* auto */

    bzero(&servaddr, sizeof(servaddr));
    servaddr.sin_family = AF_INET;
    inet_pton(AF_INET, argv[2], &servaddr.sin_addr);
    servaddr.sin_port = htons(atoi(argv[3]));

    printf("CONN: %s --> %s:%s \n", argv[1], argv[2], argv[3]);

    for (n = 0; n < 20000; n++)
    {
        sockfd = socket(AF_INET, SOCK_STREAM, 0);
        bind(sockfd, (struct sockaddr *)&my_addr, sizeof(my_addr));
        setsockopt(sockfd, SOL_SOCKET, SO_REUSEADDR, (const void *)&nOptval , sizeof(int));
        connect(sockfd, (struct sockaddr *)&servaddr, sizeof(servaddr));
    }

    // 测试长连接的个数
    sleep(2000);

    //close(sockfd);

    return 0;
 }
