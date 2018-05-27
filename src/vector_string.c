/* abtranslate
 * -vector_string.c
 *  -vector_string toolkit implementation
 *
 * vector_string is a struct for managing dynamically allocated strings.
 * It is not null terminated, but rather maintains a count of the number
 * of characters.
 *
 * Copyright (c) 2004-2005 Josh Magee <liquidchile@liquidchile.net>
 *
 *
 * This program is free software; you can redistribute it and/or
 * modify it under the terms of the GNU General Public License
 * as published by the Free Software Foundation; either version 2
 * of the License, or (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA  02111-1307, USA.
 */

#include "vector_string.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define INCREASE 50

void append(vector_string *vs, const char *text) {
  register unsigned int i;

  if (vs->used + strlen(text) >= vs->capacity) {
    /*Need to resize*/
    resize(vs);
  }

  for (i = 0; (size_t)i < strlen(text); i++)
    vs->string[vs->used++] = text[i];
}

void append_char(vector_string *vs, const char letter) {
  /*Wrapper for append()*/
  char temp_char[2];
  temp_char[0] = letter;
  temp_char[1] = '\0';

  append(vs, temp_char);
}

void resize(vector_string *vs) {
  register unsigned int i;
  char *temp;

  vs->capacity = vs->capacity + INCREASE;

  temp = (char *)calloc((size_t)vs->capacity, sizeof(char));
  if (temp == NULL) {
    fprintf(stderr, "Error allocating memory.  Cowardly bailing out.\n");
    free(vs->string);
    exit(EXIT_FAILURE);
  }

  for (i = 0; i < vs->used; i++)
    temp[i] = vs->string[i];

  free(vs->string);

  vs->string = temp;
}

void display(const vector_string *vs) {
  register unsigned int i;

  for (i = 0; i < vs->used; i++) {
    if (printf("%c", vs->string[i]) < 0)
      fprintf(stderr, "Outputting Error.\n");
  }
}

void clean(vector_string *vs) {
  free(vs->string);
  vs->string = NULL;
}
