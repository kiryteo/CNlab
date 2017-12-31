
#include <stdio.h>
#include <stdlib.h>

// Time function, sockets, htons... file stat
#include <sys/socket.h>
#include <arpa/inet.h>
#include <sys/types.h>
#include <sys/uio.h>

// File function and bzero
#include <fcntl.h>
#include <unistd.h>
#include <strings.h>

#define BUFFERT 512

int create_server_socket (int port);

struct sockaddr_in sock_serv,clt;

int main (int argc, char**argv){
    //Descriptor
	int fd, sfd;

	char buf[BUFFERT];
	long count=0, n;
	char filename[256];
    unsigned int l=sizeof(struct sockaddr_in);

	if (argc != 2){
		printf("Error usage : %s <port_serv>\n",argv[0]);
		return EXIT_FAILURE;
	}

    sfd = create_server_socket(atoi(argv[1]));

	bzero(filename,256);
	sprintf(filename,"newfile");
	printf("Creating the output file : %s\n",filename);

	//0600 chmod call for r-w , 700 for r-w-e
	if((fd=open(filename,O_CREAT|O_WRONLY|O_TRUNC,0600))==-1){
		perror("open fail");
		return EXIT_FAILURE;
	}

	bzero(&buf,BUFFERT);
    n=recvfrom(sfd,&buf,BUFFERT,0,(struct sockaddr *)&clt,&l);
	while(n){
		if(n==-1){
			perror("read fails");
			return EXIT_FAILURE;
		}
		count+=n;
		write(fd,buf,n);
		bzero(buf,BUFFERT);
        n=recvfrom(sfd,&buf,BUFFERT,0,(struct sockaddr *)&clt,&l);
	}

	printf("Number of octets transfered : %ld \n",count);

    close(sfd);
    close(fd);
	return EXIT_SUCCESS;
}


int create_server_socket (int port){
    int l;
	int sfd;

	sfd = socket(AF_INET,SOCK_DGRAM,0);
	if (sfd == -1){
        perror("socket fail");
        return EXIT_FAILURE;
	}

	l=sizeof(struct sockaddr_in);
	bzero(&sock_serv,l);

	sock_serv.sin_family=AF_INET;
	sock_serv.sin_port=htons(port);
	sock_serv.sin_addr.s_addr=htonl(INADDR_ANY);

	if(bind(sfd,(struct sockaddr*)&sock_serv,l)==-1){
		perror("bind fail");
		return EXIT_FAILURE;
	}


    return sfd;
}
