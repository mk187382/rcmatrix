#include <iostream>

using namespace std;

//*******************************************************************

class FileOpenError {};
class WrongDimension {};
class WrongDimensionMultiplication {};
class IndexOutOfRange {};

//*******************************************************************

class matrix
{
	class rcmatrix;
	class dref;
private:
	unsigned int row, col;
	rcmatrix* matrixPtr;
public:
	matrix(unsigned int _row = 1, unsigned int _col = 1);
	matrix(matrix& otherMatrix);
	matrix(const char* fileName);
	~matrix();

	unsigned int getRow() const;
	unsigned int getCol() const;

	double operator()(unsigned int x, unsigned int y) const;
	dref operator()(unsigned int x, unsigned int y);

	matrix operator+(matrix& a);
	matrix operator-(matrix& a);
	matrix operator*(matrix& a);
	matrix operator=(matrix& a);

	matrix operator+=(matrix& a);
	matrix operator-=(matrix& a);
	matrix operator*=(matrix& a);

	void load(const char* fileName);

	friend bool operator==(matrix& a, matrix& b);
	friend ostream& operator<<(ostream& out, const matrix& mtx);

};

//*******************************************************************
class matrix::rcmatrix
{
public:
	unsigned int row, col, nref;
	double** data;

	rcmatrix(unsigned int _row, unsigned int _col);
	rcmatrix(unsigned int _row, unsigned int _col, double** _data);
	~rcmatrix();

	rcmatrix* detach();
};

class matrix::dref
{
private:
	unsigned int x, y;
	matrix& matrixref;
public:
	dref(unsigned int _x, unsigned int _y, matrix& _matrixref);

	operator double() const;
	dref& operator=(const double value);
	dref& operator=(const dref& value);
};