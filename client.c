
#include <stdio.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <strings.h>
#include <netdb.h>
#include <stdlib.h>
#include <string.h>


int main(){
	int sockfd, portno, n;
	struct sockaddr_in serv_addr;
	struct hostent *server;

	char buffer[4096];
	char *host = "csweb01.csueastbay.edu";
	int uinput = 0;
	//
	printf("press 1) to select  http://csweb01.csueastbay.edu/~td4679/Pgm3/start.html: " );
	scanf("%d", &uinput);

	//
	if(uinput = 1){
	portno = 80;
	sockfd = socket(AF_INET, SOCK_STREAM, 0);
	if (sockfd < 0) 
		error("ERROR opening socket");
	server = gethostbyname(host);
	if (server == NULL) {
		fprintf(stderr,"ERROR, no such host\n");
 	 	exit(0);
 	}
 	bzero((char *) &serv_addr, sizeof(serv_addr));
 	serv_addr.sin_family = AF_INET;
 	bcopy((char *)server->h_addr, 
        (char *)&serv_addr.sin_addr.s_addr, 
	server->h_length);
	serv_addr.sin_port = htons(portno);
  	if (connect(sockfd,(struct sockaddr *) &serv_addr,sizeof(serv_addr)) < 0) error("ERROR connecting");
	const char * request = "GET http://csweb01.csueastbay.edu/~td4679/Pgm3/start.html HTTP/1.0\r\n\r\nConnection: close\r\n\r\n";
  	n = write(sockfd,request,strlen(request));
  	if (n < 0) error("ERROR writing to socket");
  	bzero(buffer,4096);
  	
	n = read(sockfd,buffer,4095);
  	if (n < 0) error("ERROR reading from socket");
	printf("%d", strlen(buffer));
	//
	int x, idx = 0;
	int y; int z = 1;
	int opened= 0;
	int flag1 = 0; int flag2 = 0; int count = 0; int c1 = 0;
	char hlink[3][25];
	char buff[4096] = "";
        for(x = 0; x < strlen(buffer); x++){
		if(buffer[x] == '<')
                        opened = 1;
		if(opened == 0 )
			buff[idx++] = buffer[x];
                if(buffer[x] == '>')
                        opened = 0;
		if(buffer[x] == '<' && buffer[x+1] == 'a' && buffer[x+2] == ' '){
			flag1 = 1; 
		}
		
		if(buffer[x] == '"' && flag2 == 1){
                       //printf("test1");
			flag2 = 0;flag1 = 0;
                        buff[idx++] = (z + '0'); z++;
                        buff[idx++] = ')';
                        c1++; count = 0;
			opened = 0; x++;
		
                }

		if(flag2 == 1){
			hlink[c1][count++] = buffer[x];
			//printf("%c", buffer[x]); 
		}
		if(flag1 == 1 && buffer[x] == '"'){
			flag2 = 1;
                //	printf("flag set:");	
		}

		

        }
        buff[idx] = '\0';

  	printf("%s\n",buff);
	close(sockfd);
	//
	char r[50];
	char *request1; // = "GET http://csweb01.csueastbay.edu/~td4679/Pgm3/camp.html HTTP/1.0\r\n\r\nConnection:: close\r\n\r\n";
	char *request2; // = "GET http://csweb01.csueastbay.edu/~td4679/Pgm3/beach.html HTTP/1.0\r\n\r\nConnection:: close\r\n\r\n";
	char *request3; // = "GET http:///csweb01.csueastbay.edu/~td4679/Pgm3/bbq.html HTTP/1.0\r\n\r\nConnection:: close\r\n\r\n";
	char urlstr[80];
	char temp[80]; char host1[80];
//	uinput =  0;
//	printf("enter choice 1)camping 2)beach 3)barbeque 0)to enter url (or 5 for quit): ");
//	scanf("%d", &uinput);
	
	char *addr = "GET http://csweb01.csueastbay.edu/~td4679/Pgm3/";
	char *closing = " HTTP/1.0\r\n\r\nConnection:: close\r\n\r\n";
	int i;


		

	while(uinput != 5){
		printf("enter choice 1)%s 2)%s 3)%s 0)enter url 5)quit: ", hlink[0], hlink[1], hlink[2]);
		scanf("%d", &uinput);
		// while(uinput != 0 || uinput != 1 || uinput != 2 || uinput != 3 || uinput != 4 || uinput != 5){
                  //      printf("enter choice 1)camping 2)beach 3)barbeque 4)start 0)enter url 5)quit: ");
                   //     scanf("%d", &uinput);}



	switch(uinput){
		case 0: {
			printf("enter url: ");
			scanf("%s", urlstr);
			strcpy(temp, "GET  / HTTP/1.0\r\nHost: ");
			strcat(temp, urlstr);
			strcpy(urlstr, temp);
			strcpy(temp, "\r\n\r\nConnection: close\r\n\r\n"); 
			strcat(urlstr, temp);
			//		
			printf("%s\n", urlstr);	
			printf("enter host url: ");
			scanf("%s", host1);
			//
			 sockfd = socket(AF_INET, SOCK_STREAM, 0);
                 if (sockfd < 0)
                        error("ERROR opening socket");
                 server = gethostbyname(host1);
                 if (server == NULL) {
                        fprintf(stderr,"ERROR, no such host\n");
                        exit(0);
                 }
                 bzero((char *) &serv_addr, sizeof(serv_addr));
                 serv_addr.sin_family = AF_INET;
                 bcopy((char *)server->h_addr,
                 (char *)&serv_addr.sin_addr.s_addr,
                 server->h_length);
                 serv_addr.sin_port = htons(portno);
                 if (connect(sockfd,(struct sockaddr *) &serv_addr,sizeof(serv_addr)) < 0) error("ERROR connecting");
                // const char * request = "GET http://csweb01.csueastbay.edu/~td4679/Pgm3/camp.html HTTP/1.0\r\n\r\nConnection: close\r\n\r\n";
                 n = write(sockfd,urlstr,strlen(urlstr));
                 if (n < 0) error("ERROR writing to socket");
                 bzero(buffer,4096);
                 n = read(sockfd,buffer,4095);
                 if (n < 0) error("ERROR reading from socket");
                 printf("%d\n", (int)strlen(buffer));
             	//
		idx = 0;
	        opened= 0;
       		 for(x = 0; x < strlen(buffer); x++){

                if(buffer[x] == '<')
                        opened = 1;
                else if(buffer[x] == '>')
                        opened = 0;
                else if(!opened)
                        buffer[idx++] = buffer[x];
       		 }
       		 buffer[idx] = '\0';

		 printf("%s\n",buffer);
                close(sockfd);
			


		break;
		}
		
		
		case 1: {
			 sockfd = socket(AF_INET, SOCK_STREAM, 0);
	         if (sockfd < 0)
	                error("ERROR opening socket");
	         server = gethostbyname(host);
	         if (server == NULL) {
	                fprintf(stderr,"ERROR, no such host\n");
	                exit(0);
	         }
	         bzero((char *) &serv_addr, sizeof(serv_addr));
	         serv_addr.sin_family = AF_INET;
	         bcopy((char *)server->h_addr,
	         (char *)&serv_addr.sin_addr.s_addr,
	         server->h_length);
	         serv_addr.sin_port = htons(portno);
	         if (connect(sockfd,(struct sockaddr *) &serv_addr,sizeof(serv_addr)) < 0) error("ERROR connecting");
		 strcpy(r, addr);
		 strcat(r, hlink[uinput-1]);
		 strcat(r, closing);
		 printf("%s", r);
		 const char * request = r; //"GET http://csweb01.csueastbay.edu/~td4679/Pgm3/camp.html HTTP/1.0\r\n\r\nConnection: close\r\n\r\n";
		 n = write(sockfd,request,strlen(request));
	         if (n < 0) error("ERROR writing to socket");
	         bzero(buffer,4096);
	         n = read(sockfd,buffer,4095);
	         if (n < 0) error("ERROR reading from socket");
	         printf("%d\n", (int)strlen(buffer));
	        //
		idx = 0;
       		y; z = 1;
        	opened= 0;
        	flag1 = 0; flag2 = 0;count = 0; c1 = 0;
        	char buff[4096] = "";
		memset(hlink[0], 0, 25); memset(hlink[1], 0 ,25); memset(hlink[2], 0 ,25);
			for (x = 0; x < strlen(buffer); x++){

				if (buffer[x] == '<')
					opened = 1;
				if (opened == 0)
					buff[idx++] = buffer[x];
				if (buffer[x] == '>')
					opened = 0;
				if (buffer[x] == '<' && buffer[x + 1] == 'a' && buffer[x + 2] == ' '){
					flag1 = 1;
				}

				if (buffer[x] == '"' && flag2 == 1){
					//printf("test1");
					flag2 = 0; flag1 = 0;
					buff[idx++] = (z + '0'); z++;
					buff[idx++] = ')';
					c1++; count = 0;
					opened = 0; x++;

				}

				if (flag2 == 1){
					hlink[c1][count++] = buffer[x];
					//printf("%c", buffer[x]);
				}
				if (flag1 == 1 && buffer[x] == '"'){
					flag2 = 1;
					//      printf("flag set:");
				}



			}
        	buff[idx] = '\0';
         	printf("%s\n",buff);
	        close(sockfd);
		

		//





		break;
		}
		case 2: {
		 sockfd = socket(AF_INET, SOCK_STREAM, 0);
         if (sockfd < 0)
                error("ERROR opening socket");
         server = gethostbyname(host);
         if (server == NULL) {
                fprintf(stderr,"ERROR, no such host\n");
                exit(0);
         }
         bzero((char *) &serv_addr, sizeof(serv_addr));
         serv_addr.sin_family = AF_INET;
         bcopy((char *)server->h_addr,
         (char *)&serv_addr.sin_addr.s_addr,
         server->h_length);
         serv_addr.sin_port = htons(portno);
         if (connect(sockfd,(struct sockaddr *) &serv_addr,sizeof(serv_addr)) < 0) error("ERROR connecting");
        //const char * request = r; //"GET http://csweb01.csueastbay.edu/~td4679/Pgm3/beach.html HTTP/1.0\r\n\r\nConnection: close\r\n\r\n";
        strcpy(r, addr);
        strcat(r, hlink[uinput-1]);
        strcat(r, closing);

	 n = write(sockfd,r,strlen(request));
         if (n < 0) error("ERROR writing to socket");
         bzero(buffer,4096);
         n = read(sockfd,buffer,4095);
         if (n < 0) error("ERROR reading from socket");
         printf("%d\n", (int)strlen(buffer));
	//
		idx = 0;
                y; z = 1;
                opened= 0;
                flag1 = 0; flag2 = 0;count = 0; c1 = 0;
                char buff[4096] = "";
		memset(hlink[0], 0 , 25); memset(hlink[1], 0 ,25); memset(hlink[2], 0 ,25);
				for (x = 0; x < strlen(buffer); x++){

					if (buffer[x] == '<')
						opened = 1;
					if (opened == 0)
						buff[idx++] = buffer[x];
					if (buffer[x] == '>')
						opened = 0;
					if (buffer[x] == '<' && buffer[x + 1] == 'a' && buffer[x + 2] == ' '){
						flag1 = 1;
					}

					if (buffer[x] == '"' && flag2 == 1){
						//printf("test1");
						flag2 = 0; flag1 = 0;
						buff[idx++] = (z + '0'); z++;
						buff[idx++] = ')';
						c1++; count = 0;
						opened = 0; x++;

					}

					if (flag2 == 1){
						hlink[c1][count++] = buffer[x];
						//printf("%c", buffer[x]);
					}
					if (flag1 == 1 && buffer[x] == '"'){
						flag2 = 1;
						//      printf("flag set:");
					}


				}
                
                buff[idx] = '\0';
                printf("%s\n",buff);
                close(sockfd);


		break;
		}
		case 3: {
		 sockfd = socket(AF_INET, SOCK_STREAM, 0);
         if (sockfd < 0)
                error("ERROR opening socket");
         server = gethostbyname(host);
         if (server == NULL) {
                fprintf(stderr,"ERROR, no such host\n");
                exit(0);
         }
         bzero((char *) &serv_addr, sizeof(serv_addr));
         serv_addr.sin_family = AF_INET;
         bcopy((char *)server->h_addr,
         (char *)&serv_addr.sin_addr.s_addr,
         server->h_length);
         serv_addr.sin_port = htons(portno);
         if (connect(sockfd,(struct sockaddr *) &serv_addr,sizeof(serv_addr)) < 0) error("ERROR connecting");
         strcpy(r, addr);
         strcat(r, hlink[uinput-1]);
         strcat(r, closing);
	 const char * request = r; //"GET http://csweb01.csueastbay.edu/~td4679/Pgm3/bbq.html HTTP/1.0\r\n\r\nConnection: close\r\n\r\n";
         n = write(sockfd,request,strlen(request));
         if (n < 0) error("ERROR writing to socket");
         bzero(buffer,4096);
         n = read(sockfd,buffer,4095);
         if (n < 0) error("ERROR reading from socket");
         printf("%d\n", (int)strlen(buffer));
	//
	 idx = 0;
                y; z = 1;
                opened= 0;
                flag1 = 0; flag2 = 0;count = 0; c1 = 0;
                char buff[4096] = "";
		memset(hlink[0], 0 , 25); memset(hlink[1], 0 ,25); memset(hlink[2], 0 ,25);
				for (x = 0; x < strlen(buffer); x++){

					if (buffer[x] == '<')
						opened = 1;
					if (opened == 0)
						buff[idx++] = buffer[x];
					if (buffer[x] == '>')
						opened = 0;
					if (buffer[x] == '<' && buffer[x + 1] == 'a' && buffer[x + 2] == ' '){
						flag1 = 1;
					}

					if (buffer[x] == '"' && flag2 == 1){
						//printf("test1");
						flag2 = 0; flag1 = 0;
						buff[idx++] = (z + '0'); z++;
						buff[idx++] = ')';
						c1++; count = 0;
						opened = 0; x++;

					}

					if (flag2 == 1){
						hlink[c1][count++] = buffer[x];
						//printf("%c", buffer[x]);
					}
					if (flag1 == 1 && buffer[x] == '"'){
						flag2 = 1;
						//      printf("flag set:");
					}


				}
                buff[idx] = '\0';
                printf("%s\n",buff);
                close(sockfd);


		break;		
		}
		default:{
			uinput = 5;
			break;
		}
	}
	
	}	
	//
	}
	
  	 return 0;	
}
