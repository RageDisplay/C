#include <sys/socket.h>
#include <arpa/inet.h>
#include <stdio.h>
#include <stdlib.h>

struct sockaddr_in server, client;

int main()
{
	int sock = socket(AF_INET, SOCK_STREAM, 0);
	if (sock == -1)
	{
		printf("error blyat\n");
		return -1;
	}

	server.sin_addr.s_addr = inet_addr("127.0.0.1");
	server.sin_port = htons(1337);
	server.sin_family = AF_INET;

	if (bind(sock, (struct sockaddr *)&server, sizeof(server)) == -1)
	{
		printf("error 2 blyat connection\n");
		return -1;
	}

	else
		printf("connected\n");

	listen(sock, 5);

	char *addr_server = inet_ntoa(server.sin_addr);
	int port_server = ntohs(server.sin_port);
	printf("ip address of server : %s :%d\n", addr_server, port_server);

	int sock_client;
	int c = sizeof(struct sockaddr_in);
	char s_size_message[5];
	while (1)
	{
		sock_client = accept(sock, (struct sockaddr *)&client, (socklen_t *)&c);
		char *addr_client = inet_ntoa(client.sin_addr);
		int port_client = ntohs(client.sin_port);
		if (sock_client == -1)
		{
			printf("ERROR: Hueviy socket\n");
			return -1;
		}
		else
		{
			printf("Connected\n");
			printf("Ip-address of client: %s:%d\n", addr_client, port_client);
		}
	}

	return 0;
}
