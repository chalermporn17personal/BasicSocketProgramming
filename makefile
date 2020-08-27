all:
	echo "Compiling server.c"
	gcc server.c -o server
	echo "Compiling client.c"
	gcc client.c -o client -w
