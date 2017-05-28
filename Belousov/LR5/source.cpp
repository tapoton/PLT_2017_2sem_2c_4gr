/*Внешние сортировки: Строка текстового файла имеет следующий вид: 
одна буква фамилии студента, один пробел, количество баллов по аттестации от 0 до 9. 
Отсортировать файл в порядке неубывания баллов.*/

#include <iostream>
#include <fstream>
using namespace std;

void Sort(char *file)//внешняя сортировка слиянием по неубыванию
{
	string Buff1 = "Buff1.txt", Buff2 = "Buff2.txt";
	int  i, j, n = 0;
	char c1, c2;
	int a1, a2;
	fstream f;
	f.open(file, ios::in);
	if (!f.is_open())
	{
		cout << endl << "Can`t open the file";
		return;
	}

	while (!f.eof())
	{
		if (f >> c1 && f >> a1)
			n++; 
	}
	f.close();

	if (n <= 1)return;

	int q = 1; //q - длина упорядоченных строк начиная с 1
	while (q < n)
	{
		//заполнение поочередно buff1 , buff2  по q строк
		f.open(file, ios::in);
		fstream buff1;
		buff1.open(Buff1, ios::out);
		fstream buff2;
		buff2.open(Buff2, ios::out);


		do
		{
			for (i = 0; i < q && !f.eof(); i++)

				if (f >> c1 && f >> a1)
				{
					buff1 << c1 << ' ';
					buff1 << a1 << endl;
				}
			for (j = 0; j < q && !f.eof(); j++)
				if (f >> c2 && f >> a2)
				{
					buff2 << c2 << ' ';
					buff2 << a2 << endl;
				}
		} while (!f.eof());

		f.close();
		buff1.close();
		buff2.close();

		//слияние buff1 , buff2 в f
		f.open(file, ios::out);
		buff1.open(Buff1, ios::in);
		buff2.open(Buff2, ios::in);

		buff1 >> c1;
		buff1 >> a1;
		buff2 >> c2;
		buff2 >> a2;

		while (!buff1.eof() && !buff2.eof())
		{
			i = 0;
			j = 0;
			while (i < q && j < q && !buff1.eof() && !buff2.eof())
			{
				if (a1 < a2)
				{

					f << c1 << ' ';
					f << a1 << '\n';
					buff1 >> c1;
					buff1 >> a1;
					i++;
				}
				else
				{

					f << c2 << ' ';
					f << a2 << '\n';
					buff2 >> c2;
					buff2 >> a2;
					j++;
				}
			}

			//остаток
			while (i < q && !buff1.eof())
			{
				f << c1 << ' ';
				f << a1 << endl;

				buff1 >> c1;
				buff1 >> a1;
				i++;
			}
			while (j < q && !buff2.eof())
			{

				f << c2 << ' ';
				f << a2 << endl;
				buff2 >> c2;
				buff2 >> a2;
				j++;
			}

		}
		//остаток
		while (!buff1.eof())
		{

			f << c1 << ' ';
			f << a1 << endl;
			buff1 >> c1;
			buff1 >> a1;

		}
		while (!buff2.eof())
		{
			f << c2 << ' ';
			f << a2 << '\n';

			buff2 >> c2;
			buff2 >> a2;

		}
		f.close();
		buff1.close();
		buff2.close();
		q *= 2;
	}

	remove("Buff1.txt");
	remove("Buff2.txt");
}

int main()
{
	Sort("students.txt");
	cout << endl;
	system("pause");
	return 0;
}
