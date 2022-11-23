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

    switch (choix) {
        case maison: {
            nouveau->taille.x = TAILLE_MAISON;
            nouveau->taille.y = TAILLE_MAISON;
            nouveau->nom = "Maison";
            nouveau->stadeEvolution = 1;
            liste = jeu->batiments[maison];
            liste = maj_liste_chaine(nouveau, tail, liste);
            jeu->batiments[maison] = liste;
            break;
        }
        case chateau_deau: {
            nouveau->taille.x = LONGUEUR_BATIMENTS;
            nouveau->taille.y = LARGEUR_BATIMENTS;
            nouveau->nom = "Chateau d'eau";
            nouveau->stadeEvolution = 0;
            liste =  jeu->batiments[chateau_deau];
            liste = maj_liste_chaine(nouveau, tail, liste);
            jeu->batiments[chateau_deau] = liste;
            break;
        }
        case usine_electrique: {
            nouveau->taille.x = LONGUEUR_BATIMENTS;
            nouveau->taille.y = LARGEUR_BATIMENTS;
            nouveau->nom = "Usine electrique";
            nouveau->stadeEvolution = 0;
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




void afficherM(Jeu* jeu) {
    int nbmaison = 1;
    int nbchateau = 1;
    int nbusine = 1;
    Batiment *listeMaison = jeu->batiments[maison];
    Batiment *listeChateau = jeu->batiments[chateau_deau];
    Batiment *listeUsine = jeu->batiments[usine_electrique];

    if(listeMaison != NULL) {
        do {
            printf("Maison %d : x: %d  y: %d    stade: %d\n", nbmaison, listeMaison->x, listeMaison->y,listeMaison->stadeEvolution);
            nbmaison++;
            listeMaison = listeMaison->next;

        } while (listeMaison != jeu->batiments[maison]);
    }
    else{printf("Liste maison vide\n");}

    if(listeChateau != NULL) {
        do {
            printf("Chateau d'eau %d : x: %d  y: %d\n", nbchateau, listeChateau->x, listeChateau->y);
            nbchateau++;
            listeChateau = listeChateau->next;

        } while (listeChateau != jeu->batiments[chateau_deau]);
    }
    else{printf("Liste chateau eau vide\n");}

    if(listeUsine != NULL) {
        do {
            printf("Usine electrique %d : x: %d   y: %d\n", nbusine, listeUsine->x, listeUsine->y);
            nbusine++;
            listeUsine = listeUsine->next;

        } while (listeUsine != jeu->batiments[usine_electrique]);
    }
    else{printf("Liste usine electrique vide\n");}
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
// centaine type de batiment dizaine evolution unite temps restant
Batiment* maj_charge_liste(Jeu* jeu,Batiment* liste,int* x,int y,FILE* ifs,int choix,int stadeEvo){
    Batiment* parcours = liste;
    bool bouclePasse = FALSE;

    if(liste == NULL) {
        ajouterBatiment(jeu, (*x), y, choix);
        jeu->batiments[choix]->enCours = TRUE;
        if(choix == maison){
            jeu->batiments[choix]->stadeEvolution = stadeEvo;
        }
        (*x) = (*x) + jeu->batiments[choix]->taille.x - 1;
        stocker(jeu->batiments[choix]->taille.x - 1,ifs);

    }
    else {
        do {
            bool conditionVerifie = FALSE;
            switch (choix) {
                case maison: {
                    if (((y == parcours->y + 2 && (*x) == parcours->x) ||
                         (y == parcours->y + 1 && (*x) == parcours->x)) &&
                        parcours->enCours == TRUE) {
                        conditionVerifie = TRUE;
                    }
                    break;
                }
                default: {
                    if (((y == parcours->y + 3 && (*x) == parcours->x) ||
                         (y == parcours->y + 2 && (*x) == parcours->x) ||
                         (y == parcours->y + 1 && (*x) == parcours->x)) &&
                        parcours->enCours == TRUE) {
                        conditionVerifie = TRUE;
                    }
                }
            }
            if (conditionVerifie == TRUE) {
                (*x) = (*x) + jeu->batiments[choix]->taille.x - 1;
                stocker(jeu->batiments[choix]->taille.x - 1, ifs);
                if (y == parcours->y + jeu->batiments[choix]->taille.x - 1) {
                    parcours->enCours = FALSE;
                }
                bouclePasse = TRUE;
            }

            parcours = parcours->next;
        }while(parcours != jeu->batiments[choix]);

        if(bouclePasse == FALSE) {
            ajouterBatiment(jeu, (*x), y, choix);
            Batiment *parcoursbis = liste;
            while (parcoursbis->next != liste) {
                parcoursbis = parcoursbis->next;
            }
            parcoursbis->y = y;
            parcoursbis->x = (*x);
            parcoursbis->enCours = TRUE;
            if(choix == maison){
                parcoursbis->stadeEvolution = stadeEvo;
            }
            (*x) = (*x) + jeu->batiments[choix]->taille.x - 1;
            stocker(jeu->batiments[choix]->taille.x - 1, ifs);
        }
    }
    return jeu->batiments[choix];
}

void chargementListe(Jeu* jeu,int num,int y,int* x,FILE** ifs,int stadeEvo){
    Batiment* liste = NULL;

    switch(num){
        case 2:{
            liste = jeu->batiments[maison];
            liste = maj_charge_liste(jeu,liste,x,y,*ifs,maison,stadeEvo);
            jeu->batiments[maison] = liste;
            break;
        }
        case 3:{
            liste = jeu->batiments[chateau_deau];
            liste = maj_charge_liste(jeu,liste,x,y,*ifs,chateau_deau,stadeEvo);
            jeu->batiments[chateau_deau] = liste;
            break;
        }
        case 4:{
            liste = jeu->batiments[usine_electrique];
            liste = maj_charge_liste(jeu,liste,x,y,*ifs,usine_electrique,stadeEvo);
            jeu->batiments[usine_electrique] = liste;
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

bool verifier_batiment_a_cote_route(Jeu *jeu, int type_de_batiment, int co_x, int co_y) {
    int nb_connexion = 0;
    switch (type_de_batiment) {
        case maison : {
            for (int i = 0; i < TAILLE_MAISON; i++) {
                if (co_y != 0 && (jeu->terrain[co_y - 1][co_x + i] == 1)) {
                    nb_connexion++;
                }
                if (co_x != 0 && (jeu->terrain[co_y + i][co_x - 1] == 1)) {
                    nb_connexion++;
                }
                if (co_y != ORDRE_EN_Y && (jeu->terrain[co_y + TAILLE_MAISON][co_x + i] == 1)) {
                    nb_connexion++;
                }
                if (co_x != ORDRE_EN_X && (jeu->terrain[co_y + i][co_x + TAILLE_MAISON] == 1)) {
                    nb_connexion++;
                }
            }
            return (nb_connexion != 0) ? TRUE : FALSE;
        }
        case chateau_deau :
        case usine_electrique : {
            for (int i = 0; i < LARGEUR_BATIMENTS; i++) {
                if (co_x != 0 && (jeu->terrain[co_y + i][co_x - 1] == 1)) {
                    nb_connexion++;
                }
                if (co_x != ORDRE_EN_X && (jeu->terrain[co_y + i][co_x + LARGEUR_BATIMENTS] == 1)) {
                    nb_connexion++;
                }
            }
            for (int i = 0; i < LONGUEUR_BATIMENTS; i++) {
                if (co_y != 0 && (jeu->terrain[co_y - 1][co_x + i] == 1)) {
                    nb_connexion++;
                }
                if (co_y != ORDRE_EN_Y && (jeu->terrain[co_y + LONGUEUR_BATIMENTS][co_x + i] == 1)) {
                    nb_connexion++;
                }
            }
            return (nb_connexion != 0) ? TRUE : FALSE;
        }
        default: {
            break;
        }
    }

}


int conditionAchatBatiment(Jeu* jeu,int choix){
    switch(choix){
        case maison:{
            if(jeu->argent >= COUT_MAISON){
                jeu->argent = jeu->argent - COUT_MAISON;
                return 1;
            }
            break;
        }
        case chateau_deau:{
            if(jeu->argent >= COUT_CHATEAU_EAU){
                jeu->argent = jeu->argent - COUT_CHATEAU_EAU;
                return 1;
            }
            break;
        }
        case usine_electrique:{
            if(jeu->argent >= COUT_USINE_ELECTRIQUE){
                jeu->argent = jeu->argent - COUT_USINE_ELECTRIQUE;
                return 1;
            }
            break;
        }
    }
    printf("Vous n'avez pas assez d'argent pour poser ce batiment") ;
    return 0;
}
