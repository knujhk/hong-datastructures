#pragma once

#include <cassert>
#include <stdint.h>

template<typename T>
class SinglyLinkedList
{
public:
	struct Node
	{
		T item = T();
		Node* next = nullptr;
	};

	SinglyLinkedList()
	{
	}

	SinglyLinkedList(const SinglyLinkedList& list)
	{
		// TODO: 연결 리스트 복사
		//SinglyLinkedList newList; 이 객체는 지역 변수이므로 복사 생성자 종료되면 소멸함
		
		Node *pos = list.first_;
		//pushback
		while(pos){
			this->PushBack(pos->item);
			pos = pos->next;
		}
	}

	~SinglyLinkedList()
	{
		Clear();
	}

	void Clear() // 모두 지워야(delete) 합니다.
	{
		// TODO: 모두 삭제
		Node *old, *pos = first_;
		while(pos){
			old = pos;
			pos = pos->next;
			delete old;
		}
	}

	bool IsEmpty()
	{
		return first_ == nullptr;
	}

	int Size()
	{
		int size = 0;

		// TODO: size를 하나하나 세어서 반환
		Node *pos = first_;
		while(pos){
			size++;
			pos = pos->next;
		}

		return size;
	}

	T Front()
	{
		assert(first_);

		return first_->item; // TODO: 수정
	}

	T Back()
	{
		assert(first_);
		//리스트에 노드가 한 개 이상이라고 가정

		Node *pos;
		for(pos = first_; pos->next != nullptr; )
			pos = pos->next;


		return pos->item; // TODO: 수정
	}

	Node* Find(T item)
	{
		// TODO: item이 동일한 노드 포인터 반환
		Node *pos = first_;
		while(pos){
			if(item == pos->item)
				return pos;
			pos = pos->next;
		}

		return nullptr;
	}

	void InsertBack(Node* node, T item)
	{
		// TODO:
		if(node){
			Node *newNode = new Node;
			newNode->item = item;
			newNode->next = node->next;
			node->next = newNode;
		}
		return;
	}

	void Remove(Node* n)
	{
		assert(first_);

		// 하나 앞의 노드를 찾아야 합니다.
		// TODO:
		Node *pre, *pos = first_;

		while(pos){
			//pos가 n과 같으면 pre 기준으로 재연결
			//first를 제거해야한다면?
			if(pos == n){
				if(pos == first_){
					first_ = first_->next;
					delete pos;
				}
				else{
					pre->next = pos->next;
					delete pos;
				}
				return;
			}
			pre = pos;
			pos = pos->next;
		}
		return;
	}

	void PushFront(T item)
	{
		// first_가 nullptr인 경우와 아닌 경우 나눠서 생각해보기 (결국은 두 경우를 하나로 합칠 수 있음)

		// 새로운 노드 만들기
		// TODO:
		Node *newNode = new Node;
		newNode->item = item;
		newNode->next = first_;
				
		// 연결 관계 정리
		// TODO:
		first_ = newNode;
	}

	void PushBack(T item)
	{
		Node *newNode = new Node;
		newNode->item = item;
		newNode->next = nullptr;

		if (first_)
		{
			// TODO:
			Node *pos = first_;
			while(pos->next != nullptr)
				pos = pos->next;
			pos->next = newNode;
		}
		else
		{
			// TODO:
			first_ = newNode;
		}
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

		// TODO: 메모리 삭제
		Node *temp = first_;
		first_ = temp->next;
		delete temp;
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
		if(first_->next == nullptr){
			delete first_;
			first_ = nullptr;
			return;
		}
		Node *pre, *pos = first_;
		while(pos->next){
			pre = pos;
			pos = pos->next;
		}
		assert(first_);
		// TODO: 메모리 삭제
		delete pos;
		pre->next = nullptr;
	}

	// void ReverseHelper(Node *pre, Node *pos){
		
	// 	if(!pos->next){
	// 		first_ = pos;
	// 		pos->next = pre;			
	// 		return;
	// 	}
	// 	ReverseHelper(pos,pos->next);
	// 	pos->next = pre;
	// }

	void Reverse()
	{
		// TODO:
		if(this->IsEmpty())
			return;

		Node *pre = nullptr;
		Node *pos = first_;

		// ReverseHelper(pre,pos);

		//재귀를 사용하지 않는 방법?
		//재귀로 해결하는 게 빠르지도 않고 메모리도 많이 씀
		//pre, pos만으로 가능한가?
		//pos가 pre를 가리키도록 만들기 전에 pos->next를 temp에 저장해야 함
		Node *temp;
		while(pos){
			temp = pos->next;
			pos->next = pre;
			pre = pos;
			pos = temp;
		}
		this->first_ = pre;
	}

	void SetPrintDebug(bool flag)
	{
		print_debug_ = flag;
	}

	void Print()
	{
		using namespace std;

		Node* current = first_;

		if (IsEmpty())
			cout << "Empty" << endl;
		else
		{
			cout << "Size = " << Size() << " ";

			while (current)
			{
				if (print_debug_)
				{
					//cout << "[" << current << ", " << current->item << ", " << current->next << "]";

					// 주소를 짧은 정수로 출력 (앞 부분은 대부분 동일하기때문에 뒷부분만 출력)
					cout << "[" << reinterpret_cast<uintptr_t>(current) % 100000 << ", "
						<< current->item << ", "
						<< reinterpret_cast<uintptr_t>(current->next) % 100000 << "]";
				}
				else
				{
					cout << current->item;
				}

				if (current->next)
					cout << " -> ";
				else
					cout << " -> NULL";

				current = current->next;
			}
			cout << endl;
		}
	}

protected:
	Node* first_ = nullptr;

	bool print_debug_ = false;
};