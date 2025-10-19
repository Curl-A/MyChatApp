#include<iostream>
#include<arpa/inet.h>
#include<unistd.h>
#include<cstring>

int main() {
	int client_fd;

	struct sockaddr_in serv_addr;
	serv_addr.sin_family=AF_INET;
	serv_addr.sin_port=htons(8080);
	inet_pton(AF_INET,"127.0.0.1",&serv_addr.sin_addr);

	char buffer[1024]={0};

	//create socket
	client_fd = socket(AF_INET,SOCK_STREAM,0);

	//connet to server
	connect(client_fd,(struct sockaddr*)&serv_addr,sizeof(serv_addr));


	//send message
	const char* msg="Hi from client";
	send(client_fd,msg,strlen(msg),0);

	std::cout<<"Message Sent"<<std::endl;
	//receive ack from server
	read(client_fd,buffer,1024);

	std::cout<<buffer<<std::endl;

	close(client_fd);

	return 0;
}

