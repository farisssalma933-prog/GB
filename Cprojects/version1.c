#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<stdbool.h>

typedef struct Animal {
    int id;
    char nom[50];
    char espece[50];
    int age;
    char habitat[50];
    float poids;
} Animal;

char *habitats[] = {
    "Savane",
    "Jungle",
    "Foret",
    "Riviere",
    "Desert",
    "Montagne",
    "Plaine",
    "Ocean",
    "Marecage",
    "Toundra",
    "Steppe",
    "Grottes",
    "Volcan",
    "Glacier"
};


bool habitat_valide(const char *habitat) {
    int n = sizeof(habitats) / sizeof(habitats[0]);
    for (int i = 0; i < n; i++) {
        if (_stricmp(habitats[i], habitat) == 0) {
            return true;
        }
    }
    return false;
}

void afficher_habitats_disponibles() {
    int n = sizeof(habitats) / sizeof(habitats[0]);
    printf("\n--- Habitats disponibles ---\n");
    for (int i = 0; i < n; i++) {
        printf("%d. %s\n", i+1, habitats[i]);
    }
    printf("----------------------------\n");
}

void ajouter(Animal tab_zoo[], int *taille, int *last_id) {
    
    int n;
    printf("Combien d'animaux tu veux ajouter ? ");
    scanf("%d", &n);

    if (*taille + n > 200) {
        printf("Erreur : capacite maximale du zoo depassee (200 animaux max) \n");
        return;
    }

    for (int i = *taille; i < *taille + n; i++) {
        printf("\n=== Animal %d/%d ===\n", (i - *taille + 1), n);
        
        (*last_id)++;
        tab_zoo[i].id = *last_id;
  
        printf("Le nom : ");
        scanf("%49s", tab_zoo[i].nom);
        
        printf("L'espece : ");
        scanf("%49s", tab_zoo[i].espece);
        
        do {
            printf("L'age : ");
            scanf("%d", &tab_zoo[i].age);
            if (tab_zoo[i].age <= 0) {
                printf("Age invalide. Veuillez entrer un age positif.\n");
            }
        } while (tab_zoo[i].age <= 0);
        
        afficher_habitats_disponibles();
        do {
            printf("L'habitat : ");
            scanf("%49s", tab_zoo[i].habitat);
            if (!habitat_valide(tab_zoo[i].habitat)) {
                printf("Habitat invalide. Choisissez parmi la liste ci-dessus.\n");
            }
        } while (!habitat_valide(tab_zoo[i].habitat));
        
        do {
            printf("Le poids en kg : ");
            scanf("%f", &tab_zoo[i].poids);
            if (tab_zoo[i].poids <= 0) {
                printf("Poids invalide. Veuillez entrer un poids positif.\n");
            }
        } while (tab_zoo[i].poids <= 0);
    }
    
    *taille += n;
    printf("\n%d animal(aux) ajoute(s) avec succes !\n", n);
}

void afficher(Animal tab_zoo[], int *taille) {
    
    if (*taille == 0) {
        printf("Aucun animal a afficher °_°\n");
        return;
    }
    
    int choix;
    printf("\n_____AFFICHAGE____\n");
    printf("1- Par ID\n");
    printf("2- Par Nom\n");
    printf("3- Par age \n");
    printf("4- Par habitat\n");
    printf("_____________\n");
    printf("Choisissez le champ a afficher : ");
    scanf("%d", &choix);
    
    Animal temp[200];
    for (int i = 0; i < *taille; i++) {
        temp[i] = tab_zoo[i];
    }
    
    if (choix == 1) {
        for (int i = 0; i < *taille - 1; i++) {
            for (int j = i + 1; j < *taille; j++) {
                if (temp[i].id > temp[j].id) {
                    Animal t = temp[i];
                    temp[i] = temp[j];
                    temp[j] = t;
                }
            }
        }
    } else if (choix == 2) {
        for (int i = 0; i < *taille - 1; i++) {
            for (int j = i + 1; j < *taille; j++) {
                if (_stricmp(temp[i].nom, temp[j].nom) > 0) {
                    Animal t = temp[i];
                    temp[i] = temp[j];
                    temp[j] = t;
                }
            }
        }
    } else if (choix == 3) {
        for (int i = 0; i < *taille - 1; i++) {
            for (int j = i + 1; j < *taille; j++) {
                if (temp[i].age > temp[j].age) {
                    Animal t = temp[i];
                    temp[i] = temp[j];
                    temp[j] = t;
                }
            }
        }
    } else if (choix == 4) {
        for (int i = 0; i < *taille - 1; i++) {
            for (int j = i + 1; j < *taille; j++) {
                if (_stricmp(temp[i].habitat, temp[j].habitat) > 0) {
                    Animal t = temp[i];
                    temp[i] = temp[j];
                    temp[j] = t;
                }
            }
        }
    } else {
        printf("Choix invalide _\n");
        return;
    }

    printf("\n");
    for (int i = 0; i < *taille; i++) {
        printf("======== Animal %d =========\n", temp[i].id);
        printf("Nom: %s\n", temp[i].nom);
        printf("Espece: %s\n", temp[i].espece);
        printf("Age: %d ans\n", temp[i].age);
        printf("Habitat: %s\n", temp[i].habitat);
        printf("Poids: %.2f kg\n", temp[i].poids);
        printf("==============================\n\n");
    }
}

void modifier(Animal tab_zoo[], int *taille) {
    
    int id_recherche, choix;
    
    printf("Entrer l'ID de l'animal : ");
    scanf("%d", &id_recherche);
    
    for (int i = 0; i < *taille; i++) {
        if (id_recherche == tab_zoo[i].id) {
            printf("\n========MODIFICATION========\n");
            printf("1- L'age\n");
            printf("2- L'habitat\n");
            printf("3- Le poids\n");
            printf("============================\n");
            printf("Choisissez le champ a modifier : ");
            scanf("%d", &choix);
            
            switch (choix) {
                case 1:
                    do {
                        printf("Nouvel age : ");
                        scanf("%d", &tab_zoo[i].age);
                        if (tab_zoo[i].age <= 0) {
                            printf("Age invalide.\n");
                        }
                    } while (tab_zoo[i].age <= 0);
                    break;
                    
                case 2:
                    afficher_habitats_disponibles();
                    do {
                        printf("Nouvel habitat : ");
                        scanf("%49s", tab_zoo[i].habitat);
                        
                        if (!habitat_valide(tab_zoo[i].habitat)) {
                            printf("Habitat invalide.\n");
                        }
                    } while (!habitat_valide(tab_zoo[i].habitat));
                    break;
                    
                case 3:
                    do {
                        printf("Nouveau poids : ");
                        scanf("%f", &tab_zoo[i].poids);
                        if (tab_zoo[i].poids <= 0) {
                            printf("Poids invalide.\n");
                        }
                    } while (tab_zoo[i].poids <= 0);
                    break;
                    
                default:
                    printf("Choix invalide _\n");
                    return;
            }
            printf("Modification terminee :)!\n");
            return;
        }
    }
    printf("Animal avec ID %d introuvable °_°\n", id_recherche);
}

void supprimer(Animal tab_zoo[], int *taille) {
    
    int id_recherche;
    printf("Entrer l'ID de l'animal : ");
    scanf("%d", &id_recherche);

    for (int i = 0; i < *taille; i++) {
        if (id_recherche == tab_zoo[i].id) {
            for (int j = i; j < *taille - 1; j++) {
                tab_zoo[j] = tab_zoo[j + 1];
            }
            (*taille)--;
            printf("Animal supprime avec succes !\n");
            return;
        }
    }
    printf("Animal avec ID %d introuvable °_°\n", id_recherche);
}

void chercher_nom(Animal tab_zoo[], int *taille) {
    char nom_recherche[50];
    int trouve = 0;
    
    printf("Entrer le nom : ");
    scanf("%49s", nom_recherche);
    
    for (int i = 0; i < *taille; i++) {
        if (_stricmp(nom_recherche, tab_zoo[i].nom) == 0) {
            trouve = 1;
            printf("\n======== Animal trouve =========\n");
            printf("ID: %d\n", tab_zoo[i].id);
            printf("Nom: %s\n", tab_zoo[i].nom);
            printf("Espece: %s\n", tab_zoo[i].espece);
            printf("Age: %d ans\n", tab_zoo[i].age);
            printf("Habitat: %s\n", tab_zoo[i].habitat);
            printf("Poids: %.2f kg\n", tab_zoo[i].poids);
            printf("================================\n");
        }
    }
    
    if (!trouve) {
        printf("%s introuvable °_°\n", nom_recherche);
    }
}

void chercher_id(Animal tab_zoo[], int *taille) {
    int id_recherche;
    int trouve = 0;
    
    printf("Entrer l'ID de l'animal : ");
    scanf("%d", &id_recherche);
    
    for (int i = 0; i < *taille; i++) {
        if (id_recherche == tab_zoo[i].id) {
            trouve = 1;
            printf("\n======== Animal trouve =========\n");
            printf("ID: %d\n", tab_zoo[i].id);
            printf("Nom: %s\n", tab_zoo[i].nom);
            printf("Espece: %s\n", tab_zoo[i].espece);
            printf("Age: %d ans\n", tab_zoo[i].age);
            printf("Habitat: %s\n", tab_zoo[i].habitat);
            printf("Poids: %.2f kg\n", tab_zoo[i].poids);
            printf("================================\n");
            break;
        }
    }
    
    if (!trouve) {
        printf("Animal avec ID %d introuvable °_°\n", id_recherche);
    }
}

void chercher_espece(Animal tab_zoo[], int *taille) {
    char espece_recherche[50];
    int trouve = 0;
    
    printf("Entrer l'espece : ");
    scanf("%49s", espece_recherche);
    
    for (int i = 0; i < *taille; i++) {
        if (_stricmp(espece_recherche, tab_zoo[i].espece) == 0) {
            trouve = 1;
            printf("\n======== Animal trouve =========\n");
            printf("ID: %d\n", tab_zoo[i].id);
            printf("Nom: %s\n", tab_zoo[i].nom);
            printf("Espece: %s\n", tab_zoo[i].espece);
            printf("Age: %d ans\n", tab_zoo[i].age);
            printf("Habitat: %s\n", tab_zoo[i].habitat);
            printf("Poids: %.2f kg\n", tab_zoo[i].poids);
            printf("================================\n");
        }
    }
    
    if (!trouve) {
        printf("%s introuvable °_°\n", espece_recherche);
    }
}

void rech(Animal tab_zoo[], int *taille) {
    
    int choix;
    
    printf("\n_______RECHERCHE______\n");
    printf("1- Rechercher par nom\n");
    printf("2- Rechercher par ID\n");
    printf("3- Rechercher par espece\n");
    printf("________________\n");
    printf("Choisissez le champ a rechercher : ");
    scanf("%d", &choix);
    
    switch (choix) {
        case 1: chercher_nom(tab_zoo, taille); break;
        case 2: chercher_id(tab_zoo, taille); break;
        case 3: chercher_espece(tab_zoo, taille); break;
        default: printf("Choix invalide _\n");
    }
}

void nombre_total(Animal tab_zoo[], int *taille) {
    
    printf("Le nombre total d'animaux dans le zoo est : %d\n", *taille);
}

void age_moyen(Animal tab_zoo[], int *taille) {
    
    if (*taille == 0) {
        printf("Aucun animal dans le zoo pour calculer l'age moyen °_°\n");
        return;
    }
    
    int somme = 0;
    for (int i = 0; i < *taille; i++) {
        somme += tab_zoo[i].age;
    }
    
    float moyenne = (float)somme / *taille;
    printf("L'age moyen des animaux dans le zoo est de %.2f ans.\n", moyenne);
}

void plus_vieux(Animal tab_zoo[], int *taille) {
    if (*taille == 0) {
        printf("Aucun animal dans le zoo °_°\n");
        return;
    }
    
    int index = 0;
    int max_age = tab_zoo[0].age;
    
    for (int i = 1; i < *taille; i++) {
        if (tab_zoo[i].age > max_age) {
            max_age = tab_zoo[i].age;
            index = i;
        }
    }
    
    printf("Le plus vieux animal est %s, age: %d ans.\n", tab_zoo[index].nom, max_age);
}

void plus_jeune(Animal tab_zoo[], int *taille) {
    if (*taille == 0) {
        printf("Aucun animal dans le zoo °_°\n");
        return;
    }
    
    int index = 0;
    int min_age = tab_zoo[0].age;
    
    for (int i = 1; i < *taille; i++) {
        if (tab_zoo[i].age < min_age) {
            min_age = tab_zoo[i].age;
            index = i;
        }
    }
    
    printf("Le plus jeune animal est %s, age: %d ans.\n", tab_zoo[index].nom, min_age);
}

void afficher_ages_extremes(Animal tab_zoo[], int *taille) {

    printf("\n");
    plus_vieux(tab_zoo, taille);
    plus_jeune(tab_zoo, taille);
}

void espece_majoritaire(Animal tab_zoo[], int*taille) {
    if (*taille == 0) {
        printf("Aucun animal dans le zoo °_°\n");
        return;
    }

    int max_count = 0;
    char *majorite = tab_zoo[0].espece;

    for (int i = 0; i < *taille; i++) {
        int count = 0;
        for (int j = 0; j < *taille; j++) {
            if (_stricmp(tab_zoo[i].espece, tab_zoo[j].espece) == 0) {
                count++;
            }
        }
        if (count > max_count) {
            max_count = count;
            majorite = tab_zoo[i].espece;
        }
    }

    printf("L'espece la plus representee est %s avec %d individu(s).\n", majorite, max_count);
}


int main() {

    Animal tab_zoo[200] = {
        {1, "Simba", "Lion", 5, "Savane", 190.5},
        {2, "Nala", "Lion", 4, "Savane", 175},
        {3, "ShereKhan", "Tigre", 8, "Jungle", 220.3},
        {4, "Baloo", "Ours", 12, "Foret", 310},
        {5, "Raja", "Elephant", 15, "Savane", 540.7},
        {6, "Marty", "Zebre", 6, "Savane", 300.2},
        {7, "Gloria", "Hippopotame", 10, "Riviere", 450},
        {8, "Alex", "Lion", 7, "Savane", 200},
        {9, "Julien", "Lemurien", 3, "Jungle", 12.5},
        {10, "Melman", "Girafe", 9, "Savane", 390.8},
        {11, "Timon", "Suricate", 2, "Desert", 1.2},
        {12, "Pumbaa", "Phacochere", 5, "Savane", 120},
        {13, "Scar", "Lion", 11, "Savane", 210.4},
        {14, "Kaa", "Serpent", 6, "Jungle", 45},
        {15, "Iko", "Perroquet", 4, "Jungle", 2.1},
        {16, "Dumbo", "Elephant", 3, "Savane", 320},
        {17, "Kiki", "Chien_sauvage", 7, "Savane", 25},
        {18, "Donatello", "Tortue", 40, "Riviere", 90.5},
        {19, "Polly", "Oiseau", 5, "Jungle", 1.5},
        {20, "Kong", "Gorille", 13, "Jungle", 180}
    };
    int last_id = 20;
    int taille = 20;
    int choix;

    do {
        printf("\n---------------------------ZOO-----------------------------\n");
        printf("1-  Ajouter des animaux\n");
        printf("2-  Afficher les animaux\n");
        printf("3-  Modifier un animal\n");
        printf("4-  Supprimer un animal\n");
        printf("5-  Rechercher un animal\n");
        printf("6-  Nombre total d'animaux\n");
        printf("7-  Age moyen des animaux\n");
        printf("8-  Afficher le plus vieux et le plus jeune animal\n");
        printf("9-  L'espece la plus representee\n");
        printf("10- Quitter\n");
        printf("------------------------------------------------------------\n");
        printf("Entrer votre choix : ");
        scanf("%d", &choix);

        switch (choix) {
            case 1: ajouter(tab_zoo, &taille, &last_id); break;
            case 2: afficher(tab_zoo, &taille); break;
            case 3: modifier(tab_zoo, &taille); break;
            case 4: supprimer(tab_zoo, &taille); break;
            case 5: rech(tab_zoo, &taille); break;
            case 6: nombre_total(tab_zoo, &taille); break;
            case 7: age_moyen(tab_zoo, &taille); break;
            case 8: afficher_ages_extremes(tab_zoo, &taille); break;
            case 9: espece_majoritaire(tab_zoo, &taille); break;
            case 10: printf("\nBye <3 !\n"); break;
            default: printf("Choix invalide *_* \n");
        }
    } while (choix != 10);

    return 0;
}