#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "Tabla.h"
#include "Tree.h"
#include "Functions.h"

int main (int argc, char **argv) {
	FILE *f1, *f2;
	f1 = fopen(argv[2], "r");
	f2 = fopen(argv[3], "w");
	if (f1 == 0 || f2 == 0) {
		puts("Eroare la deschidere fisiere\n");
		return 1;
	}
	Tree *tree;
	init(&tree);
	//Se citeste prima litera din fisier, cu aceasta se va completa primul nivel
	char jucator;
	fscanf(f1, "%c", &jucator);
	//Se citeste tabla de joc, salvata in matricea caracter[3][3]
	//Nu se vor utiliza spatiile albe
	char space1;
	fscanf(f1, "%c", &space1);
	char caracter[3][3];
	fscanf(f1, "%c", &caracter[0][0]);
	char space2;
	fscanf(f1, "%c", &space2);
	fscanf(f1, "%c", &caracter[0][1]);
	char space3;
	fscanf(f1, "%c", &space3);
	fscanf(f1, "%c", &caracter[0][2]);
	char space4;
	fscanf(f1, "%c", &space4);
	fscanf(f1, "%c", &caracter[1][0]);
	char space5;
	fscanf(f1, "%c", &space5);
	fscanf(f1, "%c", &caracter[1][1]);
	char space6;
	fscanf(f1, "%c", &space6);
	fscanf(f1, "%c", &caracter[1][2]);
	char space7;
	fscanf(f1, "%c", &space7);
	fscanf(f1, "%c", &caracter[2][0]);
	char space8;
	fscanf(f1, "%c", &space8);
	fscanf(f1, "%c", &caracter[2][1]);
	char space9;
	fscanf(f1, "%c", &space9);
	fscanf(f1, "%c", &caracter[2][2]);
	char space10;
	fscanf(f1, "%c", &space10);
	//Se creeaza radacina arborelui cu caracerele citite din fisier
	create_root(&tree, caracter);
	//In functie de primul argument din linia din comanda se rezolva taskurile
	char jucator1 = jucator;
	create_tree(&tree, jucator1, jucator);
	if (strcmp(argv[1],"-c1") == 0) {
		int nivel = 0;
		afisare(&tree, nivel, f2);
	}
	else {
		if (strcmp(argv[1],"-c2") == 0) {
			int level = 0;
			create_tree2(&tree, level, jucator, jucator1);
			afisare_value(&tree, level, f2);
		}
	}
	freeTree(tree);
	fclose(f1);
	fclose(f2);
	return 0;
}