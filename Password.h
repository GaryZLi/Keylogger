#ifndef  PASSWORD_H
#define PASSWORD_H

#include <string>

using namespace std;

class Password
{
private:
	int c, r;

	string text;

	bool allow = true;

	char spaces[5] = {'[', '_', '\\', '^', ']'};

	fstream pwAccess;

public:
	Password();

	~Password();

	bool Access();

	bool isEmpty();

	void managePW();

	string Encrypt(string password);

	string Decrypt(string password);

};

#endif // ! PASSWORD_H










