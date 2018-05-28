/* abtranslate
 *  -abtranslate.c
 *   Main body of program
 *
 * Copyright (c) 2004-2005 Josh Magee <liquidchile@liquidchile.net>
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

#include "albhed.h"
#include "vector_string.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(int argc, char *argv[]) {

  register int i;
  LanguageMode language_mode = ENGLISH;
  vector_string untranslated;

  untranslated.string = NULL;
  untranslated.used = 0;
  untranslated.capacity = 0;

  if (argc <= 1) {
    printInvalid();

  } else {
    for (i = 1; i < argc; i++) {
      if (i == 1) {
        /*Examine the command line switch*/
        if (strcmp(argv[i], "-e") == 0 || strcmp(argv[i], "--english") == 0) {
          /*English*/
          language_mode = ENGLISH;

        } else if (strcmp(argv[i], "-a") == 0 ||
                   strcmp(argv[i], "--albhed") == 0) {
          /*Al Bhed*/
          language_mode = ALBHED;

        } else if (strcmp(argv[i], "-p") == 0 ||
                   strcmp(argv[i], "--phonetics") == 0) {
          /*Phonetics*/
          language_mode = PHONETICS;

        } else if (strcmp(argv[i], "-h") == 0 ||
                   strcmp(argv[i], "--help") == 0) {
          printHelp();

        } else if (strcmp(argv[i], "-v") == 0 ||
                   strcmp(argv[i], "--version") == 0) {
          printVersion();

        } else if (strcmp(argv[i], "--authors") == 0 ||
                   strcmp(argv[i], "--author") == 0) {
          printAuthor();

        } else if (strcmp(argv[i], "--license") == 0) {
          printLicense();

        } else {
          printInvalid();
        }

        if (argc == 2) {
          /* Only one argument means we are reading
           * from stdin instead of command line.*/
          processStdin(language_mode);
          break;
        }

      } else {
        append(&untranslated, argv[i]);
        append(&untranslated, " ");
        /* Add a newline character at the end of text
         * from command line for proper outputing*/
        if (i == argc - 1)
          append(&untranslated, "\n");
      }
    }

    processBuffer(&untranslated, language_mode);

    clean(&untranslated);
  }
  return 0;
}
