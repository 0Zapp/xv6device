#include "kernel/types.h"
#include "kernel/stat.h"
#include "user.h"
#include "kernel/fcntl.h"//ovde se nalazi rdwr

int
main(int argc, char *argv[])//da bi se ovo pojavilo u xv6 mora da postoji i u Makefile
{

	char *msg = "hello, world!";
	char buf[512];
	int fdw=open("/dev/random",O_WRONLY);//otvaramo za citanje i pisanje odvojeno
	int fdr=open("/dev/random",O_RDONLY);//otvaramo za citanje i pisanje odvojeno
	printf("prosledjeno za pisanje:%s\n",msg);
	printf("write funkcija vraca:%d,\n",write(fdw,msg,strlen(msg)));
	
    printf("read funkcija vraca: %d\n",read(fdr,buf,512));
	printf("---------------------------------Sadrzaj buffera--------------------------------%s\n",buf);
	printf("-----------------------------------Objasnjenje----------------------------------");
	printf("buffer je ispunjen nasumicnim karakterima i read vraca 512,");
	printf("jer ceo je ispunjen a write vraca 13 jer je");
	printf(" to velicina prosledjene poruke za pisanje.\n");
	exit();
}
