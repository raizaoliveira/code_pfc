/*
Biblioteca wave.h contendo as especificacoes do formato de arquivo wave.
Autores: Raiza Arteman e willian Souza
Curso de Ciência da Computação
Universidade estadual de Mato Grosso do Sul - UEMS
*/
#ifndef __WAVE_H__
#define __WAVE_H__


#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/stat.h>
#include <sys/types.h>


/*
Definicoes de formato wave.
entrada PCM com um canal
taxa de gravação de 44100 (equivalente a qualidade de CDs)
  */
#define WAVE_FORMAT 0x001 //PCM
#define WAVE_CHANNELS 1
#define WAVE_SAMPLE_RATE 44100
#define WAVE_BITS_PER_SAMPLE 16
#define WAVE_FRAME_SIZE ((WAVE_BITS_PER_SAMPLE + 7) >> 3 * WAVE_CHANNELS) //(bits/sample + 7) / 8 * channels
#define WAVE_BYTES_PER_SECOND (WAVE_SAMPLE_RATE * WAVE_FRAME_SIZE) //framesize * samplerate

/*

  * (0) Sucesso
  * (-1) O arquivo não pode ser aberto
  * (-2) Cabeçalho inválido
  
int open_wave(const char *path);*/



unsigned int read_pcm(void **buffer);


int write_pcm(const void *buffer, const unsigned int size, const char *path);


void close_wave(void);

void prepare_header(const unsigned int size);


#endif
