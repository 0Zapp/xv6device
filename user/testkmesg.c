#include "kernel/types.h"
#include "kernel/stat.h"
#include "user.h"
#include "kernel/fcntl.h"//ovde se nalazi rdwr

int
main(int argc, char *argv[])//da bi se ovo pojavilo u xv6 mora da postoji i u Makefile
{

	char *msg = "hello, world!";
	char buf[512];
	int fdw=open("/dev/kmesg",O_WRONLY);//otvaramo za citanje i pisanje odvojeno
	int fdr=open("/dev/kmesg",O_RDONLY);//otvaramo za citanje i pisanje odvojeno
	printf("prosledjeno za pisanje:%s\n",msg);
	printf("write funkcija vraca:%d,\n",write(fdw,msg,strlen(msg)));
	
    printf("read funkcija vraca: %d\n",read(fdr,buf,512));
	printf("---------------------------------Sadrzaj buffera--------------------------------%s\n",buf);
	printf("-----------------------------------Objasnjenje----------------------------------");
	printf("Buffer je ispunjen karakterima internog buffera i read vraca 511,");
	printf("jer ceo je ispunjen (osim jednog karaktera koji rezervisan za ");
	printf("\\n jer zelim da na kraju predjem u novi red, write vraca");
	printf("-1, jer nije validna operacija, takodje u buffer se upisuje kruzno,");
	printf(" vodeci racuna na pocetak i kraj, na ovaj nacin sam prevazisao problem ");
	printf("prepunjavanja buffera.\n");
	exit();		
}
