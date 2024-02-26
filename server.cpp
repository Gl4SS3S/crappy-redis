#include <sys/_endian.h>
#include <sys/socket.h>
#include <stdarg.h>
#include <stdlib.h>
#include <stdio.h>
#include <netinet/in.h>


int main() {
	int fd = socket(AF_INET, SOCK_STREAM, 0);


	int val = 1;
	setsockopt(fd, SOL_SOCKET, SO_REUSEADDR, &val, sizeof(val));

	struct sockaddr_in addr = {};
	addr.sin_family = AF_INET;
	addr.sin_port = ntohs(1234); // Port selection
	addr.sin_addr.s_addr = ntohl(0); // Wildcard address
}
