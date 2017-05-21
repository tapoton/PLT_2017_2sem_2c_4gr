#include "stdafx.h"
#include <string>
#include <fstream>
#include <iostream>
#include <windows.h>
using namespace std;
const int n = 30;
enum Ternar {Equal, Smaller, Bigger};

Ternar Compare(char* const Str1, char* const Str2)
{
	
	char* ptr1 = Str1, *ptr2 = Str2;
	while (*ptr1 && *ptr2 && *ptr1 == *ptr2)
	{
		ptr1++;
		ptr2++;
	}
	if (!*ptr1 && !*ptr2) return Equal;
	else if (!*ptr1 || *ptr1 + 33 < ((*ptr2) ? (*ptr2) + 33 : *ptr2)) return Smaller;
	else return Bigger;
}

int NumOfStrings(ifstream& File, streamoff Position= 0)
{
	if (Position == -1) return 0;
	int counter = 0;
	if (File.is_open())
	{
		File.seekg(Position);
		char Str[n];
		while (!File.eof())
		{
			File.getline(Str, n, '\n');
			counter++;
		}
		File.seekg(Position);
	}

	return counter;
}

char* FindMaxInPartOfFile(ifstream& SomeFile1, ifstream& SomeFile2, int PartOfFile, int& MaxCounter, streamoff& Bottom1, streamoff& Bottom2, streamoff Position1 = 0, streamoff Position2 = 0, char* SomeString = "~")
{
	MaxCounter = 0; int steps = 0;
	SomeFile1.seekg(Position1); SomeFile2.seekg(Position2);
	Bottom1 = SomeFile1.tellg(); Bottom2 = SomeFile2.tellg();
	char Buff1[n], Buff2[n], MaxBuff[n] = "\0";
	while (Bottom1!=-1 && Bottom2!=-2 && steps < PartOfFile)
	{
		SomeFile1.getline(Buff1, n, '\n');
		SomeFile2.getline(Buff2, n, '\n');
		char CurrentBuff[n]; 
		strcpy(CurrentBuff,(Compare(Buff1, Buff2) == Bigger) ? Buff1 : Buff2);
		if (Compare(CurrentBuff, SomeString)!=Smaller) 
			strcpy(CurrentBuff, (Compare(Buff1, Buff2) == Smaller) ? Buff1 : Buff2);
		if (Compare(CurrentBuff, MaxBuff) == Bigger && Compare(CurrentBuff, SomeString)==Smaller)
		{
			strcpy(MaxBuff,CurrentBuff);
			MaxCounter = (Compare(Buff1, Buff2) == Equal) ? 2 : 1;
		}
		else if (Compare(CurrentBuff, MaxBuff) == Equal) MaxCounter++;
		steps++;
	}
	while (Bottom1!=-1 && steps < PartOfFile)
	{
		SomeFile1.getline(Buff1, n);
		if (Compare(Buff1, MaxBuff) == Bigger && Compare(Buff1, SomeString) == Smaller)
		{
			strcpy(MaxBuff, Buff1);
			MaxCounter = 1;
		}
		else if (Compare(Buff1, MaxBuff) == Equal) MaxCounter++;
		steps++;
	}
	while (Bottom2!=-1 && steps < PartOfFile)
	{
		SomeFile2.getline(Buff2, n);
		if (Compare(Buff2, MaxBuff) == Bigger && Compare(Buff2, SomeString) == Smaller)
		{
			strcpy(MaxBuff, Buff2);
			MaxCounter = 1;
		}
		else if (Compare(Buff2, MaxBuff) == Equal) MaxCounter++;
		steps++;
	}
	Bottom1 = SomeFile1.tellg(); Bottom2 = SomeFile2.tellg();
	return MaxBuff;
}

void Distribution(ifstream& OriginalFile, ofstream& NewFile1, ofstream& NewFile2, int NumOfStrings)
{
	char buff[n];
	for (int i = 1; i < NumOfStrings; i++)
	{
		OriginalFile >> buff;
		NewFile1 << buff <<endl;
	}
	OriginalFile >> buff;
	NewFile1 << buff;
	int j = 0;
	while (!OriginalFile.eof())
	{
		if (j) NewFile2 << endl;
		OriginalFile >> buff;
		NewFile2 << buff;
		j++;
	}
	OriginalFile.seekg(0);
}

void FileSort(string FileName)
{
	string Name1 = "Buff1.txt", Name2 = "Buff2.txt";
	ifstream FileIn(FileName); ofstream File1Out(Name1, ios_base::trunc), File2Out(Name2, ios_base::trunc);
	int NumOfStr = NumOfStrings(FileIn);
	int NumOfWordsInGroup = 1;
	while (NumOfWordsInGroup < NumOfStr)
	{
		Distribution(FileIn, File1Out, File2Out, NumOfStr / 2);
		FileIn.close();
		File1Out.close();
		File2Out.close();
		ofstream FileOut(FileName, ios_base::trunc);
		ifstream File1In(Name1), File2In(Name2);
		streamoff Bottom1 = 0, Bottom2 = 0, OldBottom1 = Bottom1, OldBottom2 = Bottom2;
		bool FirstStr = 1;
		while(Bottom1!=-1 || Bottom2!=-1)
		{
			int NOS1 = NumOfStrings(File1In, Bottom1), NOS2 = NumOfStrings(File2In, Bottom2);
			int MaxCounter = 0; char Max[n] = "~";
			int Steps = ((NOS1 + NOS2) / (2 * NumOfWordsInGroup)) ? 2 * NumOfWordsInGroup : NOS1 + NOS2;
			for (int i = 0; i < Steps; i += MaxCounter)
			{
				if (Bottom1 == -1)
				{
					File1In.close();
					File1In.open(Name1);
				}
				if (Bottom2 == -1)
				{
					File2In.close();
					File2In.open(Name2);
				}
				strcpy(Max, FindMaxInPartOfFile(File1In, File2In, NumOfWordsInGroup, MaxCounter, Bottom1, Bottom2, OldBottom1, OldBottom2, Max));
				int CopyCounter = MaxCounter;
				if (FirstStr) {
					FirstStr = 0;
					FileOut << Max;
					CopyCounter--;
				}
				else 
				for (int j = 0; j<CopyCounter; j++)
					FileOut << endl << Max;				
			}
			File1In.seekg(OldBottom1); File2In.seekg(OldBottom2);
			OldBottom1 = Bottom1, OldBottom2 = Bottom2;
		}
		FileOut.close(); File1In.close(); File2In.close();
		FileIn.open(FileName); File1Out.open(Name1, ios_base::trunc); File2Out.open(Name2, ios_base::trunc);
		NumOfWordsInGroup *= 2;
	}
}

void main()
{
	SetConsoleCP(1251);
	SetConsoleOutputCP(1251);
	FileSort("File.txt");
	system("pause");
}

