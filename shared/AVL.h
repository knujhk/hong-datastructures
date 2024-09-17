#pragma once

#include "BinarySearchTree.h"

template<typename K, typename V>
class AVL : public BinarySearchTree<K, V>
{
public:
	using Base = BinarySearchTree<K, V>;
	using Item = typename BinarySearchTree<K, V>::Item;	//dependent scope에 속하는 type을 using으로 typedef할 땐 
												//typename 키워드로 컴파일러에게 타입 이름인 걸 알려야함
	using Node = typename BinarySearchTree<K, V>::Node;

	//struct Item {
	//	K key = K();	// first
	//	V value = V();	// second
	//};

	//struct Node {
	//	Item item;
	//	Node* left = nullptr;
	//	Node* right = nullptr;
	//};

	int Height(Node* node)
	{
		return Base::Height(node); // 헷갈림 방지용
	}

	int Balance(Node* node)
	{
		if (node)
			return Base::Height(node->left) - Base::Height(node->right);
		else
			return 0;
	}

	Node* RotateLeft(Node* parent)
	{
		// TODO:
		//parent의 right의 left가 없는경우도 있고 left가 있는 경우도 있음
		if(parent && parent->right){
			Node *subtreeRight = parent->right;
			parent->right = subtreeRight->left;
			subtreeRight -> left = parent;
			return subtreeRight;
		}
		
		return nullptr;
	}

	Node* RotateRight(Node* parent)
	{
		// TODO:
		if(parent && parent->left){
			Node *subtreeLeft = parent->left;
			parent->left = subtreeLeft->right;
			subtreeLeft -> right = parent;
			return subtreeLeft;
		}

		return nullptr;
	}

	void Insert(const Item& item)
	{
		root_ = Insert(root_, item);
	}

	Node* Insert(Node* node, const Item& item)
	{
		if (!node)
			return new Node{ item, nullptr, nullptr };

		const auto& key = item.key;

		if (key < node->item.key)
			node->left = Insert(node->left, item);
		else if (key > node->item.key)
			node->right = Insert(node->right, item);
		else
		{
			node->item = item;
			return node;
		}

		int balance = Balance(node);

		// balance가 0, 1, -1 이면 조절할 필요가 없다고 판단

		// LL -> Right Rotation
		if (balance > 1 && Balance(node->left) >= 0){
			node = RotateRight(node);
		}
		
		// RR -> Left Rotation
		if (balance < -1 && Balance(node->right) <= 0)
			node = RotateLeft(node);

		// LR -> Left-Right Rotation
		if (balance > 1 && Balance(node->left) < 0)
		{
			node->left = RotateLeft(node->left);
			node = RotateRight(node);
		}

		// RL -> Right-Left Rotation
		if (balance < -1 && Balance(node->right) > 0)
		{
			node->right = RotateRight(node->right);
			node = RotateLeft(node);
		}

		//this->Print2D();

		return node;
	}

	Node* MaxKeyRight(Node* node)
	{
		assert(node);
		while (node->right)
			node = node->right;
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
		// BST와 동일
		if (!node) return node;

		if (key < node->item.key)
			node->left = Remove(node->left, key);
		else if (key > node->item.key)
			node->right = Remove(node->right, key);
		else
		{
			if (!node->left)
			{
				Node* temp = node->right;
				delete node;
				return temp;
			}
			else if (!node->right)
			{
				Node* temp = node->left;
				delete node;
				return temp;
			}

			Node* temp = Base::MinKeyLeft(node->right);
			node->item = temp->item;
			node->right = Remove(node->right, temp->item.key);
		}

		if (node == NULL)
			return node;

		// 균형 잡기

		int balance = Balance(node);

		// TODO:
		if (balance > 1 && Balance(node->left) >= 0){
			node = RotateRight(node);
		}
		
		// RR -> Left Rotation
		if (balance < -1 && Balance(node->right) <= 0)
			node = RotateLeft(node);

		// LR -> Left-Right Rotation
		if (balance > 1 && Balance(node->left) < 0)
		{
			node->left = RotateLeft(node->left);
			node = RotateRight(node);
		}

		// RL -> Right-Left Rotation
		if (balance < -1 && Balance(node->right) > 0)
		{
			node->right = RotateRight(node->right);
			node = RotateLeft(node);
		}

		return node;
	}

private:
	Node*& root_ = BinarySearchTree<K, V>::root_;
	// this->root_로도 사용 가능
};