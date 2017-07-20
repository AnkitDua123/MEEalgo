#include<stdio.h>
#include<sys/types.h>
#include<sys/socket.h>
#include<string.h>
#include<stdlib.h>
#include<netinet/in.h>
#define PORT 8000
#define MAXSZ 100

static const char key2[]="HIGHUH";
void encrypt(char* input, char key[])
{
int k=0;
for(int i=0;i<6;i++)
{
 input[i]=input[i]^key[i];
 cout<<input[i];
}cout<<endl;
}

void decrypt(char* input,char key[])
{
for(int i=0;i<6;i++)
{
 input[i]=input[i]^key[i];
 cout<<input[i];
 }
}


int main()
{
 int sockfd;
 int newsockfd;
 struct sockaddr_in serverAddress;
 struct sockaddr_in clientAddress;
 int n;
 char msg[MAXSZ];
 int clientAddressLength;
 int pid;

sockfd=socket(AF_INET,SOCK_STREAM,0);
memset(&serverAddress,0,sizeof(serverAddress));
 serverAddress.sin_family=AF_INET;
 serverAddress.sin_addr.s_addr=htonl(INADDR_ANY);
 serverAddress.sin_port=htons(PORT);

bind(sockfd,(struct sockaddr *)&serverAddress, sizeof(serverAddress));

listen(sockfd,5);
 while(1)
 {
  printf("Server waiting for new client connection: ");
  clientAddressLength=sizeof(clientAddress);
  newsockfd=accept(sockfd,(struct sockaddr*)&clientAddress,&clientAddressLength);
  printf("Connected to client: %s\n",inet_ntoa(clientAddress.sin_addr));
  pid=fork();
  if(pid==0)
  {
    char input[100000];
   while(1)
   {
    n=recv(newsockfd,input,MAXSZ,0);//RECV_2
    if(n==0)
    {
     close(newsockfd);
     break;
    }
    encrypt(input,key2);
    send(newsockfd,input,n,0);//SEND
    n=recv(newsockfd,input,MAXSZ,0);//RECV_2
    if(n==0)
    {
     close(newsockfd);
     break;
    }
    decrypt(input,key2);
    printf("Received: %s\n",input);
   }  exit(0);
  }
  else
  {
   close(newsockfd);  }
 }

 return 0;
}
