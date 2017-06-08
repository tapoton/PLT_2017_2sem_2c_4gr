#define _CRT_SECURE_NO_WARNINGS

#include <iostream>
#include <fstream>

using namespace std;

static const int n = 2; // matrix size
static const int k = 10; // elements of matrix will be 1..k
static const int amount = 6; // amount of matrixes

void fileFill(char *fileName)
{

	ofstream fout(fileName);

	for (int l = 0; l < amount; l++) // filling with random matrixes n x n
	{
		for (int i = 0; i < n; i++)
		{
			for (int j = 0; j < n; j++)
			{
				int element = rand() % k + 1;
				fout << element << " ";
			}
			fout << '\n';
		}
		fout << "\n";
	}
	fout.close();
}

char *elementsComposition(char *matrixes)
{
	char *newFileName = "compositions.txt";

	ifstream fin(matrixes);
	ofstream fout(newFileName);

	for (int l = 0; l < amount; l++)
	{
		unsigned long long comp = 1;
		for (int i = 0; i < n; i++)
			for (int j = 0; j < n; j++)
			{
				int a;
				fin >> a;
				comp *= a;
			}
		fout << l << " " << comp << '\n';
	}

	fout.close();
	fin.close();

	return newFileName;

}

void quickSort(unsigned long long *a, int *indexes, int l, int r)
{
	int x = a[(l + r) / 2];
	int i = l;
	int j = r;

	while (i <= j)
	{
		while (a[i] < x) i++;
		while (a[j] > x) j--;
		if (i <= j)
		{
			swap(a[i], a[j]);
			swap(indexes[i], indexes[j]);
			i++;
			j--;
		}
	}
	if (i<r) quickSort(a, indexes, i, r);
	if (l<j) quickSort(a, indexes, l, j);
}

char *sort(char *fileComps)
{
	int ind, comp;
	ifstream fin(fileComps);

	int indexes[amount];
	unsigned long long compositions[amount];

	for (int i = 0; i < amount; i++)
	{
		fin >> ind;
		fin >> comp;
		indexes[i] = ind;
		compositions[i] = comp;
	}
	fin.close();
	quickSort(compositions, indexes, 0, amount - 1);

	char *sortedComps = "compositions_sorted.txt";
	ofstream fout(sortedComps);

	for (int i = 0; i < amount; i++)
	{
		fout << indexes[i] << " " << compositions[i] << '\n';
	}
	fout.close();

	return sortedComps;
}

char *sortMatrixes(char *matrixes, char*indexes)
{
	char *newSortedFile = "matrix_array_sorted.txt";
	ofstream fout(newSortedFile);


	ifstream compin(indexes);

	for (int l = 0; l < amount; l++)
	{
		int ind;
		unsigned long long comp;
		compin >> ind >> comp;

		int x;

		ifstream fin(matrixes);

		for (int k = 0; k<ind; k++)
			for (int i = 0; i < n; i++)
				for (int j = 0; j < n; j++)
				{
					fin >> x;
				}

		for (int i = 0; i < n; i++)
		{
			for (int j = 0; j < n; j++)
			{
				fin >> x;
				fout << x << " ";
			}
			fout << '\n';
		}
		fout << '\n';
		fin.close();
	}
	return newSortedFile;
}

int main()
{
	char s[] = "matrix_array.txt";
	fileFill(s);
	char *compsAndInd = elementsComposition(s);
	char *sortedIndexes = sort(compsAndInd);
	char *sortedMatrixes = sortMatrixes(s, sortedIndexes);


	system("pause");
	return 0;
}