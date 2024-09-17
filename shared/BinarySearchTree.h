#pragma once

#include <iomanip>
#include <cassert>
#include <iostream>
#include <math.h>

template<typename K, typename V>
class BinarySearchTree
{
public:
	struct Item // key와 value의 쌍(pair)
	{
		K key = K();	// first
		V value = V();	// second
	};

	struct Node
	{
		Item item;

		Node* left = nullptr;
		Node* right = nullptr;
	};

	void Preorder()
	{
		using namespace std;
		Preorder(root_);
		cout << endl;
	}

	void Preorder(Node* node)
	{
		using namespace std;
		if (node)
		{
			cout << node->item.key << " ";
			Preorder(node->left);
			Preorder(node->right);
		}
	}

	void Inorder()
	{
		using namespace std;
		Inorder(root_);
		cout << endl;
	}

	void Inorder(Node* node)
	{
		using namespace std;
		if (node)
		{
			Inorder(node->left);
			cout << node->item.key << " ";
			Inorder(node->right);
		}
	}

	Item* RecurGet(const K& key)
	{
		return RecurGet(root_, key);
	}

	Item* RecurGet(Node* node, const K& key)
	{
		if (!node) return nullptr; // <- 동일한 키를 가진 노드를 찾지 못하면 nullptr을 반환하는 기능

		if (key < node->item.key)
			return RecurGet(node->left, key);
		if (key > node->item.key)
			return RecurGet(node->right, key);

		return &node->item; // if (key == node->item.key)
	}

	Item* IterGet(const K& key)
	{
		// TODO:
		Node *pos = root_;

		while(pos){
			if(pos->item.key > key)
				pos = pos->left;
			else if(pos->item.key < key)
				pos = pos->right;
			else{
				return &pos->item;
			}
		}

		return nullptr; // No matching
	}

	void Insert(const Item& item)
	{
		using namespace std;
		cout << "Insert " << item.key << item.value << endl;
		root_ = Insert(root_, item);
	}

	Node* Insert(Node* node, const Item& item)
	{
		// 힌트: RecurGet()

		// TODO: 현재 노드가 null일 때 , 왼쪽으로 들어가야 할 때, 오른쪽으로 들어가야 할 때, 이미 key가 있을 때
		if(!node){
			Node *newnode = new Node;
			newnode->item = item;
			newnode->left = nullptr;
			newnode->right = nullptr;
			return newnode; 
		}

		if(item.key < node->item.key){
			node->left=Insert(node->left,item);
		}
		else if(item.key > node->item.key){
			node->right=Insert(node->right,item);
		}
		else{
			node->item = item;
		}
	
		return node;
	}

	void IterInsert(const Item& item)
	{
		// TODO:
		

		//동적할당하고 노드 추가
		Node *newnode = new Node;
		newnode->item = item;
		newnode->left = nullptr;
		newnode->right = nullptr;

		if(!root_){
			root_ = newnode;
			return;
		}

		Node *pos = root_;

		while(pos){
			//왼쪽 or 오른쪽으로 들어가기
			//동일 키 가진 노드 있으면 복사 후 리턴
			if(pos->item.key > item.key){
				if(pos->left){
					pos = pos->left;
				}
				else{
					pos->left = newnode;
					return;
				}
			}
			else if(pos->item.key < item.key){
				if(pos->right){
					pos = pos->right;
				}
				else{
					pos->right = newnode;
					return;
				}
			}
			else{
				pos->item.value = item.value;
				delete newnode;
				return;
			}
		}
	}

	Node* MinKeyLeft(Node* node)
	{
		assert(node);
		while (node->left)
			node = node->left;
		return node;
	}

	void Remove(const K& key)
	{
		using namespace std;
		cout << "Remove " << key << endl;
		root_ = Remove(root_, key);
	}

	Node* Remove(Node* node, const K& key)
	{
		if (!node) return node;

		if (key < node->item.key)
			node->left = Remove(node->left, key);	//remove결과에 따라 remove호출한 노드의 left, right가 달라질 수 있다.
		else if (key > node->item.key)
			node->right = Remove(node->right, key);
		else
		{
			// TODO: node가 제거할 노드인 경우
			//자식이 없을 때 -> delete

			Node *upnode;

			if(!node->left){	//no child or right only
				Node *temp = node->right;
				delete node;
				node = temp;
			}
			else if(!node->right){	//left만 존재
				Node *temp = node->left;
				delete node;
				node = temp;
			}
			else{ //left right 모두 존재
				upnode = MinKeyLeft(node->right);
				node->item = upnode->item;
				node->right = Remove(node->right,upnode->item.key);
			}
		}
		return node;
	}

	int Height()
	{
		return Height(root_);
	}

	int Height(Node* node)	//루트의 레벨이 1
	{
		if (!node) return 0;
		return 1 + std::max(Height(node->left), Height(node->right));	
	}

	void Print2D();
	void PrintLevel(int n);
	void DisplayLevel(Node* p, int lv, int d);

protected:
	Node* root_ = nullptr;
};

// 디버깅 편의 도구
// https://stackoverflow.com/questions/36802354/print-binary-tree-in-a-pretty-way-using-c
template<typename K, typename V>
void BinarySearchTree<K, V>::Print2D()
{
	using namespace std;
	cout << "Height = " << Height() << endl;
	int i = 0;
	while (i < Height()) {
		PrintLevel(i);
		i++;
		cout << endl;
	}
	cout << endl;
}

template<typename K, typename V>
void BinarySearchTree<K, V>::PrintLevel(int n) {
	using namespace std;
	Node* temp = root_;
	int val = (int)pow(2.0, Height() - n + 1.0);
	cout << setw(val) << "";
	DisplayLevel(temp, n, val);
}

template<typename K, typename V>
void BinarySearchTree<K, V>::DisplayLevel(Node* p, int lv, int d) {
	using namespace std;
	int disp = 2 * d;
	if (lv == 0) {
		if (p == NULL) {
			cout << "   ";
			cout << setw(disp - 3) << "";
			return;
		}
		else {
			int result = ((p->item.key <= 1) ? 1 : (int)log10(p->item.key) + 1);
			cout << " " << p->item.key << p->item.value << " ";
			cout << setw(static_cast<streamsize>(disp) - result - 2) << "";
		}
	}
	else
	{
		if (p == NULL && lv >= 1) {
			DisplayLevel(NULL, lv - 1, d);
			DisplayLevel(NULL, lv - 1, d);
		}
		else {
			DisplayLevel(p->left, lv - 1, d);
			DisplayLevel(p->right, lv - 1, d);
		}
	}
}
