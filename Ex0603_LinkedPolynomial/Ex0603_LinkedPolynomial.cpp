#include <iostream>
#include <math.h>
#include "../shared/SinglyLinkedList.h"

using namespace std;

//singlylinkedlist의 find와 insertionback을 오버라이딩해서 활용가능

struct Term
{
	float coef;
	int exp;
};

class LinkedPolynomial : public SinglyLinkedList<Term>
{
public:
	typedef SinglyLinkedList<Term>::Node Node;

	void NewTerm(float coef, int exp)
	{
		// TODO: 오름차순으로 집어넣어주기
		//노드 추가할 때마다 동적할당을 해주기 때문에 리사이징 고려x
		//추가하고자 하는 항과 동일한 차수의 항이 이미 존재한다면 새 항으로 '교체'

		Term item = {coef,exp};

		if(IsEmpty()){
			PushFront(item);
			return;
		}

		Node *pos = Find(exp);
		Node *pre = nullptr;

		if(pos){	//동일한 차수의 항이 존재하는 경우
			pos->item.coef = coef;
		}
		else{
			if(!first_->next){
				if(exp < first_->item.exp){
					PushFront(item);
				}
				else{
					PushBack(item);
				}
				return;
			}	
			pos = first_;
			while(pos){
				if(pos->next == nullptr || exp < pos->next->item.exp){
					InsertBack(pos,item);
					return;
				}
				pos = pos->next;
			}
		}
	}

	float Eval(float x)
	{
		float temp = 0.0f;

		// TODO:
		Node *pos = first_;
		while(pos){
			temp += pos->item.coef * powf(x,pos->item.exp);
			pos = pos->next;
		}

		return temp;
	}

	LinkedPolynomial Add(const LinkedPolynomial& poly)
	{
		// this와 poly의 terms_가 exp의 오름차순으로 정렬되어 있다고 가정
		// 하나의 다항식 안에 exp가 중복되는 term이 없다라고 가정 (한 exp는 하나의 term만 존재)

		LinkedPolynomial temp;

		Node* i = this->first_;
		Node* j = poly.first_;

		// TODO:
		while(i && j){
			if(i->item.exp < j->item.exp){
				temp.NewTerm(i->item.coef,i->item.exp);
				i = i->next;
			}
			else if(i->item.exp > j->item.exp){
				temp.NewTerm(j->item.coef, j->item.exp);
				j = j->next;
			}
			else{
				temp.NewTerm(i->item.coef + j->item.coef,i->item.exp);
				i = i->next;
				j = j->next;
			}
		}
		while(i){
			temp.NewTerm(i->item.coef,i->item.exp);
			i = i->next;
		}
		while(j){
			temp.NewTerm(j->item.coef, j->item.exp);
			j = j->next;
		}

		return temp;
	}

	void Print()
	{
		// TODO:
		if(!first_){
			cout << "it has no term\n";
			return;
		}
		else{
			cout << first_->item.coef << "x^" << first_->item.exp;
		}
		Node *pos = first_->next;
		while(pos){
			cout << " + " <<pos->item.coef << "x^" << pos->item.exp;
			pos = pos->next;
		}

		cout << endl;
	}

	Node* Find(int exp)
	{
		// TODO: item이 동일한 노드 포인터 반환
		Node *pos = first_;
		while(pos){
			if(exp == pos->item.exp)
				return pos;
			pos = pos->next;
		}

		return nullptr;
	}

	void InsertBack(Node* node, Term item)
	{
		// TODO:
		Node *pos = first_;
		while(pos){
			if(pos == node){
				Node *newNode = new Node;
				newNode->item = item;
				newNode->next = pos->next;
				pos->next = newNode;
				return;
			}

			pos = pos->next;
		}

		return;
	}

private:
};

int main()
{
	using namespace std;

	LinkedPolynomial p1;

	// exp가 작은 항부터 추가한다고 가정
	p1.NewTerm(1.0f, 0);	// 1 * x^0 = 1
	p1.NewTerm(1.5f, 1);	// 1.5 * x^1
	p1.NewTerm(2.0f, 2);	// 2 * x^2

	p1.Print(); // 1 + 1.5*x^1 + 2*x^2

	cout << p1.Eval(0.0f) << endl; // 1 + 1.5*0 + 2*0^2 = 1
	cout << p1.Eval(1.0f) << endl; // 1 + 1.5*1 + 2*1^2 = 4.5
	cout << p1.Eval(2.0f) << endl; // 1 + 1.5*2 + 2*2^2 = 1 + 3 + 8 = 12

	cout << endl;

	// Add() Test1
	cout << "Add() Test" << endl;
	{
		LinkedPolynomial p1; // max_degree는 기본값으로 설정

		// exp가 작은 항부터 추가한다고 가정
		p1.NewTerm(1.0f, 0);
		p1.NewTerm(1.5f, 1);
		p1.NewTerm(2.0f, 2);

		p1.Print(); // 1 + 1.5*x^1 + 2*x^2

		LinkedPolynomial p2;

		// exp가 작은 항부터 추가한다고 가정
		p2.NewTerm(1.0f, 1);
		p2.NewTerm(3.0f, 2);
		p2.NewTerm(5.0f, 7);
		p2.NewTerm(2.0f, 11);

		p2.Print(); // 1*x^1 + 3*x^2 + 5*x^7 + 2*x^11

		cout << endl;

		LinkedPolynomial psum = p1.Add(p2);
		psum.Print(); // 1 + 2.5*x^1 + 5*x^2 + 5*x^7 + 2*x^11

		cout << endl;
	}

	// Add() Test2
	cout << "Add() Test2" << endl;
	{
		LinkedPolynomial p1; // max_degree는 기본값으로 설정

		// exp가 작은 항부터 추가한다고 가정
		p1.NewTerm(1.0f, 0);
		p1.NewTerm(1.5f, 1);
		p1.NewTerm(2.0f, 2);
		p1.NewTerm(5.0f, 7);
		p1.NewTerm(3.5f, 10);
		p1.NewTerm(5.5f, 20);
		p1.NewTerm(5.0f, 1000);

		p1.Print(); // 1 + 1.5*x^1 + 2*x^2 + 5*x^7 + 3.5*x^10 + 5.5*x^20 + 5*x^1000

		LinkedPolynomial p2;

		// exp가 작은 항부터 추가한다고 가정
		p2.NewTerm(3.2f, 0);
		p2.NewTerm(1.0f, 1);
		p2.NewTerm(3.0f, 2);
		p2.NewTerm(2.0f, 11);

		p2.Print(); // 3.2 + 1*x^1 + 3*x^2 + 2*x^11

		cout << endl;

		LinkedPolynomial psum = p1.Add(p2);
		psum.Print(); // 4.2 + 2.5*x^1 + 5*x^2 + 5*x^7 + 3.5*x^10 + 2*x^11 + 5.5*x^20 + 5*x^1000

		cout << endl;
	}

	return 0;
}
