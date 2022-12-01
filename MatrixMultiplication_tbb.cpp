// ==========================================================
//
// File: MatrixMultiplication_tbb.cpp
// Author: Samantha Casillas
// Description: This file implements the multiplication of a // matrix by another Matrix of the same dimension using 
// TBB.
// The time this implementation takes will be used to calculate // the improvement obtained when compared to CPP
// Copyright (c) 2021 by Tecnologico de Monterrey.
// All Rights Reserved. May be reproduced for any
// non-commercial purpose.
//
//avg time = 20.641 ms
// 2 300*300 matrixes
// =====================================================
#include <iostream>
#include <iomanip>
#include <climits>
#include <tbb/parallel_for.h>
#include <tbb/blocked_range.h>
#include "utils.h"

const int RENS = 300;//00; //1e5
const int COLS = 300;//00;

using namespace std;
using namespace tbb;

class MatrixMultiplication {
private:
	int *M1, *M2, *R;

public:
	MatrixMultiplication(int *matrix1, int *matrix2, int *result) : M1(matrix1), M2(matrix2), R(result) {}

	void operator() (const blocked_range<int> &r) const {
		int acum;

		acum = 0;
		for (int i = r.begin(); i != r.end(); i++) {
			for (int j = 0; j < COLS; j++) {
				acum = 0;
				for (int k = 0; k < RENS; k++) {
					acum += (M1[(i * COLS) + k] * M2[(k*RENS) +j]);
				}
				R[(i*COLS)+j]= acum;
			}
		}
	}

};

int main(int argc, char* argv[]) {
	int i, j, *matrix1, *matrix2, *result;
	double ms;

	matrix1 = new int [RENS * COLS];
	matrix2 = new int [RENS * COLS];
	result = new int [RENS * COLS];

	for (i = 0; i < RENS; i++) {
		for (j = 0; j < COLS; j++) {
			matrix1[(i * COLS) + j] = (j + 1);
			matrix2[(i * COLS) + j] = (j + 2);
		}
	}


	cout << "Starting..." << endl;
	ms = 0;
	for (i = 0; i < N; i++) {
		start_timer();

		parallel_for(blocked_range<int>(0, RENS),  MatrixMultiplication(matrix1, matrix2, result));

		ms += stop_timer();
	}
/*	for (i = 0; i < RENS; i++) {
		for (j = 0; j < COLS; j++) {
			cout<<result[(i*COLS)+j]<< ", ";
		}
		cout<<"\n";
	}
*/

	cout << "avg time = " << setprecision(15) << (ms / N) << " ms" << endl;

	delete [] matrix1;
	delete [] matrix2;
	delete [] result;
	return 0;
}
