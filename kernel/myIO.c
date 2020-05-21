//#include "myIO.h"
#include "types.h"
#include "defs.h"
#include "param.h"
#include "fs.h"
#include "spinlock.h"
#include "sleeplock.h"
#include "file.h"
#include "buf.h"

int nullwrite(struct inode *ip, char *usr_buf, int n){ //nasa funkcija za pisanje
	
	return n; 
}

int nullread(struct inode *ip, char *usr_buf, int n){ //nasa funkcija za citanje
	
	if (ip->minor==1){
		return 0;
	}else{
        for (int i = 0; i < n; i++)
	{
		usr_buf[i]='\0';
	}
		return n;
	}

}



int kmesgwrite(struct inode *ip, char *usr_buf, int n){ //nasa funkcija za pisanje

	return -1; 
}

int kmesgread(struct inode *ip, char *usr_buf, int n){ //nasa funkcija za citanje

	
	int j=0;
	int offstart=(starting+ip->off)%BUF_SZ;
	if(starting==0){
		for (j = offstart; j < ending; j++)
		{
			if(j==n)break;
			usr_buf[j]=localbuf[j];
		}
		
	}else{
		
		int i=offstart;
		while(i!=ending-1){
			if(i==BUF_SZ){
				i=0;
			}
			if(j==n)break;
			usr_buf[j]=localbuf[i];
			i++;
			j++;
		}
	}
	return (j);

}

int rand=42;
#define RNG_SZ 512
char randbuf[RNG_SZ];

int randomwrite(struct inode *ip, char *usr_buf, int n){ //nasa funkcija za pisanje
	
	int my_n = n;//n predstavlja koliko slova treba da se ispise

	if (my_n > RNG_SZ-1)
	{
		my_n = RNG_SZ;
	}
	int i;

	for (i = 0; i < my_n; i++)
	{
		rand += usr_buf[i] +ticks+i;
		rand%=256;
		randbuf[i] = rand;
	}
	
	return n; 
}
int randomread(struct inode *ip, char *usr_buf, int n){ //nasa funkcija za citanje
	
	int my_n = n;
	if (my_n > RNG_SZ-1)
	{
		my_n = RNG_SZ;
	}

	for (int i = 0; i < my_n; i++)
	{
		rand += usr_buf[i] +ticks+i;
		rand%=256;
		randbuf[i] = rand;
	}

		for (int i = 0; i <n; i++)
	{
		usr_buf[i] = randbuf[i];
	}


	return n;

}

int l;
struct buf *b;
int initialized=0;

int diskwrite(struct inode *ip, char *usr_buf, int n){ //nasa funkcija za pisanje
	int my_n = n;//n predstavlja koliko slova treba da se ispise

	if(initialized==0){
		b=bread(ip->dev,0);
		initialized=1;
	}

	int offset=ip->off;
	while(offset>BSIZE){
		b=b->next;
		offset-=BSIZE;
	}

	if (my_n > BSIZE-1)
	{
		my_n = BSIZE;
	}
	int i;

	for (i = 0; i < my_n; i++)
	{
		if(i+offset==n)break;
		b->data[i+offset] = usr_buf[i];
	}
	l=i;
	return n; 
}
int diskread(struct inode *ip, char *usr_buf, int n){ //nasa funkcija za citanje
	if(initialized==0){
		b=bread(ip->dev,0);
		initialized=1;
	}

	int offset=ip->off;
	while(offset>BSIZE){
		b=b->next;
		offset-=BSIZE;
	}

	int my_n = l;

	if(my_n>BSIZE-1){
		my_n=BSIZE;
	}

	int j=offset;
	for (int i = 0; i < my_n; i++)
	{
		if(j==n||i==n)break;
		usr_buf[i] = b->data[j];
		j++;
	}

	offset=ip->off;
	while(offset>BSIZE){
		b=b->prev;
		offset-=BSIZE;
	}

	//brelse(b);
	return my_n;

}