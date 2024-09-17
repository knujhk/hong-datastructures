#include "Matrix.h"

#include <algorithm>
#include <cassert>
#include <iostream>
#include <cstring>

using namespace std;

Matrix::Matrix(int num_rows, int num_cols)
{
	// TODO:
	assert(num_rows>0);
	assert(num_cols>0);

	num_rows_ = num_rows;
	num_cols_ = num_cols;
	values_ = new float[num_rows_ * num_cols_];
	memset(values_,0.0f,num_rows_ * num_cols_);
	//cout << "mat size : " << num_rows_ * num_cols_ << '\n';
}

// 복사 생성자 (b를 복사)
Matrix::Matrix(const Matrix& b)
{
	// TODO:
	this->num_rows_ = b.num_rows_;
	this->num_cols_ = b.num_cols_;

	//deepcopy
	this->values_ = new float[num_rows_ * num_cols_];
	// for(int i = 0; i < num_rows_ * num_cols_; i++){
	// 	this->values_[i] = b.values_[i];
	// }
	memcpy(this->values_,b.values_,sizeof(float)*num_cols_*num_rows_);
}

Matrix::~Matrix()
{
	// TODO:
	if(values_)
		delete[] values_;
}

void Matrix::SetValue(int row, int col, float value)
{
	// values_[TODO] = value;
	this->values_[row * num_cols_ + col] = value;
}

float Matrix::GetValue(int row, int col) const // 맨 뒤의 const는 함수 안에서 멤버 변수의 값을 바꾸지 않겠다는 의미
{
	return values_[row * num_cols_ + col];
}

Matrix Matrix::Transpose()
{
	Matrix temp(num_cols_, num_rows_); // num_cols_, num_rows_ 순서 주의

	// TODO:
	int row = 0;
	int col = 0;

	// for(int i = 0; i < num_rows_ * num_cols_; i++){
	// 	//this의 행 = i / num_cols 열 = i % num_cols
	// 	row = i / this->num_cols_;
	// 	col = i % this->num_cols_;
	// 	temp.SetValue(col,row,this->GetValue(row,col));	//클래스 멤버 함수니까 get set 쓰지말고 걍 대입해도 되지 않을까? -> 노션에 정리
	// }

	for(int i = 0; i < num_rows_; i++){
		for(int j = 0; j < num_cols_; j++){
			temp.SetValue(j,i,this->GetValue(i,j));
		}
	}

	return temp;
}

Matrix Matrix::Add(const Matrix& b)
{
	assert(b.num_cols_ == num_cols_);
	assert(b.num_rows_ == num_rows_);

	Matrix temp(num_rows_, num_cols_);

	// TODO:
	int row = 0;
	int col = 0;

	// for(int i = 0; i < num_rows_ * num_cols_; i++){
	// 	row = i / this->num_cols_;
	// 	col = i % this->num_cols_;
	// 	temp.SetValue(row,col,this->GetValue(row,col) + b.GetValue(row,col));
	// }

	for(int i = 0; i < num_rows_; i++){
			for(int j = 0; j < num_cols_; j++){
				temp.SetValue(i,j,this->GetValue(i,j)+b.GetValue(i,j));
			}
		}

	return temp;
}

void Matrix::Print()
{
	for (int r = 0; r < num_rows_; r++)
	{
		for (int c = 0; c < num_cols_; c++)
			cout << GetValue(r, c) << " ";

		cout << endl;
	}
}
