#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>
#include <windows.h>

// Table des variables
// https://docs.google.com/spreadsheets/d/100_8y61qgKU3HSVB_qyyqeg9YfAm5iXL-RIHa2iqSQM/edit?usp=sharing

// Tous les codes des symbole pour le tableaux
#define HautDroit -69
#define BasDroit -68
#define BasGauche 200
#define HautGauche 201
#define MillieuBas 202
#define MillieuHaut 203
#define MillieuGauche 204
#define MillieuDroit -71
#define ligneVertical 205
#define ligneHorizontal -70
#define Croisement 206

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
    int nbC, nbE;
    int choixOptionPrincipal, choixOptionSecondaire;
    char nom[21], prenom[21];
    int nbPersonnes, nbDEnfants;
    int i, j, m, a;
    char dateDebut[11], dateFin[11];
    int paye, idEmplacement;

    // Declaration de methode
    void affichageClient(Client **, int, int);
    void affichageClientNonReserve(Client **, int *);
    void ajoutClient(Client **, char[], char[], int, int, char[], char[], int, int, int *);
    void supprimerClient(Client **, int, int *);
    void lectureClient(Client **, int *);
    void ecritureClient(Client **, int *);

    void affichageEmplacement(Emplacement **, int, int);
    void ajouterEmplacement(Emplacement **, char[], int, int, bool, bool, bool, int *);
    void lectureEmplacement(Emplacement **, int *);
    void ecritureEmplacement(Emplacement **, int *);

    void affichageChoix();
    void annuler(Client **, Emplacement **, int, int);

    // Permet de mettre la console en pleine ecran
    HWND hwnd = GetForegroundWindow();
    ShowWindow(hwnd, SW_MAXIMIZE);

    // Initalisation
    nbC = 0;
    nbE = 0;
    debC = NULL;
    debE = NULL;
    choixOptionPrincipal = -1;
    lectureClient(&debC, &nbC);
    lectureEmplacement(&debE, &nbE);

    // Le menu
    while (choixOptionPrincipal != 0)
    {

        // Menu

        switch (choixOptionPrincipal)
        {
        case 1:
            choixOptionSecondaire = 1;
            while (choixOptionSecondaire != 0 && (30 * (choixOptionSecondaire - 1)) < nbC)
            {

                // Netoyage du terminal
                system("cls");

                affichageClient(&debC, 1 + (30 * (choixOptionSecondaire - 1)), 30 * (choixOptionSecondaire));
                printf("-------------------------------------------------------------------------------------------------------------------------------------------\n");
                printf("\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\tPages : ");
                scanf("%2d", &choixOptionSecondaire);
            }
            printf("\n");
            break;
        case 2:
            choixOptionSecondaire = 1;
            while (choixOptionSecondaire != 0 && (30 * (choixOptionSecondaire - 1)) < nbE)
            {

                // Netoyage du terminal
                system("cls");

                affichageEmplacement(&debE, 1 + (30 * (choixOptionSecondaire - 1)), 30 * (choixOptionSecondaire));
                printf("--------------------------------------------------------------------------------------\n");
                printf("\t\t\t\t\t\t\t\t\t    Pages : ");
                scanf("%2d", &choixOptionSecondaire);
            }
            printf("\n");
            break;
        case 3:
            printf("Ajouts d'un client \n");
            printf("-------------------\n");
            printf("Noms du client : ");
            scanf("%20s", &nom);
            printf("Prenoms du client : ");
            scanf("%20s", &prenom);
            printf("\nNombre de personne(enfants non-compris) : ");
            scanf("%2d", &nbPersonnes);
            printf("\nNombre d'enfants : ");
            scanf("%2d", &nbDEnfants);

            printf("\nDate de debut ");
            printf("\n--------------");
            printf("Jour : ");
            scanf("%2d", &j);
            printf("\nMois : ");
            scanf("%2d", &m);
            printf("\nAnnee : ");
            scanf("%4d", &a);
            strcpy(dateDebut, j + '/' + m + '/' + a);

            printf("\nDate de fin ");
            printf("\n--------------");
            printf("Jour : ");
            scanf("%2d", &j);
            printf("\nMois : ");
            scanf("%2d", &m);
            printf("\nAnnee : ");
            scanf("%4d", &a);
            strcpy(dateFin, j + '/' + m + '/' + a);

            printf("Es-ce payer ?");
            paye = 0;
            printf("Il a reserver quelle emplacement");
            idEmplacement = -1;
            ajoutClient(&debC, nom, prenom, nbPersonnes, nbDEnfants, dateDebut, dateFin, paye, idEmplacement, nbC);
            printf("\n");
            break;
        case 4:
            printf("Ajouts d'emplacement \n");
            printf("\n");
            break;
        case 5:
            printf("Enregistrer ! \n");
            printf("\n");
            break;
        case -1:
            break;
        default:
            printf("Mauvais choix veuillez recommencer\n\n");
        }
        // Affichage des choix
        affichageChoix();
        // Selection du  choix
        printf("\b\r");
        scanf("%2d", &choixOptionPrincipal);

        // Netoyage du terminal
        system("cls");
    }

    /////////////////////////////// Verification
}

void affichageChoix()
{
    int i;
    printf("%1c", HautGauche);
    for (i = 0; i < 32; i++)
        printf("%1c", ligneVertical);
    printf("%1c\n", HautDroit);

    printf("%1c Menu                           %1c\n", ligneHorizontal, ligneHorizontal);

    printf("%1c", MillieuGauche);
    for (i = 0; i < 32; i++)
        printf("%1c", ligneVertical);
    printf("%1c\n", MillieuDroit);

    printf("%1c 01 Affichage clients           %1c\n", ligneHorizontal, ligneHorizontal);
    printf("%1c 02 Affichage emplacements      %1c\n", ligneHorizontal, ligneHorizontal);
    printf("%1c 03 reserver                    %1c\n", ligneHorizontal, ligneHorizontal);
    printf("%1c 04 Ajouts d'emplacment         %1c\n", ligneHorizontal, ligneHorizontal);
    printf("%1c 05 Enregistrer                 %1c\n", ligneHorizontal, ligneHorizontal);
    printf("%1c 00 Quitter                     %1c\n", ligneHorizontal, ligneHorizontal);
   
    printf("%1c", MillieuGauche);
    for (i = 0; i < 32; i++)
        printf("%1c", ligneVertical);
    printf("%1c\n", MillieuDroit);

    printf("%1c               Votre choix :    %1c\n", ligneHorizontal, ligneHorizontal);
    printf("%1c", BasGauche);
    for (i = 0; i < 32; i++)
        printf("%1c", ligneVertical);
    printf("%1c\n", BasDroit);
}

//
//    Clients
//

// Affichage des Client
void affichageClient(Client **deb, int min, int max)
{
    Client *courant;
    int i;

    courant = *deb;

    for (i = 1; i < min; i++)
        courant = (*courant).suivant;

    printf(" N  |  Nom                  | Prenom                | Nb de personne | Nb d'enfant | Date de debut | Date de fin | Id emplacement | Payer ?\n");
    printf("----+-----------------------+-----------------------+----------------+-------------+---------------+-------------+----------------+--------\n");

    while (courant != NULL && i <= max)
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
            printf("%03d | %-21s | %-21s | %2d             | %2d          |  %10s   | %10s  |       %03d      | %3s \n",
                   i++, (*courant).nom, (*courant).prenom, (*courant).nbPersonne, (*courant).nbEnfant,
                   (*courant).dateDebut, (*courant).dateFin, (*courant).idEmplacement, tmp);
        courant = (*courant).suivant;
    }
}

// Ajouts clients
void ajoutClient(Client **deb, char nom[], char prenom[], int nbPersonne, int nbEnfant,
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
    Client *courant, *temp;
    int i;

    // initalisation
    courant = *deb;
    if (place >= 1 && place < (*n) + 1)
    {
        if (place == 1)
        {
            temp = *deb;
            *deb = (**deb).suivant;
            free(temp);
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
                temp = courant->suivant;
                courant->suivant = temp->suivant;
                free(temp);
            }
            else
            {
                temp = courant->suivant;
                courant->suivant = NULL;
                free(temp);
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
    void ajoutClient(Client **, char[], char[], int, int, char[], char[], int, int, int *);
    fdat = fopen("VanQuaquebekeVandijstadt01.dat", "r");

    fscanf(fdat, "%*[^\n]");
    fscanf(fdat, " %*[^\n]");

    fscanf(fdat, "%20s ", &nom);
    while (!feof(fdat))
    {
        fscanf(fdat, "%*1c %20s %*1c %2d %*1c %2d %*1c %10s %*1c %10s %*1c %2d %*1c %1d %*1c", &prenom, &nbPersonne,
               &nbEnfant, &dateDebut, &dateFin, &idEmplacement, &paye);
        ajoutClient(deb, nom, prenom, nbPersonne, nbEnfant, dateDebut, dateFin, paye, idEmplacement, nbC);
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

    fprintf(fres, "Nom                  | Prenom               |  Nb   | NbEnfants |   Debut    | Fin        | Emplacement| Payï¿½ |\n");
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
void affichageEmplacement(Emplacement **deb, int min, int max)
{
    Emplacement *courant;
    int i = min;
    courant = *deb;

    for (i = 1; i < min; i++)
        courant = (*courant).suivant;

    printf(" Num |  Type      | mettre Carre | Nb de personne max | Elec | Eau | Wifi  | Reserve | \n");
    printf("-----+------------+--------------+--------------------+------+-----+-------+---------| \n");
    while (courant != NULL && i <= max)
    {
        printf(" %03d | %-10s |     %3d      |         %2d         |  %1d   |  %1d  |  %1d    |    %1d    | \n",
               (*courant).num, (*courant).type, (*courant).superficie, (*courant).nbPersonneMax,
               (*courant).electricite, (*courant).eau, (*courant).wifi, (*courant).reserve);
        i++;
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

void ajouterEmplacementL(Emplacement **deb, char type[], int superficie, int nbMaxPers, bool electricite, bool eau, bool wifi, bool reserve, int *nb)
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
        (*courant).reserve = reserve;
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
        (*temp).reserve = reserve;
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
    void ajouterEmplacementL(Emplacement **, char[], int, int, bool, bool, bool, bool, int *);
    fdat = fopen("VanQuaquebekeVandijstadt02.dat", "r");
    fscanf(fdat, "%*[^\n]");
    fscanf(fdat, " %*[^\n]");

    fscanf(fdat, "%2d ", &num);
    while (!feof(fdat))
    {
        fscanf(fdat, "%*c %8s %*c %3d %*c %2d %*c %1d %*c %1d %*c %1d %*c %1d %*c", &type, &superficie, &nbPersonneMax, &electricite, &eau, &wifi, &reserve);
        ajouterEmplacementL(deb, type, superficie, nbPersonneMax, electricite, eau, wifi, reserve, nbE);
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

void affichageClientReserve(Client **deb, int *k)
{
    Client *courant;
    int i = 1;

    courant = *deb;

    printf(" N  |  Nom                  | Prenom                | Nb de personne | Nb d'enfant | Date de debut | Date de fin | Id emplacement | Payer ?\n");
    printf("----+-----------------------+-----------------------+----------------+-------------+---------------+-------------+----------------+--------\n");
    while (courant != NULL)
    {
        if ((*courant).idEmplacement != -1)
            printf("%03d | %-21s | %-21s | %2d             | %2d          |  %10s   | %10s  | %2d          | Non \n",
                   i++, (*courant).nom, (*courant).prenom, (*courant).nbPersonne, (*courant).nbEnfant,
                   (*courant).dateDebut, (*courant).dateFin, (*courant).idEmplacement);
        else
        {
            i += 1;
            k = k + 1;
        }

        courant = (*courant).suivant;
    }
}
void affichageClientNonReserve(Client **deb, int *k)
{
    Client *courant;
    int i = 1;

    courant = *deb;

    printf(" N  |  Nom                  | Prenom                | Nb de personne | Nb d'enfant | Date de debut | Date de fin | Id emplacement | Payer ?\n");
    printf("----+-----------------------+-----------------------+----------------+-------------+---------------+-------------+----------------+--------\n");
    while (courant != NULL)
    {
        if ((*courant).idEmplacement == -1)
            printf("%03d | %-21s | %-21s | %2d             | %2d          |  %10s   | %10s  | Aucun          | Non \n",
                   i++, (*courant).nom, (*courant).prenom, (*courant).nbPersonne, (*courant).nbEnfant,
                   (*courant).dateDebut, (*courant).dateFin);
        else
        {
            i += 1;
            k = k + 1;
        }

        courant = (*courant).suivant;
    }
}

void reserver(Client **debC, Emplacement **debE, int nbC, int nbE)
{
    Emplacement *courant;
    int k = 0; // nombre de client passï¿½s
    int e = 0; // nombre d'emplacement passï¿½s
    void affichageClientNonReserve(Client **, int *);
    void afficheEmplacementPourClient(int, Client **, Emplacement **, int *);
    void modificationDonnees(Client **, Emplacement **, int, int);
    void ecritureClient(Client **, int *);
    void ecritureEmplacement(Emplacement **, int *);
    int choixC, choixE;

    affichageClientNonReserve(debC, &k);

    printf("\nPour quel client voulez vous effectuer une reservation ?\n");
    scanf("%2d", &choixC);

    choixC = choixC + k;
    printf("\nVoici tout les emplacements disponibles pour ce client\n\n");
    // affichage si le nombre max de personne de l'emplacement <= nbPersonne
    //  et si l'emplacement n'est pas rï¿½servï¿½

    afficheEmplacementPourClient(choixC, debC, debE, &e);
    printf("\nQuel emplacement? \n");
    scanf("%2d", &choixE);

    modificationDonnees(debC, debE, choixC, choixE);

    ecritureClient(debC, &nbC);
    ecritureEmplacement(debE, &nbE);

    printf("Reservation faite !");
}
void annuler(Client **debC, Emplacement **debE, int nbC, int nbE)
{

    // déclarations
    void affichageClientReserve(Client **, int *);
    void ecritureClient(Client **, int *);
    void ecritureEmplacement(Emplacement **, int *);
    int k = 0, i; // nb clients passés
    Client *courantC;
    Emplacement *courantE;
    int numEmplacement, choixC;

    courantC = *debC;
    courantE = *debE;
    // code

    affichageClientReserve(debC, &k);
    printf("\nPour quel client voulez vous annuler la reservation ?\n");
    scanf("%2d", &choixC);

    for (i = 1; i < choixC; i++)
    {
        courantC = (*courantC).suivant;
    }

    numEmplacement = (*courantC).idEmplacement;

    (*courantC).idEmplacement = -1;

    for (i = 1; i < numEmplacement; i++)
    {
        courantE = (*courantE).suivant;
    }

    (*courantE).reserve = 0;

    ecritureClient(debC, &nbC);
    // erreur a montrer
    ecritureEmplacement(debE, &nbE);

    printf("Reservation faite !");
}

void afficheEmplacementPourClient(int choix, Client **debC, Emplacement **debE, int *e)
{

    Client *courantC;
    Emplacement *courantE;
    int nbPersonneCli;
    int i;
    courantC = *debC;

    for (i = 1; i < choix; i++)
    {
        courantC = (*courantC).suivant;
    }

    nbPersonneCli = (*courantC).nbPersonne;
    courantE = *debE;

    printf(" Num |  Type      | mettre Carre | Nb de personne max | Elec | Eau | Wifi  | Reserve  \n");
    printf("-----+------------+--------------+--------------------+------+-----+-------+--------- \n");
    while (courantE != NULL)
    {
        if ((*courantE).nbPersonneMax >= nbPersonneCli && (*courantE).reserve == 0)
            printf(" %03d | %-10s |     %3d      |         %2d         |  %1d   |  %1d  |  %1d    | %1d \n",
                   (*courantE).num, (*courantE).type, (*courantE).superficie, (*courantE).nbPersonneMax,
                   (*courantE).electricite, (*courantE).eau, (*courantE).wifi, (*courantE).reserve);
        else
            e = e + 1;
        courantE = (*courantE).suivant;
    }
}

void modificationDonnees(Client **debC, Emplacement **debE, int choixC, int choixE)
{

    Client *courantC;
    Emplacement *courantE;
    int i;
    courantC = *debC;
    courantE = *debE;

    // selectionne le bon client
    for (i = 1; i < choixC; i++)
    {
        courantC = (*courantC).suivant;
    }

    (*courantC).idEmplacement = choixE;

    // selectionne le bon emplacement
    for (i = 1; i < choixE; i++)
    {
        courantE = (*courantE).suivant;
    }

    (*courantE).reserve = 1;
}
