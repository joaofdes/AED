#include <string.h>
#include <stdio.h>
#include "aux.h"

int extension(char *filename, char *ext){
    char *dot = strrchr(filename, '.'); //strrchr procura a ultima aparicao de '.' no filename, o filename é um pointer que aponta para o inicio do filename e percorre-o
    if(!dot) return 0;
    return strcmp(dot, ext) == 0;
}

int check_extensions(char **argv) {
    return extension(argv[1], ".quests") && extension(argv[2], ".map") && extension(argv[3], ".position");
}

FILE* create_results(char *quests_filename){
    
    char results_name[100];
    strcpy(results_name, quests_filename);
    
    char *dot_ext = strrchr(results_name, '.');
    if(dot_ext != NULL) strcpy(dot_ext,".results");

    return fopen(results_name, "w");
}

void close_files(FILE *f1, FILE *f2, FILE *f3, FILE *f4) {
    if(f1) fclose(f1);
    if(f2) fclose(f2);
    if(f3) fclose(f3);
    if(f4) fclose(f4);
}