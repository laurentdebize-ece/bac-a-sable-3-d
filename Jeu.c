#include "Jeu.h"
#include "time.h"

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
    //initialisation_CONSTANTE(j);

    return j;
}

int difference_entre_2_nombres_VALEURABSOLUE(int a, int b){
    if (a<b){
        return b-a;
    }else return a-b;
}

void detecterCoordonneDouble(Jeu* jeu,int x,int y,int choix){
    Batiment *liste = jeu->batiments[choix];
    Batiment *parcours = liste;
    if(liste != NULL) {
        while (parcours->next != liste) {
            if (parcours->x == x && parcours->y == y) {
                printf("Coordonnees invalides\n");
                afficher_choix_joueur(jeu);
            }
            parcours = parcours->next;
        }
    }
}

Batiment * maj_liste_chaine(Batiment *nouveau,Batiment *tail,Batiment * liste){
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
    Batiment *nouveau = NULL;
    Batiment * tail = NULL;
    Batiment * liste = NULL;

    detecterCoordonneDouble(jeu,x,y,choix);
    nouveau = calloc(1,sizeof(Batiment));
    nouveau->x = x;
    nouveau->y = y;
    nouveau->taille.x = TAILLE_MAISON;
    nouveau->taille.y = TAILLE_MAISON;
    nouveau->nom = "Maison";
    switch (choix) {
        case maison: {
            liste = jeu->batiments[maison];
            liste = maj_liste_chaine(nouveau, tail, liste);
            jeu->batiments[maison] = liste;
            break;
        }
        case chateau_deau: {
            liste =  jeu->batiments[chateau_deau];
            liste = maj_liste_chaine(nouveau, tail, liste);
            jeu->batiments[chateau_deau] = liste;
            break;
        }
        case usine_electrique: {
            liste =  jeu->batiments[usine_electrique];
            liste = maj_liste_chaine(nouveau, tail, liste);
            jeu->batiments[usine_electrique] = liste;
            break;
        }
        default : {
            break;
        }
    }
}




void afficherM(Jeu* jeu){
    Batiment* listeMaison = jeu->batiments[maison];
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

Batiment* maj_destruction_maillon(Batiment* liste,int x,int y,Jeu* jeu) {
    if (liste != NULL) {
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
        if (liste == parcour) {
            liste = NULL;
        }
        free(parcour);
    }
    else{printf("Liste vide.\n");}

    return liste;
}

void detruireBatiment(Jeu* jeu,int x,int y,int choix) {

    Batiment *liste = NULL;
    switch (choix) {
        case maison: {
            if (jeu->batiments[maison] != NULL) {
                liste = jeu->batiments[maison];
                liste = maj_destruction_maillon(liste,x,y,jeu);
                jeu->batiments[maison] = liste;
            }
            break;
        }
        case chateau_deau: {
            if (jeu->batiments[chateau_deau] != NULL) {
                liste = maj_destruction_maillon(liste,x,y,jeu);
                jeu->batiments[chateau_deau] = liste;
            }
            break;
        }
        case usine_electrique: {
            if (jeu->batiments[usine_electrique] != NULL) {
                liste = maj_destruction_maillon(liste,x,y,jeu);
                jeu->batiments[usine_electrique] = liste;
            }
            break;
        }
        default :{
            break;
        }
    }
}

void stocker(int nb,FILE* ifs){
    int n = 0;
    for(int i = 0; i < nb;i++){
        fscanf(ifs,"%d",&n);
    }
}

Batiment* maj_charge_liste(){

}

void chargementListe(Jeu* jeu,int num,int i,int* j,FILE** ifs){
    Batiment* listeMaison = jeu->batiments[maison];
    Batiment* parcours = listeMaison;
    switch(num){
        case 2:{
            if(listeMaison == NULL) {
                ajouterBatiment(jeu, (*j), i, maison);
                jeu->batiments[maison]->retenueMaisonY = i;
                jeu->batiments[maison]->retenueMaisonX = (*j);
                jeu->batiments[maison]->enCours = TRUE;
                (*j) = (*j) + 2;
                stocker(2,*ifs);
            }
            else if(parcours->next == listeMaison){
                if (((i == parcours->retenueMaisonY + 2 && (*j) == parcours->retenueMaisonX) ||
                     (i == parcours->retenueMaisonY + 1 && (*j) == parcours->retenueMaisonX)) &&
                    parcours->enCours == TRUE) {
                    (*j) = (*j) + 2;
                    stocker(2, *ifs);
                    if (i == parcours->retenueMaisonY + 2) {
                        parcours->enCours = FALSE;
                    }
                }
            }
            else {
                while (parcours->next != listeMaison) {
                    if (((i == parcours->retenueMaisonY + 2 && (*j) == parcours->retenueMaisonX) ||
                         (i == parcours->retenueMaisonY + 1 && (*j) == parcours->retenueMaisonX)) &&
                        parcours->enCours == TRUE) {
                        (*j) = (*j) + 2;
                        stocker(2, *ifs);
                        if (i == parcours->retenueMaisonY + 2) {
                            parcours->enCours = FALSE;
                        }
                    }
                    else{
                        ajouterBatiment(jeu, (*j), i, maison);
                        Batiment* parcoursbis = listeMaison;
                        while (parcoursbis->next != listeMaison) {
                            parcoursbis = parcoursbis->next;
                        }
                        parcoursbis->retenueMaisonY = i;
                        parcoursbis->retenueMaisonX = (*j);
                        parcoursbis->enCours = TRUE;
                        (*j) = (*j) + 2;
                        stocker(2, *ifs);
                        jeu->batiments[maison] = listeMaison;
                    }
                    parcours = parcours->next;
                }

            }
            break;
        }
        case 3:{
            break;
        }
        case 4:{
            break;
        }
    }
}

void liberationListe(Jeu* jeu) {
    if (jeu->batiments[maison] != NULL) {
        Batiment *parcour = jeu->batiments[maison];
        Batiment *prochain = NULL;
        do {
            prochain = parcour->next;
            free(parcour);
            parcour = prochain;

        } while (parcour != jeu->batiments[maison]);
        jeu->batiments[maison] = NULL;
    }

    if (jeu->batiments[chateau_deau] != NULL) {
        Batiment *parcour = jeu->batiments[chateau_deau];
        Batiment *prochain = NULL;
        do {
            prochain = parcour->next;
            free(parcour);
            parcour = prochain;

        } while (parcour != jeu->batiments[chateau_deau]);
        jeu->batiments[chateau_deau] = NULL;
    }

    if (jeu->batiments[usine_electrique] != NULL) {
        Batiment *parcour = jeu->batiments[usine_electrique];
        Batiment *prochain = NULL;
        do {
            prochain = parcour->next;
            free(parcour);
            parcour = prochain;

        } while (parcour != jeu->batiments[usine_electrique]);
        jeu->batiments[usine_electrique] = NULL;
    }
    jeu->batiments[maison] = NULL;
    jeu->batiments[chateau_deau] = NULL;
    jeu->batiments[usine_electrique] = NULL;
}

void changementHeure(bool shift){

}