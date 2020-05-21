#include "kernel/types.h"
#include "kernel/stat.h"
#include "user.h"
#include "kernel/fcntl.h"//ovde se nalazi rdwr
#include "kernel/lseek.h"

int
main(int argc, char *argv[])//da bi se ovo pojavilo u xv6 mora da postoji i u Makefile
{
	int SIF=1;
	int SOF=1;
	char *Input="std";
	char *Output="std";
	int BSize=512;
	int Count=0;//vrati na -1;
	int Skip=0;
	int Seek=0;
	int fdin=1;
	int fdout=1;

	for(int i=1;i<argc;i++){
		char *c=argv[i];

		switch (*c++)
		{
		case 'i':
			if((*c++)=='f'&&(*c++)=='='){
				SIF=0;
				Input=c;
			}else{
				printf("invalid argument:%s\n",argv[i]);
				exit();
			}	
			break;
		case 'o':
			if((*c++)=='f'&&(*c++)=='='){
				SOF=0;
				Output=c;
			}else{
				printf("invalid argument:%s\n",argv[i]);
				exit();
			}	
			break;
		case 'b':
			if((*c++)=='s'&&(*c++)=='='){
				BSize=atoi(c);
			}else{
				printf("invalid argument:%s\n",argv[i]);
				exit();
			}	
			break;
		case 'c':
			if((*c++)=='o'&&(*c++)=='u'&&(*c++)=='n'&&(*c++)=='t'&&(*c++)=='='){
				Count=atoi(c);
			}else{
				printf("invalid argument:%s\n",argv[i]);
				exit();
			}	
			break;
		case 's':
			if(*c=='k'){
				*c++;
				if((*c++)=='i'&&(*c++)=='p'&&(*c++)=='='){
					Skip=atoi(c);
				}else{
					printf("invalid argument:%s\n",argv[i]);
					exit();
				}
			}else if(*c=='e'){
				*c++;
				if((*c++)=='e'&&(*c++)=='k'&&(*c++)=='='){
					Seek=atoi(c);
				}else{
					printf("invalid argument:%s\n",argv[i]);
					exit();
				}
			}else{
				printf("invalid argument:%s\n",argv[i]);
				exit();
			}	
			break;
		
		default:
			printf("invalid argument:%s\n",argv[i]);
			exit();
			break;
					}

	}

	if(SIF==0){
	fdin=open(Input,O_RDONLY);//ovo je dobro prosledjen argument
	}

	if(SOF==0){
	fdout=open(Output, O_WRONLY);//ovo je lose prosledjen argument
	}

	lseek(fdin, Skip*BSize, SEEK_SET);

	int bs=BSize;
	lseek(fdout, Seek*BSize, SEEK_SET);
	if(Count<1){
		Count=1;
		bs=512;
	}
	char buf[bs];
	int i=0;

	while (i<Count)
	{
		i++;
		read(fdin,buf,BSize);
		write(fdout,buf,BSize);
	}
	
	exit();
}
