#include<stdio.h>
#include<dirent.h>
#include<sys/stat.h>
#include<sys/types.h>
#include<string.h>
#include<pwd.h>
#include<grp.h>
#include<time.h>
class ListFile
{
public:
		ListFile(char *filename) 
		{
				strcpy(pfilename, filename);
		}
		~ListFile(){}
		void setFile(char *file)
		{
				strcpy(pfilename, file);
		}
		void ls();

protected:
		void dostat(char *file);
		void show_file_info(FILE *fp,char * name,struct stat * info_p);
		void mode_to_letters(int mode, char str[]);
		char * uidToName(uid_t uid);
		char * gidToName(gid_t gid);
private:
		char pfilename[256];


};
