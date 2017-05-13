#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>

int
main() {
    int sock0;
    struct sockaddr_in addr;
    struct sockaddr_in client;
    socklen_t len;
    int sock;
    int n;
    char buf[65536];
    int i;
    /* ソケットの作成 */
    sock0 = socket(AF_INET, SOCK_STREAM, 0);
    /* ソケットの設定 */
    addr.sin_family = AF_INET;
    addr.sin_port = htons(12345);
    addr.sin_addr.s_addr = INADDR_ANY;
    bind(sock0, (struct sockaddr*)&addr, sizeof(addr));
    /* TCPクライアントからの接続要求を待てる状態にする */
    listen(sock0, 5);
    /* TCPクライアントからの接続要求を受け付ける */
    len = sizeof(client);
    sock = accept(sock0, (struct sockaddr*)&client, &len);
    /* TCPコネクションを確立したことを表示 */
    printf("after accept\n");

    for (i = 0; i < 10; i++) {
        sleep(2);
        n = read(sock, buf, sizeof(buf));
        printf("drain data [%d] bytes\n", n);
    }

    printf("close socket and finish\n");
    /* TCPセッションの終了 */
    close(sock);
    /* listen するsocketの終了 */
    close(sock0);
    return 0;
}
