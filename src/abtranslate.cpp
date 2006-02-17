/* abtranlate
 * -abtranslate.cpp
 *  Main body of program
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



#include "albhed.h"
#include <iostream>
#include <string>
using namespace std;


int main(int argc, char* argv[]) {
	string translateMe;
	string translatedString;
	int languageMode;

	if(argc <= 1)	//no paramters is invalid
		printInvalid();

	for(int i = 1; i < argc; i++) {
		/*program takes ONE and only ONE command line option 
		 and it MUST have this option */
		if(i == 1) {	//the one option
		
			if(string(argv[i]) == "-e") {
				//language mode is english
				languageMode = 0;

			}else if(string(argv[i]) == "-a") {
				//language mode is al bhed
				languageMode = 1;

			}else if(string(argv[i]) == "-p") {
				//language mode is phonetics
				languageMode = 2;
			
			}else if(string(argv[i]) == "--help" || string(argv[i]) == "-h") {
				printHelp();	
				exit(0);

			}else if(string(argv[i]) == "--version") {
				printVersion();	
				exit(0);
			
			}else {
				//invalid paramaters
				printInvalid();
			}
		}
			
		if(i == 2) { //so we don't have a space before the string
			translateMe = translateMe + string(argv[i]);
		}else if( i > 2){
			translateMe = translateMe +  " " + string(argv[i]);
		}
	}

	translatedString = processString(translateMe, languageMode);

	cout << translatedString << endl;

	return 0;
}
