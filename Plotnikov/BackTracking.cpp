//ѕо системе двусторонних дорог определить, есть ли в ней город, из которого можно добратьс€ в каждый менее чем за 100 км. 
#include <iostream>
#include <random>
#include <ctime>

using namespace std;

template <typename T>
class Dequeue
{
	struct Node
	{
		T val;
		Node* Next;
		Node* Prev;
		Node(T value)
		{
			val = value;
			Next = Prev = nullptr;
		}
	};
	Node* Base;
	Node* Head;
	int Size;
public:
	Dequeue()
	{
		Base = Head = nullptr;
		Size = 0;
	}
	inline bool is_empty()
	{
		return Base == nullptr;
	}
	void add(T value)
	{
		Node* temp = new Node(value);
		temp->Prev = Head;
		if (!is_empty())
		{
			Head->Next = temp;
			Head = temp;
			if (Size == 1)
				Base->Next = Head;
		}
		else
			Base = Head = temp;
		Size++;
	}
	T& pop()
	{
		if (is_empty())
			throw "Error!\n";
		Node* garb = Head;
		Head = Head->Prev;
		if (Head != nullptr)
			Head->Next = nullptr;
		T rez = garb->val;
		if (Size == 1)
			Base = Head = nullptr;
		else if (Size == 2)
			Base->Next = nullptr;
		delete garb;
		Size--;
		return rez;
	}
	inline const int size()
	{
		return Size;
	}
#ifdef _IOSTREAM_
	void print_as_Queue()
	{
		if (!is_empty())
		{
			Node* temp = Base;
			while (temp->Next != nullptr)
			{
				cout << (temp->val + 1) << "->";
				temp = temp->Next;
			}
			cout << (temp->val + 1);
		}
	}
#endif
};

class Road_System
{
	int road_amount;
	int** Road_Sys;
public:
	Road_System(int amount)
	{
		Road_Sys = new int*[amount];
		for (int i = 0; i < amount; i++)
		{
			Road_Sys[i] = new int[amount];
			Road_Sys[i][i] = 0;
		}
		road_amount = amount;
		for (int i = 1; i < road_amount; i++)
			for (int j = 0; j < i; j++)
				Road_Sys[i][j] = Road_Sys[j][i] = rand() % 100;
	}
	Dequeue<int> simple_traverse(int start, int min_length, int& dist)
	{
		bool *visited = new bool[road_amount];
		int length = 0, curr = start, stuck_point = -1;
		for (int i = 0; i < road_amount; i++)
			visited[i] = false;
		visited[curr] = true;
		Dequeue<int> Container;
		Container.add(curr);
		do
		{
			bool got_stuck = 1;
			for (int i = stuck_point + 1; i < road_amount && got_stuck; i++)
				if ((!visited[i]) && (Road_Sys[curr][i]) && (min_length > (length + Road_Sys[curr][i])))
				{
					length += Road_Sys[curr][i];
					visited[i] = true;
					curr = i;
					Container.add(curr);
					got_stuck = 0;
				}
			stuck_point = -1;
			if (got_stuck && !Container.is_empty())
			{
				visited[curr] = false;
				stuck_point = curr;
				curr = Container.pop();
				length -= Road_Sys[curr][stuck_point];
			}
		} 
		while (Container.size() > 0 && Container.size() < road_amount);
		if (!Container.is_empty())
			dist = length;
		return Container;
	}
	Dequeue<int> traversable(int length, int& dist)
	{
		Dequeue<int> Rez;
		for (int i = 0; i < road_amount && Rez.is_empty(); i++)
		{
			Rez = simple_traverse(i, length, dist);
		}
		return Rez;
	}
#ifdef _IOSTREAM_
	 friend ostream& operator<<(ostream& os, const Road_System& Sys)
	{
		for (int i = 0; i < Sys.road_amount; i++)
		{
			for (int j = 0; j < Sys.road_amount; j++)
				os << Sys.Road_Sys[i][j] << "  ";
			os << "\n";
		}
		return os;
	}
#endif
};

int main()
{
	try
	{
		srand(time(0));
		int roads;
		cout << "Enter amount of roads:\n";
		cin >> roads;
		Road_System R(roads);
		int dist = -1, tr_length = 100;
		cout << "Enter the length of traversing:\n";
		cin >> tr_length;
		cout << "Here's your road system:\n" << R << endl;
		Dequeue<int> Rez = R.traversable(tr_length, dist);
		if (!Rez.is_empty())
		{
			cout << "The path exist, and it is:\n";
			Rez.print_as_Queue();
			cout << ".\nThe length of path is " << dist;
		}
		else
			cout << "Path does not exist in the current case.";
		cout << endl;
	}
	catch (char* a)
	{
		cout << a << endl;
	}
	return 0;
}