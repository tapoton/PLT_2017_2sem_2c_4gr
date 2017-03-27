//14.Задан набор записей следующей структуры: 
//ФИО студента, номер студенческого билета, список несданных зачетов. По заданному номеру студенческого найти остальные сведения.
#include <iostream>
#include <string>

using namespace std;

const int HashSize = 100;

struct Stud 
{
	string key;
	string Fam;
	string Im;
	string Ot;
	string Nesd;
};

class HashTab 
{

	struct Node 
	{
		Stud info;
		Node* next;
	};

	Node* TablMas[HashSize];
	void createNode(Node* current, string key, string Fam, string Im, string Ot, string Nesd) 
	{
		current->info.key = key;
		current->info.Fam = Fam;
		current->info.Im = Im;
		current->info.Ot = Ot;
		current->info.Nesd = Nesd;
		current->next = NULL;
	}

	int Hash(string key) 
	{
		int s = 0;
		for (unsigned int i = 0; i < key.length(); i++) 
		{
			s+= key[i];
		}
		return s % HashSize;
	}

	void Show(Node *t, int l = 0) 
	{
		if (t == NULL) 
		{
			return;
		}		
		cout << t->info.key << endl;		
		cout << t->info.Fam << endl;	
		cout << t->info.Im << endl;
		cout << t->info.Ot << endl;
		cout << t->info.Nesd << endl;
		Show(t->next, l + 1);
		cout << endl;
	}

public:

	HashTab() 
	{
		for (int i = 0; i < HashSize; i++) 
		{
			TablMas[i] = NULL;
		}
	}

	void Add(string key, string Fam, string Im,string Ot, string Nesd) 
	{
		int Ind = Hash(key);
		if (TablMas[Ind]) 
		{
			Node* p = new Node;
			p = TablMas[Ind];
			while (p->next != NULL) 
			{
				p = p->next;
			}
			Node* child = new Node;
			createNode(child, key, Fam, Im, Ot, Nesd);
			p->next = child;
		}
		else 
		{
			Node* p = new Node;
			createNode(p, key, Fam, Im, Ot, Nesd);
			TablMas[Ind] = p;
		}
	}
	void Show()
	{
		cout << endl;
		for (int i = 0; i < HashSize; i++)
		{
			Show(TablMas[i]);
		}
	}

	Stud Poisk(string key) 
	{
		Stud St;
		int Ind = Hash(key);
		Node* a = new Node;
		a = TablMas[Ind];
		if(a) 
		{
			while (a->info.key != key && a->next) 
			{
				a = a->next;
			}
			if (a->next == NULL && a->info.key != key) 
			{
				cout << "Ошибка\n" ;
			}
			else 
			{
				St.Fam = a->info.Fam;
				St.Im = a->info.Im;
				St.Ot = a->info.Ot;
				St.Nesd = a->info.Nesd;
			}	
		}
		else cout << "Ошибка\n";
		
		return St;
	}

};

int main() 
{
	setlocale(LC_ALL, "RUS");
	string StNum, Fam, Im, Ot, Nesd;
	HashTab HT;
	int k;
	Stud St;
	cout << "Ввести номер суденческого и ФИО студента через пробел,а список несданных зачетов через запятую без без пробелов\n";
	while (!(StNum == "end"))
	{
		cin >> StNum;
		if (StNum == "end") break;
		else cin >> Fam >> Im >> Ot >> Nesd;
		HT.Add(StNum, Fam, Im, Ot, Nesd);
	}
	cout << "\nВвести количество студентов для поиска\n ";
	cin >> k;
	for (int i = 0; i < k; i++)
	{
		cout << "\nВвести номер суденческого для поиска ";
		cin >> StNum;
		St = HT.Poisk(StNum);
		if (St.Fam.length() > 0 && St.Im.length() > 0 && St.Ot.length() > 0)
		{
			cout << "Фамилия : " << St.Fam << endl;
			cout << "Имя : " << St.Im << endl;
			cout << "Отчество: " << St.Ot << endl;
			cout << "Cписок несданных зачетов: " << St.Nesd << endl;
		}
	}
	
	system("pause");
  return(0);
}

