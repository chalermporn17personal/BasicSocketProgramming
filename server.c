//workflow = socket --> bind --> listen --> accept
// bind = bind ip and ports for socket -- where our socket is going to listen for connections
// accept = accept the connection that will return another socket that will perform read and write operation on
#include<stdio.h>
#include<stdlib.h>

#include<sys/socket.h>
#include<sys/types.h>

#include<netinet/in.h>
#include<unistd.h>

#include<string.h>
int main(int argc, char *argv[])
{
	system("echo --- Generating data ---");
	system("bash generator.bash");
	printf("\n --- Checksum --- \n");
	system("sha256sum Data/*.*");
	printf("server start\n");
	int size = 1500;
	char server_message[128] = "This data is from this server";
	char buffer[size];
	char filename[256];
	char status[2];
	// create socket
	int server_socket;
	server_socket = socket(AF_INET,SOCK_STREAM , 0);
	
	// define address structure
	struct sockaddr_in server_address;
	server_address.sin_family = AF_INET;
	server_address.sin_port = htons(atoi(argv[1]));
	server_address.sin_addr.s_addr = INADDR_ANY;

	//additional code

	
	// bind the socket to specified IP and port
	bind(server_socket, (struct sockaddr*) &server_address , sizeof(server_address));
	// ( socket , address structure , size of server address )
	
	//listen
	
	// ( socket , How many connection can be waiting
	// if accept we will get socket that we can write to
	//int client_socket;
	//client_socket = accept(server_socket , NULL , NULL);
	// ( socket that accept connection , structure that contain the address of the client connection , size of parameter 2)
	// Use to figure out where client is connecting from
	// This will null because know where it's from
	int n,nread;
	int client_socket;
	char dummy[256];
	while(1) {
	//read file path
	listen(server_socket , 5 );
	client_socket = accept(server_socket , NULL , NULL);
	n = read(client_socket , filename , sizeof(filename));
	printf("Request incoming\n");
	printf("receive File path : '%s' \n",filename);
	if(filename == "Close") break;
	FILE *fptr;
	    if (fptr = fopen(filename,"rb"))
	{
		write(client_socket , "1" , 2);
		// Found file
		// read file
		printf("Reading file \n");
		
		//read(client_socket , dummy , sizeof(dummy));
		read(client_socket , dummy , sizeof(dummy));
		while(0 < (nread = fread(buffer, 1, sizeof(buffer), fptr)))
		{
			//fwrite(buffer, 1, nread, fw);
			write(client_socket , buffer , nread);
		}
		write(client_socket , "--ED" , 5);
		printf("Data sended\n\n");
	}
	else
	{
		// File not found
		write(client_socket , "0" , 2);
	}
	//send
	/*
	int send_return;
	send_return = write(client_socket , server_message , strlen(server_message) + 1);
	printf("send return : %d \n",send_return);
	*/
	//(socket ,data ,size of message , flag)
	//close socket
	}
	close(server_socket);
	return 0;
}
