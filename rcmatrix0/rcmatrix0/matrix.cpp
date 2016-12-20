#include <iostream>
#include "rcmatrix.h"
#include <fstream>
#include <new>
using namespace std;

matrix::rcmatrix::rcmatrix(unsigned int _row, unsigned int _col)
{
	row = _row;
	col = _col;
	nref = 1;
	
        data = (double**)new double*[row];
        for (unsigned int i = 0; i<row; i++)
        {
                data[i] = (double*) new double[col];
                for (unsigned int j = 0; j<col; j++) data[i][j] = 0;
        }
    
}

matrix::rcmatrix::rcmatrix(unsigned int _row, unsigned int _col, double _diagonal)
{
	row = _row;
	col = _col;
	diagonal = _diagonal;
	nref = 1;
	
        data = (double**)new double*[row];
        for (unsigned int i = 0; i<row; i++)
        {
                data[i] = (double*) new double[col];

                for (unsigned int j = 0; j < col; j++) {
                        if (i == j) {
                                data[i][j] = diagonal;
                        }
                        else {
                                data[i][j] = 0;
                        }
                }
        }
	
}

matrix::rcmatrix::rcmatrix(unsigned int _row, unsigned int _col, double _diagonal, double _fill)
{
	row = _row;
	col = _col;
	diagonal = _diagonal;
	fill = _fill;
	nref = 1;

        data = (double**)new double*[row];
        for (unsigned int i = 0; i<row; i++)
        {
                data[i] = (double*) new double[col];

                for (unsigned int j = 0; j < col; j++) {
                        if (i == j) {
                                data[i][j] = diagonal;
                        }
                        else {
                                data[i][j] = fill;
                        }
                }
        }
}

matrix::rcmatrix::rcmatrix(unsigned int _row, unsigned int _col, double** _data)
{
	nref = 1;
	row = _row;
	col = _col;
        data = (double**)new double*[row];//sprawdzić wyjątek i obsłużyć, zwolnić to co się zaalokowało
        
        for (unsigned int i = 0; i<row; i++)
        {
                data[i] = (double*) new double[col];
                for (unsigned int j = 0; j<col; j++) data[i][j] = _data[i][j];
        }

}

matrix::rcmatrix::~rcmatrix()
{
	for (unsigned int i = 0; i < row; i++)
	{
		delete[] data[i];
	}
	delete[] data;
}




matrix::rcmatrix* matrix::rcmatrix::detach()
{
	if (nref == 1)
	{
		return this;
	}
	else
	{
		nref--;
		rcmatrix *copy = new rcmatrix(row, col, data);
		return copy;
	}
}




matrix::dref::dref(unsigned int _x, unsigned int _y, matrix& _matrixref) : matrixref(_matrixref)
{																	
	x = _x;
	y = _y;
}
matrix::dref:: operator double() const
{
        if ((x<(matrixref.getRow())) && (y<(matrixref.getCol())))
        {
                return matrixref.matrixPtr->data[x][y];
        }
        else throw IndexOutOfRange();
}

matrix::dref& matrix::dref::operator=(const double value)
{
        if ((x<(matrixref.getRow())) && (y<(matrixref.getCol())))
        {
                matrixref.matrixPtr = matrixref.matrixPtr->detach();
                matrixref.matrixPtr->data[x][y] = value;
                return *this;
        }
        else throw IndexOutOfRange();
}

matrix::dref& matrix::dref::operator=(const dref& value)
{
	return operator=((double)value);
}



matrix::matrix(unsigned int _row, unsigned int _col)
{
	row = _row;
	col = _col;
        
        matrixPtr = new rcmatrix(row, col);

}

matrix::matrix(unsigned int _row, unsigned int _col, double _diagonal)
{
	row = _row;
	col = _col;
	diagonal = _diagonal;

        matrixPtr = new rcmatrix(row, col, diagonal);

}

matrix::matrix(unsigned int _row, unsigned int _col, double _diagonal, double _fill)
{
	row = _row;
	col = _col;
	diagonal = _diagonal;
	fill = _fill;

        matrixPtr = new rcmatrix(row, col, diagonal, fill);
}

matrix::matrix(const matrix& otherMatrix)
{
	row = otherMatrix.getRow();
	col = otherMatrix.getCol();
	matrixPtr = otherMatrix.matrixPtr;
	matrixPtr->nref++;
}
matrix::matrix(const char* fileName)
{
	row = 1;
	col = 1;

	matrixPtr = new rcmatrix(row, col);
	this->load(fileName);
}

matrix::~matrix()
{
	matrixPtr->nref--;
	if ((matrixPtr->nref) == 0)
	{
		delete matrixPtr;
	}
}



unsigned int matrix::getRow() const
{
	return row;
}

unsigned int matrix::getCol() const
{
	return col;
}


double matrix::operator()(unsigned int x, unsigned int y) const
{
        if ((x>=(getRow())) || (y>=(getCol())))
            throw IndexOutOfRange();

        return matrixPtr->data[x][y];
}

matrix::dref matrix::operator()(unsigned int x, unsigned int y)
{
	return dref(x, y, *this);
}


matrix matrix::operator+(const matrix& a)
{
    if ((getRow() != a.getRow()) || (getCol() != a.getCol()))
    {
            throw WrongDimension();
    }
    else
    {
            matrix c(getRow(), getCol());

            for (unsigned int i = 0; i<(getRow()); i++)
            {
                    for (unsigned int j = 0; j<(getCol()); j++)
                    {
                            c(i, j) = operator()(i, j) + a(i, j);
                    }
            }
            return c;
    }
}

matrix matrix::operator-(const matrix& a)
{
    if ((getRow() != a.getRow()) || (getCol() != a.getCol()))
        {
                throw WrongDimension();
        }
        else
        {
            matrix c(getRow(), getCol());

            for (unsigned int i = 0; i<(getRow()); i++)
            {
                for (unsigned int j = 0; j<(getCol()); j++)
                {
                        c(i, j) = operator()(i, j) - a(i, j);
                }
            }
            return c;
        }
}
matrix matrix::operator*(const matrix& a) const
{
    if (getCol() == a.getRow())
    {
        matrix c(getRow(), a.getCol());

        for (unsigned int i = 0; i<(c.getCol()); i++)
        {
                for (unsigned int j = 0; j<(c.getRow()); j++)
                {
                        for (unsigned int k = 0; k<(getCol()); k++)
                        {
                                c(i, j) = c(i, j) + (operator()(i, k)*a(k, j));
                        }
                }
        }
        return c;
    }
    else throw WrongDimensionMultiplication();
}

matrix& matrix::operator=(const matrix& a)
{

	if ((matrixPtr->nref)>1)
	{
		matrixPtr->nref--;
		matrixPtr = a.matrixPtr;
		matrixPtr->nref++;
	}
	else
	{
		delete matrixPtr;
		matrixPtr = a.matrixPtr;
		matrixPtr->nref++;
	}

	row = matrixPtr->row;
	col = matrixPtr->col;

	return *this;
}



matrix& matrix::operator+=(const matrix& a)
{
	return operator=(operator+(a));
}
matrix& matrix::operator-=(const matrix& a)
{
	return operator=(operator-(a));
}
matrix& matrix::operator*=(const matrix& a)
{
	return operator=(operator*(a));
}



void matrix::load(const char* fileName)
{
	fstream file;
	unsigned int _row, _col;
	double** _data;

        file.open(fileName, ios::in);
        if (file.good())
        {
                file >> _row;
                file >> _col;
                _data = (double**)new double*[_row];
                
                row = _row;
                col = _col;
                
                for (unsigned int i = 0; i<_row; i++)
                {
                        _data[i] = (double*)new double[_col];
                        for (unsigned int j = 0; j<_col; j++) file >> _data[i][j];
                }
                
                matrixPtr->nref--;
                if ((matrixPtr->nref)<1) delete matrixPtr;
                matrixPtr = new rcmatrix(_row, _col, _data);
                
                for (unsigned int i = 0; i<_row; i++)
                {
                        delete[] _data[i];
                }
                delete[] _data;
                
                file.close();
        }
        else throw FileOpenError();

}




ostream& operator<<(ostream& out, const matrix& mtx)
{
	for (unsigned int i = 0; i<(mtx.getRow()); i++)
	{
		for (unsigned int j = 0; j<(mtx.getCol()); j++)
		{
			cout << mtx(i, j) << "\t";
		}
		cout << endl;
	}
	return out;
}




bool operator==(const matrix& a, const matrix& b)
{
	if (a.matrixPtr != b.matrixPtr)
	{
		if ((a.getRow() != b.getRow()) || (a.getCol() != b.getCol()))
		{
			return false;
		}
		else
		{
			for (unsigned int i = 0; i<(a.getRow()); i++)
			{
				for (unsigned int j = 0; j<(a.getCol()); j++)
				{
					if (a(i, j) != b(i, j)) 
                                            return false;
				}
			}
			return true;
		}
	}
	else return true;
}
