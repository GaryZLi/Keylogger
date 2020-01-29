#include <fstream>
#include <iostream>
#include <Windows.h>
#include "Password.h"
#include "Key.h"

using namespace std;

Password::Password()
{
	pwAccess.open("pass.txt");
}

Password::~Password()
{
	pwAccess.close();
}

bool Password::Access()
{
	if (pwAccess.fail())
	{
		cout << "Failed to access password..." << endl;
	}
	else
	{
		managePW();
	}

	return allow;
}

bool Password::isEmpty()
{
	c = 0;

	//check for anything stored
	pwAccess >> text;
	c += text.size();

	//clear eof flag
	pwAccess.clear();

	if (c == 0)
		return true;
	else
		return false;
}

void Password::managePW()
{
	string password, hint, input;

	switch (isEmpty())
	{
		//if nothing stored
	case true:
		allow = true;

		cout << "New user! Please enter a password with 8 characters or more: "; cin >> password;

		//loop until password is more than 8 characters
		while (password.length() < 8)
		{
			cout << "Please enter a password with 8 characters or more: "; cin >> password;
		}

		cout << "Enter a hint for your password: "; cin >> hint;

		//insert the password and hint into pass.txt file
		pwAccess << Encrypt(password) << "\n" << hint << endl;

		break;

		//has a password stored
	default:
		//put "cursor" back to the beginning of file
		pwAccess.seekg(pwAccess.beg);

		cout << "Please enter your password to access the keys logged: "; cin >> input;

		//gather the password
		pwAccess >> text;
		password = Decrypt(text);

		if (input != password)
		{
			//disable access
			allow = false;

			//initiate a counter for amount of incorrect password attempts
			int count = 3;

			//gather hint
			pwAccess >> text;
			hint = text;

			do
			{
				cout << endl;
				cout << "Incorrect! Try again..." << endl;
				cout << "Your hint is: \"" << hint << "\"." << endl;

				//wait 5 seconds after an incorrect attempt
				Sleep(5000);

				cout << "Please enter your password to access the keys logged: "; cin >> input;

				if (input == password)
				{
					allow = true;
					break;
				}

				count--;

				if (count == 0)
				{
					cout << "All attempts used. Cannot grant access to keys logged." << endl;
					cout << endl;
					break;
				}

			} while (input != password);
		}
		else
			allow = true;

		break;
	}

	//close the file when program ends
	pwAccess.close();
}

string Password::Encrypt(string password)
{
	string encryptedPW;

	int count = 0;

	//gather a specific section of ASCII
	//transform each character of the password into something unique
	//add a 'space' special char after each transformation
	for (c = 0; c < password.length(); c++)
	{
		//reset the 'space' special chars to beginning
		if (count > 4)
			count = 0;

		//a - m
		if (96 < (int)password[c] && (int)password[c] <= 109)
		{
			r = (int)password[c] - 96;
			encryptedPW += 96 - r - 5;
			encryptedPW += spaces[count++];
		}
		//n - z
		else if (109 < (int)password[c] && (int)password[c] < 123)
		{
			r = (int)password[c] - 109;
			encryptedPW += 109 - r - 31;
			encryptedPW += spaces[count++];
		}
		//A - M
		else if (64 < (int)password[c] && (int)password[c] <= 77)
		{
			r = 78 - (int)password[c];
			encryptedPW += 78 + r + 31;
			encryptedPW += spaces[count++];
		}
		//N - Z
		else if (77 < (int)password[c] && (int)password[c] < 91)
		{
			r = 91 - (int)password[c];
			encryptedPW += 91 + r + 5;
			encryptedPW += spaces[count++];
		}
		//0 - 9
		else if (47 < (int)password[c] && (int)password[c] < 58)
		{
			if ((int)password[c] < 53)
			{
				r = 52 - (int)password[c];
				encryptedPW += 52 + r + 1;
				encryptedPW += spaces[count++];
			}
			else
			{
				r = (int)password[c] - 53;
				encryptedPW += 53 - r - 1;
				encryptedPW += spaces[count++];
			}
		}
		//anything else != 'space' chars = to itself
		else /*if ((int)password[c] != spaces[0] && (int)password[c] != spaces[1] && (int)password[c] != spaces[2]
			&& (int)password[c] != spaces[3] && (int)password[c] != spaces[4])*/
		{
			encryptedPW += password[c]; 
			encryptedPW += spaces[count++];
		}
	}

	return encryptedPW;
}

string Password::Decrypt(string password)
{
	string decryptedPW;

	int r;
	int len = sizeof(spaces) / sizeof(*spaces);

	for (c = 0; c < password.length(); c++)
	{
		//gather only the 'nonspace' chars
		if (password[c] != spaces[0] && password[c] != spaces[1] && password[c] != spaces[2] && 
			password[c] != spaces[3] && password[c] != spaces[4])
		{
			if (96 < (int)password[c] && (int)password[c] < 110)
			{
				r = (int)password[c] - 96;
				decryptedPW += 96 - r - 5;
			}
			else if (109 < (int)password[c] && (int)password[c] < 123)
			{
				r = (int)password[c] - 109;
				decryptedPW += 109 - r - 31;
			}
			else if (64 < (int)password[c] && (int)password[c] < 78)
			{
				r = 78 - (int)password[c];
				decryptedPW += 78 + r + 31;
			}
			else if (77 < (int)password[c] && (int)password[c] < 91)
			{
				r = 91 - (int)password[c];
				decryptedPW += 91 + r + 5;
			}
			else if (47 < (int)password[c] && (int)password[c] < 53)
			{
				r = 53 - (int)password[c];
				decryptedPW += 53 + r - 1;
			}
			else if (52 < (int)password[c] && (int)password[c] < 58)
			{
				r = (int)password[c] - 52;
				decryptedPW += 52 - r + 1;
			}
			else
				decryptedPW += password[c];
		}
		else
		{
			for (int i = 0; i < len; i++)
			{
				if (password[c + 1] == spaces[i])
				{
					decryptedPW += password[c + 1];
					cout << spaces[i] << endl;
				}
			}
		}
	}

	return decryptedPW;
}