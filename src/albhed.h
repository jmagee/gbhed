/* abtranslate
 * -albhed.h
 *  -constants and function prototypes used by abtranslate
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

#ifndef ALBHED_H
#define ALBHED_H

#include "vector_string.h"

typedef enum {
  ENGLISH,
  ALBHED,
  PHONETICS,
} LanguageMode;

typedef enum {
  OFF = 0,
  ON,
} Toggle;

#define PROGRAM "abtranslate"
#define VERSION 0.09
#define AUTHORS "Josh Magee <magee.joshua@yahoo.com>"

char english_to_albhed(const char letter);
/* Purpose: Translate an english character to an al bhed
 * character.
 * Pre-conditions: letter should be the letter to be translated.
 * Post-conditions: Returns the corrosponding Al Bhed character.
 * Returns EOF on error.*/

char albhed_to_english(const char letter);
/* Purpose: Translate an al bhed character to english.
 * Pre-conditions: letter should be the letter to be translated.
 * Post-conditions: Returns the corrosponding English character.
 * Returns EOF on error.*/

const char *albhed_to_phonetics(const char letter);
/* Purpose: Translate an al bhed character to phonetics.
 * Pre-conditions: letter should be the letter to be translated.
 * Post-conditions: Returns a pointer to the corrosponding phonetic
 * string.  Returns NULL on error.*/

void processBuffer(const vector_string *text, LanguageMode language_mode);
/* Purpose:  Translate a vector_string according to the mode. */

void processStdin(LanguageMode language_mode);
/* Purpose:  Translate a standard input according to mode. */

void printHelp(void);
/* Purpose: Print help.
 * Post-conditions: Prints help to stdout and terminats program with
 * EXIT_SUCCESS.*/

void printVersion(void);
/* Purpose: Print Version.
 * Post-conditions: Prints version to stdout and terminates program with
 * EXIT_SUCCESS.*/

void printInvalid(void);
/* Purpose: Print invalid.
 * Post-conditions: Prints invalid to stdout and terminates program with
 * EXIT_FAILURE.*/

void printAuthor(void);
/* Purpose: Print Author.
 * Post-conditions: Prints auhor to stdout and terminates program with
 * EXIT_SUCCESS.*/

void printLicense(void);
/* Purpose: Print license.
 * Post-conditions: Prints license to stdout and terminates program with
 * EXIT_SUCCESS.*/

#endif
