#include <iostream>
#include "rcmatrix.h"

int main(int argc, char* argv[])
{
	try {
                cout << endl << endl;
            
		matrix a(3, 3);
		a.load("A.dat");
		matrix b(3, 3);
		b.load("B.dat");
		cout << "A:\n" << a << endl;
		cout << "B:\n" << b << endl;
		cout << "MNOZYMY b*a\n";
		cout << a*b << endl;
		matrix c(3, 3);
		a *= b;

		matrix x(3, 3, 1.0);
		matrix y(3, 3, 1.0, 2.0);
		matrix z = x * y;

		cout << "x(3, 3, 1.0) = " << endl;
		cout << x << endl;

		cout << "y(3, 3, 1.0, 2.0) = " << endl;
		cout << y << endl;

		cout << "z = \n" << z << endl;

		z = x;

		z(0, 0) = 3.9999;
                cout << "Set z(0, 0) = 3.9999" << endl;
                
		cout << "Check: z(0,0) = " << z(0, 0) << endl << "\nz = \n" << z << endl;
		cout << "x(0,0) = " << x(0, 0) << endl;
                
                cout << endl << endl;
	}
	catch (IndexOutOfRange&)
	{
		cout << "Index Out of Range" << endl;
		cout << "BLAD->OBJEKT MATRIX(DREF)-PODANE INDEKSY KOMORKI NIE NALEZA DO ZAKRESU TEGO OBIEKTU\n";
                
	}
	catch (WrongDimension&)
	{
		cout << "BLAD->OBIEKT MATRIX-NIE MOZNA DODAC MACIERZY O DWOCH ROZNYCH ROZMIARACH\n";
	}
        catch (WrongDimensionMultiplication&)
	{
		cout << "BLAD->OBIEKT MATRIX-NIE MOZNA POMNOZYC TYCH MACIERZY\n";
		cout << "MACIERZ A MUSI MIEC TYLE KOLUMN CO MACIERZ B WIERSZY\n";
	}
        catch (FileOpenError&)
	{
		cout << "BLAD->OBJEKT PLIK-PLIK NIE ISTNIEJE LUB DOSTEP DO ODCZYTU PLIKU JEST ZABRONIONY\n";
	}
	catch (bad_alloc)
	{
		cout << "Out of Memory" << endl;
	}
return 0;
}

/*

using namespace std;

int main()
{
	try
	{
		cout << endl;

		CMatrix A1(2, 5, 1.0);			//Create matrix A1 = [	1.0  0.0  0.0  0.0  0.0
										//						0.0  1.0  0.0  0.0  0.0  ]
		cout << A1 << endl;

		CMatrix A2(5, 3, 0.0, 6.3);		//Create matrix A1 = [	0.0  6.3  6.3 
										//						6.3  0.0  6.3 
										//						6.3  6.3  0.0
										//						6.3  6.3  6.3
										//						6.3  6.3  6.3  ]
		cout << A2 << endl;

		CMatrix S = A1 * A2;			//Multiply A1 by A2
		cout << S << endl;

		fstream f1;
		f1.open("matrix.dat", fstream::in);
		CMatrix B(f1);				//Read the matrix data from file matrix.dat
		f1.close();				//First two values in this file specify the matrix dimensions
		cout << B << endl;

		S = B;						//Assign B to S
		S[0][0] = 1.4;					//Modify S
		cout << "S[0][0]=" << S[0][0] << endl;		//Verify S
		cout << "B[0][0]=" << B[0][0] << endl;		//Verify B
	}
	catch (IndexOutOfRange&)
	{
		cout << "Index Out of Range" << endl;
	}
	catch (WrongDim&)
	{
		cout << "Wrong Matrix Dimensions" << endl;
	}
	catch (bad_alloc)
	{
		cout << "Out of Memory" << endl;
	}
};*/