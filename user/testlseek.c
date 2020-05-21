#include "kernel/types.h"
#include "kernel/stat.h"
#include "user.h"
#include "kernel/fcntl.h"//ovde se nalazi rdwr
#include "kernel/lseek.h"

int
main(int argc, char *argv[])//da bi se ovo pojavilo u xv6 mora da postoji i u Makefile
{

	if(argc!=3){
		printf("Unesite argumente: kao prvi argument s (SEEK_SET), c (SEEK_CUR) ili e (SEEK_END), a za drugi");
		printf(" argument k (kmesg) ili d (disk) zavisno od demonstracij koju zelite da vidite, npr:\n");
		printf("testlseek s k\n");
		printf("ce demonstrirati rad lseek-SEEK_SET-a nad /dev/kmesg\n");
		exit();
	}

	char *msg = "hello, world!";
	char buf[512];

	int fdw;
	int fdr;
	if(*argv[2]=='k'){
	fdw=open("/dev/kmesg",O_WRONLY);//otvaramo za citanje i pisanje odvojeno
	fdr=open("/dev/kmesg",O_RDONLY);//otvaramo za citanje i pisanje odvojeno
		printf("pozvano za /dev/kmesg");
	}else if(*argv[2]=='d'){
	fdw=open("/dev/disk",O_WRONLY);//otvaramo za citanje i pisanje odvojeno
	fdr=open("/dev/disk",O_RDONLY);//otvaramo za citanje i pisanje odvojeno
		printf("pozvano za /dev/disk");
	}else{
		printf ("invalidan argument: %s prihvatljivi argumenti su d:disk ili k:kmesg\n",argv[2]);
		exit();
	}


	if(*argv[1]=='s'){
			printf(" SEEK_SET 100\n");
			lseek(fdr, 10, SEEK_SET);
	}else if(*argv[1]=='c'){
			printf(" SEEK_CUR 100\n");
			lseek(fdr, 10, SEEK_CUR);
	}else if(*argv[1]=='e'){
			printf(" SEEK_END 100\n");
			lseek(fdr, 10, SEEK_END);
	}else{
		printf ("invalidan argument: %s prihvatljivi argumenti su s:SEEK_SET, c:SEEK_CUR ili e:SEEK_END\n",argv[1]);
		exit();
	}

	printf("prosledjeno za pisanje:%s\n",msg);
	printf("write funkcija vraca:%d,\n",write(fdw,msg,strlen(msg)));
	
    printf("read funkcija vraca: %d\n",read(fdr,buf,512));
	printf("---------------------------------Sadrzaj buffera--------------------------------%s",buf);
	exit();		

}
