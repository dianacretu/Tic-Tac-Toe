#ifndef FUNCTIONS_H_
#define FUNCTIONS_H_

void init(Tree **tree);

void create_root(Tree **tree, char pozitie[3][3]);

void create_tree(Tree **tree, char jucator1, char jucator);

void create_tree2(Tree **tree, int level, char jucator, char jucator1);

void afisare(Tree **tree, int nivel, FILE *f2);

void afisare_value(Tree **tree, int nivel, FILE *f2);

#endif