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
	double fill, diagonal;
	rcmatrix* matrixPtr;
public:
	matrix(unsigned int _row, unsigned int _col);
	matrix(unsigned int _row, unsigned int _col, double _diagonal);
	matrix(unsigned int _row, unsigned int _col, double _diagonal, double _fill);
	matrix(const matrix& otherMatrix);
	matrix(const char* fileName);
	~matrix();

	unsigned int getRow() const;
	unsigned int getCol() const;

	double operator()(unsigned int x, unsigned int y) const;
	dref operator()(unsigned int x, unsigned int y);

	matrix operator+(const matrix& a);
	matrix operator-(const matrix& a);
	matrix operator*(const matrix& a) const;

        matrix& operator=(const matrix& a);
	matrix& operator+=(const matrix& a);
	matrix& operator-=(const matrix& a);
	matrix& operator*=(const matrix& a);

	void load(const char* fileName);

	friend bool operator==(const matrix& a, const matrix& b);
	friend ostream& operator<<(ostream& out, const matrix& mtx);

};

//*******************************************************************
class matrix::rcmatrix
{
public:
	unsigned int row, col, nref;
	double** data;
	double fill, diagonal;

	rcmatrix(unsigned int _row, unsigned int _col);
	rcmatrix(unsigned int _row, unsigned int _col, double _diagonal);
	rcmatrix(unsigned int _row, unsigned int _col, double _diagonal, double _fill);
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