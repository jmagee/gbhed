/* abtranslate
 * -albhed.c
 *   abtranslate function implementations
 *
 * Copyright(c) 2004-2005 Josh Magee <liquidchile@liquidchile.net>
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
#include "cipher_tables.h"
#include <stdio.h>
#include <stdlib.h>

char english_to_albhed(const char letter) {
  register int i;
  for (i = 0; i < MAX_CHARS; i++) {
    if (letter == tableEnglish[i])
      return tableAlbhed[i];
  }
  return (char)EOF;
}

char albhed_to_english(const char letter) {
  register int i;
  for (i = 0; i < MAX_CHARS; i++) {
    if (letter == tableAlbhed[i])
      return tableEnglish[i];
  }
  return (char)EOF;
}

char *albhed_to_phonetics(const char letter) {
  register int i;
  for (i = 0; i < MAX_CHARS; i++) {
    if (letter == tableAlbhed[i])
      return (char *)tablePhonetics[i];
  }
  return NULL;
}

static Toggle processChar(char input, Toggle trans_toggle, LanguageMode mode) {
  if (input == '[')
    trans_toggle = OFF;
  else if (input == ']')
    trans_toggle = ON;

  if (trans_toggle == ON) {
    switch (mode) {
    case ENGLISH:
      printf("%c", english_to_albhed(input));
      break;
    case ALBHED:
      printf("%c", albhed_to_english(input));
      break;
    case PHONETICS:
      printf("%s", albhed_to_phonetics(input));
      break;
    }
  } else {
    printf("%c", input);
  }
  return trans_toggle;
}

void processBuffer(const vector_string *text, LanguageMode language_mode) {
  unsigned int i;
  Toggle trans_toggle = ON;

  for (i = 0; i < text->used; ++i)
    trans_toggle = processChar(text->string[i], trans_toggle, language_mode);
}

void processStdin(LanguageMode language_mode) {
  Toggle trans_toggle = ON;
  signed char input;

  while ((int)(input = (char)getchar()) != EOF)
    trans_toggle = processChar(input, trans_toggle, language_mode);
}

void printHelp(void) {
  printf("Usage: %s [options] string\n", PROGRAM);
  printf("Options:\n");
  printf("   -e, --english\tTranslate from English to Al Bhed\n");
  printf("   -a, --albhed \tTranslate from Al Bhed to English\n");
  printf("   -p, --phonetics\tTranslate from Al Bhed to Phonetics\n");
  printf("   -h, --help	\tDisplay this text\n");
  printf("   -v, --version\tDisplay version information\n");
  printf("   --author	\tDisplay author information\n");
  printf("   --license	\tDisplay license information\n");
  exit(EXIT_SUCCESS);
}

void printVersion(void) {
  printf("%s %.2f\n", PROGRAM, VERSION);
  exit(EXIT_SUCCESS);
}

void printInvalid(void) {
  printf("Invalid option\nTry \"--help\" for more options\n");
  exit(EXIT_FAILURE);
}

void printAuthor(void) {
  printf("%s\n", AUTHORS);
  exit(EXIT_SUCCESS);
}

void printLicense(void) {
  printf("copyright(c) 2004-2006 Josh Magee <liquidchile@liquidchile.net>\n\n");
  printf("This program is free software; you can redistribute it and/or\n");
  printf("modify it under the terms of the GNU General Public License\n");
  printf("as published by the Free Software Foundation; either version 2\n");
  printf("of the License, or (at your option) any later version.\n\n");
  printf("This program is distributed in the hope that it will be useful,\n");
  printf("but WITHOUT ANY WARRANTY; without even the implied warranty of\n");
  printf("MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the\n");
  printf("GNU General Public License for more details.\n\n");
  printf("You should have received a copy of the GNU General Public License\n");
  printf("along with this program; if not, write to the Free Software\n");
  printf("Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA  "
         "02111-1307, USA.\n");
  exit(EXIT_SUCCESS);
}
