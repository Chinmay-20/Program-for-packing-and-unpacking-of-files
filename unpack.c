/*
	This program is based on the "pack.c" program which collects the data of all files from one directory in to one text file(all.txt).
	This program "unpack.c" creates all files that are packed in text file.
	This program not only creates files but also writes the data of respective files into it.
	The files are created in which the text file is present.
*/	

#include <stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<fcntl.h>
#include<dirent.h>
#include<sys/types.h>
#include<sys/stat.h>

struct fileinfo
{
        char name[300];
        int size;
};

int main(int argc,char *argv[])
{
    if(argc!=2)
    {
            printf("Invalid Arguments\n");
            printf("usage: myexe file_name\n");
            return -1;
    }
    
    int fdsrc=0,ret=0,fddest=0;
    struct fileinfo fobj;
    char *p;
    
    fdsrc=open(argv[1],O_RDONLY);
   	if(fdsrc==-1)
   	{
   		perror("open");
   		return -1;
   	}
   	
   	while((ret=read(fdsrc,&fobj,sizeof(fobj)))!=0)
   	{
   		printf("%s %d\n",fobj.name,fobj.size);
   		//lseek(fdsrc,fobj.size,SEEK_CUR);
   		fddest=creat(fobj.name,0777);
   		if(fddest==-1)
   		{
   			perror("creat");
   			return -1;
   		}
   		
   		p=(char*)malloc(fobj.size);
   		if(p==NULL)
   		{
   			perror("malloc");
   			return -1;
   		}
   		
   		read(fdsrc,p,fobj.size);
   		write(fddest,p,fobj.size);
   		
   		free(p);
   		close(fddest);
   	}
   	close(fdsrc);
   	return 0;
}
   	
