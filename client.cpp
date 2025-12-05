#include <sys/socket.h>
#include <arpa/inet.h>
#include <netinet/in.h>
#include <cstdlib>
#include <stdio.h>
#include <unistd.h>

using namespace std;

int main(int argc, char **argv) {
    // 1 TWORZENIE SOCKETU
    int socktcp = socket(AF_INET, SOCK_STREAM, 0);
    int port = atoi(argv[2]);
    const char* ip = argv[1];

    // 2 TWORZENIE SOCKADDR
    sockaddr_in sockaddr_tcp {};
    sockaddr_tcp.sin_family = AF_INET;
    sockaddr_tcp.sin_port = htons(port);

    // 3 KONWERTOWANIE IP
    inet_pton(AF_INET, ip, &sockaddr_tcp.sin_addr);

    // 4 REUSABLE
    const int one = 1;
    setsockopt(socktcp, SOL_SOCKET, SO_REUSEADDR, &one, sizeof(one));

    // 5 CONNECT
    int servfd = connect(socktcp, (sockaddr*)&sockaddr_tcp, sizeof(sockaddr_tcp));

    // 6 RECIEVE
    char buf[10];
    int bytes_read = recv(socktcp, buf, sizeof(buf), 0);
    printf("%.*s",bytes_read, buf);

    // 7 CLOSE
    close(socktcp);

    // 1 SOCKET
    int sockudp = socket(AF_INET, SOCK_DGRAM, 0);

    // 2 SOCKADDR
    sockaddr_in sockaddr_udp {};
    sockaddr_udp.sin_family = AF_INET;
    sockaddr_udp.sin_port = htons(port);
    
    // 3 IP
    inet_pton(AF_INET, ip, &sockaddr_udp.sin_addr);

    // 4 REUSABLE
    setsockopt(sockudp, SOL_SOCKET, SO_REUSEADDR, &one, sizeof(one));

    // 5 SEND
    sendto(sockudp, "Goodbye\n", 8, 0, (sockaddr*)&sockaddr_udp, sizeof(sockaddr_udp));

    // 6 CLOSE
    close(sockudp);

    return 0;
}