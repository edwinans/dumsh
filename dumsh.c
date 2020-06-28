#include <stdio.h>
#include <stdlib.h>

#define RED "0;31"
#define GREEN "0;32"

int main(int argc, char const *argv[]){
    
    printf("\033[%sm%s", RED, "err");

    return 0;
}
