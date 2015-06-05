#include"ls2.h"
void ListFile::ls()
{
		DIR *dir_ptr;
		struct dirent *direntp;
		
		if((dir_ptr = opendir(pfilename)) == NULL)
				fprintf(stderr, "ls2: cannot open %s\n", pfilename);
		else
		{
				while((direntp = readdir(dir_ptr)) != NULL)
						dostat(direntp->d_name);
				closedir(dir_ptr);
		}

}

void ListFile::dostat(char * file)
{
		struct stat info;
		if(stat(file, &info) == -1)
				perror(file);
		else
				show_file_info(stdout, file, &info);
}

void ListFile::show_file_info(FILE * fp, char *file, struct stat * info)
{
		char modeStr[11];
		mode_to_letters(info->st_mode, modeStr);
		fprintf(fp, "%s ", modeStr);
		fprintf(fp, "%4d ", (int)(info->st_nlink));
		fprintf(fp, "%-8s ", uidToName(info->st_uid));
		fprintf(fp, "%-8s ", gidToName(info->st_gid));
		fprintf(fp, "%8ld", (long)(info->st_size));
		fprintf(fp, "%.12s ", 4 + ctime(&info->st_mtime));
		fprintf(fp, "%s\n", file);

}

void ListFile::mode_to_letters(int mode, char str[])
{
		strcpy(str, "----------");
		if(S_ISDIR(mode)) str[0] = 'd';
		if(S_ISCHR(mode)) str[0] = 'c';
		if(S_ISBLK(mode)) str[0] = 'b';

		if(mode & S_IRUSR) str[1] = 'r';
		if(mode & S_IWUSR) str[2] = 'w';
		if(mode & S_IXUSR) str[3] = 'x';

		if(mode & S_IRGRP) str[4] = 'r';
		if(mode & S_IWGRP) str[5] = 'w';
		if(mode & S_IXGRP) str[6] = 'x';

		if(mode & S_IROTH) str[7] = 'r';
		if(mode & S_IWOTH) str[8] = 'w';
		if(mode & S_IXOTH) str[9] = 'x';

}

char * ListFile::uidToName(uid_t uid)
{
		struct passwd  *pw_ptr;
		static char numstr[10];
		
		if((pw_ptr = getpwuid(uid)) == NULL)
		{
				sprintf(numstr, "%d", uid);
				return numstr;
		}
		else
				return pw_ptr->pw_name;
}

char * ListFile::gidToName(gid_t gid)
{
		struct group *grp_ptr;
		static char numstr[10];
		
		if((grp_ptr = getgrgid(gid)) == NULL)
		{
				sprintf(numstr,"%d", gid);
				return numstr;
		}
		else
				return grp_ptr->gr_name;
}

int main(int argc ,char * argv[])
{
		ListFile LF(".");
		if(argc == 1)
				LF.ls();
		else
		{
				while(--argc)
				{
						printf("%s\n",*(++argv));
						LF.setFile(*argv);
						LF.ls();
				}
		}

}
