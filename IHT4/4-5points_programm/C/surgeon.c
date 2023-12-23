#include <sys/types.h>
#include <sys/socket.h>
#include <stdio.h>
#include <stdlib.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <string.h>

int main(int argc, char** argv) {
    int fd = socket(AF_INET, SOCK_DGRAM, 0);
    if (fd == -1) {
        perror("Socket failed\n");
        exit(-1);
    }
    char buffer[4096];
    struct sockaddr_in adr = {0};
    socklen_t addr_size;
    adr.sin_family = AF_INET;
    adr.sin_port = htons(atoi(argv[1]));
    adr.sin_addr.s_addr = inet_addr(argv[2]);
    
    bzero(buffer, 4096);
    strcpy(buffer, "Hello World!");
    sendto(fd, buffer, 4096, 0, (struct sockaddr*)&adr, sizeof adr);
    
    bzero(buffer, 4096);
    addr_size = sizeof(adr);
    recvfrom(fd, buffer, 4096, 0, (struct sockaddr*)&adr, &addr_size);
    
    while (buffer != "done") {
        printf("Surgeon finished with patient\n");
        sendto(fd, buffer, 4096, 0, (struct sockaddr*)&adr, sizeof adr);

        bzero(buffer, 4096);
        addr_size = sizeof(adr);
        recvfrom(fd, buffer, 4096, 0, (struct sockaddr*)&adr, &addr_size);
    }
    close(fd);
    return 0;
}
