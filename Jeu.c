#include "Jeu.h"

Jeu* initialisation(){
    Jeu* j;
    printf("Destruction de votre ancien fichier de sauvegarde (si vous en aviez un)\n");
    remove(NOM_DU_FICHIER);
    //j = lire_graphe_console(); //psk pas console

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
            if (parcours->co.x == x && parcours->co.y == y) {
                printf("Coordonnees invalides\n");
            }
            parcours = parcours->next;
        }
    }
}

Batiment* maj_liste_chaine(Batiment *nouveau,Batiment *tail,Batiment * liste){
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

void ajouterBatiment_ListeChainee(Jeu* jeu, int x, int y, int choix){
    Batiment* nouveau = NULL;
    Batiment* tail = NULL;
    Batiment* liste = NULL;

    detecterCoordonneDouble(jeu,x,y,choix);
    nouveau = calloc(1,sizeof(Batiment));
    nouveau->co.x = x;
    nouveau->co.y = y;

    switch (choix) {
        case maison: {
            nouveau->taille.x = TAILLE_MAISON;
            nouveau->taille.y = TAILLE_MAISON;
            //initialisation_case_ajacentes(nouveau->cases_adjacentes,nouveau->co, TAILLE_MAISON, TAILLE_MAISON);
            nouveau->nom = "Maison";
            nouveau->stadeEvolution = 0;
            liste = jeu->batiments[maison];
            liste = maj_liste_chaine(nouveau, tail, liste);
            jeu->batiments[maison] = liste;
            compteurNbBatimentListe(jeu,maison);
            break;
        }
        case chateau_deau: {
            nouveau->taille.x = LONGUEUR_BATIMENTS;
            nouveau->taille.y = LARGEUR_BATIMENTS;
            //initialisation_case_ajacentes(nouveau->cases_adjacentes,nouveau->co, TAILLE_MAISON, TAILLE_MAISON);
            nouveau->nom = "Chateau d'eau";
            nouveau->stadeEvolution = 0;
            liste =  jeu->batiments[chateau_deau];
            liste = maj_liste_chaine(nouveau, tail, liste);
            jeu->batiments[chateau_deau] = liste;
            compteurNbBatimentListe(jeu,chateau_deau);
            break;
        }
        case usine_electrique: {
            nouveau->taille.x = LONGUEUR_BATIMENTS;
            nouveau->taille.y = LARGEUR_BATIMENTS;
            //initialisation_case_ajacentes(nouveau->cases_adjacentes,nouveau->co, TAILLE_MAISON, TAILLE_MAISON);
            nouveau->nom = "Usine electrique";
            nouveau->stadeEvolution = 0;
            liste =  jeu->batiments[usine_electrique];
            liste = maj_liste_chaine(nouveau, tail, liste);
            jeu->batiments[usine_electrique] = liste;
            compteurNbBatimentListe(jeu,usine_electrique);
            break;
        }
        default : {
            break;
        }
    }
    /*if (nouveau != NULL) {
        if (nouveau->cases_adjacentes != NULL) {
            free(nouveau->cases_adjacentes);
            nouveau->cases_adjacentes = NULL;
        }
        free(nouveau);
        nouveau = NULL;
    }
    if (tail != NULL){
        if (tail->cases_adjacentes != NULL){
            free(tail->cases_adjacentes);
            tail->cases_adjacentes = NULL;
        }
        free(tail);
        tail = NULL;
    }
    if (liste != NULL) {
        if (liste->cases_adjacentes != NULL) {
            free(liste->cases_adjacentes);
            liste->cases_adjacentes = NULL;
        }
        free(liste);
        liste = NULL;
    }*/
}

void afficherM(Jeu* jeu) {
    int nbmaison = 1;
    int nbchateau = 1;
    int nbusine = 1;
    Batiment *listeMaison = jeu->batiments[maison];
    Batiment *listeChateau = jeu->batiments[chateau_deau];
    Batiment *listeUsine = jeu->batiments[usine_electrique];

    if(listeMaison != NULL) {
        do {
            printf("Maison %d : x: %d  y: %d    stade: %d\n", nbmaison, listeMaison->co.x, listeMaison->co.y,listeMaison->stadeEvolution);
            nbmaison++;
            listeMaison = listeMaison->next;

        } while (listeMaison != jeu->batiments[maison]);
    }
    else{printf("Liste maison vide\n");}

    if(listeChateau != NULL) {
        do {
            printf("Chateau d'eau %d : x: %d  y: %d\n", nbchateau, listeChateau->co.y, listeChateau->co.y);
            nbchateau++;
            listeChateau = listeChateau->next;

        } while (listeChateau != jeu->batiments[chateau_deau]);
    }
    else{printf("Liste chateau eau vide\n");}

    if(listeUsine != NULL) {
        do {
            printf("Usine electrique %d : x: %d   y: %d\n", nbusine, listeUsine->co.x, listeUsine->co.y);
            nbusine++;
            listeUsine = listeUsine->next;

        } while (listeUsine != jeu->batiments[usine_electrique]);
    }
    else{printf("Liste usine electrique vide\n");}
}

Batiment* maj_DeCompteur(Jeu* jeu, Batiment* liste){
    Batiment* parcours = liste;
    if(liste != NULL){
        do{
            if (parcours->numero > jeu->numero_maillon_supprime){
                parcours->numero--;
            }
            parcours = parcours->next;
        }while(parcours != liste);
        liste->nb_batiment--;
    }
    return liste;
}

void decompteurNbBatimentListe(Jeu* jeu,int choix) {
    Batiment *liste = NULL;
    switch (choix) {
        case maison: {
            liste = jeu->batiments[maison];
            liste = maj_DeCompteur(jeu, liste);
            jeu->batiments[maison] = liste;
            break;
        }
        case chateau_deau: {
            liste = jeu->batiments[chateau_deau];
            liste = maj_DeCompteur(jeu, liste);
            jeu->batiments[chateau_deau] = liste;
            break;
        }
        case usine_electrique: {
            liste = jeu->batiments[usine_electrique];
            liste = maj_DeCompteur(jeu, liste);
            jeu->batiments[usine_electrique] = liste;
            break;
        }
    }
}

Batiment* maj_destruction_maillon(Batiment* liste,int x,int y,Jeu* jeu) {
    if (liste != NULL) {
        Batiment *parcour = liste;
        Batiment *prev = liste;

        while (parcour->co.x != x || parcour->co.y != y){
            if (parcour->next == liste) {
                printf("Coordonnees invalides\n");
            }
            parcour = parcour->next;
        }

        do{
            prev = prev->next;
        }
        while (prev->next != parcour);

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
                compteurNbBatimentListe(jeu,maison);
            }
            break;
        }
        case chateau_deau: {
            if (jeu->batiments[chateau_deau] != NULL) {
                liste = jeu->batiments[chateau_deau];
                liste = maj_destruction_maillon(liste,x,y,jeu);
                jeu->batiments[chateau_deau] = liste;
                compteurNbBatimentListe(jeu,chateau_deau);
            }
            break;
        }
        case usine_electrique: {
            if (jeu->batiments[usine_electrique] != NULL) {
                liste = jeu->batiments[usine_electrique];
                liste = maj_destruction_maillon(liste,x,y,jeu);
                jeu->batiments[usine_electrique] = liste;
                compteurNbBatimentListe(jeu,usine_electrique);
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
// dizaine type de batiment unite evolution
Batiment* maj_charge_liste(Jeu* jeu,Batiment* liste,int* x,int y,FILE* ifs,int choix,int stadeEvo){
    Batiment* parcours = liste;
    bool bouclePasse = 0;

    if(liste == NULL) {
        ajouterBatiment_ListeChainee(jeu, (*x), y, choix);
        jeu->batiments[choix]->enCours = 1;
        if(choix == maison){
            jeu->batiments[choix]->stadeEvolution = stadeEvo;
        }
        (*x) = (*x) + jeu->batiments[choix]->taille.x - 1;
        stocker(jeu->batiments[choix]->taille.x - 1,ifs);

    }
    else {
        do {
            bool conditionVerifie = 0;
            switch (choix) {
                case maison: {
                    if (((y == parcours->co.y + 2 && (*x) == parcours->co.x) ||
                         (y == parcours->co.y + 1 && (*x) == parcours->co.x)) &&
                        parcours->enCours == 1) {
                        conditionVerifie = 1;
                    }
                    break;
                }
                default: {
                    if (((y == parcours->co.y+ 3 && (*x) == parcours->co.x) ||
                         (y == parcours->co.y + 2 && (*x) == parcours->co.x) ||
                         (y == parcours->co.y + 1 && (*x) == parcours->co.x)) &&
                        parcours->enCours == 1) {
                        conditionVerifie = 1;
                    }
                }
            }
            if (conditionVerifie == 1) {
                (*x) = (*x) + jeu->batiments[choix]->taille.x - 1;
                stocker(jeu->batiments[choix]->taille.x - 1, ifs);
                if (y == parcours->co.y + jeu->batiments[choix]->taille.x - 1) {
                    parcours->enCours = 0;
                }
                bouclePasse = 1;
            }

            parcours = parcours->next;
        }while(parcours != jeu->batiments[choix]);

        if(bouclePasse == 0) {
            ajouterBatiment_ListeChainee(jeu, (*x), y, choix);
            Batiment *parcoursbis = liste;
            while (parcoursbis->next != liste) {
                parcoursbis = parcoursbis->next;
            }
            parcoursbis->co.y = y;
            parcoursbis->co.x = (*x);
            parcoursbis->enCours = 1;
            if(choix == maison){
                parcoursbis->stadeEvolution = stadeEvo;
            }
            (*x) = (*x) + jeu->batiments[choix]->taille.x - 1;
            stocker(jeu->batiments[choix]->taille.x - 1, ifs);
        }
    }
    return jeu->batiments[choix];
}
void construction_batiment(Jeu jeu){

}

Coordonnee* initialisation_case_ajacentes(Coordonnee coordonnee_batiment,int longueur, int hauteur ){
    Coordonnee* case_adjacente = malloc(longueur*hauteur*2* sizeof(Coordonnee));
    for (int i = 0; i < longueur*hauteur*2; i++) {
        if (i < hauteur){
            case_adjacente[i].x = coordonnee_batiment.x - 1;
            case_adjacente[i].y = coordonnee_batiment.y + i;
        }
        else if ( i < (hauteur + longueur)){
            case_adjacente[i].x = coordonnee_batiment.x + i - hauteur;
            case_adjacente[i].y = coordonnee_batiment.y + hauteur;
        }
        else if (i < (hauteur*2 + longueur)){
            case_adjacente[i].x = coordonnee_batiment.x + longueur;
            case_adjacente[i].y = coordonnee_batiment.y - i + hauteur*2 + longueur;
        }
        else{
            case_adjacente[i].x = coordonnee_batiment.x - i + hauteur*2 + longueur*2;
            case_adjacente[i].y = coordonnee_batiment.y - 1;
        }
    }
    return case_adjacente;
}


