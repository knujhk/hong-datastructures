#include <iostream>
#include <iomanip>
#include <chrono>
#include <algorithm> // swap
#include <math.h>
#include <fstream>

using namespace std;
using namespace std::chrono;

bool CheckSorted(int* arr, int size)
{
	for (int i = 0; i < size - 1; i++)
	{
		if (arr[i] > arr[i + 1])
			return false;
	}

	return true;
}

void Print(int* arr, int size)
{
	for (int i = 0; i < size; i++)
		cout << setw(3) << arr[i] << " ";
	cout << endl;
}

void Print(int* arr, int size, int start, int gap)
{
	for (int i = 0; i < size; i++)
	{
		if ((i - start) % gap == 0)
			cout << setw(3) << arr[i] << " ";
		else
			cout << "    ";
	}
	cout << endl;
}

void InsertionSort(int arr[], int n)
{
	for (int i = 1; i < n; i += 1)
	{
		int key = arr[i];
		int j = i;
		for (; j > 0 && arr[j - 1] > key; j -= 1)
			arr[j] = arr[j - 1];
		arr[j] = key;
	}
}

void InsertionSort(int arr[], int n, int gap) // gap 추가
{											
	cout << "gap = " << gap << endl;

	for (int i = gap; i < gap * 2; i += 1) //i는 각 부분 리스트의 시작 위치+gap 
									 //왜냐하면 올바른 위치에 집어넣고자 하는 요소 
									//왼쪽에 최소한 한 개는 있어야 함
	{
		cout << "Before : ";
		Print(arr, n, i, gap);

		// TODO:
		int key;
		int j,k;
		for(j = i; j < n; j += gap){
			key = arr[j];
			for(k = j; k >= i && arr[k-gap] > key; k = k-gap){
				arr[k] = arr[k-gap];
			}
			arr[k] = key;
		}


		
		cout << " After : ";
		Print(arr, n, i, gap);
	}
}

void ShellSort(int arr[], int n)
{
	for (int gap = n / 2; gap > 0; gap /= 2)	//각각의 gap에 대한 반복문 실행 안에서 여러개 부분 리스트가 정렬됨
	{
		cout << "         ";
		Print(arr, n);

		InsertionSort(arr, n, gap);
	}

	cout << "         ";
	Print(arr, n);
	cout << endl;
}

int main()
{
	//int arr[] = { 99, 83, 18, 66, 7, 54, 95, 86, 47, 69, 25, 28 };
	int arr[250]; 
	for(int i = 0; i<sizeof(arr); i++){
		arr[i] = 250 - i;
	}
	int n = sizeof(arr) / sizeof(arr[0]);

	auto start = high_resolution_clock::now();
	ShellSort(arr, n);
	auto stop = high_resolution_clock::now();
	auto duration = double(duration_cast<nanoseconds>(stop - start).count()) / 1000.0;

	cout << boolalpha << CheckSorted(arr,250) << endl;
	cout << "duration : " <<duration << '\n';
	// 최악 O(n^2), 평균 O(n^1.5)
}

