#include<stdio.h>
#include<dirent.h>

void do_ls(char path[]);

int main(int argc, char *argv[])
{
		if(argc == 1)
				do_ls(".");
		else
				while(--argc)
				{
						printf("%s:\n", *(++argv));
						do_ls(*argv);
				}
}


void do_ls(char path[])
{
		DIR *dir;
		struct dirent  *direntp;
		if((dir = opendir(path)) == NULL)
				fprintf(stderr ,"ls1 : cannot open %s\n",path);
		else
		{
				while((direntp = readdir(dir)) != NULL)
						printf("%s\n", direntp->d_name);
				closedir(dir);
		}
}
