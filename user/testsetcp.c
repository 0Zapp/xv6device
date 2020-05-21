#include "kernel/types.h"
#include "kernel/stat.h"
#include "user.h"
#include "kernel/fcntl.h" //ovde se nalazi rdwr

int main(int argc, char *argv[]) //da bi se ovo pojavilo u xv6 mora da postoji i u Makefile
{
	int x=3;
	int y=10;

	printf("kordinate prosledjene funkciji: x:%d,y:%d\n",x,y);

	setcp(x,y);
	exit();
}
