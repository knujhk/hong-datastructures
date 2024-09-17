#include <iostream>
#include <iomanip>
#include <math.h>

using namespace std;

bool CheckSorted(int* arr, int size)
{
	for (int i = 0; i < size - 1; i++)
	{
		if (arr[i] > arr[i + 1])
			return false;
	}

	return true;
}

void Print(int* arr, int low, int high, int n)
{
	for (int i = 0; i < n; i++)
		if (i >= low && i <= high)
			cout << setw(3) << arr[i] << " ";
		else
			cout << "    ";
	cout << endl;
}

// Hoare partition scheme
int midIndex(int arr[], int a, int b, int c){
	if(arr[a] >= arr[b]){
		if(arr[c] > arr[a])
			return a;
		else if(arr[c] > arr[b])
			return c;
		else
			return b;
	}
	else{
		if(arr[a] > arr[c])
			return a;
		else if(arr[b] >= arr[c])
			return c;
		else
			return b;
	}
}

int Partition(int arr[], int low, int high, int n)
{
	int pivot_index = midIndex(arr,low,high,(low+high)/2);
	int pivot = arr[pivot_index];
	int l = low;
	int r = high + 1;

	std::swap(arr[pivot_index],arr[low]);	//low + 1 인덱스부터 체크해야함

	while (true)
	{
		do{
			l++;
		}while(arr[l] < pivot);	// 

		do{
			r--;
		}while(arr[r] > pivot);	// 
			
		if(l >= r){ 
			swap(arr[low],arr[r]);
			return r;
		}

		std::swap(arr[l],arr[r]);

		cout << "pivot=" << pivot << ", l=" << l << ", r=" << r << endl;
		Print(arr, low, high, n);
	}


}

void QuickSort(int arr[], int low, int high, int n) // 마지막 n은 출력용
{
	if (low >= 0 && high >= 0 && low < high)
	{
		// Partitioning Index
		int p = Partition(arr, low, high, n);

		QuickSort(arr, low, p-1, n); // Note: the pivot is now included
		QuickSort(arr, p + 1, high, n);
	}
}

int main()
{
	int arr[] = { 4, 17, 2, 9, 7, 5, 8, 1, 5,1,2,543,1,7,333,8,3,9,2,14, 6 ,67,12,35,78,111,2,9,7,5};
	//int arr[] = {5,4,2,1,2,5};
	int n = sizeof(arr) / sizeof(arr[0]);

	cout << "         ";
	Print(arr, 0, n - 1, n);
	cout << endl;

	QuickSort(arr, 0, n - 1, n);

	cout << "         ";
	Print(arr, 0, n - 1, n);
	cout << endl;
}
