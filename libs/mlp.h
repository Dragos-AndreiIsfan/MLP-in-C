#ifndef __MLP_H__
#define __MLP_H__

#include "matrix.h"
#include <math.h>
#include <limits.h>
#include <stdlib.h>

//the library for MLP functionality
//like ReLU, forward pass, backpropagation, etc..

void ReLU(matrix *A);
void ReLU_derivative(matrix *A);
double *softmax(double *vector,uint32_t size);

#ifdef MLP_LIB_IMPLEMENTATION

void ReLU(matrix *A){
    //defined as ReLU(x) := [x when x>0 ; 0 when x<=0];
    //applying ReLU to a matrix means to apply
    //ReLU to each entry of the matrix
    for(int i=0;i<A->rows;i++){
        for(int j=0;j<A->columns;j++){
            A->data[i*A->columns+j] = (A->data[i*A->columns+j] > 0)?A->data[i*A->columns+j]:0; 
        }
    }
}

void ReLU_derivative(matrix *A){
    //define it as ReLU'(x) := [1 when x > 0 ; 0 when x <= 0]
    for(int i=0;i<A->rows;i++){
        for(int j=0;j<A->columns;j++){
            A->data[i*A->columns+j] = (A->data[i*A->columns+j] > 0)?1:0; 
        }
    }
}

double *softmax(double *vector,uint32_t size){
    
    /*softmax(z)_i = e^{z_i}/(e^{z_1}+e^{z_2}+...+e^{z_n}), \
    for z in R^n*/

    //allocate memory for the new vector of probabilities in the beginning
    //if allocation goes wrong, we can return NULL and handle somewhere else 
    //the error
    //saves time and computation

    double *probability_vector = (double*)malloc(sizeof(double)*size);
    if(probability_vector == NULL){
        fprintf(stderr,"\033[2;49;91mMALLOC FAIL:%s\033[0m\n",strerror(errno));
        return NULL;
    }

    /*for numerical stability, find the maximum
    in the array, then when calculating exp_sum, do exp(vec[i]-max)*/
    double max = -INFINITY;

    for(int i=0;i<size;i++){
        if(max < vector[i]) max=vector[i];
    }
    
    

    //define inv_exp_sum, that is one over the sum of exponentials
    long double inv_exp_sum = 0.0;
    
    //first calculate the normal exponential sum #O(N)
    for(int i=0;i<size;i++){
        //calculate the expensive exp beforehand, store it in the array
        //then add it to the sum of exponentials
        //this way, we only multiply by the inverse of the sum of 
        //exponentials when finding the probabilities
        probability_vector[i] = expl((long double)(vector[i] - max));
        inv_exp_sum += probability_vector[i];        
    }

    //then calculate the inverse once, since
    //multiplication is very expensive
    inv_exp_sum = 1.0/inv_exp_sum;


    //since each entry i of the probability vector is already e^{z_i}
    //we only multiply with inv_exp_sum, which we know is one over the 
    //sum of the exponentials
    for(int i=0;i<size;i++){
        probability_vector[i] *= inv_exp_sum;
    }

    return probability_vector;
}

#endif

#endif