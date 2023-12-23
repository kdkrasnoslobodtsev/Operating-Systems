#include <sys/types.h>
#include <sys/socket.h>
#include <stdio.h>
#include <stdlib.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <string.h>

int main(int argc, char** argv) {
  char buffer[4096];
    int server = socket(AF_INET, SOCK_DGRAM, 0);
    if (server == -1) {
        perror("Socket failed\n");
        exit(-1);
    }

    struct sockaddr_in adr = {0}, client_addr, dent_addr, surj_addr, ther_addr, log_addr;
    socklen_t addr_size;
    adr.sin_family = AF_INET;
    adr.sin_port = htons(atoi(argv[1]));
    adr.sin_addr.s_addr = inet_addr(argv[2]);
    int bindfd = bind(server, (struct sockaddr *)&adr, sizeof adr);
    if (bindfd == -1) {
        perror("Bind failed\n");
        exit(-1);
    }

    bzero(buffer, 4096);
    addr_size = sizeof(client_addr);
    int len = recvfrom(server, buffer, 4096, 0, (struct sockaddr*)&client_addr, &addr_size);
    
    bzero(buffer, 4096);
    addr_size = sizeof(dent_addr);
    recvfrom(server, buffer, 4096, 0, (struct sockaddr*)&dent_addr, &addr_size);
    
    bzero(buffer, 4096);
    addr_size = sizeof(surj_addr);
    recvfrom(server, buffer, 4096, 0, (struct sockaddr*)&surj_addr, &addr_size);
    
    bzero(buffer, 4096);
    addr_size = sizeof(ther_addr);
    recvfrom(server, buffer, 4096, 0, (struct sockaddr*)&ther_addr, &addr_size);
    
    bzero(buffer, 4096);
    addr_size = sizeof(log_addr);
    recvfrom(server, buffer, 4096, 0, (struct sockaddr*)&log_addr, &addr_size);

    for (int i = 0; i < 10; ++i) {
        bzero(buffer, 4096);
        addr_size = sizeof(client_addr);
        recvfrom(server, buffer, 4096, 0, (struct sockaddr*)&client_addr, &addr_size);
        if (buffer[0] == 't' && buffer[1] == 'o' && buffer[2] == 'o' && buffer[3] == 't' && buffer[4] == 'h') {
            sendto(server, buffer, 4096, 0, (struct sockaddr*)&dent_addr, sizeof dent_addr);
            
            bzero(buffer, 4096);
            addr_size = sizeof(dent_addr);
            recvfrom(server, buffer, 4096, 0, (struct sockaddr*)&dent_addr, &addr_size);
            
            bzero(buffer, 4096);
            strcpy(buffer, "D");
            sendto(server, buffer, 4096, 0, (struct sockaddr*)&log_addr, sizeof log_addr);
            
            bzero(buffer, 4096);
            addr_size = sizeof(log_addr);
            recvfrom(server, buffer, 4096, 0, (struct sockaddr*)&log_addr, &addr_size);
        } else if (buffer[0] == 'i' && buffer[1] == 'n' && buffer[2] == 'j' && buffer[3] == 'u' && buffer[4] == 'r' && buffer[5] == 'y') {
            sendto(server, buffer, 4096, 0, (struct sockaddr*)&surj_addr, sizeof surj_addr);
         
            bzero(buffer, 4096);
            addr_size = sizeof(surj_addr);
            recvfrom(server, buffer, 4096, 0, (struct sockaddr*)&surj_addr, &addr_size);
            
            bzero(buffer, 4096);
            strcpy(buffer, "S");
            sendto(server, buffer, 4096, 0, (struct sockaddr*)&log_addr, sizeof log_addr);
            
            bzero(buffer, 4096);
            addr_size = sizeof(log_addr);
            recvfrom(server, buffer, 4096, 0, (struct sockaddr*)&log_addr, &addr_size);
        } else {
            sendto(server, buffer, 4096, 0, (struct sockaddr*)&ther_addr, sizeof ther_addr);
            
            bzero(buffer, 4096);
            addr_size = sizeof(ther_addr);
            recvfrom(server, buffer, 4096, 0, (struct sockaddr*)&ther_addr, &addr_size);
            
            bzero(buffer, 4096);
            strcpy(buffer, "T");
            sendto(server, buffer, 4096, 0, (struct sockaddr*)&log_addr, sizeof log_addr);
            
            bzero(buffer, 4096);
            addr_size = sizeof(log_addr);
            recvfrom(server, buffer, 4096, 0, (struct sockaddr*)&log_addr, &addr_size);
        }
        bzero(buffer, 4096);
        strcpy(buffer, "E");
        sendto(server, buffer, 4096, 0, (struct sockaddr*)&log_addr, sizeof log_addr);
        
        bzero(buffer, 4096);
        addr_size = sizeof(log_addr);
        recvfrom(server, buffer, 4096, 0, (struct sockaddr*)&log_addr, &addr_size);
        
        bzero(buffer, 4096);
        strcpy(buffer, "done");
        sendto(server, buffer, 4096, 0, (struct sockaddr*)&client_addr, sizeof client_addr);
    }
    return 0;
}
