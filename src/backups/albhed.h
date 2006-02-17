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

#define ENGLISH (unsigned char)0
#define ALBHED (unsigned char)1
#define PHONETICS (unsigned char)2

#define ON (unsigned char)1
#define OFF (unsigned char)0

#define PROGRAM "abtranslate"
#define VERSION 0.07
#define AUTHORS "Josh Magee <liquidchile@liquidchile.net>"


void get_input(vector_string*);
/* Purpose: Fetch and store input from stdin.
 * Pre-conditions: vector_string must be an initilaized (but not
 * necessarily empty) vector_string struct.
 * Post-conditions:  vector_string will contain obtained user input
 * and attributes will be updated appropriately.*/

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

char* albhed_to_phonetics(const char letter);
/* Purpose: Translate an al bhed character to phonetics.
 * Pre-conditions: letter should be the letter to be translated.
 * Post-conditions: Returns a pointer to the corrosponding phonetic
 * string.  Returns NULL on error.*/

vector_string processString(const vector_string*, unsigned char mode);
/* Purpose:  Translate a vector_string according to mode.
 * Pre-conditions: vector_string should contain the string to be translated.
 * mode is a a macro of ENGLISH, ALBHED, or PHONETICS.
 * Post-conditions: Returns a vector_string containing the translated string.
 * Note, the caller is responsible for freeing the dynamic memory allocated
 * within the vector string with clean(vector_string*) or free(vector_string.string). */

void printHelp(void);
/* Purpose: Print help.
 * Post-conditions: Prints help to stdout and terminats program with EXIT_SUCCESS.*/

void printVersion(void);
/* Purpose: Print Version.
 * Post-conditions: Prints version to stdout and terminates program with EXIT_SUCCESS.*/

void printInvalid(void);
/* Purpose: Print invalid.
 * Post-conditions: Prints invalid to stdout and terminates program with EXIT_FAILURE.*/

void printAuthor(void);
/* Purpose: Print Author.
 * Post-conditions: Prints auhor to stdout and terminates program with EXIT_SUCCESS.*/

void printLicense(void);
/* Purpose: Print license.
 * Post-conditions: Prints license to stdout and terminates program with EXIT_SUCCESS.*/

#endif
