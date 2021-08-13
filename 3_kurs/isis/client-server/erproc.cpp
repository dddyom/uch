#include <iostream>
#include "erproc.h"
#include <sys/types.h>
#include <sys/socket.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <strings.h>

using namespace std;

int Socket(int domain, int type, int protocol) {
    int res = socket(domain, type, protocol);
    if (res == -1) {
        perror("socket failed");
        exit(EXIT_FAILURE);
    }
    return res;
}

void Bind(int sockfd, const struct sockaddr *addr, socklen_t addrlen) {
    int res = bind(sockfd, addr, addrlen);
    if (res == -1) {
        perror("bind failed");
        exit(EXIT_FAILURE);
    }
}

void Listen(int sockfd, int backlog) {
    int res = listen(sockfd, backlog);
    if (res == -1) {
        perror("listen failed");
        exit(EXIT_FAILURE);
    }
}

int Accept(int sockfd, struct sockaddr *addr, socklen_t *addrlen) {
    int res = accept(sockfd, addr, addrlen);
    if (res == -1) {
        perror("accept failed");
        exit(EXIT_FAILURE);
    }
    return res;
}

void Connect(int sockfd, const struct sockaddr *addr, socklen_t addrlen) {
    int res = connect(sockfd, addr, addrlen);
    if (res == -1) {
        perror("connect failed");
        exit(EXIT_FAILURE);
    }
}

void Nread_check(int nread){
        if (nread == -1) {
            perror("read failed");
            exit(EXIT_FAILURE);
    }
    if (nread == 0) {
        cout << ("END OF FILE occured\n");
    }
}

void Inet_pton(int af, const char *src, void *dst) {
    int res = inet_pton(af, src, dst);
    if (res == 0) {
        cout <<"inet_pton failed: src does not contain a character"
            " string representing a valid network address in the specified"
            " address family" << endl;
        exit(EXIT_FAILURE);
    }
    if (res == -1) {
        perror("inet_pton failed");
        exit(EXIT_FAILURE);
    }
}

void Send_file(FILE *f, int sockfd){
    char buffer[SIZE] = { };
    int words = 0;
    char c;
     //f=fopen("sendfile.txt","r");
    while((c=getc(f))!=EOF)
	{	
		fscanf(f , "%s" , buffer);
		if(isspace(c)||c=='\t')
		words++;	
	}
       
      
	write(sockfd, &words, sizeof(int));
     	rewind(f);

    char ch ;
       while(ch != EOF)
      {
		
		fscanf(f , "%s" , buffer);
		write(sockfd, buffer, SIZE);
		ch = fgetc(f);
      }
	cout << "The file was sent successfully" << endl;
}


void Write_file(FILE *fp, int sockfd){

  char buffer[SIZE];
    int ch = 0;            
    int words;
	
	read(sockfd, &words, sizeof(int));

    while(ch != words)
       	   {
        	 read(sockfd , buffer , SIZE); 
	   	     fprintf(fp , " %s" , buffer);   
		      //cout << buffer << " ---->" << ch << endl;
		 ch++;
	   }
    cout << "The file was received successfully\n";
}

int Check_buffer(char buf[]){
    if (strncmp(buf, "send**", 4) == 0){
        return 1;
    }
    else if (strncmp(buf, "get**", 3) == 0){
        return 2;
    }
    else if (strncmp(buf, "exit**", 4) == 0){
        return 3;
    }
    else{
    return 0;
    }
}
