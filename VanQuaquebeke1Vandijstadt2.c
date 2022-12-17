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
    int nbJour;
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
    float prix;
    struct Emplacement *suivant;
} Emplacement;

void main()
{
    // Declaration
    Client *debC;
    Emplacement *debE;
//    Personnel *debP;
    int i; 
    int nbC, nbE, nbP;
    int choixOptionPrincipal, choixOptionSecondaire;
    char nom[21], prenom[21];
    int nbPersonnes, nbDEnfants;
    char j[2], m[2], a[4];
    char dateDebut[11], dateFin[11];
    int nbJour, paye, idEmplacement;

    // Declaration de methode
    void affichageClient(Client **, int, int);
    void ajoutClient(Client **, char[], char[], int, int, char[], int, int, int, int *);
    void lectureClient(Client **, int *);
    void ecritureClient(Client **, int *);

    void affichageEmplacement(Emplacement **, int, int);
    void ajouterEmplacement(Emplacement **, char[], int, int, bool, bool, bool, float, int *);
    void lectureEmplacement(Emplacement **, int *);
    void ecritureEmplacement(Emplacement **, int *);

//	void modificationDonnees(Client**, Emplacement**, int, int);
    void affichageChoix();
//	void annuler(Client **, Emplacement **, int*, int*);

    // Permet de mettre la console en pleine ecran
    HWND hwnd = GetForegroundWindow();
    ShowWindow(hwnd, SW_MAXIMIZE);

    // Initalisation
    nbC = 0;
    nbE = 0;
    nbP = 0;
    debC = NULL;
    debE = NULL;
    // debP = NULL;
    choixOptionPrincipal = -1;
    lectureClient(&debC, &nbC);
    lectureEmplacement(&debE, &nbE);

    // Le menu
    while (choixOptionPrincipal != 0)
    {
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
                printf("----------------------------------------------------------------------------------------------\n");
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
            printf("Nombre de personne(enfants non-compris) : ");
            scanf("%2d", &nbPersonnes);
            printf("Nombre d'enfants : ");
            scanf("%2d", &nbDEnfants);

    		printf("Date de debut \n");
    		printf("--------------\n");
    		printf("Jour : ");
    		scanf("%s", &j);
    		printf("Mois : ");
    		scanf("%s", &m);
    		printf("Annee : ");
    		scanf("%4s", &a);
		    strcpy(dateDebut, strcat(strcat(strcat(strcat(j, "/"),m),"/"),a));
		    
    		printf("Nombre de jour \n");
    		scanf("%2d", &nbJour);
            printf("Es-ce payer (O = oui, N = non) : ");
            scanf("%s", &paye);
            if (toupper(paye) == 'O')
                paye = 0;
            else if (toupper(paye) == 'N')
                paye = 1;
            printf("Il a reserver quelle emplacement : ");
            scanf("%1d", &idEmplacement);

            ajoutClient(&debC, nom, prenom, nbPersonnes, nbDEnfants, dateDebut, nbJour, paye, idEmplacement, &nbC);
            ecritureClient(&debC, &nbC);
            ecritureEmplacement(&debE, &nbE);
            printf("\n");
            break;
        case 4 :
            printf("anuller \n");
            printf("En cours de creation \n");
            annuler(&debC, &debE,&nbC,&nbE);
        	break;
		case 5:
            printf("Ajouts d'emplacement \n");
            printf("En cours de creation \n");
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
        printf("                Votre choix : ");
        scanf("%2d", &choixOptionPrincipal);

        // Netoyage du terminal
        system("cls");
    }

    /////////////////////////////// Verification a faire   ///////////////////////////////
    /////////////////////////////// Personnel a faire      ///////////////////////////////
}

void affichageChoix() // Permet d'afficher tous les choix que peut faire l'utilisateur
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
    printf("%1c 03 Reserver                    %1c\n", ligneHorizontal, ligneHorizontal);
    printf("%1c 04 Annuler                     %1c\n", ligneHorizontal, ligneHorizontal);
    printf("%1c 05 Ajouts d'emplacment         %1c\n", ligneHorizontal, ligneHorizontal);
    printf("%1c 00 Quitter                     %1c\n", ligneHorizontal, ligneHorizontal);

    // printf("%1c", MillieuGauche);
    // for (i = 0; i < 32; i++)
    //     printf("%1c", ligneVertical);
    // printf("%1c\n", MillieuDroit);

    // printf("%1c               Votre choix :  %1c\n", ligneHorizontal, ligneHorizontal);

    printf("%1c", BasGauche);
    for (i = 0; i < 32; i++)
        printf("%1c", ligneVertical);
    printf("%1c\n", BasDroit);
}

//
//    Clients
//

// Affichage des Client d'un certain nombre a un autre
void affichageClient(Client **deb, int min, int max)
{
    Client *courant;
    int i;

    courant = *deb;

    for (i = 1; i < min; i++)
        courant = (*courant).suivant;

    printf(" N  |  Nom                  | Prenom                | Nb de personne | Nb d'enfant | Date de debut | Nombre jour | Id emplacement | Payer ?\n");
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
            printf("%03d | %-21s | %-21s | %2d             | %2d          |  %10s   |      %2d       |     Aucun      | %3s \n",
                   i++, (*courant).nom, (*courant).prenom, (*courant).nbPersonne, (*courant).nbEnfant,
                   (*courant).dateDebut, (*courant).nbJour, tmp);
        else
            printf("%03d | %-21s | %-21s | %2d             | %2d          |  %10s   |      %2d       |       %03d      | %3s \n",
                   i++, (*courant).nom, (*courant).prenom, (*courant).nbPersonne, (*courant).nbEnfant,
                   (*courant).dateDebut, (*courant).nbJour, (*courant).idEmplacement, tmp);
        courant = (*courant).suivant;
    }
}

// Ajouts clients
void ajoutClient(Client **deb, char nom[], char prenom[], int nbPersonne, int nbEnfant,
                 char dateDebut[], int nbJour, int payer, int idEmplacement, int *nb)
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
        (*courant).nbJour= nbJour;
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
        (*temp).nbJour= nbJour;
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

// Lire les clients dans le fichier de donnÃƒÆ’Ã‚Â©es
void lectureClient(Client **deb, int *nbC)
{
    FILE *fdat;
    char nom[22], prenom[22];
    int nbPersonne, nbEnfant, idEmplacement, paye, nbJour;
    char dateDebut[11];
    void ajoutClient(Client **, char[], char[], int, int, char[], int, int, int, int *);
    fdat = fopen("VanQuaquebekeVandijstadt01.dat", "r");

    fscanf(fdat, "%*[^\n]");
    fscanf(fdat, " %*[^\n]");

    fscanf(fdat, "%20s ", &nom);
    while (!feof(fdat))
    {
        fscanf(fdat, "%*c %20s %*c %2d %*c %2d %*c %10s %*c %2d %*c %2d %*c %1d %*c", &prenom, &nbPersonne,
               &nbEnfant, &dateDebut, &nbJour, &idEmplacement, &paye);
        ajoutClient(deb, nom, prenom, nbPersonne, nbEnfant, dateDebut, nbJour, paye, idEmplacement, nbC);
        fscanf(fdat, "%20s ", &nom);
    }
}


void affichageClientReserve(Client **deb, int *k)
{
    Client *courant;
    int i = 1;

    courant = *deb;

    printf(" N  |  Nom                  | Prenom                | Nb de personne | Nb d'enfant | Date de debut | Nombre jour | Id emplacement | Payer ? | Prix |\n");
    printf("----+-----------------------+-----------------------+----------------+-------------+---------------+-------------+----------------+---------+------|\n");
    while (courant != NULL)
    {
        if ((*courant).idEmplacement != -1)
            printf("%03d | %-21s | %-21s | %2d             | %2d          |  %10s   |      %2d       | %2d          | Non \n",
                   i++, (*courant).nom, (*courant).prenom, (*courant).nbPersonne, (*courant).nbEnfant,
                   (*courant).dateDebut, (*courant).nbJour, (*courant).idEmplacement);
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

    printf(" N  |  Nom                  | Prenom                | Nb de personne | Nb d'enfant | Date de debut | Nombre jour | Id emplacement | Payer ? | Prix |\n");
    printf("----+-----------------------+-----------------------+----------------+-------------+---------------+-------------+----------------+---------+------|\n");
    while (courant != NULL)
    {
        if ((*courant).idEmplacement == -1)
            printf("%03d | %-21s | %-21s | %2d             | %2d          |  %10s   |     %2d      | Aucun          | Non  |\n",
                   i++, (*courant).nom, (*courant).prenom, (*courant).nbPersonne, (*courant).nbEnfant,
                   (*courant).dateDebut, (*courant).nbJour) ;
        else
        {
            i += 1;
            k = k + 1;
        }

        courant = (*courant).suivant;
    }
}

// Lire les clients dans le fichier de donnÃƒÆ’Ã‚Â©es
void ecritureClient(Client **deb, int *nbc)
{
    FILE *fres;
    fres = fopen("VanQuaquebekeVandijstadt01.dat", "w");
    Client *courant = *deb;

    int i;

    fprintf(fres, "Nom                  | Prenom               |  Nb   | NbEnfants |   Debut    | Nb Jour    | Emplacement| Payer |\n");
    fprintf(fres, "---------------------+----------------------+-------+-----------+------------+------------+------------+-------|\n");

    while (courant != NULL)
    {
        fprintf(fres, "%-20s | %-20s |  %2d   |    %2d     | %10s |     %2d     |     %2d     |   %1d   |\n", (*courant).nom, (*courant).prenom,
                (*courant).nbPersonne, (*courant).nbEnfant, (*courant).dateDebut, (*courant).nbJour,
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

    printf(" Num |  Type      | mettre Carre | Nb de personne max | Elec | Eau | Wifi  | Reserve | Prix  | \n");
    printf("-----+------------+--------------+--------------------+------+-----+-------+---------+-------| \n");
    while (courant != NULL && i <= max)
    {
        printf(" %03d | %-10s |     %3d      |         %2d         |  %1d   |  %1d  |  %1d    |    %1d    | %5.2f | \n",
               (*courant).num, (*courant).type, (*courant).superficie, (*courant).nbPersonneMax,
               (*courant).electricite, (*courant).eau, (*courant).wifi, (*courant).reserve, (*courant).prix);
        i++;
        courant = (*courant).suivant;
    }
}

// Ajouter un emplacement
void ajouterEmplacement(Emplacement **deb, char type[], int superficie, int nbMaxPers, bool electricite, bool eau, bool wifi, float prix, int *nb)
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
        (*courant).prix = prix;
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
        (*courant).prix = prix;
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
void ajouterEmplacementL(Emplacement **deb, char type[], int superficie, int nbMaxPers, bool electricite, bool eau, bool wifi, bool reserve, float prix, int *nb)
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
        (*courant).prix = prix;
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
        (*temp).prix = prix;
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
void lectureEmplacement(Emplacement **deb, int *nbE)
{
    FILE *fdat;
    int num, superficie, nbPersonneMax;
    char type[11];
    int electricite, eau, wifi, reserve;
    float prix;
    void ajouterEmplacementL(Emplacement **, char[], int, int, bool, bool, bool, bool , float,int *);
    fdat = fopen("VanQuaquebekeVandijstadt02.dat", "r");
    fscanf(fdat, "%*[^\n]");
    fscanf(fdat, " %*[^\n]");

    fscanf(fdat, "%2d ", &num);
    while (!feof(fdat))
    {
        fscanf(fdat, "%*c %8s %*c %3d %*c %2d %*c %1d %*c %1d %*c %1d %*c %1d %*c %5f %*c", &type, &superficie, &nbPersonneMax, &electricite, &eau, &wifi, &reserve, &prix);
        ajouterEmplacementL(deb, type, superficie, nbPersonneMax, electricite, eau, wifi, reserve, prix, nbE);
//        printf("%2d %9s %3d %2d %1d %1d %1d %1d\n", num, type, superficie, nbPersonneMax, electricite, eau, wifi, reserve);
        fscanf(fdat, "%2d ", &num);
    }
}

// Lire les clients dans le fichier de donnees
void ecritureEmplacement(Emplacement **deb, int *nbc)
{
    FILE *fres;
    fres = fopen("VanQuaquebekeVandijstadt02.dat", "w");
    Emplacement *courant = *deb;

    int i;

    fprintf(fres, "Num | Type     | mCarre | NbPersonMax | Elec | Eau |  Wifi | Reserve | Prix  |\n");
    fprintf(fres, "----+----------+--------+-------------+------+-----+-------+---------+-------|\n");

    while (courant != NULL)
    {
        fprintf(fres, "%3d | %-9s|   %3d  |      %2d     |  %1d   |  %1d  |   %1d   |    %1d    | %5.2f |\n",
                (*courant).num, (*courant).type, (*courant).superficie, (*courant).nbPersonneMax,
                (*courant).electricite, (*courant).eau, (*courant).wifi, (*courant).reserve, (*courant).prix);
        courant = (*courant).suivant;
    }
}


void annuler(Client **debC, Emplacement **debE, int *nbC, int *nbE)
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

    // Supprimer client
    for (i = 1; i < choixC; i++)
        courantC = (*courantC).suivant;

    numEmplacement = (*courantC).idEmplacement;
	supprimerClient(debC, choixC, nbC);
	
	// Supprimer emplacement
	// A modifier
	for(i =1;i<=numEmplacement;i++)
        courantE = (*courantE).suivant;
    (*courantE).reserve=0;

    printf("Reservation annuler !");
}
/*
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
/*
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
}*/
