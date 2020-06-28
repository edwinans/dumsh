#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>

#define RED "0;31"
#define GREEN "0;32"
#define BUFSZ 1024

char buf[BUFSIZ];

int main(int argc, char const *argv[]){ 
    write(STDOUT_FILENO, "\033[0;31m", strlen("\033[0;31m"));
    // printf("\033[%sm%s", RED, "err");
    printf("fdasf");
    perror("r");

    while(1){
        read()
    }
    return 0;
}
