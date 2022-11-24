#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>

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
    struct Client *suivant;
} Client;
typedef struct Emplacement
{
    int num;
    char type[9];
    int superficie;
    int nbPersonneMax;
    bool electricite;
    bool eau;
    bool wifi;
    struct Emplacement *suivant;
} Emplacement;
void main()
{
    // Declaration
    Client *debC;
    int nbC = 0;
    // Initalisation

    // Declaration de methode
    void affichageClient(Client **);
    void ajoutClient(Client **, char[], char[], int, int, char[], char[], int *);
    void supprimerClient(Client **, int, int *);

    // Netoyage du terminal
    // system("cls");

    // Creation du premier Client
    debC = NULL;

    // TEST !!
    // Test Clients

    // Test d'ajouts
    ajoutClient(&debC, "Van Quaquebeke", "Nathan", 2, 0, "24/11/2022", "27/11/2022", &nbC);
    ajoutClient(&debC, "Vandijstadt", "Nicolas", 4, 0, "25/11/2022", "26/11/2022", &nbC);
    ajoutClient(&debC, "xxxxxxxxxxxxxxxxxxxxxxxxx", "xxxxxxxxxxxxxxxxxxxxxxxxx", 0, 0, "00/00/0000", "00/00/0000", &nbC);

    // Test suppression
    printf("Suppression du 1er (Van Quaquebeke):\n");
    supprimerClient(&debC, 3, &nbC);
    affichageClient(&debC);
    printf("Suppression du 2e (XXXXXX) :\n");
    supprimerClient(&debC, 2, &nbC);
    affichageClient(&debC);
}

//
//    Clients
//

// Gestion des Client
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
            // on se d�place jusqu'� la bonne adresse
            for (i = 1; i < place - 1; i++)
            {
                courant = courant->suivant;
            }
            if (place != *n)
            {
                // on fait dispara�tre un maillon de la chaine
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
// pour encoder un emplacment
void reserver(int id, int idEmplacement)
{
}
// Affichage des Client
void affichageClient(Client **deb)
{
    Client *courant;
    int i = 1;

    courant = *deb;

    printf(" N  |  Nom                  | Prenom                | Nb de personne | Nb d'enfant | Date de debut | Date de fin \n");
    printf("----+-----------------------+-----------------------+----------------+-------------+---------------+-------------\n");
    while (courant != NULL)
    {
        printf("%03d | %-21s | %-21s | %2d             | %2d          |  %10s   | %10s \n",
               i++, (*courant).nom, (*courant).prenom, (*courant).nbPersonne, (*courant).nbEnfant,
               (*courant).dateDebut, (*courant).dateFin);
        courant = (*courant).suivant;
    }
    //    while (courant != NULL)
    //    {
    //        printf("%03d | %7x | %-20s |%7x\n",
    //               i++, courant, (*courant).nom, (*courant).suivant);
    //        courant = (*courant).suivant;
    //    }
}
