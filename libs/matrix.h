#ifndef __MATRIX_H__
#define __MATRIX_H__

#include <stdio.h>
#include <stdint.h>
#include <errno.h>
#include <string.h>

//standard matrix structure, rows, columns and data

typedef struct{
    double *data;
    uint16_t rows;
    uint16_t columns;
}matrix;

//STANDARD MATRIX ALLOCATION AND FILLING WITH ZEROS,ONES OR A SPECIFIC ARRAY
matrix *alloc_matrix(uint16_t rows, uint16_t columns);
void fill_matrix(matrix *A, double *data);
void fill_matrix_ones(matrix *A);
void fill_matrix_zeros(matrix *A);

void print_matrix(matrix *A);

//MATRIX OPERATIONS LIKE ADDITION, HADAMARD PRODUCT, MULTIPLICATION


void matadd(matrix *A, matrix *B,matrix *C);
void matmul(matrix *A, matrix *B,matrix *C);
void hadamardProduct(matrix *A, matrix *B,matrix *C);


void dealloc_matrix(matrix *A);

#ifdef MATRIX_LIB_IMPLEMENTATION
//if defined in a program, will contain the implementations of the functions
//this way, we need not to stress over compiling the implementations as 
//objects than linking them to an executable file

//=======MATRIX ALLOCATION, FILLING============

matrix *alloc_matrix(uint16_t rows, uint16_t columns){
    /*Suppose we have a N*M matrix, we represent it in C, 
    not as an array of arrays, e.g. double matrix[ROWS][COLUMNS]
    but rather as a 1D array which containts N*M elements, e.g. 
    double mat[N*M], to acces the entry (i,j), we do i*COLUMNS + j*/

    matrix *A = (matrix*)malloc(sizeof(matrix));
    if(A == NULL){
        fprintf(stderr,"\033[2;49;91mMALLOC FAIL:%s\033[0m\n",strerror(errno));
        return NULL;
    }
    A->rows = rows;
    A->columns = columns;
    A->data = (double*)malloc(sizeof(double)*rows*columns);
    if(A->data == NULL){
        fprintf(stderr,"\033[2;49;91mMALLOC FAIL:%s\033[0m\n",strerror(errno));
        free(A);
        return NULL;
    }
    return A;
}

void fill_matrix_ones(matrix *A){
    for(int i=0;i<A->rows;i++){
        for(int j=0;j<A->columns;j++){
            A->data[i*A->columns + j] = 1;
        }
    }
}

void fill_matrix_zeros(matrix *A){
    for(int i = 0;i<A->rows;i++){
        for(int j=0;j<A->columns;j++){
            A->data[i*A->columns + j] = 0;
        }
    }
}

void fill_matrix(matrix *A, double *data){
    for(int i=0;i<A->rows;i++){
        for(int j=0;j<A->columns;j++){
            A->data[i*A->columns+j] = data[i*A->columns+j];
        }
    }
}

//=====MATRIX OPERATIONS, ADD, MULTIPLY, HADAMARD PRODUCT,etc...=======

void matadd(matrix *A, matrix *B,matrix *C){
    //C = A+B
    //The function should add matrix A to matrix B and store it in matrix C
    //not allocate space for another matrix
    if(A->rows != B->rows || A->columns != B->columns){
        fprintf(stderr,"\033[1;49;91mERROR: The matrices to be added do not have the same size!\033[0m\n");
        return NULL;
    }
    uint16_t rows = A->rows;uint16_t columns = B->columns;
    if(C == NULL){
        return NULL;
    }
    for(int i=0;i<rows;i++){
        for(int j=0;j<columns;j++){
            C->data[i*columns+j] = A->data[i*columns+j]+B->data[i*columns+j];
        }
    }
    
}

void hadamardProduct(matrix *A, matrix *B,matrix *C){
    if(A->rows != B->rows || A->columns != B->columns){
        fprintf(stderr,"\033[1;49;91mERROR: The matrices given for hadamard product do not have the same size!\033[0m\n");
        return NULL;
    }
    uint16_t rows = A->rows;uint16_t columns = B->columns;
    if(C == NULL){
        return NULL;
    }
    for(int i=0;i<rows;i++){
        for(int j=0;j<columns;j++){
            C->data[i*columns+j] = A->data[i*columns+j]*B->data[i*columns+j];
        }
    }
    return C;
}

void print_matrix(matrix *A){
    for(int i=0;i<A->rows;i++){
        for(int j=0;j<A->columns;j++){
            printf("%lf ",A->data[i*A->columns+j]);
        }
        printf("\n");
    }
}

void dealloc_matrix(matrix *A){
    free(A->data);
    free(A);
}

#endif

#endif