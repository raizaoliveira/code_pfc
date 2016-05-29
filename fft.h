
#ifndef __FFT_H__
#define __FFT_H__


#include <math.h>
#include <stdlib.h>

typedef struct
{
		double real;
		double imag;
}comp;

void fft(comp *time, comp *freq, unsigned int n);

#endif
