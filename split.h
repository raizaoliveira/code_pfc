/*Biblioteca split.h 
Autores: Raiza Arteman e Wilian Souza
Curso de Ciência da Computação
Universidade estadual de Mato Grosso do Sul - UEMS
*/


#ifndef __SPLIT_H__
#define __SPLIT_H__

#include "frame.h"


typedef
	struct
	{
		int16_t *buffer;/*inteiro de 16 bits*/
		unsigned int number;
	} voice_signal;

int split(int16_t *buffer, unsigned int n, voice_signal **signals);

#endif
