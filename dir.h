#ifndef __DIR_H__
#define __DIR_H__
#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <dirent.h>
#include <stdint.h>

#include <pthread.h>
#include <alsa/asoundlib.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/stat.h>
#include <sys/types.h>


void ls();
int find_dir();

void list();

#endif
