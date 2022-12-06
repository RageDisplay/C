#include <sys/socket.h>
#include <arpa/inet.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct sockaddr_in client;

int main()
{
	int sock = socket(AF_INET, SOCK_STREAM, 0);
	if (sock == -1)
	{
		printf("error, idi nahui\n");
		return -1;
	}

	client.sin_addr.s_addr = inet_addr("127.0.0.1");
	client.sin_port = htons(1337);
	client.sin_family = AF_INET;

	printf("waiting\n");
	if (connect(sock, (struct sockaddr *)&client, sizeof(client)) == -1)
	{
		printf("error opyat c connection\n");
		return -1;
	}
	else
		printf("connected\n");

	return 0;
}
