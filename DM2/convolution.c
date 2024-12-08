bool in_list(int* tab, int size, int element) {
    for(int i = 0; i<size; i++) {
        if(tab[i] == element) return true;
    }
    return false;
}

int first_iteration(int* tab, int size, int element) {
    for(int i = 0; i<size; i++) {
        if(tab[i] == element) return i;
    }
    return -1;
}

int min(int* tab, int size) {
    int _min = tab[0];
    for(int i = 0; i<size; i++) {
        if(tab[i] < _min) {
            _min = tab[i];
        }
    }
    return _min;
}

int* ecart(int* tab, int size) {
    int* repertoire = malloc(sizeof(int) * size);
    for(int i = 0; i<size; i++) { repertoire[i] = 0; }

    for(int i = 0; i<size; i++) {
        int indice = first_iteration(tab, size, tab[i]);
        repertoire[indice] += 1;
    }
    
    for(int i = 0; i<size; i++) {
        if(repertoire[i] == 0) repertoire[i] = size + 1; // exclure les 0 placés par la fonction précédente
    }

    int min_1 = min(repertoire, size);
    int max_1 = size + 1; // forcément le max du tableau
    
    int min_1_indice = first_iteration(repertoire, size, min_1);
    repertoire[min_1_indice] = max_1 + 1; // new max
    
    int min_2 = min(repertoire, size);
    int min_2_indice = first_iteration(repertoire, size, min_2);

    int* return_value = malloc(sizeof(int) * 2);
    return_value[0] = tab[min_1_indice];
    return_value[1] = tab[min_2_indice];

    return return_value;
}