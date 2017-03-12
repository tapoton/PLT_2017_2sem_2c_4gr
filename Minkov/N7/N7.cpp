// N7: ¬ trie-дереве определить кол-во слов, которые содержат определЄнное кол-во согласных (это делает ф-ци€ missionX в trie.h)

#include "stdafx.h"
#include "iostream"
#include "trie.h"
#include "string"

using namespace std;

void main()
{
	setlocale(0, "");
	Trie Tree;
	Tree.push("cat"); // 2 согл
	Tree.push("cata"); // 2 согл
	Tree.push("cattingham"); // 7 согл
	Tree.push("catoraptor"); // 6 согл
	Tree.push("car"); // 2 согл
	Tree.push("carpet"); // 4 согл
	Tree.push("dog"); // 2 согл
	Tree.push("dog");
	Tree.print("", true, Tree.getHead());
	cout << "—колько согласных должно быть в слове?\n";
	int cq; cin >> cq;
	//cout << Tree.countCons(Tree.getHead()->child[2]->child[0]->child[17]);
	//cout << Tree.getHead()->child[2]->key;
	cout << "¬ дереве найдено " << Tree.missionX(cq,Tree.getHead()) << " cлов с заданным кол-вом слогаемых\n";
	system("pause");
}

