#pragma once

#include <iostream>
#include <fstream>
#include <iomanip>
#include <vector>
#include <string>
#include <sstream>
#include <stdio.h>
#include <math.h>
#include <algorithm>
#include <array>
#include <unordered_map>


/*template <class T>
class INTERFACE_CONTAINER 
{
protected:
	//std::vector<T>MyContainer;
	int size;
	float* Container = new float[size];

public:
	virtual float ElementAdd(float other) const = 0;
	virtual std::vector<T> ElementSubstract(std::vector<T> other) const = 0;
	virtual std::vector<T> ElementMultiplyScalar(float s) const = 0;
	virtual std::vector<T> ElementDivideScalar(float s) const = 0;
	virtual void ToNumpy() const = 0;

	INTERFACE_CONTAINER(std::vector<T>& _myContainer) {}
	virtual ~INTERFACE_CONTAINER() = 0 {};
};
*/

/*
class Vector : public INTERFACE_CONTAINER<float>
{
public:
	virtual float ElementAdd(float other) override;
	virtual std::vector<float> ElementSubstract(std::vector<float> other) override;
	virtual Vector ElementMultiplyScalar(float s) override;
	virtual Vector ElementDivideScalar(float s) override;

	Matrix MultiplyWithMatrix(Matrix M);
};

class Matrix : public INTERFACE_CONTAINER<std::vector<float>>
{
public:
	virtual Matrix ElementAdd(Matrix other) override;
	virtual Matrix ElementSubstract(Matrix other) override;
	virtual Matrix ElementMultiplyScalar(float s) override;
	virtual Matrix ElementDivideScalar(float s) override;

	void Inv();
	void PInv();
	Matrix MultiplyWithMatrix(Matrix M);
	
};
*/

class Vector
{
private:
	std::vector<float> AddorSub(std::vector<float> &other, bool &doAdd);
	std::vector<float> MulorDiv(float &s, bool &doMul);
public:
	std::vector<float> Container;

	std::vector<float> ElementAdd(std::vector<float> other);
	Vector ElementAdd(Vector other);
	std::vector<float> ElementSubtract(std::vector<float> other);
	Vector ElementSubtract(Vector other);
	Vector ElementMultiplyScalar(float s);
	Vector ElementDivideScalar(float s);
	void print();

	Vector operator+(Vector other);
	Vector operator-(Vector other);
	Vector operator*(float s);
	Vector operator/(float s);

	Vector(std::list<float> input);
	Vector(std::vector<float> input);
	Vector();
};

class Matrix
{
private:
	std::vector<std::vector<float>> AddorSub(std::vector<std::vector<float>>& other, bool& doAdd);
	std::vector<std::vector<float>> MulorDiv(float& s, bool& doMul);
	std::vector<std::vector<float>> Cofactor(std::vector<std::vector<float>> m, int j, int k);
	int CalcDeterminant(std::vector<std::vector<float>> m);
	std::vector<std::vector<float>> Transpose(std::vector<std::vector<float>> m);
	std::vector<std::vector<float>> CalcAdjugant(std::vector<std::vector<float>> m);

public:
	std::vector<std::vector<float>> Container;

	std::vector<std::vector<float>> ElementAdd(std::vector<std::vector<float>> other);
	Matrix ElementAdd(Matrix other);
	std::vector<std::vector<float>> ElementSubtract(std::vector<std::vector<float>> other);
	Matrix ElementSubtract(Matrix other);
	Matrix ElementMultiplyScalar(float s);
	Matrix ElementDivideScalar(float s);
	void print();

	Matrix Inv();
	std::vector<std::vector<float>> PInv();
	Matrix MultiplyWithMatrix(Matrix other);
	Vector MultiplyWithVector(Vector other);

	Matrix operator+(Matrix other);
	Matrix operator-(Matrix other);
	Matrix operator*(float s);
	Matrix operator*(Matrix other);
	Vector operator*(Vector v);
	Matrix operator/(float s);

	Matrix(std::list<std::list<float>> input);
	Matrix(std::vector<std::vector<float>> input);
	Matrix();
};