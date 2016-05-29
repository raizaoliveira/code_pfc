
#include "wave.h"



static FILE *f = NULL;
// Conteúdo do arquivo atualmente 
static void *f_buf = NULL;
//cabeçalho WAVE
static char header[45] = "RIFF1234WAVEfmt 12341212123412341212data1234";


unsigned int read_pcm(void **buffer)
{
	unsigned int data_size = *((int *)f_buf + 10);
	*buffer = malloc(data_size);
	memcpy(*buffer, (char *)f_buf + 44, data_size);
	return data_size;
}

int write_pcm(const void *buffer, const unsigned int size, const char *path)
{
	FILE *file = NULL;

	if (path != NULL)
		file = fopen(path, "w");
	else
	{
		rewind(f);
		file = f;
	}
	if (file == NULL)
		return -1;

	prepare_header(size + 44);

	fwrite(header, 44, 1, file);
	fwrite(buffer, size, 1, file);

	if (path != NULL)
		fclose(file);
	return 0;
}

void close_wave(void)
{
	free(f_buf);
	fclose(f);
}

/*
  * Preenche o cabeçalho comparação com os valores válidos, que são especificados em wave.h e o arquivo e bloco de tamanho correto, que é derivado dos parâmetros.
  * (Const unsigned int) tamanho do arquivo
  */
void prepare_header(const unsigned int size)
{
	int values[9] = {size - 8, 16, WAVE_FORMAT, WAVE_CHANNELS, WAVE_SAMPLE_RATE, WAVE_BYTES_PER_SECOND, WAVE_FRAME_SIZE, WAVE_BITS_PER_SAMPLE, size - 44};

	memcpy(header + 4, values, 4);
	memcpy(header + 16, values + 1, 4);
	memcpy(header + 20, values + 2, 2);
	memcpy(header + 22, values + 3, 2);
	memcpy(header + 24, values + 4, 4);
	memcpy(header + 28, values + 5, 4);
	memcpy(header + 32, values + 6, 2);
	memcpy(header + 34, values + 7, 2);
	memcpy(header + 40, values + 8, 4);
}

