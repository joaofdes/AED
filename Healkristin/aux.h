#ifndef AUX_H
#define AUX_H

int extension(char *filename, char *ext);
int check_extensions(char **argv);
FILE* create_results(char *quests_filename);
void close_files(FILE *f1, FILE *f2, FILE *f3, FILE *f4);

#endif