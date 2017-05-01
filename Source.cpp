// №8 Из trie-дерева удалить все слова , которые содержат указанную подстроку
#include <iostream>
#include <string>

using namespace std;
const int MAXL = 100;

struct Node
{
	int info;
	Node *next[26]; //26 символов в анг.алфавите
};

void add(Node *t, string s, int k) // добавление слова в дерево
{
	if (s.length() > k)
	{
		int ind = s[k] - 'a';
		if (t->next[ind] == NULL)//если вершины нет
		{
			Node *nt;// создаем новую
			nt = new Node;
			nt->info = 0;
			for (int i = 0; i < 26; i++)
				nt->next[i] = NULL;
			t->next[ind] = nt;
		}
		add(t->next[ind], s, k + 1);
	}
	else
		t->info += 1;
}

void dell(Node *t) // удаление всего поддерева
{
	for (int i = 0; i < 26; i++) // удаление всех поддеревьев из данной вершины
	{
		if (t->next[i] != NULL) // проверка наличия поддерева по данному направлению
		{
			dell(t->next[i]); // рекурсивно вызываем
			t->next[i] = NULL;
		}
	}
	delete t;
}

bool faind(Node *t, string s, int k) // проверка наличия подстроки начиная с вершины t
{
	if (s.length() == k)
		return (true);
	else
		if (t->next[s[k] - 'a'] == NULL)
			return (false);
		else
			return (faind(t->next[s[k] - 'a'], s, k + 1));
}

void go(Node *t, string s) // обход всего дерева и поиск слов содержащих подстроку S
{
	if (faind(t, s, 0)) // проверка наличия подстроки начиная с вершины T
	{
		Node *v;
		v = t;
		for (int i = 0; i < s.length(); i++) // найдем вершину, на которой заканчивается данная подстрока начиная с T
		{
			v = v->next[s[i] - 'a'];
		}
		Node *p;
		p = t;
		for (int i = 0; i < s.length() - 1; i++) // предыдущая вершина к v
		{
			p = p->next[s[i] - 'a'];
		}
		p->next[s[s.length() - 1] - 'a'] = NULL; // отсоединим v от дерева и удалим все поддерево включая v
		dell(v);
	}
	for (int i = 0; i < 26; i++) // ведем поиск слов с подстрокой s дальше
	{
		if (t->next[i] != NULL)
			go(t->next[i], s);
	}
}

void rebild(Node *t, Node *pr, int c) // перестройка дерева (удаление пустых веток образовавшихся из-за удаления слов)
{
	for (int i = 0; i < 26; i++) // перестроить все поддеревья
	{
		if (t->next[i] != NULL)
			rebild(t->next[i], t, i);
	}
	if (pr != NULL)
		if (t->info == 0) // перестроить текущую вершину если необходимо
		{
			bool f = true;
			for (int i = 0; i < 26; i++)
			{
				f &= (t->next[i] == NULL);
			}
			if (f)
			{
				pr->next[c] = NULL;
				delete t;
			}
		}
}

void print(Node *t, string s) // вывод на экран после всех преобразований
{
	for (int i = 0; i < t->info; i++)
		cout << s << endl;
	for (int i = 0; i < 26; i++)
	{
		if (t->next[i] != NULL)
			print(t->next[i], s + (char)('a' + i));
	}
}

int main()
{
	int n;
	Node *tree;
	tree = new Node;
	tree->info = 0;
	for (int i = 0; i < 26; i++)
		tree->next[i] = NULL;
	cout << "Number of words :" << endl;
	cin >> n; // количество добавленных слов
	cout << "Enter the string :" << endl;
	for (int i = 0; i < n; i++)
	{
		string s;
		cin >> s;
		add(tree, s, 0); // добавление слов в дерево
	}

	string p;
	cout << "Enter the substring:" << endl;
	cin >> p; // та нужная подстрока
	go(tree, p); // удаление всех слов содержащих подстроку p
	rebild(tree, NULL, 0); //перестроить дерево после всех преобразований 

	cout << endl;
	cout << "New tree:" << endl;
	print(tree, "");

	system("pause");
	return 0;
}