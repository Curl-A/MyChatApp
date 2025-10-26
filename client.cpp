#include<iostream>
#include<arpa/inet.h>
#include<unistd.h>
#include<cstring>
#include "Logger.h"

int main() {
	Logger logger("client.log");
	int client_fd;

	struct sockaddr_in serv_addr;
	serv_addr.sin_family=AF_INET;
	serv_addr.sin_port=htons(8080);
	inet_pton(AF_INET,"127.0.0.1",&serv_addr.sin_addr);

	char buffer[1024]={0};

	//create socket
	client_fd = socket(AF_INET,SOCK_STREAM,0);
        
	//connet to server
	if(connect(client_fd,(struct sockaddr*)&serv_addr,sizeof(serv_addr))>0)
	        logger.log("INFO","Connection to server successful");
	else
		logger.log("DEBUG","Connection to server failed");

	std::string msg;
	//send message
	while(true) {
		std::cout<<" >";
		std::getline(std::cin,msg);
	        send(client_fd,msg.c_str(),strlen(msg.c_str()),0);
                
		//std::cout<<"Message Sent"<<std::endl;
		//receive ack from server
		read(client_fd,buffer,1024);
                
		std::string msg2(buffer);
		std::cout<<msg2<<std::endl;
	}
	close(client_fd);

	return 0;
}

