 
#include <stdio.h>
#include <sys/types.h>
#include <dirent.h>
#include <errno.h>
#include <string.h>
#include <stdint.h>
#include <stdlib.h>
#include <stdbool.h>
// max PATH length in linux
#define MAX_PATH 4096 + 1
// max file NAME length in linux
#define NAME_MAX 255

//start index of the current file/dir name
int8_t PATH_SLASH_INDEX = -1;
char FILTERNAME[NAME_MAX] = "";
struct options {
	bool look_for_name;
	bool wildcard_used;

};

//allocates a new path string and returns it. (leaks a lot of mem🙈🙈, prob can be fixed easily)
char *joinPath(char path[], char dirname[]) {
	char *joinedPath = (char*) malloc(MAX_PATH * sizeof(char));
	int pathLen = strlen(path);
	path[pathLen] = '/';
	
	strcpy(joinedPath, path);
	strcpy(joinedPath + pathLen + 1, dirname);

	path[pathLen] = '\0';
	PATH_SLASH_INDEX = pathLen;
	return joinedPath;
}

//returns if the dir/file name matches the one that the user wants
bool compareNames(char thingName[]){
	if (strcmp(thingName, FILTERNAME) == 0) return true;
	else return false;
}

//recursively parses through every file in the directory 
int dirrecursor(char dirpath[]){

	DIR * dp;
	struct dirent * ep;

	dp = opendir(dirpath);
	if (dp != NULL)
	{
		while ((ep = readdir(dp)))
		{
			if (ep->d_type == DT_DIR && (strcmp(ep->d_name, ".") != 0 && strcmp(ep->d_name, "..") != 0))
			{
				//if is a dir
				//printf("%s/%s/\t- from recursed\n", dirpath, ep->d_name);
				printf("%s/%s\n", dirpath, ep->d_name);
				//printf("with dirpath: %s and dirname %s\n", dirpath, ep->d_name);
				dirrecursor(joinPath(dirpath, ep->d_name));
					// strncpy(cwd + cwdLen + 1, ep->d_name, strlen(ep->d_name) + 1);
					// cwd[cwdLen] = '/';
					// printf("\trecursing to \'%s\': %s\n", ep->d_name, cwd);
					// probably some recursor dirhandler(ep, cwd, startingStr);
					// cwd[cwdLen] = '\0';
			}
			else if (ep->d_type == DT_REG | ep->d_type == DT_LNK)
			{
			 	//printf("SPECIAL: %s | d_type = %d\n", ep->d_name, ep->d_type);
				printf("%s/%s\n", dirpath, ep->d_name);
			}
			if (compareNames(ep->d_name)) printf("\tFUCKING FOUND IT:%s/%s",dirpath, ep->d_name );
		}

		closedir(dp);
	}
	else {
		// an error or there is no entry in the dir ig idk
		printf("Couldnt open directory '%s', terminating. Fournir un fichier no droit s'il vous plaît\n", dirpath);
	}

	return 0;
}

int main(int argc, char *argv[])
{
	/*TODOS
	   -read about the flags that can be passed to opendir, such as O_NOATIME
	   -optimize with seekdirwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwww
	*/

	// directory stream
	DIR * dp;
	//
	struct dirent * ep;

	char cwd[MAX_PATH] = "./output";
	if (argc == 3 )
	{
		strncpy(cwd, argv[1], MAX_PATH);
		strncpy(FILTERNAME, argv[2], NAME_MAX);
	}
	else puts("Fournir un fichier and a non regex filter, s'il vous plaît");

	int cwdLen = strlen(cwd);
	puts(cwd);

	dirrecursor(cwd);
	return 0;
}
