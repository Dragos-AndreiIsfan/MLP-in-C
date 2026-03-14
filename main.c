#include <stdio.h>
#include <stdlib.h>


#define MATRIX_LIB_IMPLEMENTATION
#define MLP_LIB_IMPLEMENTATION
#include "libs/matrix.h"
#include "libs/mlp.h"
#include "libs/matrix-calculus.h"

int main(){

    double vec[] = {2.1,-1.5,2.6,1.07,2.88,9.15,0.2525251,2.211};
    double *probs = softmax(vec,8);
    double sum = 0;
    for(int i=0;i<8;i++){
        printf("%e ",probs[i]);
        sum += probs[i];
    }
    printf("\nSum = %lf\n",sum);
    return 0;
}