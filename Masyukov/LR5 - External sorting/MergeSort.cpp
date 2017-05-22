// В текстовом файле задана целочисленная матрица размера n*n. Отсортировать файл так, чтобы строки матрицы располагались в порядке возрастания элементов, находящихся на побочной диагонали.

#include <iostream>
#include <fstream>
#include <string>

using namespace std;

void Merge(string As, int startA, int nA, string Bs, int startB, int nB, ofstream &C, int* keyA, int* keyB, int* keyC) {

	int a, b;
	a = b = 0;
	string temp;
	int* key = new int[nA + nB];
	while (a + b < nA + nB) {
		if (b >= nB || a < nA && keyA[a] <= keyB[b]) {
			ifstream A(As, ios_base::in);
			for (int i = 0; i <= startA + a; i++) {
				getline(A, temp);
			}
			C << temp << "\n";
			keyC[a + b] = keyA[a];
			a++;
		}
		else {
			ifstream B(Bs, ios_base::in);
			for (int i = 0; i <= startB + b; i++) {
				getline(B, temp);
			}
			C << temp << "\n";
			keyC[a + b] = keyB[b];
			b++;
		}
	}
}

void MergeSort(string As, int start, int n, int* key) {
	ifstream A(As, ios_base::in);
	A.seekg(0, ios_base::beg);

	if (n < 2) return;

	if (n == 2) {
		if (key[0] > key[1]) {
			ofstream fsup1("support1.txt", ios_base::out, ios_base::trunc);
			string temp, string_to_remember;
			int line_current = 0;
			ifstream A1(As, ios_base::in);
			while (!A1.eof()) {
				getline(A1, temp);
				line_current++;
				if (line_current != start + 1) {
					fsup1 << temp;
					fsup1 << "\n";
				}
				else {
					string_to_remember = temp;
					getline(A1, temp);
					line_current++;
					fsup1 << temp << "\n" << string_to_remember << "\n";
				}
			}
			A1.close();

			fsup1.close();
			ifstream fsup1in("support1.txt", ios_base::in);
			ofstream A(As, ios_base::out);
			while (!fsup1in.eof()) {
				getline(fsup1in, temp);
				A << temp << "\n";
			}

			int t2 = key[0];
			key[0] = key[1];
			key[1] = t2;
			A.close();
		}

		return;
	}

	MergeSort(As, start, n / 2, key);
	MergeSort(As, start + n / 2, n - n / 2, key + n / 2);

	ofstream fout("output.txt", ios_base::out, ios_base::trunc);
	int* keyB = new int[n];
	Merge(As, start, n / 2, As, start + n / 2, n - n / 2, fout, key, key + n / 2, keyB);
	for (int i = 0; i < n; i++) {
		key[i] = keyB[i];
	}

	remove("support1.txt");
}

int main() {
	string inp;
	inp = "input.txt";
	ifstream fin(inp, ios_base::in);
	if (!fin)
	{
		cerr << "Error open file" << endl;
		system("pause");
		return 0;
	}

	ofstream temp("temp.txt", ios_base::out);

	string len;
	int n = 0;
	while (!fin.eof()) {
		getline(fin, len);
		temp << len << "\n";
		if (len != "") n++;
	}
	fin.clear();
	fin.seekg(0, ios_base::beg);
	temp.close();
	
	int* key = new int[n]; // key[i] - is an element of an i-th line standing on a secondary diagonal 
	int i = 0;
	while (!fin.eof()) {
		int c;
		for (int j = 0; j < n; j++) {
			fin >> c;
			if (j == n - i - 1) {
				key[i] = c;
			}
		}
		i++;
	}

	MergeSort(inp, 0, n, key);
	
	ifstream temp1("temp.txt", ios_base::in);
	ofstream fin1(inp, ios_base::out);
	fin1.clear();
	for (int i = 0; i < n; i++) {
		getline(temp1, len);
		if (i == n) len.erase(len.length() - 1, 1);
		fin1 << len << "\n";
	}
	temp1.close();
	fin1.close();
	remove("temp.txt");

	system("pause");
	return 0;
}
