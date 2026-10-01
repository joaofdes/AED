#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

int extension(char *filename, char *ext){
    char *dot = strrchr(filename, '.'); //strrchr procura a ultima aparicao de '.' no filename, o filename é um pointer que aponta para o inicio do filename e percorre-o
    if(!dot) return 0;
    return strcmp(dot, ext) == 0;

}

int main(int argc, char **argv){
    
    if(argc != 4){
        return 0; //se n tiver o .quest, .map e .position, não corre nem dá output
    }

    //verifica se as extensões estão corretas
    if(!extension(argv[1], ".quest")||!extension(argv[2], ".map")||!extension(argv[3], ".position")) return 0;
     
    
}
