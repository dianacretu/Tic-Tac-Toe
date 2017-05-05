#ifndef TREE_H_
#define TREE_H_

void init(Tree **tree) {
	*tree = NULL;
}

//Se creeaza nivelul 0 al arborelui
void create_root(Tree **tree, char pozitie[3][3]) {
	Tree *root = (Tree*) calloc(1,sizeof(Tree));
	int i,j;
	//Se completeaza campul pozitie cu matricea de caractere
	for (i = 0; i < 3; i ++) {
		for (j = 0; j < 3; j ++) {
			root->pozitie[i][j] = pozitie[i][j];
		}
	}
	root->value = '0';

	//Se initializeaza copiii ce pornesc din radacina
	for (i = 0; i < 9; i ++) {
		root->next[i] = NULL;
	}
	*tree = root;
}

//Returneaza 1 pentru castigul jocului
int check_win(Tree **tree) {
	//Compararea caracterelor de pe fiecare linie, coloana si diagonale pentru a determina castigul
	if (((*tree)->pozitie[0][0] == (*tree)->pozitie[0][1]) && ((*tree)->pozitie[0][1] == (*tree)->pozitie[0][2]) && ((*tree)->pozitie[0][0] != '-')) {
		return 1;
	}
	else {
		if (((*tree)->pozitie[1][0] == (*tree)->pozitie[1][1]) && ((*tree)->pozitie[1][1] == (*tree)->pozitie[1][2]) && ((*tree)->pozitie[1][0] != '-')) {
			return 1;
		}
		else {
			if (((*tree)->pozitie[2][0] == (*tree)->pozitie[2][1]) && ((*tree)->pozitie[2][1] == (*tree)->pozitie[2][2]) && ((*tree)->pozitie[2][0] != '-')) {
				return 1;
			}
			else {
				if (((*tree)->pozitie[0][0] == (*tree)->pozitie[1][0]) && ((*tree)->pozitie[1][0] == (*tree)->pozitie[2][0]) && ((*tree)->pozitie[0][0] != '-')) {
					return 1;
				}
				else {
					if (((*tree)->pozitie[0][1] == (*tree)->pozitie[1][1]) && ((*tree)->pozitie[1][1] == (*tree)->pozitie[2][1]) && ((*tree)->pozitie[0][1] != '-')) {
						return 1;
					}
					else {
						if (((*tree)->pozitie[0][2] == (*tree)->pozitie[1][2]) && ((*tree)->pozitie[1][2] == (*tree)->pozitie[2][2]) && ((*tree)->pozitie[0][2] != '-')) {
							return 1;
						}
						else {
							if (((*tree)->pozitie[0][0] == (*tree)->pozitie[1][1]) && ((*tree)->pozitie[1][1] == (*tree)->pozitie[2][2]) && ((*tree)->pozitie[0][0] != '-')) {
								return 1;
							}
							else {
								if (((*tree)->pozitie[0][2] == (*tree)->pozitie[1][1]) && ((*tree)->pozitie[1][1] == (*tree)->pozitie[2][0]) && ((*tree)->pozitie[0][2] != '-')) {
									return 1;
								}
								else {
									return 0;
								}					
							}
						}				
					}
				}		
			}

		}
	}
}

void create_tree(Tree **tree, char jucator1, char jucator) {
	int nr = 0, i, j, win;
	if ((*tree) != NULL) {
		win = check_win(tree);
		for (i = 0; i < 3; i ++) {
			for(j = 0; j < 3; j ++) {
				if ((*tree)->pozitie[i][j] == '-') {
					nr ++;
				}
			}
		}
	}
	//Conditia de oprire este lipsa caracterelor '-' sau castigul 
	if (nr == 0 || win == 1) {
		return;
	}
	else {
		int x,y, contor = 0;
		for (i = 0; i < 3; i ++) {
			for (j = 0; j < 3; j ++) {

				//Se creeaza cate un copil pentru fiecare loc ce trebuie completat
				if ((*tree)->pozitie[i][j] == '-') {
				
					Tree *new =  (Tree*) calloc(1,sizeof(Tree));
					
					for (x = 0; x < 3; x ++) {
						for (y = 0; y < 3; y ++) {
							new->pozitie[x][y] = (*tree)->pozitie[x][y];
						}
					}
					new->value = '0';
					new->pozitie[i][j] = jucator1;
					(*tree)->next[contor] = new;
					//Se trece la crearea urmatorului copil
					contor ++;

				}
			}
		}
		for (i = 0; i < contor ; i ++) {
			//Se schimba caracterul cu care a fost completat nivelul precedent
			char jucator2;
			if (jucator1 == 'X') {
				jucator2 = 'O';
			}
			else {
				if (jucator1 == 'O') {
					jucator2 = 'X';
				}
			}
			//Se repeta pentru ceilalti copii
			create_tree(&(*tree)->next[i], jucator2, jucator);
		}
	}
}

void afisare(Tree **tree, int nivel, FILE *f2) {
	//Conditia de oprire 
	if ((*tree) == NULL) {
		return;
	}
	else {
		int index = 0;
		int i, nr = 0;
		//Se afiseaza matricea in functie de linia 0,1 si 2
		for (i = 0; i < 3; i ++) {
			for (nr = 0; nr < nivel; nr ++) {
				if (nivel > 0) {
					fprintf(f2, "\t");
				}
			}
			fprintf(f2, "%c %c %c\n", (*tree)->pozitie[i][0], (*tree)->pozitie[i][1], (*tree)->pozitie[i][2]);
		}
		nivel ++;
		fprintf(f2,"\n");
		//Se trece la urmatorul nivel
		while ((*tree)->next[index] != NULL) {
			afisare(&(*tree)->next[index],nivel, f2);
			index ++;
		}
	}
}

void create_tree2(Tree **tree, int level, char jucator, char jucator1) {
	//Jucator este carcaterul citit din fisier, iar jucator1 cel care se schimba
	if ((*tree) == NULL) {
		return;
	}
	//Cazul in care este frunza
	if ((*tree)->next[0] == NULL) {
		int win;
		if (jucator1 != jucator) {
			win = check_win(tree);
			if (win == 1) {
				(*tree)->value = 'T';
			}
			else {
				(*tree)->value = 'F';
			}
		}
		else {
			(*tree)->value = 'F';
		}
		return;
	}
	level ++;
	int i;
	//Recursiv pentru copii
	for (i = 0; i < 9 ; i ++) {
		if ((*tree)->next[i] != NULL) {
			if(jucator1 == 'X') {
				create_tree2(&(*tree)->next[i], level, jucator, 'O');
			}
			else {
				create_tree2(&(*tree)->next[i], level, jucator, 'X');
			}
		}
	}
	if (jucator1 == jucator) {
		int i, ok = 0;
		for (i = 0; i < 9; i ++) {
			if ((*tree)->next[i] != NULL) {
				if ((*tree)->next[i]->value == 'T') {
					ok = 1;
					break;
				}
			}
		}
		if (ok == 1) {
			(*tree)->value = 'T';
		}
		else {
			(*tree)->value = 'F';
		}
	}
	else {
		int i, ok = 0;
		for (i = 0; i < 9; i ++) {
			if ((*tree)->next[i] != NULL) {
				if ((*tree)->next[i]->value == 'F') {
					ok = 1;
					break;
				}
			}
		}
		if (ok == 1) {
			(*tree)->value = 'F';
		}
		else {
			(*tree)->value = 'T';
		}
	}
}

void afisare_value(Tree **tree, int nivel, FILE *f2) {
	if ((*tree) == NULL) {
		return;
	}
	else {
		int index = 0;
		int nr;
		for (nr = 0; nr < nivel; nr ++) {
			if (nivel > 0) {
				fprintf(f2, "\t");
			}
		}
		fprintf(f2, "%c\n", (*tree)->value);
		nivel ++;
		while ((*tree)->next[index] != NULL) {
			afisare_value(&(*tree)->next[index],nivel, f2);
			index ++;
		}
	}
}

//Eliberarea memoriei utilizata
void freeTree(Tree *tree) {
	//Cazul in care am ajuns la frunza
	if (tree->next[0] == NULL) {
		free(tree);
		return;
	}
	else {
		int index = 0;
		while (tree->next[index] != NULL) {
			freeTree(tree->next[index]);
			index ++;
		}

	}
	free(tree);
}

#endif