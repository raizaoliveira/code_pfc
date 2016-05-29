#include "dir.h"

int find_dir()
{
    char* pPath;
    pPath = getenv ("PATH");
    if (pPath!=NULL)
    {
            printf ("diretorio atual: %s \n",pPath);
            return 1;
    }
    else return 0;


}


void list()
{
	system("ls palavras");
}


void ls()
 {
    char *curr_dir = NULL;
    DIR *dp = NULL;
    struct dirent *dptr = NULL;
    unsigned int count = 0;

    curr_dir = getenv("PWD");
    if(NULL == curr_dir)
        printf("\n ERRO : dir trabalho\n");

    dp = opendir((const char*)curr_dir);
    if(NULL == dp)
        printf("\n ERROR : dir trabalho\n");

    printf("\n");

    for(count = 0; NULL != (dptr = readdir(dp)); count++)
   		printf("%s   ", dptr->d_name);
      
    printf("\n %u", count);

 }

