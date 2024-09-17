#include "Polynomial.h"

#include <cassert>
#include <iostream>
#include <math.h> // std::powf()

using namespace std;

Polynomial::Polynomial(int max_degree) // 편의상 기본값 사용
{
	assert(max_degree > 0);

	// - 상수항 포함
	// - 예: max_degree가 2이면 c0*x^0 + c1*x^1 + c2*x^2 총 3개의 항들
	capacity_ = max_degree + 1;

	// 동적 메모리 할당
	coeffs_ = new float[capacity_];

	// 0으로 초기화
	for (int i = 0; i < capacity_; i++)
		coeffs_[i] = 0.0f;
}

Polynomial::Polynomial(const Polynomial& poly)
{
	this->capacity_ = poly.capacity_;
	coeffs_ = new float[capacity_];
	for (int i = 0; i < capacity_; i++)
		coeffs_[i] = poly.coeffs_[i];
}

Polynomial::~Polynomial()
{
	if (coeffs_) delete[] coeffs_;
}

int Polynomial::MaxDegree()
{
	return this->capacity_ - 1;
}

void Polynomial::NewTerm(const float coef, const int exp)
{
	assert(exp < capacity_); // exp가 너무 크면 resize 하도록 구현할 수도 있음
							//assert의 매개변수가 false면 실행 중지
	// TODO: 쉬워요
	//주석 처리 코드는 max degree 보다 exp가 클 때 처리하는 코드
	// int capacity_new = exp+1;
	// float *coef_new = new float[exp+1];

	// for (int i = 0; i < this->capacity_; i++){
	// 	coef_new[i] = this->coeffs_[i];
	// }
	// delete[] this->coeffs_;

	// for (int i = this->capacity_; i< capacity_new; i++){
	// 	coef_new[i] = 0.0f;
	// }
	// coef_new[exp] = coef;

	// this->coeffs_ = coef_new;
	// this->capacity_ = capacity_new;

	this->coeffs_[exp] = coef;
	return;
}

Polynomial Polynomial::Add(const Polynomial& poly)
{
	assert(poly.capacity_ == this->capacity_); // 문제를 단순화하기 위한 가정

	Polynomial temp(this->MaxDegree());

	// TODO:
	for(int i = 0; i < this->capacity_; i++){
		temp.coeffs_[i] = this->coeffs_[i] + poly.coeffs_[i];
	}

	return temp;
}

Polynomial Polynomial::Mult(const Polynomial& poly)
{
	assert(poly.capacity_ == this->capacity_); // 문제를 단순화하기 위한 가정

	// coeff_[i]가 0.0f가 아닌 경우에 대해서만 계산 (곱하면 0이 되기 때문)

	Polynomial temp(this->MaxDegree());

	for(int i = 0; i < this->capacity_; i++){ //i는 this의 i차항 의미
		if(this->coeffs_[i] == 0)
			continue;
		for(int j = 0; j < this->capacity_; j++){	//j는 poly의 j차항 의미
			if((poly.coeffs_[j] == 0) || i+j > this->capacity_)
				continue;
			
			temp.coeffs_[i+j] += this->coeffs_[i] * poly.coeffs_[j];
		}
	}

	// TODO: 항상 인덱싱 오류 조심

	return temp;
}

float Polynomial::Eval(float x)
{
	float temp = 0.0f;

	// TODO:
	// 힌트 std::powf(2.0f, float(3)); // 2.0f^3.0f = 8.0f (2.0f의 3.0f 제곱)
	for(int i=0; i < this->capacity_; i++){
		temp += this->coeffs_[i] * powf(x,float(i));
	}

	return temp;
}

void Polynomial::Print()
{
	bool is_first = true; // 더하기 출력시 확인용

	for (int i = 0; i < capacity_; i++)
	{
		if (coeffs_[i] != 0.0f) // 주의: 0이 아닌 항들만 출력
		{
			if (!is_first)
				cout << " + "; // 첫 항이 아니라면 사이사이에 더하기 출력

			cout << coeffs_[i];

			if (i != 0) cout << "*" << "x^" << i;

			is_first = false;
		}
	}

	cout << endl;
}