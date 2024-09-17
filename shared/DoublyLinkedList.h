#pragma once

#include <cassert>
#include <stdint.h>
#include <algorithm>

template<typename T>
class DoublyLinkedList
{
public:
	struct Node
	{
		T item = T();

		Node* left = nullptr;
		Node* right = nullptr;

		// 참고: prev/next가 아니라 left/right
	};

	DoublyLinkedList()
	{
	}

	~DoublyLinkedList()
	{
		Clear();
	}

	void Clear() // 모두 지워야(delete) 합니다.
	{
		// TODO:
		if(IsEmpty())
			return;
		else{
			while(first_){
				PopFront();
			}
		}
		
		return;
	}

	bool IsEmpty()
	{
		return first_ == nullptr;
	}

	int Size()
	{
		// TODO:
		int size = 0;

		Node *pos = first_;
		while(pos){
			size++;
			pos = pos->right;
		}
		return size;
	}

	void Print()
	{
		using namespace std;

		Node* current = first_;

		if (IsEmpty())
			cout << "Empty" << endl;
		else
		{
			cout << "Size = " << Size() << endl;

			cout << " Forward: ";
			// TODO:
			for(Node *pos = first_; pos != nullptr; pos = pos->right){
				cout << pos->item << ' ';
			}

			cout << endl;

			cout << "Backward: ";
			// TODO:
			Node *pos = last_;
			while(pos){
				cout << pos->item << ' ';
				pos = pos->left;
			}
			cout << endl;
		}
	}

	Node* Find(T item)
	{
		Node *pos = first_;
		while(pos){
			if(item == pos->item)
				return pos;
			pos = pos->right;
		}

		return nullptr; // TODO:
	}

	void InsertBack(Node* node, T item)
	{
		// TODO:
		if(node){
			Node *newNode = new Node;
			newNode->item = item;
			newNode->left = node;
			newNode->right = node->right;

			Node *post = node->right;
			node->right = newNode;
			post->left = newNode;

			if(node == last_){
				last_ = newNode;	
			}
		}
		return;
	}

	void PushFront(T item)
	{
		// TODO:
		Node *newNode = new Node;
		newNode->item = item;
		if(IsEmpty()){
			newNode->right = nullptr;
			first_ = newNode;
			last_ = newNode;
		}
		else{
			newNode->right = first_;
			first_->left = newNode;
			first_ = newNode;
		}
		newNode->left = nullptr;

		return;

	}

	void PushBack(T item)
	{
		// TODO:
		Node *newNode = new Node;
		newNode->item = item;
		if(IsEmpty()){
			newNode->left = nullptr;
			first_ = newNode;
			last_ = newNode;
		}
		else{
			newNode->left = last_;
			last_->right = newNode;
			last_ = newNode;
		}
		newNode->right = nullptr;

		return;
	}

	void PopFront()
	{
		if (IsEmpty())
		{
			using namespace std;
			cout << "Nothing to Pop in PopFront()" << endl;
			return;
		}

		assert(first_);

		// TODO:
		if(first_->right){
			first_ = first_->right;
			delete first_->left;
			first_->left = nullptr;
		}
		else{
			delete first_;
			first_ = nullptr;
			last_ = nullptr;
		}
		
		return;
	}

	void PopBack()
	{
		if (IsEmpty())
		{
			using namespace std;
			cout << "Nothing to Pop in PopBack()" << endl;
			return;
		}

		// 맨 뒤에서 하나 앞의 노드를 찾아야 합니다.

		assert(first_);

		// TODO:
		if(last_->left){
			last_ = last_->left;
			delete last_->right;
			last_->right = nullptr;
		}
		else{
			delete last_;
			first_ = nullptr;
			last_ = nullptr;
		}
		return;
	}

	void Reverse()
	{
		// TODO:
		if(IsEmpty())
			return;
		else{
			Node *pos = first_;
			while(pos){
				std::swap(pos->left,pos->right);
				pos = pos->left;
			}
			std::swap(first_,last_);
		}
		return;
	}

	T Front()
	{
		assert(first_);

		return first_->item; // TODO:
	}

	T Back()
	{
		assert(first_);

		return last_->item; // TODO:
	}

protected:
	Node* first_ = nullptr;
	Node* last_  = nullptr;
};