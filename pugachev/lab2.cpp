#include <iostream>
#include <string>
#include <fstream>

using namespace std;

const int  n = 15;

class hashtabl
{
public:
	struct spisok
	{
		int kolvo;
		string word;
		spisok* next;
	};
	spisok* tabl = new spisok[n];

	hashtabl()
	{
		for (int i = 0; i < n; i++)
		{
		tabl[i].next = NULL;

		}
	}

	/*void insert(string wordp)
	{
	int k = 0;
	spisok* newsp;
	//bool check = 0;
	for (int i = 0; i<n; i++)
	{
	newsp = tabl[i].next;
	while (newsp)
	{
	if (wordp == newsp->word)
	k++;
	newsp = newsp->next;
	}

	}
	if (k == n)
	return;
	newsp = &tabl[k];
	while (newsp->next)
	{
	newsp = newsp->next;
	}
	spisok* paste = new spisok;
	paste->word = wordp;
	newsp->next = paste;
	paste->next = NULL;
	return;
	}*/

	/*void printstrok(int i)
	{
	spisok* newsp = tabl[i].next;
	while (newsp)
	{
	cout << newsp->word << ' ';
	newsp = newsp->next;
	}
	};*/



	int hashfunc(string word)
	{
		int k = 0;
		for (int i = 0; i < word.length(); i++)
			k += (int)word[i];
		return k % n;
	}

	void insert(string pushword)
	{
		int key = hashfunc(pushword);
		spisok* newsp = &tabl[key];
		bool check = 0;
		while (newsp->next)
		{
			newsp = newsp->next;
			if (newsp->word == pushword)
			{
				check = 1;
				newsp->kolvo++;
				return;
			}
			
		}
		if (!check)
		{
			spisok* paste = new spisok;
			paste->word = pushword;
			paste->kolvo = 1;
			newsp->next = paste;
			newsp->next->next = NULL;
		}

		/*{
		newsp->word = pushword;
		newsp->next = NULL;
		newsp->kolvo = 1;
		}*/

	};
	void search(int kolvo)
	{
		spisok* newsp;
		for (int i = 0; i<n; i++)
		{
			newsp = &tabl[i];
			while (newsp)
			{
				if (newsp->kolvo >= kolvo)
					cout << newsp->word << " ";
				newsp = newsp->next;
			}
			
		}
	}

};

int main()
{
	string word;
	char simb;
	hashtabl newht;
	FILE* fin = fopen("Text.txt", "r");
	if (fin != NULL)
		while ((simb = fgetc(fin)) != EOF) // посимвольно читаем файл;
		{
			if ((simb != '.') && (simb != ',') && (simb != ' '))
				word += simb;
			else
			{
				newht.insert(word);//функция хэширования;
				word.clear();
			}
		}
	newht.search(4);
	//newht.printstrok(4);
	system("pause");
	return 0;
}