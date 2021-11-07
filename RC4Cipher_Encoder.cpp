#include <iostream>
#include <fstream>
#include <algorithm>
#include <iomanip>
#include <string>
using namespace std;

int main()
{
	//Get input file name, attempt to open
	cout << "Enter the name of the plain text file: ";
	string inFileName;
	cin >> inFileName;
	ifstream inFile;
	inFile.open(inFileName);
	if (!inFile.is_open())
	{
		cout << "Error: File not found. " << endl; // Opening failed
		return -1;
	}

	//Initialize S array
	int S[256];
	for (int i = 0; i < 256; i++)
		S[i] = i;

	//Get key
	cout << "Enter Key" << endl;
	string key;
	cin >> key;

	//Randomize S array
	int j = 0;
	for (int i = 0; i < 256; i++)
	{
		j = (j + S[i] + key.at(i % key.length())) % 256;
		swap(S[i], S[j]);
	}

	//Get output file
	ofstream outFile;
	cout << "Enter output file name: ";
	string outFileName;
	cin >> outFileName;
	outFile.open(outFileName);

	//Vars
	char t;
	int x;
	int i = 0;
	j = 0;

	//Read File, write to output file in hex
	while (inFile.read(&t, 1))
	{
		i = (i + 1) % 256;
		j = (j + S[i]) % 256;
		swap(S[i], S[j]);
		x = S[(S[i] + S[j]) % 256] ^ t;
		outFile << setw(2) << setfill('0') << hex << x;
	}
	system("pause");
}