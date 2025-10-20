#include<iostream>
#include<arpa/inet.h>
#include<cstring>
#include<unistd.h>
int main(){

     int server_fd, new_socket;
     struct sockaddr_in serv_addr, client_addr;
     serv_addr.sin_family=AF_INET;
     serv_addr.sin_port=htons(8080);
     serv_addr.sin_addr.s_addr = INADDR_ANY;

    //create socket
    server_fd = socket(AF_INET,SOCK_STREAM,0);

    //bind socket to port
    bind(server_fd, (struct sockaddr*)&serv_addr, sizeof(serv_addr));

    //listen on socket
    listen(server_fd,3);

    //accept the client connection
    new_socket= accept(server_fd, (struct sockaddr*)&client_addr, (socklen_t*) &client_addr);
    char buffer[1024];
    while(true) {
        //read message
    	//read(new_socket, buffer, 1024);

	int bytes=recv(new_socket, buffer, sizeof(buffer),0);
	//if(bytes<=0) break;
	buffer[bytes]='\0';

	std::string msg(buffer);

    	std::cout<<"Message from Client: "<<msg<<std::endl;

       //send message
       //const char* msg="message Received";
       //send(new_socket, msg, strlen(msg),0);
    }
    //closing connection
    close(new_socket);
    close(server_fd);

    return 0;
}
