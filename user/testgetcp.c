#include "kernel/types.h"
#include "kernel/stat.h"
#include "user.h"
#include "kernel/fcntl.h"//ovde se nalazi rdwr

int
main(int argc, char *argv[])//da bi se ovo pojavilo u xv6 mora da postoji i u Makefile
{

	int x;
	int y;
	int* xp=&x;//ovako linkujes pointer i promenljivu pravilno
	int* yp=&y;
	getcp(xp,yp);
	printf("kordinate kursora su:x=%d,y=%d\n",x,y);
	exit();
}
