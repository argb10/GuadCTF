#include <stdlib.h>
#include <stdio.h>
#include <string.h>

// Compile with the next command:
// gcc main.c -o main

#define MIN_PASSWORD 8
#define MAX_PASSWORD 511

typedef struct {
	short int request_len;
	char request_password[MAX_PASSWORD + 1]; // null byte
	short int pwd_len;
	char real_password[MAX_PASSWORD + 1];
} t_request;

void cpy(char *dst, char *src) {
	while (*src) {
		*dst = *src;
		dst++;
		src++;
	}

	// Bugfix: strings are not null-terminated
	*dst = 0;
}

void getPassword(char dst[MAX_PASSWORD+1]) {
	char *buf = getenv("PASSWORD");
	cpy(dst, buf);
}

t_request create_request(char *password) {
	t_request req;

	getPassword(req.real_password);
	req.pwd_len = strnlen(req.real_password, MAX_PASSWORD);
	cpy(req.request_password, password);
	req.request_len = strnlen(req.request_password, MAX_PASSWORD);

	return req;
}

void login(char *password) {
	t_request req = create_request(password);

	if (req.request_len < MIN_PASSWORD) {
		printf("Provided password is too short!\n");
	} else if (req.pwd_len != req.request_len) {
		// Don't need to compare strings if lengths aren't equal -- optimization!!
		printf("Password length doesn't match!\n");
	} else if (strncmp(req.real_password, req.request_password, req.pwd_len) == 0) { // strcmp is unsafe!!
		printf("Your security token is %s.\n", getenv("FLAG"));
	} else {
		printf("Password is incorrect!\n");
	}
}

int main(int argc, char *argv[]) {
	if (argc >= 2) {
		login(argv[1]);
	}
	return 0;
}
