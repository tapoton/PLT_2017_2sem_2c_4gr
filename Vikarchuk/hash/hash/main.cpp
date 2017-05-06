#include<iostream>
#include<string>
#include<fstream>
using namespace std;

class Hash
{
	struct Node
	{
		string word;
		int count;
		Node *next;
	};
	Node **head;
	static const int tableSize = 26;

public:
	
	Hash()
	{
		head = new Node *[tableSize];
		for (int i = 0; i < tableSize; i++)
			head[i] = NULL;
	}
	~Hash()
	{
		for(int i=0; i<tableSize; i++)
			if (head[i])
			{
				Node *temp;
				while (head[i])
				{
					temp = head[i];
					head[i] = head[i]->next;
					temp = NULL;
					delete temp;
				}
			}
	}

	int Index(string word)
	{
		int index = 0;
		
		for (int i = 0; i < word.length(); i++)
		{
			index += (int)word[i];
		}
		index %= tableSize;
		
		return index;
	}
	
	Node *Search(string word)
	{
		int index = Index(word);
		Node *temp = head[index];
		while (temp && temp->word != word)
			temp = temp->next;
		return temp;
	}

	void InsertElement(string word)
	{
		if (word != "\0")
		{
			Node *foundWord = Search(word);
			int index = Index(word);

			if (!foundWord)
			{
				Node *curr = new Node;
				curr->word = word;
				curr->count = 1;
				head[index] = curr;
			}
			else
			{
				foundWord->count++;
			}
		}
	}

	void Show()
	{
		cout << "Result is: \n";
		int sum = 0;

		for(int i=0; i<tableSize; i++)
			if (head[i])
			{
				Node *temp;
				while (head[i])
				{
					temp = head[i];
					if (temp->count > 5)
						cout << temp->word << endl;
					head[i] = head[i]->next;
				}
			}
		delete[] head;
	}

};

int main()
{
	ifstream fin("inputText.txt");
	char signs[] = " .,\/*+-=()[]{}:;<>!?";
	int const n = 20;
	char word[n] = "";
	int m = sizeof(signs) - 1;
	Hash hashObj;

	if (!fin)
	{
		cout << "Error opening file.\n";
		return 0;
	}
	char c;
	int i = 0;
	
	string file;
	getline(fin, file);
	int l = file.length(); int j = 0;
	for (int i = 0; i < l; i++)
	{
		word[j] = file[i];
		for(int k=0; k<m; k++)
			if (word[j] == signs[k])
			{
				word[j] = '\0';
				j = -1;
				hashObj.InsertElement(word);
			}
		j++;
	}

	hashObj.Show();

	fin.close();

	system("pause");

	return 0;
}