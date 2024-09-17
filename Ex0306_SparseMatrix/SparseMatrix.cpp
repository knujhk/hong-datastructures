#include "SparseMatrix.h"

#include <algorithm>
#include <cassert>
#include <iostream>

using namespace std;

SparseMatrix::SparseMatrix(int num_rows, int num_cols, int capacity)
{
	// TODO:
	num_rows_ = num_rows;
	num_cols_ = num_cols;
	capacity_ = capacity;
	
	terms_ = new MatrixTerm[capacity];
	
}

// 복사 생성자 (b를 복사)
SparseMatrix::SparseMatrix(const SparseMatrix& b)
{
	// TODO:
	this->num_rows_ = b.num_rows_;
	this->num_cols_ = b.num_cols_;
	this->capacity_ = b.capacity_;
	this->num_terms_ = b.num_terms_;

	this->terms_ = new MatrixTerm[capacity_];
	memcpy(this->terms_,b.terms_,sizeof(MatrixTerm)*num_terms_);
}

SparseMatrix::~SparseMatrix()
{
	// TODO:
	if(terms_)
		delete[] terms_;
}

void SparseMatrix::SetValue(int row, int col, float value)
{
	if (value == 0.0f) return; // value가 0이 아닌 term만 저장
	//추가할 때마다 항들이 정렬된 상태를 유지하도록 구현
	// TODO:
	if(num_terms_ >= capacity_){
		capacity_ = capacity_ > 0 ? capacity_ * 2 : 1;
		MatrixTerm* temp = new MatrixTerm[capacity_];
		memcpy(temp,terms_,sizeof(MatrixTerm)*num_terms_);
		delete[] terms_;
		terms_ = temp;
	}
	//1. 존재하는 entry의 값을 바꾸는 경우 2. 새 entry를 추가하는 경우
	//terms에서 (row,col)에 해당하는 인덱스 먼저 찾아야하는데 정렬된 상태를 유지할것이므로 이진탐색 써도 됨
	int i = 0;
	int key = row * num_cols_ + col;
	int i_key = 0;
	for(; i < num_terms_; i++){
		i_key = terms_[i].row * num_cols_ + terms_[i].col;
		if(key == i_key){
			terms_[i].value = value;
			return;
		}
		else if(key < i_key){
			break;	//i 자리에 넣으면 됨
		}
	}
	for(int j = num_terms_; j >= i+1; j--){
		terms_[j] = terms_[j-1];
	}
	terms_[i].row = row;
	terms_[i].col = col;
	terms_[i].value = value;
	num_terms_++;
}

float SparseMatrix::GetValue(int row, int col) const // 맨 뒤의 const는 함수 안에서 멤버 변수의 값을 바꾸지 않겠다는 의미
{
	int key = col + num_cols_ * row;

	//binary search
	int left = 0;
	int right = num_terms_ - 1;
	int mid = 0;
	int mid_key = 0;

	while(left <= right){
		mid = (left + right) / 2;
		mid_key = terms_[mid].row * num_cols_ + terms_[mid].col;
		if(key < mid_key){
			right = mid - 1;
		}
		else if(key > mid_key){
			left = mid + 1;
		}
		else
			return terms_[mid].value;
	}

	return 0.0f;
}

SparseMatrix SparseMatrix::Transpose()
{
	SparseMatrix temp(num_cols_, num_rows_, capacity_); // num_cols_, num_rows_ 순서 주의

	// TODO:
	// for(int i = 0; i < num_terms_; i++){
	// 	temp.SetValue(this->terms_[i].col,this->terms_[i].row,this->terms_[i].value);
	// }

	for(int r = 0; r < num_rows_; r++){
		for(int i = 0; i < this->num_terms_; i++){
			if(this->terms_[i].col == r){
				temp.terms_[temp.num_terms_].row = r;
				temp.terms_[temp.num_terms_].col = this->terms_[i].row;
				temp.terms_[temp.num_terms_].value = this->terms_[i].value;
				temp.num_terms_++;
			}
		}
	}

	return temp;
}

void SparseMatrix::PrintTerms()
{
	for (int i = 0; i < num_terms_; i++)
		cout << "(" << terms_[i].row
		<< ", " << terms_[i].col
		<< ", " << terms_[i].value
		<< ")" << endl;
}

void SparseMatrix::Print()
{
	for (int r = 0; r < num_rows_; r++)
	{
		for (int c = 0; c < num_cols_; c++)
			cout << GetValue(r, c) << " ";
		cout << endl;
	}
}
