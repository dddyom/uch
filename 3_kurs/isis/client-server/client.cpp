#include <iostream>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <fstream>
#include "../erproc.h"

using namespace std;
int main() {
    FILE *fp;
    const char *sendfile = "sendfile.txt";
    const char *getfile = "getfile.txt";
    string helpMessage = "For send file to server, enter 'send'\n"
                          "For get file from server, enter 'get'\n"
                          "For disconnect, enter 'exit'\n"
                          "For help, enter 'help'\n";
    int fd = Socket(AF_INET, SOCK_STREAM, 0);
    struct sockaddr_in adr = { };
    adr.sin_family = AF_INET;
    adr.sin_port = htons(34543);
    Inet_pton(AF_INET, "127.0.0.1", &adr.sin_addr);
    Connect(fd, (struct sockaddr *) &adr, sizeof adr);
    

        cout << " > ";
        getline(cin, fdInput);
        
        if (fdInput == "help"){
            cout << helpMessage;
            continue;
        }
        
        if (fdInput == "send"){
            write(fd, "send\n", 6);
            cout << "Enter file name\n>";
            getline(cin, fdInput);
            if (fdInput == sendfile){
                write(fd, "sendfile.txt\n", 14);
                fp = fopen(sendfile, "r");
                if (fp == NULL) {
                    perror("[-]Error in reading file.");
                    exit(1);
                }
                else{
                    Send_file(fp, fd);
                    fclose(fp);
                    continue;
                }
            }
            else{
                cout << "File does not exist" << endl;
                continue;
            }
        }
        
        if (fdInput == "get"){
            write(fd, "get\n", 5);
            cout << "Enter file name\n>";
            getline(cin, fdInput);
            if (fdInput == getfile){
                //write(fd, "getfile.txt\n", 13);
                fp = fopen("getfile.txt", "a");
                Write_file(fp, fd);
                fclose(fp);   
                
            }else{
                cout << "File does not exist" << endl;
                continue;
            } 
            continue;    
        }
        
        if (fdInput == "exit"){
            write(fd, "exit\n", 6);
            break;
        }
        else{//echo
            int sendRes = write(fd, fdInput.c_str(), fdInput.size() + 1);
        
            if (sendRes == -1){
                cout << "Could not send to server!\r\n";
                continue;
            }
            
            char buf[SIZE];
            ssize_t nread;
            nread = read(fd, buf, SIZE);
    
            if (nread == -1){
                perror("read failed");
                exit(EXIT_FAILURE);
            }
            if (nread == 0){
                cout << "EOF occured\n";
                continue;
            }
            cout << "\necho:"<< buf << endl;
            continue;
        }
    }while(true);
    
    close(fd);
    return 0;
}
