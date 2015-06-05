#include<stdio.h>
#include<utmp.h>
#include<unistd.h>
#include<fcntl.h>
#include<time.h>

#define SHOWHOST
#define UTMPNULL ((struct utmp *) NULL)
#define UTMPLEN sizeof(struct utmp)
#define NRECS 16

static char utmp_buff[ NRECS * UTMPLEN];
static int num_recs;
static int cur_recs;
static int fd_utmp = -1;

int utmp_open(char* name)
{
	fd_utmp = open(name, O_RDONLY);
	cur_recs = num_recs = 0;
	return fd_utmp;
}

int utmp_reload()
{
		int amt_read;
		amt_read = read(fd_utmp, utmp_buff, NRECS * UTMPLEN);
		num_recs = amt_read/UTMPLEN;
		cur_recs = 0;
		return num_recs;
}

void utmp_close()
{
		if(fd_utmp != -1)
				close(fd_utmp);
}

struct utmp * utmp_next()
{
	struct utmp *arm;
	if(fd_utmp == -1)
			return UTMPNULL;
	if(cur_recs == num_recs && utmp_reload() == 0)
			return UTMPNULL;

	arm = (struct utmp *) &utmp_buff[cur_recs * UTMPLEN];
	cur_recs ++;
	return arm;
}

void show_info( struct utmp *utbufp);

int main()
{
		struct utmp *utbufp, utmp_next();
		if(utmp_open(UTMP_FILE) == -1)
		{
				perror(UTMP_FILE);
				exit(1);
		}
		while((utbufp = utmp_next()) != UTMPNULL)
				show_info(utbufp);
		utmp_close();
		return 0;

}

void show_info( struct utmp *utbufp)
{
		if(utbufp->ut_type != USER_PROCESS)
				return;
		printf("% -8.8s", utbufp->ut_name);
		printf(" ");
		
		printf("% -8.8s", utbufp->ut_line);
		printf(" ");

		printf("%12.12s", ctime(&utbufp->ut_time) + 4);
		printf(" ");
#ifdef SHOWHOST
		printf("(%s)", utbufp->ut_host);
#endif
		printf("\n");
}
