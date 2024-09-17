#pragma once

#include "Queue.h"

#include <cassert>
#include <iostream>
#include <iomanip>

// Double Ended Queue (덱, dequeue와 구분)
template<typename T>
class Deque : public Queue<T>
{

	typedef Queue<T> Base;

public:
	Deque(int capacity)
		: Queue<T>(capacity)
	{
	}

	T& Front()
	{
		return Base::Front();
	}

	T& Back()
	{
		return Base::Rear();
	}

	void PushFront(const T& item)
	{
		if (Base::IsFull())
			Base::Resize();

		// TODO:
		queue_[front_] = item;
		front_ = (front_ + capacity_ - 1) % capacity_;
	}

	void PushBack(const T& item)
	{
		Base::Enqueue(item);
	}

	void PopFront()
	{
		Base::Dequeue();
	}

	void PopBack()
	{
		assert(!Base::IsEmpty());
		// TODO:
		rear_ = (rear_ + capacity_ - 1) % capacity_;
	}

private:
	// Queue와 동일, front_, rear_ 등 상속하여 
	//typedef Queue<T> Base;
	T* &queue_ = Base::queue_;
	int &front_ = Base::front_;
	int &rear_ = Base::rear_;
	int &capacity_ = Base::capacity_;
};
