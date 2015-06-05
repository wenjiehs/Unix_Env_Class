#include<stdio.h>
#include<fcntl.h>
#include<unistd.h>

#define LINEMAX 512
void seeFile(FILE *fd);
int main(int argc, char *argv[])
{
		char buff[LINEMAX];

		if(argc == 1)
		{
				while(fgets(buff, LINEMAX, stdin))
				{
						fputs(buff, stdout);
				}
		}
		FILE * fd;
		while(--argc)
		{
				if((fd = fopen(*(++argv), "r")) != NULL)
						seeFile(fd);
		}
		return 0;
}

void seeFile(FILE* fd)
{
		char buff[LINEMAX];
		while(fgets(buff, LINEMAX, fd))
				fputs( buff, stdout);
}
