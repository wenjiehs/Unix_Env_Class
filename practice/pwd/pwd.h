#include<stdio.h>
#include<stdlib.h>
#include<sys/types.h>
#include<sys/stat.h>
#include<dirent.h>
#include<unistd.h>
#include<string.h>

class FilePath
{
public:
		FilePath(){}
		~FilePath(){}
		
		char * getPath();
		
protected:
		void printPathTo(ino_t this_inode);
		void inum_to_name(ino_t inode_to_find, char * namebuff, int buflen);
		ino_t get_inode(char * fname);
private:
		char path[BUFSIZ];


};
