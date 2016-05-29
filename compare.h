
#ifndef __COMPARE_H__
#define __COMPARE_H__

#include "frame.h"


/*
  * Compara os dois determinados vectores de expressões MFCC e retorna um valor,
  * Indicando a correlação. Quanto menor for essa, mais semelhante são os dois vectores.
  * <<< >>> ENTRADA
  * (Mfcc_frame) mfcc_frames1 O primeiro vetor com as características MFCC
  * (Unsigned int) n1 O comprimento do segundo vector
  * (Mfcc_frame) mfcc_frames2 O segundo vector com as características MFCC
  * (Unsigned int) n2 O comprimento do segundo vector
  * <<< >>> OUTPUT
  * (Duplo), indicando o valor de correlação dos dois vectores
  */
double compare(mfcc_frame *mfcc_frames1, unsigned int n1, mfcc_frame *mfcc_frames2, unsigned int n2);

#endif
