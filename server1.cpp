#include<iostream>
#include<arpa/inet.h>
#include<unistd.h>
#include<cstring>
#include<thread>
#include<mutex>
#include<vector>
#include<algorithm>

std::mutex cout_mtx;
std::mutex client_mtx;
std::vector<int> clients;
void broadcastMessage(const std::string &msg, int sender){
	for(int client:clients){
		if(client!=sender)
		    send(sender,msg.c_str(),msg.length(),0);
	}
}

void handleClient(int clsock){
	char buffer[1024];
	while(true){
	 	int bytes=recv(clsock,buffer,sizeof(buffer),0);
		if(bytes<0)
		    std::cout<<"client "<<std::to_string(clsock)<<" got disconnected"<<std::endl;
		buffer[bytes]='\0';
		
		std::string msg;
		msg="Client "+std::to_string(clsock)+" saying "+buffer;
		{
			std::lock_guard<std::mutex> lock(cout_mtx);
			std::cout<<msg<<std::endl;
		}
		broadcastMessage(msg,clsock);
	}
	{
		std::lock_guard<std::mutex> lock(client_mtx);
		clients.erase(std::remove(clients.begin(),clients.end(),clsock),clients.end());
	}
	close(clsock);	
}
int main() {
	int server_fd,clsock;
	struct sockaddr_in serv_addr,client_addr;
	serv_addr.sin_family = AF_INET;
	serv_addr.sin_port = htons(8080);
	serv_addr.sin_addr.s_addr = INADDR_ANY;

	//create socket
	server_fd = socket(AF_INET, SOCK_STREAM,0);
	if(server_fd == -1){
		perror("socket creation failed");
		return 1;
	}
	
	//bind socket with port
	if(bind(server_fd,(struct sockaddr*)&serv_addr,sizeof(serv_addr))<0) {
		perror("Bind failed");
		return 1;
	}


	//listen
	if(listen(server_fd,3) < 0){
		perror("listen failed");
		return 1;
	}
	
        while(true){
	//accept connections
	
		clsock=accept(server_fd,(struct sockaddr*)&client_addr, (socklen_t*)&client_addr);
		if(clsock < 0) {
			perror("Client Socket creation failed");
			return 1;
		}
		clients.push_back(clsock);
		std::thread(handleClient,clsock).detach();	
	}
	close(clsock);
	close(server_fd);
}
