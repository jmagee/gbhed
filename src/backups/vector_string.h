/* abtranslate
 * -vector_string.h
 *  -vector_string definition and related toolkit functions
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

#ifndef VECTOR_STRING
#define VECTOR_STRING

typedef struct {
	char *string;
	unsigned int used;
	unsigned int capacity;
} vector_string;

void append(vector_string*, const char*);
/* Purpose: append string to vector_string struct.
 * Pre-conditions: vector_string should be initialized and const char should
 * be a null terminated string.
 * Post-conditions: Appends string to vector_string, allocating more memory if
 * neccessary and updated used and capacity.*/

void append_char(vector_string*, const char);
/* Purpose: Same as above but appends a single character instead of a string.*/

void resize(vector_string*);
/* Purpose: Resize vector_string->string.
 * Pre-conditions: vector_string should be initialized.
 * Post-conditions: Resizes vector_string by INCREASE characters (50 at this
 * time.*/

void display(const vector_string*);
/* Purpose: Display vector_string.
 * Pre-conditions: vector_string should be initialized.
 * Post-conditions: Displays vector_string->string to stdout.*/

void clean(vector_string*);
/* Purpose: Clean up vector_string object.
 * Pre-conditions: vector_string should be iniatilized.
 * Post-conditions: vector_string->string is freed and set to NULL.*/

#endif
