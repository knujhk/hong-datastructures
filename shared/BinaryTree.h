#pragma once

#include <iostream>
#include <fstream>
#include <string> // BinaryTree 출력
#include <cmath>

#include "Queue.h"
#include "Stack.h"

using namespace std;

template<typename T>
class BinaryTree
{
public:
	struct Node
	{
		T item = T();
		Node* left = nullptr; // Left child
		Node* right = nullptr; // Right child
	};

	// 디버깅 도구: 큐에서 주소 대신에 아이템 출력
	class MyQueue : public Queue<Node*>
	{
	public:
		void Print()
		{
			using namespace std;
			cout << "queue\n:";
			for (int i = (this->front_ + 1) % this->capacity_; i != (this->rear_ + 1) % this->capacity_; i = (i + 1) % this->capacity_)
				cout << this->queue_[i]->item << " ";
			cout << endl;
		}
	};

	// 디버깅 도구: 스택에서 주소 대신에 아이템 출력
	class MyStack : public Stack<Node*>
	{
	public:
		void Print()
		{
			using namespace std;
			cout << "stack\n:";
			for (int i = 0; i < this->Size(); i++)
				cout << this->stack_[i]->item << " ";
			cout << endl;
		}
	};

	BinaryTree() {}

	BinaryTree(Node* root)
	{
		root_ = root;
	}

	bool IsEmpty()
	{
		return root_ == nullptr;
	}

	void Visit(Node* node)
	{
		using namespace std;
		cout << node->item << " "; // 수행하고 싶은 작업 구현(여기서는 출력)
	}

	int Sum()
	{
		return Sum(root_);
	}

	int Sum(Node* node)
	{
		MyQueue queue;
		Node *pos;
		int result = 0;

		if(!root_)
			return 0;

		queue.Enqueue(root_);
		while(!queue.IsEmpty()){
			pos = queue.Front();
			queue.Dequeue();
			result += pos->item;
			
			if(pos->left){
				queue.Enqueue(pos->left);
			}
			if(pos->right){
				queue.Enqueue(pos->right);
			}
		}
		return result;
	}

	int Height()
	{
		return Height(root_);
	}

	int Height(Node* node)
	{	
		
		if(!node)
			return -1;
		
		MyQueue queue;
		Node *temp;
		int height = -1;
		int countOfCurrent = 0;

		queue.Enqueue(node);
		while(!queue.IsEmpty()){	//while 조건 참이면 하위 레벨 존재하는 것,
			height++;
			countOfCurrent = queue.Size();
			
			for(int i = 0; i < countOfCurrent; i++){
				temp = queue.Front();
				queue.Dequeue();

				if(temp->left){
					queue.Enqueue(temp->left);
				}
				if(temp->right){
					queue.Enqueue(temp->right);
				}
			}
		}
		return height;

		//재귀쓰는 방법
		/*
		if(!node)
			return -1;
		
		return 1 + std::max(Height(node->left,node->right));
		*/
	}

	~BinaryTree()
	{
		DeleteTree(root_);
	}

	void DeleteTree(Node* node)
	{
		if (node)
		{
			DeleteTree(node->left);
			DeleteTree(node->right);
			delete(node);
		}
	}

	void Preorder() { Preorder(root_); }
	void Preorder(Node* node)
	{
		// TODO:
		if(!node)
			return;
		
		cout << ' ' << node->item;
		Preorder(node->left);
		Preorder(node->right);
	};

	void Inorder() { Inorder(root_); }
	void Inorder(Node* node)
	{
		// TODO:
		if(!node)
			return;
		
		Inorder(node->left);
		cout << ' ' << node->item;
		Inorder(node->right);
	}

	void Postorder() { Postorder(root_); }
	void Postorder(Node* node)
	{
		// TODO:
		if(!node)
			return;
		
		Postorder(node->left);
		Postorder(node->right);
		cout << ' ' << node->item;
	}

	void LevelOrder()
	{
		//재귀 사용하지 않음
		Queue<Node*> q; // 힌트: MyQueue q;
		Node *current;

		q.Enqueue(root_);
		while (!q.IsEmpty())
		{
			current = q.Front();
			q.Dequeue();
			Visit(current);
			// TODO:
			if(current->left){
				q.Enqueue(current->left);
			}
			if(current->right){
				q.Enqueue(current->right);
			}
		}
	}

	void IterPreorder()
	{
		if (!root_) return;

		MyStack s; // 힌트: MyStack q;
		s.Push(root_);
		Node *current;

		while (!s.IsEmpty())
		{
			// TODO:
			current= s.Top();
			s.Pop();
			Visit(current);

			if(current->right){
				s.Push(current->right);
			}
			if(current->left){
				s.Push(current->left);
			}
			cout << "stack: ";
			s.Print();
		}
	}

	void IterInorder()
	{
		if (!root_) return;

		MyStack s;
		Node* current = root_;

		while (current || !s.IsEmpty())
		{
			// TODO:
			
			while(current){
				s.Push(current);
				current = current->left;
			}
			current = s.Top();
			s.Pop();
			Visit(current);
			current = current->right;
			
		}
	}

	void IterPostorder()
	{
		if (!root_) return;

		MyStack s1, s2;
		s1.Push(root_);
		//Node *current = s1.Top()->left;

		//모범답안
		while (!s1.IsEmpty())
		{
			// TODO:
			Node *node = s1.Top();
			s1.Pop();
			s2.Push(node);

			if(node->left)
				s1.Push(node->left);
			if(node->right)
				s1.Push(node->right);
		}
		while (!s2.IsEmpty())
		{
			// TODO:
			Node *node = s2.Top();
			s2.Pop();

			Visit(node);
		}

		//내 답안
		/*
		while(!s1.IsEmpty()){
			while (!s1.IsEmpty() || current)
			{
				// TODO:
				while(current){
					s1.Push(current);

					current = current->left;
				}
				current = s1.Top();
				s1.Pop();
				s2.Push(current);
				current = current->right;
				if(!current){
					break;
				}
			}

			while (!s2.IsEmpty())
			{
				// TODO:
				Visit(s2.Top());
				s2.Pop();
			}
		}
		*/
		

	}

	void Print2D();
	void PrintLevel(int n);
	void DisplayLevel(Node* p, int lv, int d);

protected:
	Node* root_ = nullptr;
};

// 디버깅 편의 도구
// https://stackoverflow.com/questions/36802354/print-binary-tree-in-a-pretty-way-using-c
template<typename T>
void BinaryTree<T>::Print2D()
{
	using namespace std;
	int i = 0;
	while (i < Height()+1) {
		PrintLevel(i);
		i++;
		cout << endl;
	}
}

template<typename T>
void BinaryTree<T>::PrintLevel(int n) {
	using namespace std;
	Node* temp = root_;
	int val = (int)std::pow(2.0, Height() - n + 1.0);
	cout << setw(val) << "";
	DisplayLevel(temp, n, val);
}

template<typename T>
void BinaryTree<T>::DisplayLevel(Node* p, int lv, int d) {
	using namespace std;
	int disp = 2 * d;
	if (lv == 0) {
		if (p == NULL) {
			cout << "   ";
			cout << setw(disp - 3) << "";
			return;
		}
		else {
			int result = ((p->item <= 1) ? 1 : (int)log10(p->item) + 1);
			cout << " " << p->item << " ";
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
