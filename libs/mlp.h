#ifndef __MLP_H__
#define __MLP_H__

#include "matrix.h"
#include <math.h>

//the library for MLP functionality
//like ReLU, forward pass, backpropagation, etc..

void ReLU(matrix *A);
void ReLU_derivative(matrix *A);
void softmax(double *vector);

#ifdef MLP_LIB_IMPLEMENTATION

void ReLU(matrix *A){
    //defined as ReLU(x) := [x when x>0 ; 0 when x<=0];
    //applying ReLU to a function means to apply
    //ReLU to each entry of the matrix
    for(int i=0;i<A->rows;i++){
        for(int j=0;j<A->columns;j++){
            A->data[i*A->columns+j] = (A->data[i*A->columns+j] > 0)?A->data[i*A->columns+j]:0; 
        }
    }
}

void ReLU_derivative(matrix *A){
    //define it as 1 if input is > 0, and 0 if input is smaller 
    //than 0
    for(int i=0;i<A->rows;i++){
        for(int j=0;j<A->columns;j++){
            A->data[i*A->columns+j] = (A->data[i*A->columns+j] > 0)?1:0; 
        }
    }
}

#endif

#endif