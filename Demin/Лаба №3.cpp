#include "stdafx.h"
#include "windows.h"
#include <iostream>
#include <string>
using namespace std;

template <class T>
struct Node
{
	T info;
	Node* next = NULL;
};
struct Point
{
	string Name;
	bool Label = false;
};
template <class T>
class List
{
	Node<T>* head;
public:
	List() :head(NULL)
	{}
	void Add(T value)
	{
		Node<T>* NewNode = new Node<T>;
		NewNode->info = value;
		NewNode->next = NULL;
		Node<T>* ptr = head;
		while (ptr && ptr->next)
			ptr = ptr->next;
		if (ptr)
			ptr->next = NewNode;
		else
			head = NewNode;
	}
	void Print()
	{
		cout << "Список";
		Node<T>* ptr = head;
		if (ptr)
		{
			cout << ": ";
			while (ptr->next)
			{
				cout << ptr->info << " -> ";
				ptr = ptr->next;
			}
			cout << ptr->info;
		}
		else cout << " пуст";
	}
};
template <class T>
class Stack
{
	Node<T>* Top;
public:
	Stack() : Top(NULL)
	{}
	void Push(int value)
	{
		Node<T>* newnode = new Node<T>;
		newnode->info = value;
		newnode->next = Top;
		Top = newnode;
	}
	T Pop()
	{
		T ret_info = Top->info;
		Node<T>* ptr = Top;
		Top = Top->next;
		ptr->next = NULL;
		delete ptr;
		return ret_info;
	}
	T GetInfo()
	{
		return Top->info;
	}
	bool IsEmpty()
	{
		return Top == NULL;
	}
};
enum GraphType { Unoriented, Oriented };
class Graph
{
	GraphType Type;
	int Num_Of_Points;
	Point* Points;
	bool** Matr;
public:
	Graph() : Num_Of_Points(0), Points(NULL), Matr(NULL)
	{}
	void Initial(int n)
	{
		Matr = new bool*[n];
		Points = new Point[n];
		for (int i = 0; i < n; i++)
		{
			Matr[i] = new bool[n];
			cout << "Введите название вершины №" << i + 1 << ": ";
			cin >> Points[i].Name;
			int j = 0;
			while (j < i)
			{
				if (Points[j].Name == Points[i].Name)
				{
					cout << "Вершина с таким именем уже существует, повторите ввод названия вершины №" << i + 1 << ": ";
					cin >> Points[i].Name;
					j = -1;
				}
				j++;
			}
		}
		Num_Of_Points = n;
		cout << "Выберите тип графа:\n   1) Неориентированный граф\n   2) Ориентированный граф\nОтвет: ";
		string answer; cin >> answer;
		bool Or = answer == "2" || answer == "2." || answer == "2)";
		bool Unor = answer == "1" || answer == "1." || answer == "1)";
		while (!(Or || Unor))
		{
			cout << "Повторите ответ: : "; cin >> answer;
			Or = answer == "2" || answer == "2." || answer == "2)";
			Unor = answer == "1" || answer == "1." || answer == "1)";
		}
		if (Or)
		{
			Type = Oriented;
			for (int i = 0; i<Num_Of_Points; i++)
				for (int j = 0; j < Num_Of_Points; j++)
				{
					if (i == j)
						Matr[i][i] = 1;
					else
					{
						cout << "Существует дуга между вершинами " << Points[i].Name << " и " << Points[j].Name << "? ";
						cin >> answer;
						bool Yes = answer == "Yes" || answer == "yes" || answer == "1" || answer == "Да" || answer == "да";
						bool No = answer == "No" || answer == "no" || answer == "0" || answer == "Нет" || answer == "нет";
						while (!(Yes || No))
						{
							cout << "Потвторите ответ: "; cin >> answer;
							Yes = answer == "Yes" || answer == "yes" || answer == "1" || answer == "Да" || answer == "да";
							No = answer == "No" || answer == "no" || answer == "0" || answer == "Нет" || answer == "нет";
						}
						if (Yes)
						{
							Matr[i][j] = 1;
							Matr[j][i] = 0;
						}
						else Matr[i][j] = 0;
					}
				}
		}
		else
		{
			Type = Unoriented;
			for (int i = 0; i < Num_Of_Points; i++)
			{
				Matr[i][i] = 1;
				for (int j = i + 1; j < Num_Of_Points; j++)
				{
					cout << "Существует ребро " << Points[i].Name << " <---> " << Points[j].Name << " (" << Points[j].Name << " <---> " << Points[i].Name << ")? ";
					cin >> answer;
					bool Yes = answer == "Yes" || answer == "yes" || answer == "1" || answer == "Да" || answer == "да";
					bool No = answer == "No" || answer == "no" || answer == "0" || answer == "Нет" || answer == "нет";
					while (!(Yes || No))
					{
						cout << "Повторите ответ: "; cin >> answer;
						Yes = answer == "Yes" || answer == "yes" || answer == "1" || answer == "Да" || answer == "да";
						No = answer == "No" || answer == "no" || answer == "0" || answer == "Нет" || answer == "нет";
					}
					Matr[i][j] = Matr[j][i] = (Yes) ? 1 : 0;
				}
			}
		}
	}
	void ClearLabels()
	{
		for (int i = 0; i < Num_Of_Points; i++)
			Points[i].Label = 0;
	}
	bool WayExist(int first, int second)
	{
		int seek = -1;
		Stack<int> S;
		S.Push(first);
		while (seek != second && !S.IsEmpty())
		{
			seek = S.Pop();
			Points[seek].Label = 1;
			for (int i = 0; i < Num_Of_Points; i++)
			{
				if (i != seek && Points[i].Label != 1 && Matr[seek][i] == 1)
					S.Push(i);
			}

		}
		ClearLabels();
		return seek == second;
	}
	bool Connective()
	{
		for (int i = 0; i < Num_Of_Points; i++)
			for (int j = 0; j < Num_Of_Points; j++)
				if (!WayExist(i, j)) return 0;
		return 1;
	}
	int FindStartPoint()
	{
		int i = 0; bool t = 1;
		while (i < Num_Of_Points && t)
		{
			int counter1 = 0, counter2 = 0;
			if (!Type)
			{
				for (int j = 0; j < Num_Of_Points; j++)
					if (i != j && Matr[i][j] == 1) counter1++;                                  //
				t = counter1 % 2 == 0;
			}
			else
			{
				for (int j = 0; j < Num_Of_Points; j++)
				{
					if (i != j)
					{
						if (Matr[i][j] == 1) counter1++;
						if (Matr[j][i] == 1) counter2++;
					}
				}
				t = counter2 - counter1 != 1;
			}
			i++;
		}
		return (!t) ? i - 1 : 0;
	}
	bool Check()
	{
		int Counter1 = 0, Counter2 = 0, i = 0;
		bool t = 1;
		while (t && i < Num_Of_Points)
		{
			if (!Type)
			{
				Counter2 = 0;
				for (int j = 0; j < Num_Of_Points; j++)
					if (i != j && Matr[i][j] == 1) Counter2++;
				if (Counter2 % 2 == 1) Counter1++;
				t = Counter1 < 3;
			}
			else
			{
				int InCounter = 0, OutCounter = 0;
				for (int j = 0; j < Num_Of_Points; j++)
				{
					if (Matr[i][j] == 1) OutCounter++;
					if (Matr[j][i] == 1) InCounter++;
				}
				if (InCounter - OutCounter == 1) Counter1++;
				else if (InCounter - OutCounter == -1) Counter2++;
				else if (InCounter != OutCounter) return 0;
				t = Counter1 < 2 && Counter2 < 2;
			}
			i++;
		}
		return (!Type) ? t && Connective() : (Counter1 == Counter2 == 1) || (Counter1 == Counter2 == 0);
	}
	List<string> FindEulerPath()
	{

		List<string> L;
		if (Check())
		{
			bool **CopyMatr = new bool*[Num_Of_Points];
			for (int i = 0; i < Num_Of_Points; i++)
			{
				CopyMatr[i] = new bool[Num_Of_Points];
				for (int j = 0; j < Num_Of_Points; j++)
					CopyMatr[i][j] = Matr[i][j];
			}
			int StartPoint = FindStartPoint();
			Stack<int> S;
			S.Push(StartPoint);
			while (!S.IsEmpty())
			{
				StartPoint = S.GetInfo();
				int i = 0; bool t = 1;
				while (t && i < Num_Of_Points)
				{
					if (i != StartPoint)
						t = CopyMatr[i][StartPoint] == 0;
					i++;
				}
				i--;
				if (t) L.Add(Points[S.Pop()].Name);
				else
				{
					S.Push(i);
					CopyMatr[i][StartPoint] = CopyMatr[StartPoint][i] = 0;
				}
			}
			return L;
		}
		else
		{
			cout << "Этот граф нельзя начертить не отрывая карандаша от бумаги...\n";
			return L;
		}
	}
	void PrintMatr()
	{
		int MaxLen = 0;
		for (int i = 0; i < Num_Of_Points; i++)
		{
			int Len = sizeof(Points[i].Name);
			if (Len > MaxLen) MaxLen = Len;
		}
		cout << endl << ' ';
		for (int i = 0; i < Num_Of_Points; i++)
			cout << ' ' << Points[i].Name;
		cout << endl;
		for (int i = 0; i < Num_Of_Points; i++)
		{
			cout << Points[i].Name;
			for (int j = 0; j<Num_Of_Points; j++)
				cout << ' ' << Matr[i][j];
			cout << endl;
		}
	}
};


void main()
{
	SetConsoleCP(1251);
	SetConsoleOutputCP(1251);
	Graph MyGraph;
	int n;
	cout << "Введите кол-во вершин графа: "; cin >> n;
	while (n>0)
	{
		MyGraph.Initial(n);
		MyGraph.FindEulerPath().Print();
		cout << endl;
		system("pause");
		cout << endl << "Введите кол-во вершин графа: "; cin >> n;
	}
}
