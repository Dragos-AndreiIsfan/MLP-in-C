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

/*Function that allocates memory for a matrix, 
it takes as input the rows and columns that are going to
be forming the matrix.
WARNING!: ALWAYS MAKE SURE YOU DEALLOC THE MATRIX AT THE END 
OF THE PROGRAM, THERE IS AN ALREADY DEFINED FUNCTION FOR THIS CALLED 
dealloc_matrix() that takes as input the matrix to be dealloc'ed.*/
matrix *alloc_matrix(uint16_t rows, uint16_t columns);

/*Fill matrix is a function that will fill the given matrix
as input with the values stored in the data array of doubles.
CAUTION: IT IS REQUIRED AND IN THE HANDS OF THE PROGRAMMER THAT 
THE NUMBER OF ELEMENTS OF THE MATRIX ARE EQUAL TO THE 
NUMBER OF ELEMENTS IN THE ARRAY OF DOUBLES, THE FUNCTION DOES 
NOT CHECK SIZE, NEITHER TAKES AS A PARAMETER THE SIZE OF THE ARRAY, SINCE 
IT ASSUMES THAT THE MATRIX HAS THE SAME AMOUNT OF ELEMENTS AS THE 
ARRAY OF DOUBLES.
THE MATRIX MUST BE ALLOCED AND IT'S SIZE NEEDS TO BE SET BEFORE USING 
THIS FUNCTION, OTHERWISE UNDEFINED BEHAVIOUR MAY OCCUR. */
void fill_matrix(matrix *A, double *data);

/*A function that takes as input a matrix, and assigns each entry 
with the value 1.*/
void fill_matrix_ones(matrix *A);

/*Fills the matrix given as input with the value 0.*/
void fill_matrix_zeros(matrix *A);

void print_matrix(matrix *A);

//MATRIX OPERATIONS LIKE ADDITION, HADAMARD PRODUCT, MULTIPLICATION

/*Standard matrix additon, C_{i,j} = A_{i,j} + B_{i,j}.
The functions checks if the shapes of the matrices 
A,B,C are the same, if not, it prints an error to stderr, then 
returns, since it is void, it returns nothing, use cautiously.*/
void matadd(matrix *A, matrix *B,matrix *C);

/*Matrix multiplication, so far not implemented, thinking of 
the way to do it.*/
void matmul(matrix *A, matrix *B,matrix *C);

/*Hadamard Product, or element-wise mutliplication, it is just like 
matrix addition, but instead of adding the entries (i,j) of the matrices A,B
, we multiply them and store them in matrix C. Just like with addition, it prints an 
error to stderr when matrices are not the same shape and returns nothing. Use with caution.*/
void hadamardProduct(matrix *A, matrix *B,matrix *C);

/*Always make sure you free the memory you use.*/
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
        return ;
    }
    uint16_t rows = A->rows;uint16_t columns = B->columns;
    if(C == NULL){
        return ;
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
        return ;
    }
    uint16_t rows = A->rows;uint16_t columns = B->columns;
    if(C == NULL){
        return ;
    }
    for(int i=0;i<rows;i++){
        for(int j=0;j<columns;j++){
            C->data[i*columns+j] = A->data[i*columns+j]*B->data[i*columns+j];
        }
    }
    
}

void matmul(matrix *A, matrix *B, matrix *C){
    
    //Assume A is n by m and B is m by p, then
    //the matrix C will be n by p
    if(A->columns != B->rows || (C->columns != B->columns && C->rows != A->rows)){
        fprintf(stderr,"\033[1;49;91mERROR: The matrices of size (%hu,%hu) and (%hu,%hu) given for matrix multiplication, either do not have the same size or the result matrix of size (%hu,%hu) does not fit (%hu,%hu)!\033[0m\n",A->rows,A->columns,B->rows,B->columns,C->rows,C->columns,A->rows,B->columns);
        return ;
    }

    //To Be Implemented...

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