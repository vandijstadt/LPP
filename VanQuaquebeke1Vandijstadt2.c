#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>
#include <windows.h>

// Table des variables
// https://docs.google.com/spreadsheets/d/100_8y61qgKU3HSVB_qyyqeg9YfAm5iXL-RIHa2iqSQM/edit?usp=sharing

// Creation des structure
typedef struct Client
{
    char nom[22];
    char prenom[22];
    int nbPersonne;
    int nbEnfant;
    char dateDebut[11];
    char dateFin[11];
    int idEmplacement;
    bool paye;
    struct Client *suivant;
} Client;

typedef struct Emplacement
{
    int num;
    char type[11];
    int superficie;
    int nbPersonneMax;
    bool electricite;
    bool eau;
    bool wifi;
    bool reserve;
    struct Emplacement *suivant;
} Emplacement;
void main()
{
    // Declaration
    Client *debC;
    Emplacement *debE;

    int nbC = 0, nbE = 0;
    // Initalisation

    // Declaration de methode
    void affichageClient(Client **);
    void ajoutClient(Client **, char[], char[], int, int, char[], char[], int *);
    void supprimerClient(Client **, int, int *);
    void lectureClient(Client **, int *);
    void reserver(Client **, Emplacement **);

    void affichageEmp(Emplacement **);
    void ajouterEmplacement(Emplacement **, char[], int, int, bool, bool, bool, int *);
    void lectureEmplacement(Emplacement **, int *);

    // Netoyage du terminal
    system("cls");

    // Permet de mettre la console en pleine ecran
    HWND hwnd = GetForegroundWindow();
    ShowWindow(hwnd, SW_MAXIMIZE);

    // Creation du premier Client
    debC = NULL;
    debE = NULL;

    // Le menu

    /////// GERER LES ECRITURES presque fini
    /////// Verification
    /////// 

    // Les test !
    void test(int, Client **, Emplacement **);
    test(3, &debC, &debE);
}
void test(int test, Client **debC, Emplacement **debE)
{
    // Initalisation
    int nbC = 0, nbE = 0;

    // Declaration de methode
    void affichageClient(Client **);
    void affichageClientNonReserve(Client **);
    void ajoutClient(Client **, char[], char[], int, int, char[], char[], int *);
    void supprimerClient(Client **, int, int *);
    void lectureClient(Client **, int *);
    void ecritureClient(Client **, int *);

    void affichageEmp(Emplacement **);
    void ajouterEmplacement(Emplacement **, char[], int, int, bool, bool, bool, int *);
    void lectureEmplacement(Emplacement **, int *);
    void ecritureEmplacement(Emplacement **, int *);
    // TEST !!
    // Test Clients
    if (test == 1)
    {
        // Test d'ajouts
        ajoutClient(debC, "Van Quaquebeke", "Nathan", 2, 0, "24/11/2022", "27/11/2022", &nbC);
        ajoutClient(debC, "Vandijstadt", "Nicolas", 4, 0, "25/11/2022", "26/11/2022", &nbC);
        ajoutClient(debC, "xxxxxxxxxxxxxxxxxxxxxxxxx", "xxxxxxxxxxxxxxxxxxxxxxxxx", 0, 0, "00/00/0000", "00/00/0000", &nbC);
        affichageClient(debC);
        // Test suppression
        printf("Suppression du 1er (Van Quaquebeke):\n");
        supprimerClient(debC, 1, &nbC);
        affichageClient(debC);
        printf("Suppression du 2e (XXXXXX) :\n");
        supprimerClient(debC, 2, &nbC);
        affichageClient(debC);
    }
    // Test emplacements
    else if (test == 2)
    {
        // Test ajouts
        ajouterEmplacement(debE, "Tente", 100, 4, true, true, true, &nbE);
        ajouterEmplacement(debE, "Bungalow", 100, 4, true, true, true, &nbE);
        ajouterEmplacement(debE, "Caravane", 100, 4, true, true, true, &nbE);
        affichageEmp(debE);
    }
    // Lecture
    else if (test == 3)
    {
        lectureClient(debC, &nbC);
        affichageClient(debC);
        lectureEmplacement(debE, &nbE);
        affichageEmp(debE);
    }
    // Ecriture
    else if (test == 4)
    {
        // Clients
        lectureClient(debC, &nbC);
        ecritureClient(debC, &nbC);
        // Emplacement
        lectureEmplacement(debE, &nbE);
        ecritureEmplacement(debE, &nbE);
    }
}
//
//    Clients
//

// Affichage des Client
void affichageClient(Client **deb)
{
    Client *courant;
    int i = 1;

    courant = *deb;

    printf(" N  |  Nom                  | Prenom                | Nb de personne | Nb d'enfant | Date de debut | Date de fin | Id emplacement | Payer ?\n");
    printf("----+-----------------------+-----------------------+----------------+-------------+---------------+-------------+----------------+--------\n");
    while (courant != NULL)
    {
        char tmp[4];
        strcpy(tmp, "Oui");
        if ((*courant).paye == 0)
        {
            strcpy(tmp, "Non");
        }
        if ((*courant).idEmplacement == -1)
            printf("%03d | %-21s | %-21s | %2d             | %2d          |  %10s   | %10s  |     Aucun      | %3s \n",
                   i++, (*courant).nom, (*courant).prenom, (*courant).nbPersonne, (*courant).nbEnfant,
                   (*courant).dateDebut, (*courant).dateFin, tmp);
        else
            printf("%03d | %-21s | %-21s | %2d             | %2d          |  %10s   | %10s  | %03d | %1d | %3s \n",
                   i++, (*courant).nom, (*courant).prenom, (*courant).nbPersonne, (*courant).nbEnfant,
                   (*courant).dateDebut, (*courant).dateFin, (*courant).idEmplacement, tmp);
        courant = (*courant).suivant;
    }
}

// Ajouts d'un client
void ajoutClient(Client **deb, char nom[], char prenom[], int nbPersonne, int nbEnfant,
                 char dateDebut[], char dateFin[], int *nb)
{
    // Declaration
    Client *courant, *temp;
    // On verifie si il exist deja un element dans la liste
    if (*deb == NULL)
    {
        // on alloue de la memoire pour le client
        courant = malloc(sizeof(Client));

        // On declarre que c'est le premier element
        *deb = courant;

        // Assigne les valeurs
        strcpy((*courant).nom, nom);
        (*courant).nom[21] = '\0';
        strcpy((*courant).prenom, prenom);
        (*courant).prenom[21] = '\0';
        (*courant).nbPersonne = nbPersonne;
        (*courant).nbEnfant = nbEnfant;
        strcpy((*courant).dateDebut, dateDebut);
        strcpy((*courant).dateFin, dateFin);
        (*courant).idEmplacement = -1;
        (*courant).paye = 0;
        (*courant).suivant = NULL;
    }

    else
    {
        // on alloue de la memoire pour le client
        temp = malloc(sizeof(Client));

        // Assigne les valeurs
        strcpy((*temp).nom, nom);
        (*temp).nom[21] = '\0';
        strcpy((*temp).prenom, prenom);
        (*temp).prenom[21] = '\0';
        (*temp).nbPersonne = nbPersonne;
        (*temp).nbEnfant = nbEnfant;
        strcpy((*temp).dateDebut, dateDebut);
        strcpy((*temp).dateFin, dateFin);
        (*temp).idEmplacement = -1;
        (*temp).paye = 0;
        (*temp).suivant = NULL;

        // Recherche ou mettre a optimisier
        courant = *deb;
        while (0 == 0)
        {
            if ((*courant).suivant == NULL)
            {
                break;
            }
            courant = (*courant).suivant;
        }
        (*courant).suivant = temp;
    }
    *nb += 1;
}
// Ajouts clients lors de la lecture
void ajoutClientL(Client **deb, char nom[], char prenom[], int nbPersonne, int nbEnfant,
                  char dateDebut[], char dateFin[], int payer, int idEmplacement, int *nb)
{
    // Declaration
    Client *courant, *temp;
    // On verifie si il exist deja un element dans la liste
    if (*deb == NULL)
    {
        // on alloue de la memoire pour le client
        courant = malloc(sizeof(Client));

        // On declarre que c'est le premier element
        *deb = courant;

        // Assigne les valeurs
        strcpy((*courant).nom, nom);
        (*courant).nom[21] = '\0';
        strcpy((*courant).prenom, prenom);
        (*courant).prenom[21] = '\0';
        (*courant).nbPersonne = nbPersonne;
        (*courant).nbEnfant = nbEnfant;
        strcpy((*courant).dateDebut, dateDebut);
        strcpy((*courant).dateFin, dateFin);
        (*courant).idEmplacement = idEmplacement;
        (*courant).paye = payer;
        (*courant).suivant = NULL;
    }

    else
    {
        // on alloue de la memoire pour le client
        temp = malloc(sizeof(Client));

        // Assigne les valeurs
        strcpy((*temp).nom, nom);
        (*temp).nom[21] = '\0';
        strcpy((*temp).prenom, prenom);
        (*temp).prenom[21] = '\0';
        (*temp).nbPersonne = nbPersonne;
        (*temp).nbEnfant = nbEnfant;
        strcpy((*temp).dateDebut, dateDebut);
        strcpy((*temp).dateFin, dateFin);
        (*temp).idEmplacement = idEmplacement;
        (*temp).paye = payer;
        (*temp).suivant = NULL;

        // Recherche ou mettre a optimisier
        courant = *deb;
        while (0 == 0)
        {
            if ((*courant).suivant == NULL)
            {
                break;
            }
            courant = (*courant).suivant;
        }
        (*courant).suivant = temp;
    }
    *nb += 1;
}

// Retirer un client
void supprimerClient(Client **deb, int place, int *n)
{
    // Declaration
    Client *courant, *tempo;
    int i;

    // initalisation
    courant = *deb;
    if (place >= 1 && place < (*n) + 1)
    {
        if (place == 1)
        {
            tempo = *deb;
            *deb = (**deb).suivant;
            free(tempo);
        }
        else
        {
            courant = *deb;
            // on se d?place jusqu'? la bonne adresse
            for (i = 1; i < place - 1; i++)
            {
                courant = courant->suivant;
            }
            if (place != *n)
            {
                // on fait dispara?tre un maillon de la chaine
                tempo = courant->suivant;
                courant->suivant = tempo->suivant;
                free(tempo);
            }
            else
            {
                tempo = courant->suivant;
                courant->suivant = NULL;
                free(tempo);
            }
        }
        (*n) = (*n) - 1;
    }
    else
        printf("impossible place = %d\n", place);
}

// Lire les clients dans le fichier de donnÃƒÂ©es
void lectureClient(Client **deb, int *nbC)
{
    FILE *fdat;
    char nom[22], prenom[22];
    int nbPersonne, idEmplacement, nbEnfant;
    char dateDebut[11], dateFin[11];
    int paye;
    void ajoutClientL(Client **, char[], char[], int, int, char[], char[], int, int, int *);
    fdat = fopen("VanQuaquebekeVandijstadt01.dat", "r");

    fscanf(fdat, "%*[^\n]");
    fscanf(fdat, " %*[^\n]");

    fscanf(fdat, "%20s ", &nom);
    while (!feof(fdat))
    {
        fscanf(fdat, "%*1c %20s %*1c %2d %*1c %2d %*1c %10s %*1c %10s %*1c %2d %*1c %1d %*1c", &prenom, &nbPersonne,
               &nbEnfant, &dateDebut, &dateFin, &idEmplacement, &paye);
        ajoutClientL(deb, nom, prenom, nbPersonne, nbEnfant, dateDebut, dateFin, paye, idEmplacement, nbC);
        // printf("%-20s %-20s %2d %2d %-10s %-10s %2d %1d\n", nom, prenom, nbPersonne,
        // nbEnfant, dateDebut, dateFin, idEmplacement, paye);
        fscanf(fdat, "%20s ", &nom);
    }
}

// Lire les clients dans le fichier de donnÃƒÂ©es
void ecritureClient(Client **deb, int *nbc)
{
    FILE *fres;
    fres = fopen("VanQuaquebekeVandijstadt01.dat", "w");
    Client *courant = *deb;

    int i;

    fprintf(fres, "Nom                  | Prenom               |  Nb   | NbEnfants |   Debut    | Fin        | Emplacement| Payé |\n");
    fprintf(fres, "---------------------+----------------------+-------+-----------+------------+------------+------------+------|\n");

    for (i = 0; i < *nbc; i++)
    {
        fprintf(fres, "%-20s | %-20s |  %2d   |    %2d     | %10s | %10s |     %2d     |  %1d   |\n", (*courant).nom, (*courant).prenom,
                (*courant).nbPersonne, (*courant).nbEnfant, (*courant).dateDebut, (*courant).dateFin,
                (*courant).idEmplacement, (*courant).paye);
        courant = (*courant).suivant;
    }
}

//
// Emplacement
//

// Affichage emplacement
void affichageEmp(Emplacement **deb)
{
    Emplacement *courant;

    courant = *deb;

    printf(" Num |  Type      | mettre Carre | Nb de personne max | Elec | Eau | Wifi  | Reserve | \n");
    printf("-----+------------+--------------+--------------------+------+-----+-------+---------| \n");
    while (courant != NULL)
    {
        printf(" %03d | %-10s |     %3d      |         %2d         |  %1d   |  %1d  |  %1d    |    %1d    | \n",
               (*courant).num, (*courant).type, (*courant).superficie, (*courant).nbPersonneMax,
               (*courant).electricite, (*courant).eau, (*courant).wifi, (*courant).reserve);
        courant = (*courant).suivant;
    }
}
// Ajouter un emplacement
void ajouterEmplacement(Emplacement **deb, char type[], int superficie, int nbMaxPers, bool electricite, bool eau, bool wifi, int *nb)
{
    // Declaration
    Emplacement *courant, *temp;
    int i;
    //
    i = 0;

    // On verifie si il exist deja un element dans la liste
    if (*deb == NULL)
    {
        // on alloue de la memoire pour le client
        courant = malloc(sizeof(Emplacement));

        // On declarre que c'est le premier element
        *deb = courant;

        // Assigne les valeurs
        (*courant).num = 1;
        strcpy((*courant).type, type);
        (*courant).superficie = superficie;
        (*courant).nbPersonneMax = nbMaxPers;
        (*courant).electricite = electricite;
        (*courant).eau = eau;
        (*courant).wifi = wifi;
        (*courant).reserve = false;
        (*courant).suivant = NULL;
    }

    else
    {
        // on alloue de la memoire pour le client
        temp = malloc(sizeof(Emplacement));

        // Assigne les valeurs
        (*temp).num = (*nb) + 1;
        strcpy((*temp).type, type);
        (*temp).superficie = superficie;
        (*temp).nbPersonneMax = nbMaxPers;
        (*temp).electricite = electricite;
        (*temp).eau = eau;
        (*temp).wifi = wifi;
        (*temp).reserve = false;
        (*temp).suivant = NULL;
        // Recherche ou mettre
        courant = *deb;
        while (0 == 0)
        {
            if ((*courant).suivant == NULL)
            {
                break;
            }
            courant = (*courant).suivant;
        }
        (*courant).suivant = temp;
    }
    *nb += 1;
}

// supprimer un emplacement
// lire les remplacements
void lectureEmplacement(Emplacement **deb, int *nbE)
{
    FILE *fdat;
    int num, superficie, nbPersonneMax;
    char type[11];
    int electricite, eau, wifi, reserve;
    void ajouterEmplacement(Emplacement **, char[], int, int, bool, bool, bool, int *);
    fdat = fopen("VanQuaquebekeVandijstadt02.dat", "r");
    fscanf(fdat, "%*[^\n]");
    fscanf(fdat, " %*[^\n]");

    fscanf(fdat, "%2d ", &num);
    while (!feof(fdat))
    {
        fscanf(fdat, "%*c %8s %*c %3d %*c %2d %*c %1d %*c %1d %*c %1d %*c %1d %*c", &type, &superficie, &nbPersonneMax, &electricite, &eau, &wifi, &reserve);
        ajouterEmplacement(deb, type, superficie, nbPersonneMax, electricite, eau, wifi, nbE);
        // printf("%2d %9s %3d %2d %1d %1d %1d %1d\n", num, type, superficie, nbPersonneMax, electricite, eau, wifi, reserve);
        fscanf(fdat, "%2d ", &num);
    }
}

// Lire les clients dans le fichier de donnÃƒÂ©es
void ecritureEmplacement(Emplacement **deb, int *nbc)
{
    FILE *fres;
    fres = fopen("VanQuaquebekeVandijstadt02.dat", "w");
    Emplacement *courant = *deb;

    int i;

    fprintf(fres, "Num | Type     | mCarre | NbPersonMax | Elec | Eau |  Wifi | Reserve |\n");
    fprintf(fres, "----+----------+--------+-------------+------+-----+-------+---------|\n");

    while (courant != NULL)
    {
        fprintf(fres, "%3d | %-9s|   %3d  |      %2d     |  %1d   |  %1d  |   %1d   |    %1d    | \n",
               (*courant).num, (*courant).type, (*courant).superficie, (*courant).nbPersonneMax,
               (*courant).electricite, (*courant).eau, (*courant).wifi, (*courant).reserve);
        courant = (*courant).suivant;
    }
}
void affichageClientNonReserve(Client **deb)
{
    Client *courant;
    int i = 1;

    courant = *deb;

    printf(" N  |  Nom                  | Prenom                | Nb de personne | Nb d'enfant | Date de debut | Date de fin | Id emplacement | Payer ?\n");
    printf("----+-----------------------+-----------------------+----------------+-------------+---------------+-------------+----------------+--------\n");
    while (courant != NULL)
    {
        if ((*courant).idEmplacement == -1)
            printf("%03d | %-21s | %-21s | %2d             | %2d          |  %10s   | %10s  | Aucun | Non \n",
                   i++, (*courant).nom, (*courant).prenom, (*courant).nbPersonne, (*courant).nbEnfant,
                   (*courant).dateDebut, (*courant).dateFin);
        courant = (*courant).suivant;
    }
}

void reserver(Client **debC, Emplacement **debE)
{
    Emplacement *courant;

    void affichageClientNonReserve(Client **);

    int choix;

    affichageClientNonReserve(debC);

    printf("\nPour quel client voulez vous effectuer une reservation ?\n");
    scanf("%2d", &choix);

    printf("Voici tout les emplacements disponibles pour ce client");

    // affichage si le nombre max de personne de l'emplacement <= nbPersonne
    //  et si l'emplacement n'est pas réservé
}

