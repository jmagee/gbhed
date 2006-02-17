/*
 *
 *
 */

#include "translation_fork.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>
#include <gtk/gtk.h>

char* translation_fork(const char *string, int n, const int mode) {
	if(string != NULL) {
		char *buffer = (char*)calloc((size_t)n, sizeof(char*));
		if(buffer == NULL) { /*something*/ }

		pid_t pid;
		int pipe_out[2];
		int pipe_in[2];

		pipe(pipe_out);
		pipe(pipe_in);

		fprintf(stderr, "hi SEX SEX SEX!");

		switch (pid = fork()) {
			case -1:
				g_print("Error forking translation process\n");
				free(buffer);
				return (char*)NULL;
			case 0:
				close(STDIN_FILENO);
				close(pipe_in[1]);
				dup(pipe_in[0]);
				close(pipe_in[0]);

				close(STDOUT_FILENO);
				close(pipe_out[0]);
				dup(pipe_out[1]);
				close(pipe_out[1]);

				fprintf(stderr, "WHAT?!?!\n");

				free(buffer);
				if(mode == 1) {
					fprintf(stderr, "nipple?!?!\n");
					execlp("abtranslate", "-e", "-e", NULL);

				}else if(mode == 2) {
					execlp(ABTRANSLATE, "-a", NULL);

				}else {
					execlp(ABTRANSLATE, "-p", NULL);

				}
				g_print("Error executing %s\n", ABTRANSLATE);
				fprintf(stderr, "ERROR!!!!!!!!'\n");
				exit(EXIT_FAILURE);

			default:

				close(pipe_in[0]);
				close(pipe_out[1]);

				write(pipe_in[1], (void*)string,
						(size_t)strlen(string)+1);
				close(pipe_in[1]);
				wait(NULL);
				read(pipe_out[0], (void*)buffer, (size_t)n);

				fprintf(stderr, "HI!\n");
				return buffer;
		}
	}else {
		return NULL;
	}
}
