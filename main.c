
#include "link.h"
#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <stdlib.h>
#include <sys/types.h>
#include <dirent.h>
#include <stdint.h>


int main(void)
{
	char opt;
	do
	{
		do{
			printf("a - inserir palavra\nb - listar palavras\nc - reconhecer\nd - sair: ");
			scanf(" %c", &opt);
		}while(opt < 'a' || opt > 'd');

		switch (opt)
		{
			case 'a':
				usleep(200000);
				get_word(0);
				break;
			case 'b':
				system("ls palavras");
				break;
			case 'c':
				usleep(200000);
				get_word(1);
				break;
		}
	}
	while (opt != 'd');
	return 0;
}


