﻿#include "../shared/Queue.h"

#include <iostream>

using namespace std;

int main()
{
	int n = 7, k = 4; // set n and k to the desired values

	Queue<int> q(n + 1);
	q.SetDebugFlag(false);

	// 처음에 n명 추가 (1, 2, ..., n)
	for (int i = 1; i <= n; i++)
		q.Enqueue(i);
	q.Print();

	// 마지막 한 명이 남을 때까지 반복
	while(q.Size() != 1)
	{
		int temp = 0;
		// k-1 명은 맨 앞에서 뒤로 보내기
		for(int i = 0; i<k-1; i++){
			temp = q.Front();
			q.Dequeue();
			q.Enqueue(temp);
		}
		q.Print();
		// k 번째 사람 처형
		cout << "Executed " << q.Front() << endl;
		q.Dequeue();
	}

	// 최후의 생존자 번호
	cout << "Survivor: " << q.Front() << endl;

	return 0;
}