/* abtranslate
 * -cipher_tables.h
 *  -language cipher tables and related constants
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

#ifndef CIPHER_TABLES
#define CIPHER_TABLES

#define MAX_CHARS 98 /* # of characters in each table*/

const char tableEnglish[] = {
    'a', 'b', 'c',  'd',  'e', 'f',  'g',  'h', 'i', 'j', 'k', 'l', 'm',  'n',
    'o', 'p', 'q',  'r',  's', 't',  'u',  'v', 'w', 'x', 'y', 'z', 'A',  'B',
    'C', 'D', 'E',  'F',  'G', 'H',  'I',  'J', 'K', 'L', 'M', 'N', 'O',  'P',
    'Q', 'R', 'S',  'T',  'U', 'V',  'W',  'X', 'Y', 'Z', ',', '!', '?',  '"',
    '.', '[', ']',  '\'', ' ', '\n', '\r', '1', '2', '3', '4', '5', '6',  '7',
    '8', '9', '-',  ';',  '{', '}',  ':',  '(', ')', '<', '>', '~', '@',  '$',
    '*', '&', '\t', '/',  '0', '%',  '_',  '#', '^', '`', '+', '=', '\\', '|'};

const char tableAlbhed[] = {
    'y', 'p', 'l',  't',  'a', 'v',  'k',  'r', 'e', 'z', 'g', 'm', 's',  'h',
    'u', 'b', 'x',  'n',  'c', 'd',  'i',  'j', 'f', 'q', 'o', 'w', 'Y',  'P',
    'L', 'T', 'A',  'V',  'K', 'R',  'E',  'Z', 'G', 'M', 'S', 'H', 'U',  'B',
    'X', 'N', 'C',  'D',  'I', 'J',  'F',  'Q', 'O', 'W', ',', '!', '?',  '"',
    '.', '[', ']',  '\'', ' ', '\n', '\r', '1', '2', '3', '4', '5', '6',  '7',
    '8', '9', '-',  ';',  '{', '}',  ':',  '(', ')', '<', '>', '~', '@',  '$',
    '*', '&', '\t', '/',  '0', '%',  '_',  '#', '^', '`', '+', '=', '\\', '|'};

const char *tablePhonetics[] = {
    "ae-", "pe-",  "lu-",  "te-", "ah-",  "fu-",  "kuk-", "ra-",  "eay-", "z-",
    "ge-", "m-",   "see-", "ha-", "oo-",  "bae-", "x-",   "n-",   "ku-",  "de-",
    "ee-", "jae-", "fe-",  "q-",  "oh-",  "w-",   "AE-",  "PE-",  "LU-",  "TE-",
    "AH-", "FU-",  "KUK-", "RA-", "EAY-", "Z-",   "GE-",  "M-",   "SEE-", "HA-",
    "OO-", "BAE-", "X-",   "N-",  "KU-",  "DE-",  "EE-",  "JAE-", "FE-",  "Q-",
    "OH-", "W-",   ",",    "!",   "?",    "\"",   ".",    "[",    "]",    "\'",
    " ",   "\n",   "\r",   "1",   "2",    "3",    "4",    "5",    "6",    "7",
    "8",   "9",    "-",    ";",   "{",    "}",    ":",    "(",    ")",    "<",
    ">",   "~",    "@",    "$",   "*",    "&",    "\t",   "/",    "0",    "%",
    "_",   "#",    "^",    "`",   "+",    "=",    "\\",   "|"};

#endif
