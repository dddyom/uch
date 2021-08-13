#include <iostream>
#include <sys/types.h>
#include <sys/socket.h>
#include <stdio.h>
#include <stdlib.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <fstream>
#include "../erproc.h"


using namespace std;

int main() {

    int server = Socket(AF_INET, SOCK_STREAM, 0);
    struct sockaddr_in adr = { };
    adr.sin_family = AF_INET;
    adr.sin_port = htons(34543);
    Bind(server, (struct sockaddr *) &adr, sizeof adr);
    Listen(server, 5);
    
    socklen_t adrlen = sizeof adr;
    int client_fd = Accept(server, (struct sockaddr *) &adr, &adrlen);
    ssize_t nread;
    
    
    int flag;
    FILE *fp;
    while(true){
    char buf[SIZE];
    char filename[SIZE];
    const char *getfile = "getfile.txt";
    nread = read(client_fd, buf, SIZE);
    cout << "\n";

    Nread_check(nread);
    
    flag = Check_buffer(buf);
        
    //cout << flag << "->" << buf << endl;
        
        if (flag == 1){ //send
        
            read(client_fd, filename, SIZE);
            
            fp = fopen(filename, "a");
            Write_file(fp, client_fd);
            fclose(fp);
            continue;
        }
            
        else if (flag == 2){ //get
            fp = fopen(getfile, "r");
            if (fp == NULL) {
                perror("[-]Error in reading file.");
                exit(1);
            }
            else{
                Send_file(fp, client_fd);
                fclose(fp);
                continue;
            }
        }
        
        else if (flag == 3){ //exit
            cout << "\nclient disconnected" << endl;
           break;
        }
        else{ //echo
        
            write(STDOUT_FILENO, buf, nread);
            write(client_fd, buf, nread);
            continue; 
        }
        
        
    }
    close(client_fd);
    close(server);
    return 0;
}
