/*
	This programs collects the data of all text files into one text file.
	The files that are packed are deleted from mentioned directory.
*/

#include <stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<fcntl.h>
#include<dirent.h>
#include<sys/types.h>
#include<sys/stat.h>
#include<string.h>

struct fileinfo
{
        char name[300];
        int size;
};

int main(int argc,char *argv[])
{
    if(argc!=3)
    {
            printf("Invalid Arguments\n");
            printf("usage: myexe Directory_name File_name\n");
            return -1;
    }
    DIR *dir=NULL;
    struct dirent *statd=NULL;
    struct stat statf;
    int fddest=0;
    char name[300]={'\0'};
    struct fileinfo fobj;
    int fd=0;
    char buf[1024];
    int ret=0;
   
   fddest=creat(argv[2],0777);
   if(fddest==-1)
   {
        perror("creat");
        return -1;
   }
   
   dir=opendir(argv[1]);
   if(dir==NULL)
   {
        perror("opendir");
        return -1;
   }
   chdir(argv[1]);
   printf("Names of file are \n");
   while((statd=readdir(dir))!=NULL)
   {
        
        sprintf(name,"%s/%s",argv[1],statd->d_name);
        stat(statd->d_name,&statf);
        
        if((S_ISREG(statf.st_mode)))
        {
            printf("%s\n",statd->d_name);
            printf("%ld\n",statf.st_size);
            
            strcpy(fobj.name,statd->d_name);
            fobj.size=statf.st_size;
            
            write(fddest,&fobj,sizeof(fobj));
            memset(&fobj,0,sizeof(fobj));
            
            fd=open(statd->d_name,O_RDONLY);
            if(fd==-1)
            {
            	perror("read");
            	return -1;
            }
            while((ret=read(fd,buf,sizeof(buf)))!=0)
            {
            	write(fddest,buf,ret);
            	memset(buf,0,sizeof(buf));
            }
            close(fd);
	    unlink(statd->d_name);
            
            
        }
   }
   
   closedir(dir);
    return 0;
}
