#include "stdafx.h"
#include <string>
#include <fstream>
#include <iostream>
using namespace std;

struct Edge
{
	int MaxStream = 0, CurrentStream = 0;
};

struct Node
{
	int Point;
	Node* Next;
};

class List
{
	Node* Head;
public:
	List() : Head(NULL)
	{}
	void Add(int SomePoint)
	{
		Node* NewNode = new Node;
		NewNode->Next = NULL;
		NewNode->Point = SomePoint;
		if (!Head) Head = NewNode;
		else
		{
			Node* ptr = Head;
			while (ptr->Next)
				ptr = ptr->Next;
			ptr->Next = NewNode;
		}
	}
	void Print()
	{
		cout << "Список";
		if (Head)
		{
			Node* ptr = Head;
			cout << ": ";
			while (ptr->Next)
			{
				cout << ptr->Point<<" -> ";
				ptr = ptr->Next;
			}
			cout << ptr->Point;
		}
		else cout << " пуст...";
		cout << endl;
	}
	Node* GetHead()
	{
		return Head;
	}
	void Delete()
	{
		Node* ptr = Head, *oldptr = ptr;
		if (Head && Head->Next)
		{
			while (ptr != Head->Next)
			{
				while (ptr->Next)
				{
					oldptr = ptr;
					ptr = ptr->Next;
				}
				delete ptr;
				oldptr->Next = NULL;
			}
		}
		else if (Head)
		{
			delete Head;
			Head = NULL;
		}
	}
};

class Stack
{
	Node* Top;
public:
	Stack() : Top(NULL)
	{}
	bool IsEmpty()
	{
		return !Top;
	}
	void Push(int SomePoint)
	{
		Node* NewNode = new Node;
		NewNode->Next = Top;
		Top = NewNode;
		Top->Point = SomePoint;
	}
	int Pop()
	{
		int RetPoint = Top->Point;
		Node* DelPtr = Top;
		Top = Top->Next;
		DelPtr->Next = NULL;
		delete DelPtr;
		return RetPoint;
	}
	int View()
	{
		return Top->Point;
	}
};

void MissPtr(char*& ptr)
{
	while (*ptr != ' ')
		ptr++;
	while (*ptr == ' ')
		ptr++;
}

class Graph
{
	int Num_Of_Points, Num_Of_Edges;
	Edge** Matr;
	bool* PointLabels;
	void CreateLabels(List SomePath)
	{
		Node* ptr = SomePath.GetHead();
		while (ptr && ptr->Next)
		{
			int CurrentPoint = ptr->Point, i = 0;
			bool NoWays = 1;
			while (NoWays && i < Num_Of_Points)
			{
				if (i != CurrentPoint && Matr[CurrentPoint][i].CurrentStream < Matr[CurrentPoint][i].MaxStream)
					NoWays = 0;
				i++;
			}
			if (NoWays) PointLabels[CurrentPoint] = 1;
			ptr = ptr->Next;
		}
	}
	void ClearLabels()
	{
		for (int i = 0; i < Num_Of_Points; i++)
			PointLabels[i] = 0;
	}
	void MinStream(List SomePath)
	{
		Node* ptr = SomePath.GetHead();
		int i = ptr->Point, j = ptr->Next->Point, Min = Matr[i][j].MaxStream - Matr[i][j].CurrentStream;
		while (ptr && ptr->Next)
		{
			i = ptr->Point; j = ptr->Next->Point;
			int StreamInList = Matr[i][j].MaxStream - Matr[i][j].CurrentStream;
			if (StreamInList < Min) Min = StreamInList;
			ptr = ptr->Next;
		}
		ptr = SomePath.GetHead();
		while (ptr && ptr->Next)
		{
			i = ptr->Point; j = ptr->Next->Point;
			Matr[i][j].CurrentStream += Min;
			ptr = ptr->Next;
		}
	}
	List FindSomePath()
	{
		int S = 0, T = Num_Of_Points - 1, CurrentPoint = -1;
		Stack A; List RetList;
		A.Push(S);
		while (CurrentPoint != T && !A.IsEmpty())
		{
			CurrentPoint = A.Pop();
			RetList.Add(CurrentPoint);
			for (int i = 0; i < Num_Of_Points; i++)
				if (i != CurrentPoint && Matr[CurrentPoint][i].MaxStream > Matr[CurrentPoint][i].CurrentStream && !PointLabels[i])
					A.Push(i);
		}
		if (CurrentPoint != T) RetList.Delete();
		return RetList;
	}
public:
	Graph() :Matr(NULL), PointLabels(NULL), Num_Of_Edges(0), Num_Of_Points(0)
	{}
	void Initial(string FileName)
	{
		ifstream File(FileName);
		if (File.is_open())
		{
			char buff[10];
			File.getline(buff, 10);
			Num_Of_Points = atoi(buff);
			char* ptr = buff;
			MissPtr(ptr);
			Num_Of_Edges = atoi(ptr);
			Matr = new Edge*[Num_Of_Points];
			PointLabels = new bool[Num_Of_Points];
			for (int i = 0; i < Num_Of_Points; i++)
			{
				Matr[i] = new Edge[Num_Of_Points];
				PointLabels[i] = 0;
			}
			for (int k = 0; k < Num_Of_Edges; k++)
			{				
				File.getline(buff, 10);
				int i = atoi(buff), j;
				ptr = buff;
				MissPtr(ptr); j = atoi(ptr);
				MissPtr(ptr); Matr[i][j].MaxStream = atoi(ptr);
			}
			File.close();
		}
		else cout << "Не удалось открыть файл.../n";
	}
	void PrintMatr()
	{
		for (int i = 0; i < Num_Of_Points; i++)
		{
			for (int j = 0; j < Num_Of_Points; j++)
				cout << '(' << Matr[i][j].MaxStream << " , " << Matr[i][j].CurrentStream << ") ";
			cout << endl;
		}
	}
	void PrintLabels()
	{
		for (int i = 0; i < Num_Of_Points; i++)
			cout << PointLabels[i] << "       ";
		cout << endl;
	}
	void MaxStream(string FileName)
	{
		bool WaysExist = 1;
		while (WaysExist)
		{
			List CurrentList = FindSomePath();
			WaysExist = CurrentList.GetHead();
			if (WaysExist)
			{
				MinStream(CurrentList);
				CreateLabels(CurrentList);
			}
		}
		int Max = 0;
		for (int i = 0; i < Num_Of_Points; i++)
			Max += Matr[i][Num_Of_Points - 1].CurrentStream;
		ofstream File(FileName);
		File << "Максимальный поток графа = " << Max;
		File.close();
	}
};

void main()
{
	setlocale(LC_ALL, "rus");
	Graph G;
	string FileName, ResultFileName;
	cout << "Введите название файла: "; cin >> FileName;
	int n = FileName.length() - 4;
	ResultFileName = FileName.substr(0, n) + "-Result.txt";
	G.Initial(FileName);
	G.MaxStream(ResultFileName);
	system("pause");
}

