#include <iostream>
#include <string>

using namespace std;

const int alphabet = 26;


class derevko
{
	struct Node
	{
		char key;
		bool isend;
		Node* child[alphabet];
	};
	void show(Node *tmp, unsigned int level = 1)
	{
		if (tmp == NULL)
		{
			return;
		}
		for (unsigned int i = 1; i < level; i++)
		{
			cout << "\t";
		}
		cout << tmp->key << ' ' << tmp->isend << endl;
		for (int i = 0; i < alphabet; i++)
		{
			show(tmp->child[i], level + 1);
		}
	}
private:
	Node* head;

public:

	derevko()
	{
		head = NULL;
	}
	void zapolnenie(string str)
	{
		if (head == NULL)
		{
			creattree();
		}
		Node* newtree = head;
		for (unsigned int i = 0;i < str.length();i++)
		{
			if (newtree->child[str[i] - 'a'] == NULL)
			{
				char c = str[i];
				bool t = (i + 1 == str.length()) ? true : false;
				int a = str[i] - 'a';
				newitem(newtree, c, t, a);

				if (i + 1 == str.length())
				{
					newtree->child[str[i] - 'a']->isend = true;
				}
			}

			newtree = newtree->child[str[i] - 'a'];
		}
	}
	void creattree()
	{
		head = new Node;
		head->key = '~';
		head->isend = false;
		for (int i = 0; i < alphabet; i++)
		{
			head->child[i] = NULL;
		}
	}
	void newitem(Node*ptr, char c, bool t, int a)
	{
		Node* newtree = new Node;
		newtree->key = c;
		newtree->isend = t;
		for (int i = 0; i < alphabet; i++)
		{
			newtree->child[i] = NULL;
		}
		ptr->child[a] = newtree;
	}
	int poisk(string trs)
	{
		Node *pv = head;
		bool fl = true;
		int i = 0;
		while (fl&&i < trs.length())
		{
			if (pv->child[trs[i] - 'a'] != NULL)
			{
				pv = pv->child[trs[i] - 'a'];
				i++;
			}
			else fl = false;

		}
		int klv = 0;
		if (fl&&i == trs.length())
		{
			klv = podchet(pv, klv);
		}
		return klv;
	}
	int podchet(Node*pv, int klv)
	{
		if (pv == NULL)
		{
			return 0;
		}
		else if (pv->isend && !proverkanadetey(pv))
		{
			return 1;
		}
		else {
			if (pv->isend)
			{
				klv++;
			}
			for (int i = 0; i < alphabet; i++)
			{
				klv = klv + podchet(pv->child[i], 0);
			}
			return klv;
		}
	}
	bool proverkanadetey(Node* pv)
	{
		bool ft = false;
		int i = 0;
		while (!ft&&i < alphabet)
		{
			if (pv->child[i] != NULL)
				ft = true;
			i++;
		}
		cout << ft;
		return ft;
	}
	void show()
	{
		show(head);
	}
};


void main()
{
	setlocale(0, "");
	derevko a;
	string str;
	cout << "Вводите строки через пробел, а потом нажмите Enter:" << endl;
	while (cin.peek() != '\n')
	{
		cin >> str;
		a.zapolnenie(str);
	}
	a.show();
	cout << "\n\nВведите приставку для поиска кол-ва слов:" << endl;
	string trs;
	cin >> trs;
	int klv = a.poisk(trs);
	cout << "Кол-во слов с приставкой ( " << trs << " ) = " << klv << endl;
	system("pause");
}
