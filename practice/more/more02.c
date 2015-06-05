#include <stdio.h>

#define PAGELEN 24
#define LINELEN 512

void do_more( FILE * fp);
int see_more( FILE * fp);

int main(int argc, char *argv[])
{
		FILE *fp;
		if( argc == 1)
				do_more(stdin);
		else
				while( --argc)
				{
						if((fp = fopen(*(++argv), "r")) != NULL)
						{
								do_more(fp);
								fclose(fp);
						}
						else 
								exit(1);
				}
		return 0;
}

void do_more( FILE *fp)
{
		char line[LINELEN];
		int numOfLine = 0;
		int see_more(FILE *fp), reply;
		FILE *fp_tty;
		if((fp_tty = fopen("/dev/tty", "r")) == NULL)
				exit(1);
		while( fgets(line, LINELEN, fp))
		{
				if(numOfLine == PAGELEN)
				{
						reply = see_more(fp_tty);
						if(reply == 0)
								break;
						numOfLine -= reply;
				}
				if(fputs(line ,stdout) == EOF)
						exit(1);
				numOfLine++;
		}
}

int see_more(FILE *fp)
{
	int c;
	printf("\033[7m more? \033[m");
	while((c = getc(fp)) != EOF)
	{
			if(c == 'q')
					return 0;
			if(c == ' ')
					return PAGELEN;
			if(c == '\n')
					return 1;
	}
	return 0;
}
