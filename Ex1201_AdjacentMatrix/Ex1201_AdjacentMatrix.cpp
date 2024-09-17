#include <iostream>
#include <cassert>
#include <stack>
#include <queue>

#include "../shared/Stack.h"
#include "../shared/Queue.h"

using namespace std;

template<typename T>
class AdjMatGraph // Adjacent Matrix Graph
{
public:
	struct Vertex // Node
	{
		T item = T();
	};

	AdjMatGraph(int max_vertices)
	{
		max_vertices_ = max_vertices; // capacity

		matrix_ = new int* [max_vertices_];
		for (int r = 0; r < max_vertices_; r++) {
			matrix_[r] = new int[max_vertices_];
			for (int c = 0; c < max_vertices_; c++)
				matrix_[r][c] = 0;
		}

		vertices_ = new Vertex[max_vertices_];

		n_ = 0;
	}

	~AdjMatGraph()
	{
		delete[] vertices_;

		for (int i = 0; i < max_vertices_; i++)
			delete[] matrix_[i];
		delete[] matrix_;

		if (visited_)
			delete[] visited_;
	}

	void PrintMatrix()
	{
		using namespace std;
		if (n_)
			for (int r = 0; r < n_; r++) {
				for (int c = 0; c < n_; c++)
					cout << matrix_[r][c] << ", ";
				cout << endl;
			}
		else
			cout << "Empty" << endl;

		cout << endl;
	}

	void InsertVertex(T item)
	{
		//공간이 꽉 차있을 경우 blocking하거나 확장하는 처리 해줘야함 (여기선 생략)
		vertices_[n_].item = item;
		n_++;
	}

	void InsertEdge(int u, int v) // 여기서 u, v는 인덱스
	{
		assert(u < n_ && v < n_);

		// TODO:
		matrix_[u][v] = 1;
	}

	int Capacity()
	{
		return max_vertices_;
	}

	void DepthFirstTraversal()
	{
		ResetVisited();

		DepthFirstTraversal(0);

		cout << endl;
	}

	void DepthFirstTraversal(int v) // v는 인덱스
	{
		// TODO:
		cout << "visit " << vertices_[v].item << '\n';

		visited_[v] = true;

		for(int i = 0; i < max_vertices_; ++i){
			if(matrix_[v][i] && visited_[i] == false){
					DepthFirstTraversal(i);
			}
		}
	}

	void IterDFT()
	{
		// TODO:
		//맨 처음엔 시작 노드를 스택에 집어넣고 루프로 들어가야함.
		ResetVisited();

		stack<int> s;
		int v = 0; //시작 위치

		s.push(v);
		while(!s.empty()){
			v = s.top();
			s.pop();
			if(!visited_[v]){
				cout << "visit " << vertices_[v].item << '\n';
				visited_[v] = true;

				for(int i = max_vertices_-1; i >= 0 ; --i){
					if(matrix_[v][i])
					s.push(i);
				}
			}
		}
		
	}

	void BreadthFirstTraversal()
	{
		int v = 0; // 0번에서 시작

		queue<int> q;

		ResetVisited();

		// TODO:
		q.push(v);

		while(!q.empty()){
			v = q.front();
			q.pop();

			if(!visited_[v]){
				cout << "visit " << vertices_[v].item << '\n';
				visited_[v] = true;
				for(int i = 0; i < max_vertices_; ++i){
					if(matrix_[v][i])
						q.push(i);
				}
			}
		}
	}

	void ResetVisited()
	{
		if (!visited_)
			visited_ = new bool[max_vertices_];
		for (int i = 0; i < max_vertices_; i++) visited_[i] = false; // 초기화
	}

private:
	int** matrix_ = nullptr;
	Vertex* vertices_ = nullptr;
	int n_ = 0;					// size
	int max_vertices_ = 0;		// capacity

	bool* visited_ = nullptr;
};

int main()
{
	// 정점(vertex), 간선(edge)

	AdjMatGraph<int> g(7);

	for (int i = 0; i < g.Capacity(); i++)
		g.InsertVertex(i);

	g.InsertEdge(0, 2);	g.InsertEdge(2, 0);
	g.InsertEdge(0, 1);	g.InsertEdge(1, 0);
	g.InsertEdge(1, 4);	g.InsertEdge(4, 1);
	g.InsertEdge(1, 3);	g.InsertEdge(3, 1);
	g.InsertEdge(2, 4);	g.InsertEdge(4, 2);
	g.InsertEdge(3, 6);	g.InsertEdge(6, 3);
	g.InsertEdge(4, 6);	g.InsertEdge(6, 4);
	g.InsertEdge(5, 6);	g.InsertEdge(6, 5);

	g.PrintMatrix();

	//g.DepthFirstTraversal();
	//g.IterDFT();

	g.BreadthFirstTraversal();

	return 0;
}