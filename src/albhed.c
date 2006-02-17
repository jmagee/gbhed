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

void get_input(vector_string *text) {
	char temp_char;

	while((int)(temp_char = (char)getchar()) != EOF) {
		append_char(text, temp_char);
	}
}

char english_to_albhed(const char letter) {
	register int i;
	for(i = 0; i < MAX_CHARS; i++) {
		if(letter == tableEnglish[i])
			return tableAlbhed[i];
	}
	return (char)EOF;
}

char albhed_to_english(const char letter) {
	register int i;
	for(i = 0; i < MAX_CHARS; i++) {
		if(letter == tableAlbhed[i])
			return tableEnglish[i];
	}
	return (char)EOF;
}

char* albhed_to_phonetics(const char letter) {
	register int i;
	for(i = 0; i < MAX_CHARS; i++) {
		if(letter == tableAlbhed[i])
			return (char*)tablePhonetics[i];
	}
	return NULL;
}

vector_string processString(const vector_string *text, unsigned char language_mode) {

	register unsigned int i;
	unsigned char trans_toggle = ON;
	vector_string translated_text;
	translated_text.string = NULL;
	translated_text.used = 0;
	translated_text.capacity = 0;

	if(language_mode == ENGLISH) {
		/*Tranlsate from ENGLISH to AL BHED*/
		for(i = 0; i < text->used; i++) {
			if(text->string[i] == '[')
				trans_toggle = OFF;
			if(text->string[i] == ']')
				trans_toggle = ON;

			if(trans_toggle == ON) {
				append_char(&translated_text, english_to_albhed(
							text->string[i]));
			}else {
				append_char(&translated_text, text->string[i]);
			}
		}
	}else if(language_mode == ALBHED) {
		/*Translate from AL BHED to ENGLISH*/
		for(i = 0; i < text->used; i++) {
			if(text->string[i] == '[')
				trans_toggle = OFF;
			if(text->string[i] == ']')
				trans_toggle = ON;

			if(trans_toggle == ON) {
				append_char(&translated_text, albhed_to_english(
							text->string[i]));
			}else {
				append_char(&translated_text, text->string[i]);
			}
		}
	}else if(language_mode == PHONETICS) {
		/*Translate from AL BHED to PHONETICS*/
		for(i = 0; i < text->used; i++) {
			if(text->string[i] == '[')
				trans_toggle = OFF;
			if(text->string[i] == ']')
				trans_toggle = ON;

			if(trans_toggle == ON) {
				append(&translated_text, albhed_to_phonetics(
							text->string[i]));
			}else {
				append_char(&translated_text, text->string[i]);
			}
		}
	}else { /*Error*/
		fprintf(stderr, "Invalid Translating mode error.\n");
		fprintf(stderr, "This is most likely a bug, please report it to: ");
		fprintf(stderr, "<liquidchile@liquidchile.net>\n");
		exit(EXIT_FAILURE);
	}

	return translated_text;
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
	printf("copyright(c) 2004-2005 Josh Magee <liquidchile@liquidchile.net>\n\n");
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
	printf("Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA  02111-1307, USA.\n");
	exit(EXIT_SUCCESS);
}
