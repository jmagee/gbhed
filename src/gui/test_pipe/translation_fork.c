/* translation_fork.c
 *
 */

#include "bad_alloc.h"

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>


char* translation_fork(const char *text, int n, int mode) {
	if(string != NULL) {
		char *buffer;
		pid_t pid;
		int outbound[2];
		int inbound[2];

		buffer = (char*)calloc((size_t)n, sizeof(text));
		if(buffer == NULL) bad_alloc("translation_fork()");

		switch(pid = fork()) {
			case -1:
				g_print("Error forking translation process.\n");
				free(buffer);
				return (char*)NULL;

			case 0:



