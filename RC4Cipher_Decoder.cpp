#include <iostream>
#include <fstream>
#include <algorithm>
#include <iomanip>
#include <string>
using namespace std;

//Converts 2 digit hex into integer value
int toInt(char* buffer)
{
	int result = 0;
	if (isdigit(buffer[0]))
		result += (buffer[0] - 48) * 16;
	else
		result += (buffer[0] - 87) * 16;

	if (isdigit(buffer[1]))
		result += (buffer[1] - 48);
	else
		result += (buffer[1] - 87);

	return result;
}

int main()
{
	//Get input file, attempt to open
	cout << "Enter the name of the cipher text file: ";
	string inFileName;
	cin >> inFileName;
	ifstream inFile;
	inFile.open(inFileName, ios::binary);
	if (!inFile.is_open())
	{
		cout << "Error: File not found. " << endl; // Open failed
		return -1;
	}

	//Initialize S array
	int S[256];
	for (int i = 0; i < 256; i++)
		S[i] = i;

	//Get Key
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
	char* buffer = new char[2];
	int t;
	char x;
	int i = 0;
	j = 0;

	//Read File, output de-coded message (in chars)
	while (inFile.read(buffer, 2))
	{
		t = toInt(buffer);
		i = (i + 1) % 256;
		j = (j + S[i]) % 256;
		swap(S[i], S[j]);
		x = S[(S[i] + S[j]) % 256] ^ t;
		outFile << x;
	}

	//Free Memory
	delete[] buffer;
	system("pause");
}