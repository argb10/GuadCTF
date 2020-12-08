# WriteUP for the "GiveMeThaPassword" Challenge

## Recon
At first we receive a link to the challenge. 

Inspect it and we can a blank page. Umm smells like we are going to use burp.

Use Burp proxy to inspect the GET requets.

When we try to make the GET we get (lol) a 400 Bad Requets.

Since we don't any more info, let's change to POST Request.

We do the POST and receive this:

```tcp
HTTP/1.1 200 OK
Content-Length: 41
Content-Type: text/plain; charset=utf-8
Date: Tue, 08 Dec 2020 12:46:26 GMT
Connection: close

Passwords must be at least 8 characters! 
```

Nice! :)

Sending a password with 8 characters:

```tcp
HTTP/1.1 200 OK
Content-Length: 64
Content-Type: text/plain; charset=utf-8
Date: Tue, 08 Dec 2020 12:48:49 GMT
Connection: close

Looks like you forgot your password! Your password is: AAAAAAAA
```

OK, now we know how the requets are working, let's check the code.

We can summarize the code in this lines

```c
void ctf(char *password, int print) {
	char buffer[256];
	int pwdlen = strlen(password);

	if (strlen(password) < 8) {
		printf("Passwords must be at least 8 characters!\n");
		return;
	}
	// passwords are case-insensitive
	//uppercase
	while (password) {
		//WARNING 1!
		*password &= ~0x20; //*password = *password & ~0x20; to uppercase
		password++;
	}
	//cpy
	while (*password) {
    //WARNING 2!
		*buffer = *password;
		buffer++;
		password++;
	}
	//email
	if (print){
		printf("Looks like you forgot your password! Your password is: ");
		for (int i = 0; i < n; i++) {
			printf("%c", password[i]);
		}
		printf("\n");
	}
	// Erase sensitive information!!
  //WARNING 3!
	memset(buffer, ' ', 256);
}

int main(int argc, char *argv[]) {
	while (--argc) {
		char buffer[256] = {0};
		strcpy(buffer, argv[argc]);
		ctf(&buffer[0], argc == 1);
	}

	return 0;
}
```
As you can see in the code, I added 3 warnings, let's check it, to see if we can exploit them.

