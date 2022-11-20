#include "Jeu.h"
#include "time.h"

int difference_entre_2_nombres_VALEURABSOLUE(int a, int b){
    if (a<b){
        return b-a;
    }else return a-b;
}


Jeu* initialisation(){
    Jeu* j;
    color(8, 0);
    printf("Destruction de votre ancien fichier de sauvegarde (si vous en aviez un)\n");
    color(15, 0);
    remove(NOM_DU_FICHIER);
    j = lire_graphe();

    j->argent = ARGENT_DE_DEBUT;
    j->production_eau_restante = 0;
    j->production_elec_restante = 0;

    return j;
}
Batiment* maj_liste_chaine(Batiment* nouveau, Batiment* tail, Batiment* liste){
    if(liste == NULL){
        liste = nouveau;
        liste->next = liste;
    }
    else{
        tail = liste;
        while(tail->next != liste){
            tail = tail->next;
        }
        tail->next = nouveau;
        nouveau->next = liste;
    }return liste;
}


void ajouterBatiment(Jeu* jeu,int x,int y,int choix){
    Batiment* nouveau = NULL;
    Batiment* tail = NULL;
    Batiment* liste = NULL;
    nouveau = calloc(1,sizeof(Batiment));
    nouveau->x = x;
    nouveau->y = y;
    switch (choix) {
        case maison: {
            liste = &jeu->batiments[maison];
            liste = maj_liste_chaine(nouveau, tail, liste);
            jeu->batiments[maison] = *liste;
            break;
        }
        case chateau_deau: {
            liste =  &jeu->batiments[chateau_deau];
            liste = maj_liste_chaine(nouveau, tail, liste);
            jeu->batiments[chateau_deau] = *liste;

            break;
        }
        case usine_electrique: {
            liste = *listeUsineElectrique;
            break;
        }
    }
}




void afficherM(Jeu* jeu){
    Batiment* listeMaison = &jeu->batiments[maison];
    Batiment *parcour = listeMaison;

    if(parcour == NULL){
        printf("Liste vide.\n");
    }

    else {
        do {
            printf("Maison en: %d   %d\n",parcour->x,parcour->y);
            parcour = parcour->next;

        }while(parcour != listeMaison);
    }
}

void detruireBatiment(Batiment** listeMaison,Batiment** listeChateauEau,Batiment** listeUsineElectrique,int x,int y,int choix,Jeu* jeu) {

    Batiment *liste = NULL;
    switch (choix) {
        case maison: {
            if ((listeMaison) != NULL) {
                liste = (listeMaison);
            }
            break;
        }
        case chateau_deau: {
            if ((listeChateauEau) != NULL) {
                liste = (listeChateauEau);
            }
            break;
        }
        case usine_electrique: {
            if ((listeUsineElectrique) != NULL) {
                liste = (listeUsineElectrique);
            }
            break;
        }
    }

    if(liste != NULL) {
        Batiment *parcour = liste;
        Batiment *prev = liste;

        while (parcour->x != x && parcour->y != y) {
            parcour = parcour->next;
            if (parcour->next == liste) {
                printf("Coordonnees invalides\n");
                afficher_choix_joueur(jeu);
            }
        }
        while (prev->next != parcour) {
            prev = prev->next;
        }
        if (parcour == liste) {
            liste = liste->next;
        }
        prev->next = parcour->next;
        if(liste == parcour){
            liste = NULL;
        }
        free(parcour);

        switch (choix) {
            case maison: {
                (listeMaison) = liste;
                break;
            }
            case chateau_deau: {
                (listeChateauEau) = liste;
                break;
            }
            case usine_electrique: {
                (listeUsineElectrique) = liste;
                break;
            }
        }
    }
    else{printf("Liste vide.\n");}
}

void sauvBatiment(Batiment* listeMaison,Batiment* listeChateauEau,Batiment* listeUsineElectrique){
    remove("liste.txt");
    Batiment *head = listeMaison;
    Batiment *headChateau = listeChateauEau;
    Batiment *headUsine = listeUsineElectrique;
    FILE *ifs = fopen("liste.txt", "w");
    if(ifs==NULL){
        printf("Erreur lors de l'1ouverture d'un fichier");
        exit(1);
    }
    if(head != NULL) {
        do{
            fprintf(ifs, "%d ", head->x);
            fprintf(ifs, "%d ", head->y);
            head = head->next;
        }while (head != listeMaison);
    }
    fprintf(ifs,"\n");

    if(headChateau != NULL) {
        do{
            fprintf(ifs, "%d ", headChateau->x);
            fprintf(ifs, "%d ", headChateau->y);
            headChateau = headChateau->next;
        }while (headChateau != listeChateauEau);
    }
    fprintf(ifs,"\n");

    if(headUsine != NULL) {
        do{
            fprintf(ifs, "%d ", headUsine->x);
            fprintf(ifs, "%d ", headUsine->y);
            headUsine = headUsine->next;
        }while (headUsine != listeUsineElectrique);
    }
    fclose(ifs);
}


void chargeBatiment(Jeu* jeu){
    Batiment* listeMaison = &jeu->batiments[maison];
    Batiment* listeChateauEau = &jeu->batiments[chateau_deau];
    Batiment* listeUsineElectrique = &jeu->batiments[usine_electrique];
    int x = 0;
    int y = 0;
    char c = 0, cPrec = 0;


    /*FILE *ifs = fopen("liste.txt", "r");
    while((c != ' ' && cPrec != ' ' ) || (c != '\000' && cPrec != '\000')){
        cPrec = c;
        fscanf(ifs,"%c",&c);
        i++;
    }
    fscanf(ifs,"\n");
    c = 0;
    while((c != ' ' && cPrec != ' ' ) || (c != '\000' && cPrec != '\000')){
        cPrec = c;
        fscanf(ifs,"%c",&c);
        j++;
    }
    fscanf(ifs,"\n");
    c = 0;
    while((c != ' ' && cPrec != ' ' ) || (c != '\000' && cPrec != '\000')){
        cPrec = c;
        fscanf(ifs,"%c",&c);
        k++;
    }
    fclose(ifs);*/
    int i = 0,j = 0,k = 0;
    FILE *ifs2 = fopen("liste.txt", "r");
    for(int p = 0;p<1;p++){
        fscanf(ifs2,"%d",&x);
        fscanf(ifs2,"%d",&y);
        ajouterBatiment(listeMaison,listeChateauEau,listeUsineElectrique,x,y,maison);
    }
    fscanf(ifs2,"\n");
    for(int p = 0;p<1;p++){
        fscanf(ifs2,"%d",&x);
        fscanf(ifs2,"%d",&y);
        ajouterBatiment(listeMaison,listeChateauEau,listeUsineElectrique,x,y,chateau_deau);
    }
    fscanf(ifs2,"\n");
    for(int p = 0;p<1;p++){
        fscanf(ifs2,"%d",&x);
        fscanf(ifs2,"%d",&y);
        ajouterBatiment(listeMaison,listeChateauEau,listeUsineElectrique,x,y,usine_electrique);
    }



    fclose(ifs2);
    //fscanf()
    //while()
    /*int espace = 0;
    int type = 0;
    FILE *ifs = fopen(NOM_DU_FICHIER, "r");

    fscanf(ifs,"%d\n",&espace);
    fscanf(ifs,"%d\n",&espace);

    for(int i = 0;i < ORDRE_EN_Y;i++){
        for(int j = 0;j < ORDRE_EN_X;j++){
            fscanf(ifs,"%d",&type);
            if(type != 0) {
                if (i == 0) {
                    ajouterBatiment(listeMaison, listeChateauEau, listeUsineElectrique, i, j, type);
                    switch (type) {
                        case maison: {
                            j = j + 2;
                            fscanf(ifs,"%d",&type);
                            fscanf(ifs,"%d",&type);
                            break;
                        }
                        case chateau_deau: {
                            j = j + 5;
                            break;
                        }
                        case usine_electrique: {
                            j = j + 5;
                            break;
                        }
                    }
                }
                else{
                    switch (type) {
                        case maison: {
                            Batiment **head = listeMaison;
                            Batiment **parcour = head;
                            while ((*parcour)->next != head) {
                                if(i > 1 && j > 1) {
                                    if ((i - 1 != (*parcour)->x && j != (*parcour)->y) ||
                                        (i - 2 != (*parcour)->x && j != (*parcour)->y) ||
                                        (i != (*parcour)->x && j - 1 != (*parcour)->y) ||
                                        (i - 1 != (*parcour)->x && j - 1 != (*parcour)->y)
                                        || (i - 2 != (*parcour)->x && j - 1 != (*parcour)->y) ||
                                        (i != (*parcour)->x && j - 2 != (*parcour)->y) ||
                                        (i - 1 != (*parcour)->x && j - 2 != (*parcour)->y) ||
                                        (i - 2 != (*parcour)->x && j - 2 != (*parcour)->y)) {
                                        ajouterBatiment(listeMaison, listeChateauEau, listeUsineElectrique, i, j,
                                                        maison);
                                    }
                                }
                                else if(i == 1 && j > 1){
                                    if ((i - 1 != (*parcour)->x && j != (*parcour)->y) ||
                                        (i != (*parcour)->x && j - 1 != (*parcour)->y) ||
                                        (i - 1 != (*parcour)->x && j - 1 != (*parcour)->y)
                                        ||(i != (*parcour)->x && j - 2 != (*parcour)->y) ||
                                        (i - 1 != (*parcour)->x && j - 2 != (*parcour)->y)) {
                                        ajouterBatiment(listeMaison, listeChateauEau, listeUsineElectrique, i, j,
                                                        maison);
                                    }
                                }
                                else if(i == 1 && j == 1){
                                    if ((i - 1 != (*parcour)->x && j != (*parcour)->y) ||
                                        (i != (*parcour)->x && j - 1 != (*parcour)->y) ||
                                        (i - 1 != (*parcour)->x && j - 1 != (*parcour)->y)) {
                                        ajouterBatiment(listeMaison, listeChateauEau, listeUsineElectrique, i, j,
                                                        maison);
                                    }
                                }
                                else if(i == 1 && j == 0) {
                                    if ((i - 1 != (*parcour)->x && j != (*parcour)->y)){
                                        ajouterBatiment(listeMaison, listeChateauEau, listeUsineElectrique, i, j,
                                                        maison);
                                    }
                                }
                                else if(i == 2 && j == 0) {
                                    if ((i - 1 != (*parcour)->x && j != (*parcour)->y) ||
                                        (i - 2 != (*parcour)->x && j != (*parcour)->y)){
                                        ajouterBatiment(listeMaison, listeChateauEau, listeUsineElectrique, i, j,
                                                        maison);
                                    }
                                }
                                else if(i == 2 && j == 1) {
                                    if ((i - 1 != (*parcour)->x && j != (*parcour)->y) ||
                                        (i - 2 != (*parcour)->x && j != (*parcour)->y) ||
                                        (i != (*parcour)->x && j - 1 != (*parcour)->y) ||
                                        (i - 1 != (*parcour)->x && j - 1 != (*parcour)->y)
                                        || (i - 2 != (*parcour)->x && j - 1 != (*parcour)->y)) {
                                        ajouterBatiment(listeMaison, listeChateauEau, listeUsineElectrique, i, j,
                                                        maison);
                                    }
                                }

                                (*parcour) = (*parcour)->next;
                            }
                            break;
                        }
                        case chateau_deau: {
                            break;
                        }
                        case usine_electrique: {
                            break;
                        }
                    }
                }
            }
        }
    }*/

}

void liberationListe(Jeu* jeu) {
    Batiment* listeMaison = &jeu->batiments[maison];
    Batiment* listeChateauEau = &jeu->batiments[chateau_deau];
    Batiment* listeUsineElectrique = &jeu->batiments[usine_electrique];
    if (listeMaison != NULL) {
        Batiment *parcour = listeMaison;
        Batiment *prochain = NULL;
        do {
            prochain = parcour->next;
            free(parcour);
            parcour = prochain;

        } while (parcour != listeMaison);
        listeMaison = NULL;
    }

    if (listeChateauEau != NULL) {
        Batiment *parcour = listeChateauEau;
        Batiment *prochain = NULL;
        do {
            prochain = parcour->next;
            free(parcour);
            parcour = prochain;

        } while (parcour != listeChateauEau);
        listeChateauEau = NULL;
    }

    if (listeUsineElectrique != NULL) {
        Batiment *parcour = listeUsineElectrique;
        Batiment *prochain = NULL;
        do {
            prochain = parcour->next;
            free(parcour);
            parcour = prochain;

        } while (parcour != listeUsineElectrique);
        listeUsineElectrique = NULL;
    }
}

void changementHeure(bool shift){

}