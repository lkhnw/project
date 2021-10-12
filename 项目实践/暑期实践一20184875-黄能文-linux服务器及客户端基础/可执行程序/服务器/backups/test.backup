#include<stdio.h>
#include<stdlib.h>
#include<errno.h>
#include<string.h>
#include<netdb.h>
#include<sys/types.h>
#include<netinet/in.h>
#include<sys/socket.h>
#define SERVPORT 3333
#define MAXDATASIZE 1024
#include<unistd.h>
int timerclient();
int backupsclient();

int main(){
   int select;
   while(1){
      printf("Please enter number to chose function!\n");
      printf("1 timerclient\n");
      printf("2 backupsclient\n");
      scanf("%d",&select);
      if(select==1){
         timerclient();
      }
      else if(select == 2){
          backupsclient();
      }
      else{break;}
   }
}


int backupsclient(){
  int sockfd,recvbytes;
  char buf[MAXDATASIZE];
  struct hostent *host;
  struct sockaddr_in serv_addr;
  host = gethostbyname("192.168.0.102");
  if((sockfd = socket(AF_INET,SOCK_STREAM,0))==-1){
    perror("socket create error");
    exit(1);
   } 
   printf("1");
   serv_addr.sin_family=AF_INET;
   serv_addr.sin_port=htons(SERVPORT);
   serv_addr.sin_addr = *((struct in_addr*)host->h_addr);
   bzero(&(serv_addr.sin_zero),8);
   if(connect(sockfd,(struct sockaddr*)&serv_addr,sizeof(struct sockaddr))==-1)
   {
	perror("connect error!");
        exit(1);
   }
   printf("connect server...!\n");
   char se[100]={};
   while(1){
   	if((recvbytes = recv(sockfd,buf,1024,0))==-1){
		perror("recv do not finish");
       		 exit(0);
   	 }
        sleep(1);
   	buf[recvbytes] = '\0';
    	printf("%s\n",buf);
        scanf("%s",se);
        printf("se:%s",se);
        se[99]='\0';
        if(send(sockfd,se,3,0)==-1){perror("send error!\n");exit(0);}
        if(se[0]=='1'){
             recvbytes = recv(sockfd,buf,1024,0);
             printf("%s",buf),
             scanf("%s",se);
             se[20]='\0';
             send(sockfd,se,20,0);
             printf("Please choose file");
             scanf("%s",se);
             FILE *fp =fopen(se,"r");
             if(fp==NULL){printf("can't find file\n");close(sockfd);
                 fflush(stdin);   
                 fflush(stdout);
             exit(1);}
             else{printf("ok");}
             char c[3]={'a','\0','\0'};
             printf("%s",c);
             int ch;
             while((ch=fgetc(fp))!=EOF){
                 wait(1);
                 printf("%d ",ch);
                // printf("blank:%c",char(ch));`
                 c[0]=(char)ch;
                 if(send(sockfd,c,3,0)==-1){perror("send error\n");exit(1); }
             }
             send(sockfd,"end",3,0);
	}
	//scanf("%s",se);
        //se[99]='\0';
        //if(send(sockfd,se,3,0)==-1){perror("send error!");
          // exit(1);
	//}
    }
    close(sockfd);
  return 1;
}
int timerclient(){
  int sockfd,recvbytes;
  char buf[MAXDATASIZE];
  struct hostent *host;
  struct sockaddr_in serv_addr;
  host = gethostbyname("192.168.0.102");
  if((sockfd = socket(AF_INET,SOCK_STREAM,0))==-1){
    perror("socket create error");
    exit(1);
   }
   serv_addr.sin_family=AF_INET;
   serv_addr.sin_port=htons(SERVPORT);
   serv_addr.sin_addr = *((struct in_addr*)host->h_addr);
   bzero(&(serv_addr.sin_zero),8);
   if(connect(sockfd,(struct sockaddr*)&serv_addr,sizeof(struct sockaddr))==-1)
   {
	perror("connect error!");
        exit(1);
   }
   printf("Request time from server...!\n");
   if((recvbytes = recv(sockfd,buf,MAXDATASIZE,0))==-1){
	perror("recv do not finish");
        exit(1);
    }
    buf[recvbytes] = '\0';
    printf("Received:  %s",buf);
    close(sockfd);
  return 1;
}
