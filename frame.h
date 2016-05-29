
#ifndef __FRAME_H__
#define __FRAME_H__

#include <sys/types.h>
#include "fft.h"
#include "inaudio.h"


#define N 512
#define QTD_FILTER 26
#define N_MFCC QTD_FILTER 
#define OVERLAY 64
/*
  * Estrutura constituindo um quadro.
  * Os valores no quadro são as intensidades da representação da função no domínio da frequência.
  * Magnitudes (duplo), as intensidades dos valores Fourier transformado.
  */
typedef struct
	{
		double magnitudes[N];
	} frame;

typedef struct
	{
		double features[N_MFCC];
	} mfcc_frame;


unsigned int make_frames_hamming(int16_t *buffer, unsigned int n, frame **frames);

void mfcc_features(frame *frames, unsigned int n, mfcc_frame *mfcc_frames);

void set_filters();

#endif


