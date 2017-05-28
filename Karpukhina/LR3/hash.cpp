#include <iostream>
#include <fstream>
#include <string>
#include <windows.h>

using namespace std;

struct lNode
{
	string word;
	int n;
	lNode* next;
};

struct hashTable
{
	lNode* table[256];
};

//создание эл-та линейного списка
lNode* lCreate(string word)
{
	lNode* first = new lNode;
	first->n = 1;
	first->next = NULL;
	first->word = word;
	return first;
}

//добавление в линейный список
void lPush(lNode* &first, string word)
{
	if (first == NULL)
	{
		first = lCreate(word);
	}
	else
	{
		if (first->word == word)
			first->n++;
		else
		{
			if (first->next == NULL)
				first->next = lCreate(word);
			else lPush(first->next, word);
		}
	}
}

//хэш-функция
unsigned char hashF(string word)
{
	unsigned char h = 0;
	for(int i = 0; i < word.length(); i++)
	   h = h ^ word[i];
	return h;
}

//добавление слова в таблицу
void tablePush(hashTable* table, string word, unsigned char(*hash)(string)) 
{
	lPush(table->table[hash(word)], word);
}

string getWord(ifstream *f) //ф-я считывания одного слова из файла
{
	char c;
	string s;
	f->get(c);
	while (c != ' ' && !f->eof() && c != char(13)) //считываем до пробела
	{
		if (c != '.' && c != ',' && c != '!' && c != '?' && c != '-')  
		{
			s += c;
			f->get(c);
		}
		else if (c == '-') //нашли тире - идем до следующего слова
		{
			f->get(c);
			f->get(c);
		}
		else while (c != ' ' && !f->eof() && c != char(13)) // встретился знак пунктуации. доводим указатель до следующего пробела и выходим из функции
		{
			f->get(c);
		}
	}
	return s;
}

lNode* findName(hashTable* table, string word, unsigned char(*hash)(string))
{
	lNode* ptr = table->table[hash(word)];
	while (ptr)
	{
		if (word == ptr->word)
			return ptr; //найден
		else ptr = ptr->next; //пока не найден, идем по списку
	}
	return 0; //не найден
}


int main()
{
	//поддержка русских символов
	SetConsoleCP(1251);
	SetConsoleOutputCP(1251); 

	hashTable* hashT = new hashTable;
	for (int i = 0; i < 256; i++)
	{
		hashT->table[i] = NULL;
	}
	ifstream fin("input.txt");
	string inp;
	lNode* nameList = NULL;

	//считывание нужных имен
	int n;
	cout << "Введите количество имен" << endl;
	cin >> n;
	cout << endl << "Введите имена" << endl;
	for (int i = 0; i < n; i++)
	{
		cin >> inp;
		lPush(nameList, inp);
	}
	cout << endl;

	//обработка файла с текстом
	while (!fin.eof()) 
	{
		inp = getWord(&fin);
		tablePush(hashT, inp, &hashF);
	}

	//вывод результата
	lNode* ptr = nameList;
	while (ptr)
	{
		cout << ptr->word << ' ';
		lNode* res = findName(hashT, ptr->word, &hashF); //ищем имя из списка в таблице
		if (res) //найдено. выводим количество
		{
			cout << res->n << endl;
		}
		else
		{
			cout << "не найдено" << endl;
		}
		ptr = ptr->next;
	}

	return 0;
}
