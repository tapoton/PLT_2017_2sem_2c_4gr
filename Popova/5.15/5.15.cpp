#include <iostream>
#include <fstream>
#include <string>

using namespace std;

char* diagonal_sum(char* file) {

	char *newFile = "indices_and_sum.txt";

	ifstream fin(file);
	ofstream fout(newFile);

	int m,x;
	fin >> m;
	int n;
	fin >> n;

	for (int i = 0; i < m; i++) {
		int sum = 0;
		for (int j = 0; j < n; j++) {
			for (int k = 0; k < n; k++) {
				fin >> x;
				if (j == n - 1 - k) {
					sum+=x;
				}

			}
		}
		fout << i << " " << sum << '\n';
	}

	fout.close();
	fin.close();

	return newFile;
}

void simple_merging_sort(char *name) {

	fstream f;
	f.open(name, ios::in);

	int ind1, ind2, a1, a2;
	int count = 0;

	if (!f.is_open()) {
		cout << "The file can not be read\n";
		return;
	}
	else {
		while (!f.eof()) {
			f >> a1;
			f >> a1;
			count++;
		}
		f.close();
	}

	int k = 1;

	while (k < count) {

		f.open(name, ios::in);
		fstream f1;
		f1.open("smsort_1.txt", ios::out);
		fstream f2;
		f2.open("smsort_2.txt", ios::out);

		if (!f.eof()) {
			f >> ind1;
			f >> a1;
		}

		while (!f.eof()) {

			for (int i = 0; i < k; i++) {
				f1 << ind1 << ' ';
				f1 << a1 << '\n';
				f >> ind1;
				f >> a1;
			}

			for (int j = 0; j < k; j++) {
				f2 << ind1 << ' ';
				f2 << a1 << '\n';
				f >> ind1;
				f >> a1;
			}
		}

		f.close();
		f1.close();
		f2.close();

		f.open(name, ios::out);
		f1.open("smsort_1.txt", ios::in);
		f2.open("smsort_2.txt", ios::in);

		if (!f1.eof()) {
			f1 >> ind1;
			f1 >> a1;
		}

		if (!f2.eof()) {
			f2 >> ind2;
			f2 >> a2;
		}

		while (!f1.eof() && !f2.eof()) {

			int i = 0;
			int j = 0;

			while (i < k && j < k && !f1.eof() && !f2.eof()) {

				if (a1 < a2) {
					f << ind1<<' ';
					f << a1 << '\n';
					f1 >> ind1;
					f1 >> a1;
					i++;
				}
				else {
					f << ind2<<' ';
					f << a2 << '\n';
					f2 >> ind2;
					f2 >> a2;
					j++;
				}
			}

			while (i < k && !f1.eof()) {
				f << ind1<<' ';
				f << a1 << '\n';
				f1 >> ind1;
				f1 >> a1;
				i++;
			}

			while (j < k && !f2.eof()) {
				f << ind2 << ' ';
				f << a2 << '\n';
				f2 >> ind2;
				f2 >> a2;
				j++;
			}
		}

		while (!f1.eof()) {
			f << ind1 << ' ';
			f << a1 << '\n';
			f1 >> ind1;
			f1 >> a1;
		}

		while (!f2.eof()) {
			f << ind2 << ' ';
			f << a2 << '\n';
			f2 >> ind2;
			f2 >> a2;
		}

		f.close();
		f1.close();
		f2.close();
		k *= 2;
	}

	remove("smsort_1.txt");
	remove("smsort_2.txt");
}

char *new_sorted_file(char *input, char *sum) {

	char *output = "output.txt";

	ifstream sin(sum);
	ofstream fout(output);
	ifstream fin(input);

	int m;
	fin >> m;
	fin.close();

	for (int i = 0; i < m; i++) {

		int ind , sum;
		sin >> ind >> sum;

		ifstream fin(input);

		int x,n;
		fin >> x;
		fin >> n;

		for (int j = 0; j < ind; j++)
			for (int k = 0; k < n; k++)
				for (int l = 0; l < n; l++)
					fin >> x;

		for (int k = 0; k < n; k++) {
			for (int l = 0; l < n; l++) {
				fin >> x;
				fout << x << ' ';
			}
			fout << '\n';
		}

		fout << '\n';

		fin.close();
	}

	sin.close();
	fout.close();

	remove(sum);

	return output;
}

int main() {
	char *s = diagonal_sum("matrix.txt");
	simple_merging_sort(s);
	char *output = new_sorted_file("matrix.txt", s);
	cout << "Output file name: " << output << "\n";
	system("pause");
}