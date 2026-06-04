#include <stdio.h>
#include <stdlib.h>

void test_func(int ** n) {
    *n = (int*)malloc(sizeof(int));

    **n = 20;
    

}

int main() {
    int *n;

    test_func(&n);

    printf("%d\n", *n);

    if (-1) {
        printf("sdfdsfsdfds\n");
        }
}