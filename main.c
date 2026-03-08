#include <stdio.h>
#include <stdlib.h>


#define MATRIX_LIB_IMPLEMENTATION
#define MLP_LIB_IMPLEMENTATION
#include "libs/matrix.h"
#include "libs/mlp.h"
#include "libs/matrix-calculus.h"

int main(){

    matrix *A = alloc_matrix(3,3);
    if(A == NULL){
        exit(1);
    }

    matrix *B = alloc_matrix(3,3);

    if(B==NULL){
        dealloc_matrix(A);
        exit(1);
    }   
    
    double dataA[3*3];
    double dataB[3*3];

    for(int i=0;i<3;i++){
        for(int j=0;j<3;j++){
            dataA[i*3+j] = i+j-1;
            dataB[i*3+j] = i*j+2*i/(j+1);
        }
    }

    fill_matrix(A,dataA);
    fill_matrix(B,dataB);

    ReLU(A);

    print_matrix(A);
    printf("\n\n");

    ReLU(B);
    print_matrix(B);
    printf("\n\n");
    matrix *C = hadamardProduct(A,B);
    
    if(C == NULL){
        dealloc_matrix(A);
        dealloc_matrix(B);
        exit(1);
    }

    ReLU_derivative(C);

    print_matrix(C);

    dealloc_matrix(A);
    dealloc_matrix(B);
    dealloc_matrix(C);    

    return 0;
}