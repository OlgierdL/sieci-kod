#include <sys/socket.h>
#include <arpa/inet.h>
#include <netinet/in.h>
#include <cstdlib>
#include <stdio.h>
#include <unistd.h>

using namespace std;

int main(int argc, char **argv) {
    // SOCKET
    int socktcp = socket(AF_INET, SOCK_STREAM, 0);
    int port = atoi(argv[1]);

    // 2 SOCKADDR
    sockaddr_in sockaddr_tcp {};
    sockaddr_tcp.sin_family = AF_INET;
    sockaddr_tcp.sin_addr.s_addr = INADDR_ANY;
    sockaddr_tcp.sin_port = htons(port);

    // 3 REUSABLE
    const int one = 1;
    setsockopt(socktcp, SOL_SOCKET, SO_REUSEADDR, &one, sizeof(one));

    // 4 BIND I LISTEN
    bind(socktcp, (sockaddr*)&sockaddr_tcp, sizeof(sockaddr_tcp));
    listen(socktcp, SOMAXCONN);

    // 5 ACCEPT
    sockaddr_in cliaddr{};
    socklen_t l = sizeof(cliaddr);
    int clifd = accept(socktcp, (sockaddr*)&cliaddr, &l);

    // 6 SEND
    send(clifd, "Hello\n", 7, 0);

    // 7 CLOSE
    close(socktcp);


    // 1 SOCKET
    int sockudp = socket(AF_INET, SOCK_DGRAM, 0);

    // 2 SOCKADDR
    sockaddr_in sockaddr_udp{};
    sockaddr_udp.sin_family = AF_INET;
    sockaddr_udp.sin_addr.s_addr = INADDR_ANY;
    sockaddr_udp.sin_port = htons(port);

    // 3 BIND
    bind(sockudp, (sockaddr*)&sockaddr_udp, sizeof(sockaddr_udp));

    // 4 REUSABLE
    setsockopt(sockudp, SOL_SOCKET, SO_REUSEADDR, &one, sizeof(one));

    // 5 RECIEVE
    sockaddr_in cliaddr2{};
    socklen_t l2 = sizeof(cliaddr2);

    char buf[10];
    int b = recvfrom(sockudp, buf, sizeof(buf), 0, (sockaddr*)&cliaddr2, &l2);
    printf("%.*s", b, buf);

    // 6 CLOSE
    close(sockudp);

    return 0;
}