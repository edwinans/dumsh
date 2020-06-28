#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <assert.h>
#include <errno.h>

#define DEBUG 1

#define RED "0;31"
#define GREEN "0;32"
#define COLRED "\033[0;31m"
#define COLGREEN "\033[0;32m"
#define COLBLUE "\033[0;34m"
#define COLDEF "\033[0m"

#define EXIT_DUMSH -2

#define BUFSZ 1024

char buf[BUFSIZ];



void print_out(char *buf, int n){
    write(STDOUT_FILENO, COLGREEN, strlen(COLGREEN));
    write(STDOUT_FILENO, buf, n);
    write(STDOUT_FILENO, COLDEF, strlen(COLDEF));
}

void print_err(char *buf, int n){
    write(STDERR_FILENO, COLRED, strlen(COLRED));
    write(STDERR_FILENO, buf, n);
    write(STDOUT_FILENO, "\n", 2);
    write(STDERR_FILENO, COLDEF, strlen(COLDEF));
}

void print_blue(char *buf, int n){
    write(STDOUT_FILENO, COLBLUE, strlen(COLBLUE));
    write(STDOUT_FILENO, buf, n);
    write(STDOUT_FILENO, COLDEF, strlen(COLDEF));
}

//this function is just for debugging (use high level io)
void print_args(char **args){
    int i = 0;
    while(args[i]){
        printf("args[%d] = %s | ", i, args[i]);
        i++;
    }
    
    printf("\n");
}

char **split_line(char *line){
    size_t len = strlen(line);
    char **args = 0;
    int count=0;
    char *tmp = line;
    char *last_token = 0;
    const char s[] = " \n\t\r\f\v";
    char *token;

    while (*tmp){
        if (' ' == *tmp){
            count++;
            last_token = tmp;
        }
        tmp++;
    }
    count += last_token < (line + strlen(line) - 1);

    //the last element is 0
    if((args = malloc(sizeof(char*) * (count+1))) == NULL)
        return NULL;

    token = strtok(line, s);
   
    int i=0;
    while( token != NULL ) {
        args[i] = strdup(token);
        token = strtok(NULL, s);
        i++;
    }
    assert(i == count);
    args[i] = 0;

    return args;
}

int exec_line(){
    int sz = read(STDIN_FILENO, buf, BUFSZ);
    buf[sz] = '\0';
    char **args = split_line(buf);
    if(DEBUG)
        print_args(args);

    if(!strcmp(args[0], "exit"))
        return EXIT_DUMSH;

    if (execvp(args[0], args) < 0){
        char *error = strerror( errno );
        print_err(error , strlen(error));
    }

    return 0;
}

int run(){
    char wd[100];
    char pd[]="DUMSH:";
    strcat(pd, getcwd(wd, 100));
    print_blue(pd, strlen(pd));
    print_out("$ ", 3);

    return exec_line();

    return 0;
}


int main(int argc, char const *argv[]){ 

    while(1){
        run();
    }

    return 0;
}
