#include"pwd.h"

char* FilePath::getPath()
{
		printPathTo(get_inode("."));
		return path;	
}

void FilePath::printPathTo(ino_t this_inode)
{
		ino_t my_inode;
		char its_name[BUFSIZ];
		if( get_inode("..") != this_inode)
		{
				chdir("..");
				inum_to_name(this_inode, its_name, BUFSIZ);
				my_inode = get_inode(".");
				printPathTo(my_inode);
				printf("/%s", its_name);
		}
		strcpy(path, its_name);
}

void FilePath::inum_to_name(ino_t inode_to_find, char *namebuff, int buflen)
{
		DIR *dir_ptr;
		struct dirent *direntp;

		dir_ptr = opendir(".");
		if(dir_ptr == NULL)
		{
			perror(".");
			exit(0);
		}
		while((direntp = readdir(dir_ptr)) != NULL)
		{
				if(direntp->d_ino == inode_to_find)
				{
						strncpy(namebuff, direntp->d_name, buflen);
						namebuff[buflen - 1] = '\0';
						closedir(dir_ptr);
						return;
				}
		}
		fprintf(stderr, "error looking for inum %d \n", inode_to_find);
		exit;
}
ino_t FilePath::get_inode(char * fname)
{
		struct stat info;
		if(stat(fname, &info) == -1)
		{
				fprintf(stderr, "cannot stat");
				perror(fname);
				exit(1);
		}
		return info.st_ino;
}


int main(int argc, char *argv[])
{
		FilePath path;
		printf("%s/n", path.getPath());
		return 0;
}
