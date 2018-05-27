/* translation_fork.h
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

#ifndef TRANSLATION_FORK
#define TRANSLATION_FORK

#define ABTRANSLATE "abtranslate"

char *translation_fork(const char *string, int n, const int mode);
/* Purpose: Fork a proccess to translate.
 * Pre: string is the string to be translated of length n.  Mode corrosponds to
 * a translation mode (currently either 1, 2, or 3). Post: Return a dyanically
 * allocated translated string. The size of the returned string wi either be n
 * for modes 1 and 2, or 3*n for modes 3. (As a phonetic translation requires
 * more characters. */

char *t_error(void);
/*  Purpose: Generate an error string.
 *  Pre: None.
 *  Post: Returns a dynamically allocated error string.*/

#endif
