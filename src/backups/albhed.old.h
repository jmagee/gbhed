/* abtranslate
 * -albhed.h
 *   function prototypes
 *
 * Copyright (c) 2004 Josh Magee <liquidchile@liquidchile.net>
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

#include <iostream>
#include <string>
using namespace std;

char englishLetterToAlbhed(char, char*, char*); 
char AlbhedLetterToEnglish(char, char*, char*); 
string AlbhedLetterToPhonetics(char, char*, string*); 
string processString(string, int); 
void printHelp(void);
void printVersion(void); 
void printInvalid(void); 

#endif