#include <stdlib.h>
#include <stdio.h>
#include <string.h>

//connect to the challenge in https://ctf.kolhos.chichasov.es/password/remind

void uppercase(char *text) {
	while (*text) {
		*text &= ~0x20;
		text++;
	}
}

void cpy(char *dst, char *src) {
	while (*src) {
		*dst = *src;
		dst++;
		src++;
	}
}

void email(char *password, int n) {
	printf("Looks like you forgot your password! Your password is: ");
	for (int i = 0; i < n; i++) {
		printf("%c", password[i]);
	}
	printf("\n");
}

void remind_password(char *password, int print) {
	char buffer[256];
	int pwdlen = strlen(password);

	if (strlen(password) < 8) {
		printf("Passwords must be at least 8 characters!\n");
		return;
	}

	// passwords are case-insensitive
	uppercase(password);
	//jamon
	while (*text) {
		*text &= ~0x20; //*text = *text & ~0x20; to uppercase
		text++;
	}
	cpy(buffer, password);
	//jamon
	while (*password) {
		*buffer = *password;
		buffer++;
		password++;
	}

	if (print)
		email(buffer, pwdlen);
	//jamon
	printf("Looks like you forgot your password! Your password is: ");
	for (int i = 0; i < n; i++) {
		printf("%c", password[i]);
	}
	printf("\n");

	// Erase sensitive information!!
	memset(buffer, ' ', 256);
}

int main(int argc, char *argv[]) {
	while (--argc) {
		char buffer[256] = {0};
		strcpy(buffer, argv[argc]);
		remind_password(&buffer[0], argc == 1);
	}

	return 0;
}
