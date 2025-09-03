/*
 * TLinearSolver.h. Class definition for general purpose
 * linear equation solver. Capped at dimension MAX_DIM.
 * 
 * Author: A. Chester
 *
 */

#ifndef TLINEARSOLVER_H
#define TLINEARSOLVER_H

#define MAX_DIM 20

/*
 * Linear equation solver class definition
 */
class TLinearSolver
{
public:
  int dim;
  long double chisq;
  long double matrix[MAX_DIM][MAX_DIM];
  long double copy_matrix[MAX_DIM][MAX_DIM];
  long double vector[MAX_DIM];
  long double solution[MAX_DIM];

  TLinearSolver();
  void Reset();
  int SolveLinEq();
  long double Determinant(int m);
};

#endif
