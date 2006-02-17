/* abtranslate
 * -albhed.cpp
 *   abtranslate functions
 *
 * Copyright(c) 2004 Josh Magee <liquidchile@liquidchile.net>
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


char englishLetterToAlbhed(char letter, char tableEnglish[], char tableAlbhed[]) {
	int i;
	for(i =  0; i < 86; i++) {  

		if(letter == tableEnglish[i]) {
			return tableAlbhed[i];
		}
	}
}

char AlbhedLetterToEnglish(char letter, char tableEnglish[], char tableAlbhed[]) {
	//works just like englishLetterToAlbhed
	int i;
	for (i = 0; i  < 86; i++) {

		if(letter == tableAlbhed[i]) {
			return tableEnglish[i];
		}
	}
}

string AlbhedLetterToPhonetics(char letter, char tableAlbhed[], string tablePhonetics[]) {
	//maps the albhed character the phoentic string
	int i;
	for (i = 0; i < 86; i++) {
		if(letter == tableAlbhed[i]) {
			return tablePhonetics[i];
		}
	}
}

string processString(string text, int languageMode) {
	//translates the string by looping over each character
	string translatedText;
	string tempText(1000,'0'); // a temporary place to hold the letters that are returned
	bool transToggle = 0;

	/* These are the cipher tables.  English A is an Albhed Y, and so on */
	char tableEnglish[] = {'a','b','c','d','e','f','g','h','i','j','k','l','m',
				'n','o','p','q','r','s','t','u','v','w','x','y','z',
				'A','B','C','D','E','F','G','H','I','J','K','L','M',
				'N','O','P','Q','R','S','T','U','V','W','X','Y','Z',
				',','!','?','"','.','[',']','\'',' ','\n','\r','1','2','3','4','5',
				'6','7','8','9','-',';','{','}',':','(',')','<','>','~','@','$','*','&'};

	char tableAlbhed[]  = {'y','p','l','t','a','v','k','r','e','z','g','m','s',
				'h','u','b','x','n','c','d','i','j','f','q','o','w',
				'Y','P','L','T','A','V','K','R','E','Z','G','M','S',
				'H','U','B','X','N','C','D','I','J','F','Q','O','W',
				',','!','?','"','.','[',']','\'',' ','\n','\r','1','2','3','4','5',
				'6','7','8','9','-',';','{','}',':','(',')','<','>','~','@','$','*','&'};

	string tablePhonetics[] = {"ae-","pe-","lu-","te-","ah-","fu-","kuk-","ra-","eay-","z-","ge-","m-","see-",
			"ha-","oo-","bae-","x-","n-","ku-","de-","ee-","jae-","fe-","q-","oh-","w-",
			"AE-","PE-","LU-","TE-","AH-","FU-","KUK-","RA-","EAY-","Z-","GE-","M-","SEE-",
			"HA-","OO-","BAE-","X-","N-","KU-","DE-","EE-","JAE-","FE-","Q-","OH-","W-",
				",","!","?","\"",".","[","]","\'"," ","\n","\r","1","2","3","4","5",
			"6","7","8","9","-",";","{","}",":","(",")","<",">","~","@","$","*","&"};

	if(languageMode == 0) {

		/* Translate from ENGLISH o AL BHED */
		for(int i = 0; text[i] != '\0'; i++) {
			if(text[i] == '[') {
				//lets not translate
				transToggle = 1;
			}
			if(text[i] == ']') {
				//start translating again
				transToggle = 0;
			}
			if(transToggle == 0) {
				tempText[i] = englishLetterToAlbhed(text[i], tableEnglish,
						tableAlbhed);

				translatedText = translatedText + tempText[i];
			}else {
				tempText[i] = text[i];
				translatedText = translatedText + tempText[i];
			}
		}
	}else if(languageMode == 1){
		/* Translate from AL BHED to ENGLISH */
		for(int i = 0; text[i] != '\0'; i++) {
                        if(text[i] == '[') {
				//lets not translate
				transToggle = 1;
			}
			if(text[i] == ']') {
				//start translating again
				transToggle = 0;
			}

			if(transToggle == 0) {
				tempText[i] = AlbhedLetterToEnglish(text[i], tableEnglish,
						tableAlbhed);
				translatedText = translatedText + tempText[i];
			}else {
				tempText[i] = text[i];
				translatedText = translatedText + tempText[i];
			}
		}
	}else if(languageMode == 2) {
		/* Translate from Al BHED to PHONETICS */
		for(int i = 0; text[i] != '\0'; i++) {
			if(text[i] == '[') {
				transToggle = 1;
			}
			if(text[i] == ']') {
				transToggle = 0;
			}

			if(transToggle == 0) {
				tempText = AlbhedLetterToPhonetics(text[i], tableAlbhed,
							tablePhonetics);
				translatedText = translatedText + tempText;
			}else {
				tempText[i] = text[i];
				translatedText = translatedText + tempText[i];
			}
		}
	} else {	//something has gone wrong
		translatedText = "There has been an error.  Text not translated.";
	}

	return translatedText;
}

void printHelp(void) {
	cout << "Usage: abtranslate [options] string" << endl;
	cout << "Options:" << endl;
	cout << "  -e \t\t Translate from English to Al Bhed" << endl;
	cout << "  -a \t\t Translate from Al Bhed to English" << endl;
	cout << "  -p \t\t Translate from Al Bhed to Phonetics" << endl;
	cout << "  --help \t Display this text" << endl;
	cout << "  --version \t Display version information" << endl;
}

void printVersion(void) {
	cout << "abtranslate 0.06" << endl;
}

void printInvalid(void) {
	cout << "Invalid option" << endl;
	cout << "Try \"--help\" for more options" << endl;
	exit(1);
}
