/*
Decrypt IBM KDB STH files.

Stash files are used by IBM WebSphere and WebSEAL.

It's possible to lose the password so use this utility to decrypt the stash file, it has happened to me before!
Not a real encryption, it's just a simple XOR obfuscation of each byte in the sth file with the key value of 0xf5.
(c) By Shoestring

g++ -o <output> <unstash.cpp>

*/

#include <iostream>
#include <fstream>
#include <string>


using namespace::std;
char key = 0xf5;

void usage(char **argv)
{
	cout << "Usage" << endl;
	cout << argv[0] << " <stashfile.sth>" << endl;
}

char decrypt(char c)
{
	c = c ^ key;
	return c;
}

int main(int argc, char **argv)
{
		char c = 0;
		if(argc==0 || !argv[1])
		{
			usage(argv);
			return -1;
		}
		std::ifstream file (argv[1], std::ifstream::in | std::ios::binary);
		if (!file)
		{
			cerr << argv[1] << " not found, error!" << endl;
			return -2;
		}
		else
		{
			do
			{
				c = file.get();
				std::cout << decrypt(c);
				
			} while(file.good());
		}
		return 0;
}

