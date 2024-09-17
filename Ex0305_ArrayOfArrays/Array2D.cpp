#include "Array2D.h"

#include <algorithm>
#include <cassert>
#include <iostream>
#include <cstring>

using namespace std;

Array2D::Array2D(int num_rows, int num_cols)
{
	//TODO:
	num_rows_ = num_rows;
	num_cols_ = num_cols;

	arrays_ = new float*[num_rows];
	for(int i = 0; i < num_rows; i++){
		arrays_[i] = new float[num_cols];
		memset(arrays_[i],0.0f,num_cols);
	}
	/*
	for (int r = 0; r < num_rows_; r++){
		for (int c = 0; c < num_cols_; c++){
			arrays_[r][c] = 0.0f;
		}
	}
	*/
}

// 복사 생성자 (b를 복사)
Array2D::Array2D(const Array2D& b)
{
	//TODO:
	this->num_rows_ = b.num_rows_;
	this->num_cols_ = b.num_cols_;

	this->arrays_ = new float*[num_rows_];
	for(int r = 0; r < num_rows_; r++){
		this->arrays_[r] = new float[num_cols_];
		memcpy(this->arrays_[r],b.arrays_[r],sizeof(float)*num_cols_);
	}
	
}

Array2D::~Array2D()
{
	//TODO:
	if(arrays_){
		for(int r = 0; r < num_rows_; r++){
			if(arrays_[r])
				delete[] arrays_[r];
		}
		delete[] arrays_;
	}
}

void Array2D::SetValue(int row, int col, float value)
{
	// TODO:
	arrays_[row][col] = value;
}

float Array2D::GetValue(int row, int col) const // 맨 뒤의 const는 함수 안에서 멤버 변수의 값을 바꾸지 않겠다는 의미
{
	return arrays_[row][col];
}

Array2D Array2D::Transpose()
{
	Array2D temp(num_cols_, num_rows_); // num_cols_, num_rows_ 순서 주의

	for (int r = 0; r < num_rows_; r++)
		for (int c = 0; c < num_cols_; c++)
			temp.SetValue(c, r, GetValue(r, c));

	return temp;
}

Array2D Array2D::Add(const Array2D& b)
{
	assert(b.num_cols_ == num_cols_);
	assert(b.num_rows_ == num_rows_);

	Array2D temp(num_rows_, num_cols_);

	for (int r = 0; r < num_rows_; r++)
		for (int c = 0; c < num_cols_; c++)
			temp.SetValue(r, c, GetValue(r, c) + b.GetValue(r, c));

	return temp;
}

void Array2D::Print()
{
	for (int r = 0; r < num_rows_; r++)
	{
		for (int c = 0; c < num_cols_; c++)
			cout << GetValue(r, c) << " ";

		cout << endl;
	}
}
