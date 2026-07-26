#include <stdio.h>
#include <stdlib.h>
#include "dynamic_memory.h"


int main(){
    int a = 10, b = 20;
    printf(" a = %d & b = %d \n", a, b);
    swap_variable(&a,&b);
    printf(" a = %d & b = %d \n", a, b);
    printf("hello world...");
    return(EXIT_SUCCESS);
}