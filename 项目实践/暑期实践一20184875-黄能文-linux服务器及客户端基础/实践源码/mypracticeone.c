#include<stdio.h>
#include<stdlib.h>
#include<errno.h>
#include<string.h>
#include<sys/types.h>
#include<netinet/in.h>
#include<sys/socket.h>
#include<sys/wait.h>
#include<time.h>
#define SERVPORT 3333
#define BACKLOG 3
#include<dirent.h>
#include<unistd.h>
//#include"getmaskcode.h"
int timerserver();
int backupsserver();

int main(){
  int select;
  while(1){
    printf("Please enter number to choose server1\n");
    printf("1 timerserver\n");
    printf("2 backupsserver\n");
    printf("3 get mask\n");
    printf("4 get a packet\n");
    printf("5 pcap loop\n");
    printf("6 get ip\n");
    printf("-1 quit");
    scanf("%d",&select);
    if(select==1){
        timerserver();	
    }
    else if(select==2){
         backupsserver();
    }
    else if(select==3){
        if(execl("./getmask.out",NULL)<0){
             fprintf(stderr,"execl failed:%s",strerror(errno));
             return -1;
	}
    }
    else if(select==4){
           if(execl("./getapacket.out",NULL)<0){
              fprintf(stderr,"execl failed:%s",strerror(errno));
              return -1;
	   }
    }
    else if(select==5){
	if(execl("./pcaploop.out",NULL)<0){
            fprintf(stderr,"execl failed:%s",strerror(errno));
            return -1;
	}
    }
    else if(select==6){
         if(execl("./getip.out",NULL)<0){
            fprintf(stderr,"execl failed:%s",strerror(errno));
            return -1;
	}
    }
    else if(select ==-1){return 1;}
    else{break;} 
    }
}
int backupsserver(){
  int sockfd,client_fd;
  struct sockaddr_in my_addr;
  struct sockaddr_in remote_addr;
  if((sockfd = socket(AF_INET,SOCK_STREAM,0))==-1){
	perror("socker create error!");exit(1);
  }

  my_addr.sin_family = AF_INET;
  my_addr.sin_port = htons(SERVPORT);
  my_addr.sin_addr.s_addr = INADDR_ANY;
  bzero(&(my_addr.sin_zero),8);
  if(bind(sockfd,(struct sockaddr *)&my_addr,sizeof(struct sockaddr)) ==-1){
      perror("bind error!");exit(1);
  }
  if(listen(sockfd,BACKLOG)==-1){
     perror("listen error!");
     exit(1);
  }
  while(1){
       int  sin_size = sizeof(struct sockaddr_in);
      if((client_fd = accept(sockfd,(struct sockaddr *)&remote_addr,&sin_size))
		==-1){
	perror("accept error");
	continue;
       }
      printf("received a connection from %s\n",inet_ntoa(remote_addr.sin_addr));
      if(!fork()){
        char FilePath[]="/home/hnw/backups";
        while(1){
            DIR *dir = NULL;
            struct dirent *entry;
	    char a[800]="Choose function:\n1 upload \n\n";
            char dd[500]={};
            char font[3]={'F',':','\0'};
            char et[2]={'\n','\0'};
            if((dir = opendir(FilePath))==NULL){printf("in3\n");
                   perror("open fail!\n");exit(1);}
            else{ 
            //  printf("1.%s",a);
              while((entry=readdir(dir))!=NULL){
            //   printf("2.%s",a);
                  // printf("a\n");
               // strcat(dd,entry->d_name);
               // printf("%s\n",entry->d_name);
               // strcat(dd,et);
                  if(strncmp(entry->d_name,".",1)!=0&&strncmp(entry->d_name,"..",2)!=0){
		        char  te[20];
                        strcpy(te,entry->d_name);
                    //    printf("3.%s",a);
                        strcat(dd,font);
                       // printf("3.1%s",a);
                       // printf("aa\n");
                        strcat(dd,te);
                      //  printf("3.2%s",a);
                        strcat(dd,et);
                        printf("4.%s",a);
                     //   printf("%s",dd);
                    }
                }
                closedir(dir);   
             }
             printf("%s%s",a,dd);
             strcat(a,dd);
            // printf("aaaaa\n");
             if(send(client_fd,a,1024,0)==-1){
                perror("send error!");
                close(client_fd);
                exit(1);
	    }
            int recvbytes;
             char buf[1024]={};
            if((recvbytes = recv(client_fd,buf,1024,0))==-1){
                 perror("receive error!");
                 exit(1);
            }
            buf[recvbytes]='\0';
            if(buf[0]=='1'){
                if(send(client_fd,"please enter the name of the txt\n",100,0)==-1){
                    perror("send error");
                    exit(1); 		
		}
                if((recvbytes = recv(client_fd,buf,20,0))==-1){printf("recv error");exit(0);}
                buf[recvbytes]='\0';
              //  printf("cha yan\n");
                char temp[100];
                strcpy(temp,FilePath);
                strcat(temp,"/");
                strcat(temp,buf);
               // printf("%s\n",temp);
                FILE *fp;
                if(( fp  = fopen(temp,"w+"))==NULL){
                   printf("create %s error",buf);
                   exit(1);
                }else{printf("create file success\n");}
                while(1){
                  if((recvbytes = recv(client_fd,buf,3,0))==-1){printf("recv error\n");exit(0);}
                   if(buf[0]=='e'&& buf[1]=='n' && buf[2]=='d'){
                       send(client_fd,"ok",2,0);
                      break;}
                   fputc(buf[0],fp);
                   printf("%c",buf[0]);
		}
                fclose(fp);
                send(client_fd,"finish",6,0);
	     }
        }
	close(client_fd);
   }
 }
}
int timerserver(){
  int sockfd,client_fd;
  struct sockaddr_in my_addr;
  struct sockaddr_in remote_addr;
  if((sockfd = socket(AF_INET,SOCK_STREAM,0))==-1){
	perror("socker create error!");exit(1);
  }

  my_addr.sin_family = AF_INET;
  my_addr.sin_port = htons(SERVPORT);
  my_addr.sin_addr.s_addr = INADDR_ANY;
  bzero(&(my_addr.sin_zero),8);
  if(bind(sockfd,(struct sockaddr *)&my_addr,sizeof(struct sockaddr)) ==-1){
      perror("bind error!");exit(1);
  }
  if(listen(sockfd,BACKLOG)==-1){
     perror("listen error!");
     exit(1);
  }
  while(1){
       int  sin_size = sizeof(struct sockaddr_in);
      if((client_fd = accept(sockfd,(struct sockaddr *)&remote_addr,&sin_size))
		==-1){
	perror("accept error");
	continue;
       }
      printf("received a connection from %s\n",inet_ntoa(remote_addr.sin_addr));
      if(!fork()){
	time_t rawtime;
	struct tm* timeinfo;
	time(&rawtime);
	timeinfo = localtime(&rawtime);
	if(send(client_fd,asctime(timeinfo),24,0)==-1){
	   perror("send error!");
	   close(client_fd);
	   exit(0);
	}
	close(client_fd);
   }
 }
}
