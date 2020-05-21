//moj header file za citanje i pisanje device fajlova
int nullwrite(struct inode *ip, char *usr_buf, int n);//ove funkcije ce da budu javne
int nullread(struct inode *ip, char *usr_buf, int n);
int kmesgwrite(struct inode *ip, char *usr_buf, int n);
int kmesgread(struct inode *ip, char *usr_buf, int n);
int randomwrite(struct inode *ip, char *usr_buf, int n);
int randomread(struct inode *ip, char *usr_buf, int n);
int diskwrite(struct inode *ip, char *usr_buf, int n);
int diskread(struct inode *ip, char *usr_buf, int n);
