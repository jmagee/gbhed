/* translation_fork.c
 *  -al bhed cipher program
 *  -translation command forker
 *
 * copyright (c) 2005 Josh Magee <liquidchile@liquichile.net>
 *
 *  This program is free software; you can redistribute it and/or
 *  modify it under the terms of the GNU General Public License
 *  as published by the Free Software Foundation; either version 2
 *  of the License, or (at your option) any later version.
 *
 *  This program is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *  GNU General Public License for more details.
 *
 *  You should have received a copy of the GNU General Public License
 *  along with this program; if not, write to the Free Software
 *  Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA  02111-1307, USA.
 */

#include "translation_fork.h"
#include <errno.h>
#include <gtk/gtk.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>

char *translation_fork(const char *string, int n, const int mode) {
  if (string != NULL) {
    char *buffer;
    int len;
    pid_t pid;
    int pipe_out[2];
    int pipe_in[2];

    /* Phoentics mode requires a larger n, as 1 character
     *  yields 3 after translation */
    if (mode == 3)
      len = n * 3;
    else
      len = n;

    buffer = (char *)calloc((size_t)len, sizeof(char *));
    if (buffer == NULL) {
      g_print("Error allocation emory in translation_fork");
      exit(EXIT_FAILURE);
    }

    pipe(pipe_out);
    pipe(pipe_in);

    switch (pid = fork()) {
    case -1:
      g_print("Error forking translation process\n");
      free(buffer);
      return t_error();

    case 0:
      close(STDIN_FILENO);
      close(pipe_in[1]);
      dup(pipe_in[0]);
      close(pipe_in[0]);

      close(STDOUT_FILENO);
      close(pipe_out[0]);
      dup(pipe_out[1]);
      close(pipe_out[1]);

      free(buffer);
      if (mode == 1) {
        execlp(ABTRANSLATE, "-e", "-e", NULL);

      } else if (mode == 2) {
        execlp(ABTRANSLATE, "-a", "-a", NULL);

      } else {
        execlp(ABTRANSLATE, "-p", "-p", NULL);
      }
      g_print("Error executing %s\n", ABTRANSLATE);
      exit(EXIT_FAILURE);

    default:

      close(pipe_in[0]);
      close(pipe_out[1]);

      while (write(pipe_in[1], (void *)string, n) == -1) {
        if (errno == EINTR)
          continue;
        else {
          g_print("Error writting to pipe.");
          return t_error();
        }
      }

      close(pipe_in[1]);
      wait(NULL);

      while (read(pipe_out[0], (void *)buffer, (size_t)len) == -1) {
        if (errno == EINTR)
          continue;
        else {
          g_print("Error reading from pipe.");
          return t_error();
        }
      }

      close(pipe_out[0]);

      return buffer;
    }
  } else {
    return t_error();
  }
}

char *t_error(void) {
  /* Return a translation error string */
  char *error = (char *)calloc(19, sizeof(char));
  if (!error) {
    g_print("Error allocation emory in t_error()");
    exit(EXIT_FAILURE);
  }

  strcpy(error, "Error translating.\n");

  return error;
}
