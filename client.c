//Client work flow = socket --> connect --> receive
#include <stdio.h>
#include <stdlib.h>

#include <sys/types.h>
#include <sys/socket.h>

#include <netinet/in.h>
#include <unistd.h>
#include <string.h>
int main(int argc, char *argv[])
{
	// 1 address 2 port 3 filename 4 destination
	// create a socket
	int size=1500;
	int network_socket;
	network_socket = socket(AF_INET , SOCK_STREAM,0); //(domain of socket , socket type ,  something about protocol)
	char filename[255] = "/Home/Test1/test2";
	char buffer[size];
	//specity an address for the socket that want connect to
	struct sockaddr_in server_address;
	server_address.sin_family = AF_INET; // specify address memory
	server_address.sin_port = htons(atoi(argv[2])); // specify port , need to convert port to (right network byte order)
	server_address.sin_addr.s_addr = inet_addr(argv[1]);//specify address ex. ip address , use 0.0.0.0 to bind in local address sin_addr holding address and data of address
	//s_addr mean real server address , INADDR_ANY same with 0.0.0.0
	
	//connect
	int connection_status = connect(network_socket , (struct sockaddr *) &server_address , sizeof(server_address)); // return integer 0 = ok , -1 = not ok 
	// ( actual socket , input server address structure but differrent structer in server_address , size of address )
	// sockaddr_in structure is address data in ip base ( in = internet ) , sockaddr structure is address data in gerneral structer
	if ( connection_status == -1 ) {
		perror("There was an error making connection to the remote socket\n\n");
		//printf("There was an error making connection to the remote socket\n\n");
		return 0;
	}
	//receive data from server
	char server_response[size]; //string that get from server
	int receive_return;
	//receive_return = read(network_socket , &server_response , sizeof(server_response)); // ( socket , string of data , size of buffer , flag parameter )
	

	//send file path
	write(network_socket , argv[3] , strlen(argv[3]) + 1);
	receive_return = read(network_socket , &server_response , sizeof(server_response)); // ( socket , string of data , size of buffer , flag parameter )
	if(server_response[0] == '1')
	{
		printf("file found ... receiving ... \n");
		FILE *fw;
		fw = fopen(argv[4], "wb+");
		while(1)
		{
			receive_return = read(network_socket , &buffer , sizeof(buffer));
			//printf("receive %d : %s \n",receive_return , buffer);
			//printf("Check end : %c%c%c%c \n" , buffer[0] , buffer[1] , buffer[2] , buffer[3]);
			//printf("Check2end : %c%c%c%c \n" , buffer[receive_return-5] , buffer[receive_return-4] , buffer[receive_return-3] , buffer[receive_return-2]);
			if(buffer[0] == '-' && buffer[1] == '-' && buffer[2] == 'E' && buffer[3] == 'D' ) break;
			if(receive_return > 4 && buffer[receive_return-5] == '-' && buffer[receive_return-4] == '-' && buffer[receive_return-3] == 'E' && buffer[receive_return-2] == 'D')
			{
				fwrite(buffer, 1, receive_return-5, fw);
				break;
			}
			fwrite(buffer, 1, receive_return, fw);
			write(network_socket,"1",2);
		}
		printf("Ending\n");
	}
	else
	{
		printf("file not found\n");
	}
	/*
	//print data
	printf("return : %d Receive : '%s' \n" , receive_return , server_response);
	printf(" string long : %ld \n",strlen(server_response));
	*/
	//close socket
	close(network_socket);
	return 0;
}
