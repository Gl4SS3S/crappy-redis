#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <sys/_endian.h>
#include <sys/_types/_ssize_t.h>
#include <sys/socket.h>
#include <stdarg.h>
#include <stdlib.h>
#include <stdio.h>
#include <netinet/in.h>
#include <type_traits>
#include <errno.h>
#include <unistd.h>

static void die(const char* msg){
	int err = errno;
	fprintf(stderr, "[%d] %s\n", err, msg); 
	abort();
}

static void msg(const char* msg) {
	fprintf(stderr, "%s\n", msg);
}

static void do_something(int connfd) {
	char rbuf[64] = {};
	ssize_t n = read(connfd, rbuf, sizeof(rbuf) - 1);
	if (n < 0) {
		msg("read() error");
		return;
	}

	printf("client says: %s\n", rbuf);

	char wbuf[] = "world";
	write(connfd, wbuf, strlen(wbuf));
}

int main() {
	int fd = socket(AF_INET, SOCK_STREAM, 0);


	int val = 1;
	setsockopt(fd, SOL_SOCKET, SO_REUSEADDR, &val, sizeof(val));

	struct sockaddr_in addr = {};
	addr.sin_family = AF_INET;
	addr.sin_port = ntohs(1234); // Port selection
	addr.sin_addr.s_addr = ntohl(0); // Wildcard address
	int rv = bind(fd, (const sockaddr *) &addr, sizeof(addr));

	if (rv) {
		die("bind()");
	}

	rv = listen(fd, SOMAXCONN);
	if (rv) {
		die("listen()");
	}

	while (true) {
		struct sockaddr_in client_addr = {};
		socklen_t addrlen = sizeof(client_addr);
		int connfd = accept(fd, (struct sockaddr *) &client_addr, &addrlen);
		if (connfd < 0) {
			continue;
		}

		// TODO: Something method
		close(connfd);
	}

	return 0;
}
