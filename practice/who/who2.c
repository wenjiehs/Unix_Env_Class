#include<stdio.h>
#include<utmp.h>
#include<unistd.h>
#include<fcntl.h>
#include<time.h>
#define SHOWHOST
void show_info( struct utmp *utbufp);

int main()
{
		struct utmp current_record;
		int utmp_fd;
		int reclen = sizeof(current_record);

		if((utmp_fd = open(UTMP_FILE, O_RDONLY)) == -1)
		{
				perror(UTMP_FILE);
				exit(1);
		}
		while( read(utmp_fd,&current_record, reclen) == reclen)
				show_info(&current_record);
		close(utmp_fd);
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
