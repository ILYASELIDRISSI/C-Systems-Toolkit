#include <stdio.h>
#include <stdlib.h>
//in c arguments are passed by value and not address/pointer
void swap_address(int** a, int** b){
    int* temp;
    temp = *a;
    *a = *b;
    *b = temp;
}

void swap_variable(int*a, int* b){
    int temp = *a;
    *a = *b;
    *b = temp;
}

// int main(){
//     int* ptr1 = NULL, *ptr2 = NULL;
//     int a = 10, b = 20;
    
//     ptr1 = &a;
//     ptr2 = &b;

//     printf("a = %d ::: b = %d\n",*ptr1, *ptr2);

//     // swap_address(&ptr1, &ptr2)
//     swap_variable(&a,&b);
//     printf("a = %d ::: b = %d\n",*ptr1, *ptr2);

//     // printf("variable : %d => Address : %d\n", a, &a);
//     printf("variable : %d => Address : %p\n", a, &a);
//     printf("variable : %d => Address : %p\n", a, (void*) &a);
//     //array as dynamic array

//     int* A = (int*)malloc(sizeof(int)*10);
//     for(int i=0;i<10;i++){
//         *(A+i) = i;
//         printf("%d =>",*(A+i));
//     } 
//     free(A);
//     printf("Press Enter to exit...\n");
//     getchar();
//     return(EXIT_SUCCESS);
// }