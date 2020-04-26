#include "container.h"

using namespace std;

std::vector<float> Vector::AddorSub(std::vector<float> &other, bool &doAdd)
{
	if ((this->Container.empty()) || (this->Container.size() != other.size()))
	{
		return std::vector<float>();
	}

	std::vector<float> result;
	for (int i = 0; i < this->Container.size();i++)
	{
		if (doAdd)
		{
			result.push_back(this->Container[i] + other[i]);
		}
		else
		{
			result.push_back(this->Container[i] - other[i]);
		}
	}
	return result;
}

std::vector<float> Vector::MulorDiv(float &s, bool &doMul)
{
	if (this->Container.empty())
	{
		return std::vector<float>();
	}

	std::vector<float> result;
	for (int i = 0; i < this->Container.size();i++)
	{
		if (doMul)
		{
			result.push_back(this->Container[i] * s);
		}
		else
		{
			result.push_back(this->Container[i] / s);
		}
	}
	return result;
}

std::vector<float> Vector::ElementAdd(std::vector<float> other)
{
	bool doAdd = true;
	return this->AddorSub(other, doAdd);
}

Vector Vector::ElementAdd(Vector other)
{
	bool doAdd = true;
	vector<float> result_vec = AddorSub(other.Container, doAdd);
	Vector result = Vector(result_vec);
	return result;
}

std::vector<float> Vector::ElementSubtract(std::vector<float> other)
{
	bool doAdd = false;
	return this->AddorSub(other, doAdd);
}

Vector Vector::ElementSubtract(Vector other)
{
	bool doAdd = false;
	vector<float> result_vec = this->AddorSub(other.Container, doAdd);
	Vector result = Vector(result_vec);
	return result;
}

Vector Vector::ElementMultiplyScalar(float s)
{
	bool doMul = true;
	vector<float> result_vec = this->MulorDiv(s, doMul);
	Vector result = Vector(result_vec);
	return result;
}

Vector Vector::ElementDivideScalar(float s)
{
	bool doMul = false;
	vector<float> result_vec = this->MulorDiv(s, doMul);
	Vector result = Vector(result_vec);
	return result;
}

void Vector::print()
{
	cout << "Content of vector: [";
	for (int i = 0; i < this->Container.size();i++)
	{
		cout << this->Container[i] << " ";
	}
	cout << "]" << endl;
}

Vector Vector::operator+(Vector other)
{	
	return this->ElementAdd(other);
}

Vector Vector::operator-(Vector other)
{
	return this->ElementSubtract(other);
}

Vector Vector::operator*(float s)
{
	return this->ElementMultiplyScalar(s);
}

Vector Vector::operator/(float s)
{
	return this->ElementDivideScalar(s);
}


Vector::Vector(std::list<float> input)
{
	std::list<float>::const_iterator iterator;
	for (iterator = input.begin(); iterator != input.end(); ++iterator)
	{
		this->Container.push_back(*iterator);
	}
}

Vector::Vector(std::vector<float> input)
{
	this->Container = input;
}

Vector::Vector()
{
	this->Container = vector<float>();
}




std::vector<std::vector<float>> Matrix::AddorSub(std::vector<std::vector<float>>& other, bool& doAdd)
{
	if ((this->Container.empty()) || (this->Container.size() != other.size()))
	{
		return std::vector<std::vector<float>>();
	}

	std::vector<std::vector<float>> result;
	for (int i = 0; i < this->Container.size();i++)
	{
		vector<float> result_row;
		for (int j = 0; j < this->Container[i].size(); j++)
		{
			if (doAdd)
			{
				result_row.push_back(this->Container[i][j] + other[i][j]);
			}
			else
			{
				result_row.push_back(this->Container[i][j] - other[i][j]);
			}
		}
		result.push_back(result_row);
		
	}
	return result;
}

std::vector<std::vector<float>> Matrix::MulorDiv(float& s, bool& doMul)
{
	if ((this->Container.empty()))
	{
		return std::vector<std::vector<float>>();
	}

	std::vector<std::vector<float>> result;
	for (int i = 0; i < this->Container.size();i++)
	{
		vector<float> result_row;
		for (int j = 0; j < this->Container[i].size(); j++)
		{
			if (doMul)
			{
				result_row.push_back(this->Container[i][j]*s);
			}
			else
			{
				result_row.push_back(this->Container[i][j]/s);
			}
		}
		result.push_back(result_row);

	}
	return result;
}

std::vector<std::vector<float>> Matrix::Cofactor(std::vector<std::vector<float>> m, int j, int k)
{
	std::vector<std::vector<float>> temp;
	vector<float> temp_row;

	for (int row = 0; row < m.size(); row++)
	{
		for (int col = 0;col < m[0].size();col++)
		{
			if (row == j || col == k)
			{
				continue;
			}
			else 
			{
				temp_row.push_back(m[row][col]);
			}
		}
		if (!temp_row.empty())
		{
			temp.push_back(temp_row);
			temp_row = vector<float>();
		}
	}
	return temp;
}

int Matrix::CalcDeterminant(std::vector<std::vector<float>> m)
{
	int sign = 1;
	int det = 0;

	if ((m.size() != m[0].size()) || m.empty()) 
	{
		return 0;
	}

	if (m.size() == 1)
	{
		return m[0][0];
	}
	else if (m.size() == 2)
	{
		return (m[0][0] * m[1][1] - m[0][1] * m[1][0]);
	}
	else
	{
		for (int i = 0;i < m.size();i++)
		{
			vector<vector<float>> temp = this->Cofactor(m, 0, i);

			Matrix CurrentTemp(temp);
			//cout<<"current temp: "<< endl;
			//CurrentTemp.print();
			//cout << "current det: " << sign << " * " << m[0][i] * this->CalcDeterminant(temp) << endl;

			det += sign * m[0][i] * this->CalcDeterminant(temp);
			sign = -sign;
		}
	}
	
	return det;
}

std::vector<std::vector<float>> Matrix::Transpose(std::vector<std::vector<float>> m)
{
	std::vector<std::vector<float>> transposed = m;

	for (int row = 0;row < m.size();row++)
	{
		for (int col = 0;col < m[0].size();col++)
		{
			transposed[row][col] = m[col][row];
		}
	}
	return transposed;
}

std::vector<std::vector<float>> Matrix::CalcAdjugant(std::vector<std::vector<float>> m)
{
	int sign = 1;
	std::vector<std::vector<float>> adj;
	std::vector<float> adj_row;

	if (m.size() == 2)
	{
		adj = m;
		adj[0][0] = m[1][1];
		adj[0][1] = -m[1][0];
		adj[1][0] = -m[0][1];
		adj[1][1] = m[0][0];

		return adj;
	}

	for (int row = 0;row < m.size();row++)
	{
		for (int col = 0;col < m[0].size();col++)
		{
			vector<vector<float>> temp = this->Cofactor(m, row, col);
			float element = sign * this->CalcDeterminant(temp);
			adj_row.push_back(element);
			sign = -sign;
		};
		adj.push_back(adj_row);
		adj_row = vector<float>();
	}
	return adj;
}

std::vector<std::vector<float>> Matrix::ElementAdd(std::vector<std::vector<float>> other)
{
	bool doAdd = true;
	return this->AddorSub(other, doAdd);
}

Matrix Matrix::ElementAdd(Matrix other)
{
	bool doAdd = true;
	vector<vector<float>> v2 = this->AddorSub(other.Container, doAdd);
	Matrix result = Matrix(v2);
	return result;
}

std::vector<std::vector<float>> Matrix::ElementSubtract(std::vector<std::vector<float>> other)
{
	bool doAdd = false;
	return this->AddorSub(other, doAdd);
}

Matrix Matrix::ElementSubtract(Matrix other)
{
	bool doAdd = false;
	vector<vector<float>> v2 = this->AddorSub(other.Container, doAdd);
	Matrix result = Matrix(v2);
	return result;
}

Matrix Matrix::ElementMultiplyScalar(float s)
{
	bool doMul = true;
	vector<vector<float>> m2 = this->MulorDiv(s, doMul);
	Matrix result = Matrix(m2);
	return result;
}

Matrix Matrix::ElementDivideScalar(float s)
{
	bool doMul = false;
	vector<vector<float>> m2 = this->MulorDiv(s, doMul);
	Matrix result = Matrix(m2);
	return result;
}

void Matrix::print()
{
	cout << "Print content of matrix: " << endl;
	for (int i = 0;i < this->Container.size();i++)
	{
		for (int j = 0; j < this->Container[i].size();j++)
		{
			cout << this->Container[i][j] << " ";
		}
		cout << endl;
	}
}

Matrix Matrix::Inv()
{
	float det = this->CalcDeterminant(this->Container);
	cout << "det: " << det << endl;
	if (det == -1 || det == 0)
	{
		return Matrix();
	}
	vector<vector<float>> transposed = this->Transpose(this->Container);
	
	Matrix adjoint = Matrix(this->CalcAdjugant(transposed));

	Matrix inverse = adjoint.ElementDivideScalar(det);

	return inverse;	
}

Matrix Matrix::MultiplyWithMatrix(Matrix other)
{
	if (this->Container.empty() || other.Container.empty() || (this->Container[0].size() != other.Container.size()))
	{
		return Matrix();
	}

	vector<vector<float>> result;
	
	for (int i = 0;i < this->Container.size();i++)
	{
		vector<float> result_row;
		for (int k = 0;k < other.Container[0].size();k++)
		{
			float element = 0;
			for (int j = 0;j < this->Container[i].size();j++)
			{
				element += this->Container[i][j] * other.Container[j][k];
			}
			result_row.push_back(element);
		}
		result.push_back(result_row);
	}

	Matrix M(result);

	return M;
}

Vector Matrix::MultiplyWithVector(Vector other)
{
	if (this->Container.empty() || (this->Container[0].size() != other.Container.size()))
	{
		return std::vector<float>();
	}

	vector<float> result;

	for (int i = 0;i < this->Container.size();i++)
	{
		float element = 0;
		for (int j = 0;j < this->Container[i].size();j++)
		{
			element += this->Container[i][j] * other.Container[j];
		}
		result.push_back(element);
	}
	Vector V(result);

	return V;
}

Matrix Matrix::operator+(Matrix other)
{
	return this->ElementAdd(other);
}

Matrix Matrix::operator-(Matrix other)
{
	return this->ElementSubtract(other);
}

Matrix Matrix::operator*(float s)
{
	return this->ElementMultiplyScalar(s);
}

Matrix Matrix::operator*(Matrix other)
{
	return this->MultiplyWithMatrix(other);
}

Vector Matrix::operator*(Vector v)
{
	return this->MultiplyWithVector(v);
}

Matrix Matrix::operator/(float s)
{
	return this->ElementDivideScalar(s);
}


Matrix::Matrix(std::list<std::list<float>> input)
{
	std::list<std::list<float>>::const_iterator it_outer;
	std::list<float>::const_iterator it_inner;
	for (it_outer = input.begin(); it_outer != input.end(); ++it_outer)
	{
		vector<float> inner_container;
		list<float> inner_list = *it_outer;
		for (it_inner = inner_list.begin(); it_inner != inner_list.end(); ++it_inner)
		{
			inner_container.push_back(*it_inner);
		}
		this->Container.push_back(inner_container);
	}
}

Matrix::Matrix(std::vector<std::vector<float>> input)
{
	this->Container = input;
}

Matrix::Matrix()
{
	this->Container = vector<vector<float>>();
}
