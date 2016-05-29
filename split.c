
#include "split.h"


#define LEN_PART_MIN 10
#define LEN_MIN 20

struct voice_signal_list
{
	voice_signal vs;
	struct voice_signal_list *next;
};

int split(int16_t *buffer, unsigned int n, voice_signal **signals)
{
	unsigned int i = 0, j = 0, k = 0, start_pos = 0, len_sig = 0, len_nothing = 0, count = 0;
	char started = 0;
	double means[n / N], sds[n / N];
	double sdmean = 0;
	void **free_list = NULL;
	struct voice_signal_list *head = malloc(sizeof(struct voice_signal_list));
	struct voice_signal_list *now = head;

	head->next = NULL;

	// Calcula os desvios padrão de cada quadro
	for (i = 0; i < n / N; i++)
	{
		means[i] = 0;
		for (j = 0; j < N; j++)
			means[i] += ((int16_t *)buffer)[i * N + j];
		means[i] /= N;
		sds[i] = 0;
		for (j = 0; j < N; j++)
			sds[i] += pow(((int16_t *)buffer)[i * N +j] - means[i], 2);
		sds[i] = sqrt(sds[i]) / (N - 1);
		sdmean += sds[i];
	}
	sdmean /= (n / N);

	// comparação dos desvios-padrão do quadro atual com o desvio padrão médio, para descobrir onde os sinais ocorrem
	for (i = 0; i < n / N; i++)
	{
		//sinal disponivel
		if (sdmean < sds[i])
		{
			//inicializacao sinal start
			if (!started)
			{
				started = 1;
				start_pos = i;
				len_nothing = 0;
			}
			len_sig++;
		}
		//sinal muito fraco
		else
			// (sinal - curto silêncio - sinal) deve ser interpretado como um único sinal
			if (len_sig > LEN_PART_MIN)
			{
				len_nothing = 0;
				len_sig = 0;
			}
			else
			{
				// Duração do silêncio
				len_nothing++;
				if (started && i - LEN_MIN > start_pos && (len_nothing > 2 * LEN_MIN || i == n / N - 1))
				{
					 // Cria uma nova entrada 
					now->next = malloc(sizeof(struct voice_signal_list));
					now = now->next;
					now->next = NULL;
					now->vs.number = (i - start_pos) * N;
					now->vs.buffer = malloc(sizeof(int16_t) * now->vs.number);

					for (j = start_pos; j < i; j++)
					{
						for (k = 0; k < N; k++)
							now->vs.buffer[(j - start_pos) * N + k] = ((int16_t *)buffer)[j * N + k];
					}

					count++;
					started = 0;
				}
			}
	}

	//Preenche o sinal parâmetro com os sinais de voz reconhecidos
	*signals = malloc(sizeof(voice_signal) * count);
	free_list = malloc(sizeof(void *) * count);
	now = head;
	for (i = 0; i < count; i++)
	{
		now = now->next;
		free_list[i] = now;
		(*signals)[i] = now->vs;
	}
	for (i = 0; i < count; i++)
		free(free_list[i]);
	free(free_list);
	free(head);

	return count;
}


