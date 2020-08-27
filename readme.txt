------------------------- Read me -----------------------------

---> client.c
use to download file from server
	syntax : ./client [ip] [port] [file path in server] [destination]
	example : ./client 0.0.0.0 14545 Data/1000000.file Output.file
          	--> Download file "Data/1000000" ( relative with server directory ) from localhost to Output.file

--> server.c
use to host file server
	syntax: ./server [host]
	example: ./server 14545
		--> open server on port 4545

--> ./perform.sh
use to run command multiply round and measure time and bandwidth
	syntax: ./perform.sh n "command"
	example: ./perform.sh 10 "./client 0.0.0.0 14545 Data/1000000.file Output.file"
		--> run " ./client 0.0.0.0 14545 Data/1000000.file Output.file " 10 times and measure time and bandwidth

--> ./auto.sh
run ./perform.sh with ./client command with multiply filesize
	syntax: ./auto.sh [ip] [port] n
	example: ./auto.sh 0.0.0.0 14545 10 
		---> Download Multiply file size from server and download to Output.file 
		     For each filesize testing 10 times

