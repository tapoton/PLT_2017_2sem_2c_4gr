#include <iostream>
#include <map>
#include <set>
#include <string>

using namespace std;

map<long long, int> map_name;
set<string> dif_name;

const int p = 127; // только простое
const long long mod = 1125899839733759; //модуль хеша (от 0 до 1125899839733759 (только простое)) // 1e9+7

long long bild_hash(string s)
{
	long long hash = 0;
	for (int i = s.length() - 1; i >= 0; i--)
	{
		hash *= p;
		hash += s[i];
		hash %= mod;
	}
	return (hash);
}

int main()
{
	int n;
	cout << "The number of names = ";
	cin >> n; // общее количество имен

	for (int i = 0; i < n; i++)
	{
		string s;
		cin >> s; // ввод имени
		int sz = dif_name.size(); // различные имена на  iтом шаге
		dif_name.insert(s); //  добавление в множество новое имя
		long long t = bild_hash(s); // вычислить хеш имени
		if (sz != dif_name.size()) // если истинно то у нас есть новое имя
		{
			map_name[t] = 1;
		}
		else
			map_name[t]++; // иначе + 1 имя
	}

	for (set<string>::iterator it = dif_name.begin(); it != dif_name.end(); it++) // перебор всех различных имен в множестве
	{
		long long t = bild_hash(*it); // вычисление хеша имени
		cout << *it << " " << map_name[t] << endl; // вывод имени и сколько оно раз встретилось
	}

	system("pause");

	return 0;
}