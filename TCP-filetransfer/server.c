
#include <stdio.h>
#include <stdlib.h>
#include <sys/time.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <sys/types.h>
#include <sys/uio.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <strings.h>

#define BUFFERT 512

int create_server_socket (int port);

struct sockaddr_in sock_serv,sock_clt;

int main(int argc,char** argv)
{
    int sfd,fd;
    unsigned int length=sizeof(struct sockaddr_in);
    long int n, m,count=0;
    unsigned int nsid;
    int clt_port;
    char buffer[BUFFERT],filename[256];
    char dst[INET_ADDRSTRLEN]; // length of string form of ip
        
    if(argc!=2)
    {
        perror("utilisation ./a.out <num_port> <file2send>\n");
        exit(3);
    }
    
    sfd = create_server_socket(atoi(argv[1]));
    
    bzero(buffer,BUFFERT);
    listen(sfd,1);
    
    nsid = accept(sfd,(struct sockaddr*)&sock_clt, &length); // accept new conn on socket
    if(nsid==-1)
    {
        perror("accept fail");
        return EXIT_FAILURE;
    }
    else
    {
        if(inet_ntop(AF_INET,&sock_clt.sin_addr,dst,INET_ADDRSTRLEN)==NULL)
        {
            perror("error socket");
            exit (4);
        }
        clt_port=ntohs(sock_clt.sin_port);
        printf("Start of connection for : %s:%d\n",dst,clt_port);
        
        bzero(filename,256);
        sprintf(filename,"cltfile");
        
        if((fd=open(filename,O_CREAT|O_WRONLY,0600))==-1)
        {
            perror("open fail");
            exit (3);
        }
        bzero(buffer,BUFFERT);
        
        n=recv(nsid,buffer,BUFFERT,0);
        while(n)
        {
            if(n==-1)
            {
                perror("recv fail");
                exit(5);
            }
            if((m=write(fd,buffer,n))==-1)
            {
                perror("write fail");
                exit (6);
            }
            count=count+m;
            bzero(buffer,BUFFERT);
            n=recv(nsid,buffer,BUFFERT,0);
        }
        close(sfd);
        close(fd);
    }
    close(nsid);
    
    printf("End of transmission with %s.%d\n",dst,clt_port);
    printf("Number of bytes received : %ld \n",count);
    
    return EXIT_SUCCESS;
}

int create_server_socket (int port)
{
    int l,sfd,yes=1;
    
    sfd = socket(AF_INET,SOCK_STREAM,0); // (domain, type, protocol)
    if(sfd == -1)
    {
        perror("socket fail");
        return EXIT_SUCCESS;
    }
    /*SOL_SOCKET : To manipulate options at the sockets API level
     *SO_REUSEADDR : When you need to restart a server after a crash*/

    if(setsockopt(sfd, SOL_SOCKET, SO_REUSEADDR,&yes,sizeof(int)) == -1 ) 
    {
        perror("setsockopt error");
        exit(5);
    }
    //preparing the address of the destination socket
    l=sizeof(struct sockaddr_in);
    bzero(&sock_serv,l);
	
    sock_serv.sin_family=AF_INET;
    sock_serv.sin_port=htons(port);
    sock_serv.sin_addr.s_addr=htonl(INADDR_ANY);

	//assign an identity to the socket
    if(bind(sfd,(struct sockaddr*)&sock_serv,l)==-1)
    {
	perror("bind fail");
	return EXIT_FAILURE;
    }

    return sfd;
}
