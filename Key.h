#ifndef KEY_H
#define KEY_H

#include <map>
#include <fstream>

using namespace std;

class Key
{
private:
	int a, z, temp, vTop, cTop;

	char i, tempVow, tempCons, vowArr[5], consArr[21];

	map<char, int> consonants, vowels;
	map<char, int>::iterator it;

	fstream vowFile, consFile, loggedFile;

public:
	Key();

	~Key();

	void setLetters();

	void Keylogger();

	void recordLetters(char x);

	void Sort();

	char pickVow();

	char pickCons();

	string Word();

	void Terminate();

	void showKeys();

};

#endif // !KEY_H