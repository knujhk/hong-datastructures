#include <iostream>
#include <cmath>

using namespace std;

int SequentialSearch(int arr[], int start, int stop, int x)
{
	for (int i = start; i < stop; i++)
	{
		if (arr[i] == x)
			return i;
	}

	return -1;
}

int makeIndexTable(int arr[],int **keys, int **indices, int n){
	//색인 테이블을 만들고자 하는 대상 리스트 사이즈가 n일 때 
	//테이블 사이즈 m은 어떻게 결정할까?
	//-> m제곱이 n과 최대한 가깝게
	int m = int(sqrt(n));

	*keys = new int[m];
	*indices = new int[m+1];

	for(int k = 0; k < m; k++){
		(*keys)[k] = arr[k*m];	//간접 참조가 배열 연산자보다 우선순위 낮다.
		(*indices)[k] = k*m;
	}
	(*indices)[m] = n;

	return m;	//색인 갯수 반환
}

int main()
{
	int arr[] = { 1, 2, 8, 13, 22, 45, 55, 75, 88 };
	int n = sizeof(arr) / sizeof(arr[0]);

	// int keys[] = { 1, 13, 55 };
	// int kn = sizeof(keys) / sizeof(keys[0]);

	// int indices[] = { 0, 3, 6, n }; // 마지막에 n 하나 더 추가

	int *keys,*indices;
	int kn = makeIndexTable(arr,&keys,&indices,n);

	int found = 0;

	for (int x : {1, 2, 8, 13, 22, 45, 55, 75, 88, 99, -1, 47, 101, 1000, 7, 10, 50, 60 })
	{
		found = 0;
		if (x < arr[0] || x > arr[n - 1])
			cout << x << " was not found" << endl;
		else
		{
			// TODO: 
			// int low = 0, high = 0;	//x가 arr[0]이상이므로 탐색범위의 초기값은 low = 0 
			// int index = 0;
			// for(int i = 0; i < kn; i++){
			// 	if(x > keys[i]){
			// 		low = indices[i] + 1;
			// 		high = indices[i+1] - 1;
			// 	}
			// 	else if(x < keys[i])
			// 		break;
			// 	else{
			// 		cout << x << " was found on index " << indices[i] << endl; 
			// 		found = 1;
			// 		break;
			// 	}
			// }
			// if(!found){
			// 	index = SequentialSearch(arr,low,high,x);
			// 	if(index == -1){
			// 		cout << x << " was not found" << endl;
			// 	}
			// 	else{
			// 		cout << x << " was found on index " << index << endl;
			// 	}
			// }

			//방법2
			int k = 0;
			while(k < kn-1 && x >= keys[k+1])
				k++;

			int found = SequentialSearch(arr,indices[k],indices[k+1],x);
			if(found == -1){
					cout << x << " was not found" << endl;
				}
				else{
					cout << x << " was found on index " << found << endl;
				}
		}
	}

	delete[] keys;
	delete[] indices;

	return 0;
}
