#include <stdio.h>
#include <string.h>

int main(int argc, char **argv){
    if(argc >= 2){
        if(strstr(argv[1], "variant")){
            printf("0\n");
        }
    }
    return 0;
}