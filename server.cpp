#include<stdio.h>
#include<sys/types.h>//socket
#include<sys/socket.h>//socket
#include<string.h>//memset
#include<stdlib.h>//sizeof
#include<netinet/in.h>//INADDR_ANY
#define PORT 8000
#define SERVER_IP "127.0.0.1"
#define MAXSZ 100

static const char key[]="BDUFGH";
void encrypt(char* input, char key[])
{
  int k=0;
  for(int i=0;i<6;i++)
  {
    input[i]=input[i]^key[i];
    cout<<input[i];
  }
  cout<<endl;
}

void decrypt(char* input,char key[])
{
  for(int i=0;i<6;i++)
  {
    input[i]=input[i]^key[i];
    cout<<input[i];
  }
  cout<<endl;
}
int main()
{
 int sockfd;
 struct sockaddr_in serverAddress;

 int n;
 char input[100000];

 sockfd=socket(AF_INET,SOCK_STREAM,0);
memset(&serverAddress,0,sizeof(serverAddress));
 serverAddress.sin_family=AF_INET;
 serverAddress.sin_addr.s_addr=inet_addr(SERVER_IP);
 serverAddress.sin_port=htons(PORT);

connect(sockfd,(struct sockaddr *)&serverAddress,sizeof(serverAddress));
while(1)
 {
  printf("\nEnter message to send to server:\n");
  fgets(input,MAXSZ,stdin);
  if(input[0]=='#')
   break;
  n=strlen(msg1)+1;
  encrypt(input,key);
  send(sockfd,input,n,0);//SEND
  n=recv(sockfd,msg2,MAXSZ,0);//RECV
  decrypt(input,key);
  n=strlen(input)+1;
  send(sockfd,input,n,0);//SEND

  cout<<"Sent Message Successfully";
 }

 return 0;
}
