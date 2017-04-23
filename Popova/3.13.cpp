#include <iostream>
#include <string>

using namespace std;

	void initcities(string* name, int n) {
		for (int i = 0; i < n; i++) {
			cout << "\nEnter the name of city number " << i+1 << '\n';
			cin >> name[i];
		}
	}

	void initroads(string *name, int **way, int n) {
		char ok;
		int dist;
		for (int i = 0; i < n - 1; i++)
			for (int j = i + 1; j < n; j++) {
				cout << "\nIs there a road between " << name[i] << " and " << name[j] << "? Y/N\n";
				cin >> ok;
				if (ok == 'Y') {
					cout << "\nEnter the distance between " << name[i] << " and " << name[j] << ":\n";
					cin >> dist;
					way[i][j] = dist;
					way[j][i] = dist;
				}
			}
	}

	void showroads(string *name, int **way, int n) {
		cout << "\n     Road system:\n";
		for (int i = 0; i < n; i++) {
			for (int j = i + 1; j < n; j++)
				cout << "\n" << name[i] << " - " << way[i][j] << " - " << name[j];
		}
	}

	bool periphery(bool* marker, int** way, int dist, int cityindex, int n, int i, int Nperiph) {
		int current = 1;
		bool ok = true;
		while (current < n && ok) {
			if (way[cityindex, current] != 0 && marker[current]) {
				dist = dist + *way[cityindex, current];
				marker[current] = false;
				if (current == i) {
					if (dist < Nperiph && dist != 0) {
						ok = false;
					}
				}
				else
					periphery(marker, way, dist, current, n, i, Nperiph);
				dist = dist - *way[cityindex, current];
			}
			current++;
		}
		return ok;
	}

		int get_city_index(string* name, int n, string c) {
			int i=0; 
			bool;
			while (i < n) {
				if (name[i] == c)
					return i;
			}
		}

	void main() {
		int n;
		cout << "Enter the number of the cities: ";
		cin >> n;
		int **way = new int*[n];
		for (int i = 0; i < n; i++) {
			way[i] = new int[n];
			for (int j = 0; j < n; j++) {
				way[i][j] = 0;
			}
		}
		string* name = new string[n];
		initcities(name, n);
		initroads(name, way, n);
		showroads(name, way, n);
		bool* marker = new bool[n];
		for (int i = 0; i < n; i++) {
			marker[i] = true;
		}
		cout << "\nEnter the city to find it's N - periphery: ";
		string c;
		cin >> c;
		int city = get_city_index(name, n, c);
		cout << "\nEnter the distance to find N - periphery: ";
		int N;
		cin >> N;
		cout << "\n" << N << " - periphery of " << c << ": ";
		bool is_periph = false;
		for (int i = 0; i < n; i++) {
			if (city != i) {
				if (periphery(marker, way, 0, city, n, i, N)) {
					is_periph = true;
					cout << name[i] << " ";
				}
			}
		}
		if (!is_periph)
			cout << " no city was found";
		system("pause");
	}