
#include "frame.h"

/*frequencias centrais em Hz*/
static int frequency[QTD_FILTER] = {150, 200, 250, 300, 350, 400, 450,
				490, 560, 640, 730, 840, 960, 1100,
				1210, 1340, 1480, 1640, 1810, 2000,
				2250, 2520, 2840, 3190, 3580, 4020};


void mfcc_features(frame *frames, unsigned int n, mfcc_frame *mfcc_frames)
{

	unsigned int i = 0, j = 0, k = 0;
	double out_filter[QTD_FILTER];
	double filterSpectrum[QTD_FILTER][N] = {{0}};
	double c0 = sqrt(1.0 / QTD_FILTER);
	double cn = sqrt(2.0 / QTD_FILTER);
	double pi = 4 * atan(1.0);

	for (i = 0; i < QTD_FILTER; i++)
	{
		double maxFreq = 0, minFreq = 0, centerFreq = 0;

		if (i == 0)
			minFreq = frequency[0] - (frequency[1] - frequency[0]);
		else
			minFreq = frequency[i - 1];
		centerFreq = frequency[i];

		if (i == QTD_FILTER - 1)
			maxFreq = frequency[QTD_FILTER - 1] + (frequency[QTD_FILTER - 1] - frequency[QTD_FILTER - 2]);
		else
			maxFreq = frequency[i + 1];

		for (j = 0; j < N; j++)
		{
			double freq = 1.0 * j * WAVE_SAMPLE_RATE / N;
			if (freq > minFreq && freq < maxFreq)
				if (freq < centerFreq)
					filterSpectrum[i][j] = 1.0 * (freq - minFreq) / (centerFreq - minFreq);
				else
					filterSpectrum[i][j] = 1 - 1.0 * (freq - centerFreq) / (maxFreq - centerFreq);
			else
				filterSpectrum[i][j] = 0;
		}
	}

	/*Calcula os coeficientes MFCC para cada quadro.*/
	for (i = 0; i < n; i++)
	{
		for (j = 0; j < QTD_FILTER; j++)
		{
			out_filter[j] = 0;
			for (k = 0; k < N; k++)
				out_filter[j] += frames[i].magnitudes[k] * filterSpectrum[j][k];
		}
		for (j = 0; j < N_MFCC; j++)
		{
			mfcc_frames[i].features[j] = 0;

			for (k = 0; k < QTD_FILTER; k++)
				mfcc_frames[i].features[j] += log(fabs(out_filter[k]) + 1e-10) * cos((pi * (2 * k + 1) * j) / (2 * QTD_FILTER));

			if (j)
				mfcc_frames[i].features[j] *= cn;
			else
				mfcc_frames[i].features[j] *= c0;
		}
	}
}


unsigned int make_frames_hamming(int16_t *buffer, unsigned int n, frame **frames)
{
	unsigned int id_frame = (n / (N - OVERLAY)) - 1;
	comp *result = malloc(sizeof(comp) * id_frame * N);
	comp *data = malloc(sizeof(comp) * id_frame * N);
	unsigned int pos = 0, i = 0, j = 0;
	double pi = 4 * atan(1.0);

	*frames = malloc(sizeof(frame) * id_frame);
	for (i = 0; i < id_frame; i++)
	{
		pos = (i + 1) * (N - 64);
		for (j = 0; j < N; j++)
		{
			data[i * N + j].real = buffer[pos + j] * (0.54 + 0.46 * cos(2 * pi * (j - N / 2) / N));
			data[i * N + j].imag = 0;
		}
	}
	for (i = 0; i < id_frame; i++)
		fft(data + i * N, result + i * N, N);

	for (i = 0; i < id_frame; i++)
		for (j = 0; j < N; j++)
			(*frames)[i].magnitudes[j] = sqrt(pow(result[i * N + j].real, 2) + pow(result[i * N + j].imag, 2));

	for (i = 0; i < id_frame; i++)
	{
		double sig = 0;
		for (j = 0; j < N; j++)
			sig += (*frames)[i].magnitudes[j];
		sig /= N;
		for (j = 0; j < N; j++)
			(*frames)[i].magnitudes[j] /= sig;
	}
	free(data);
	free(result);
	return id_frame;
}


