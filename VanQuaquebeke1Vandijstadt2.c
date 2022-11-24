#include <stdio.h>
#include <string.h>
#include <stdlib.h>

// Creation des structure
typedef struct Client
{
    char nom[22];
    char prenom[22];
    int nbPersonne;
    int nbEnfant;
    char dateDebut[11];
    char dateFin[11];
    struct Client *suivant;
} Client;

void main()
{
    // Declaration
    Client *deb, *courant, *suivant, *intercale;

    // Initalisation

    // Declaration de methode
    void affichageClient(Client **);
    void ajoutClient(Client **, char[], char[], int, int, char[], char[]);

    // Netoyage du terminal
    // system("cls");

    // Creation du premier Client
    deb = NULL;
    ajoutClient(&deb, "Van Quaquebeke", "Nathan", 2, 0, "24/11/2022", "27/11/2022");
    ajoutClient(&deb, "Vandijstadt", "Nicolas", 4, 0, "25/11/2022", "26/11/2022");
    ajoutClient(&deb, "xxxxxxxxxxxxxxxxxxxxxxxxxxx", "Nicolas", 4, 0, "25/11/2022", "26/11/2022");

    // Affichage du client
    affichageClient(&deb);
    
}

//------- A finir (pour ajouter pas pour creer)
// Gestion des Client
void ajoutClient(Client **deb, char nom[], char prenom[], int nbPersonne, int nbEnfant, char dateDebut[], char dateFin[])
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
        (*temp).nbPersonne = nbPersonne;
        (*temp).nbEnfant = nbEnfant;
        strcpy((*temp).dateDebut, dateDebut);
        strcpy((*temp).dateFin, dateFin);
        (*temp).suivant = NULL;

        // Recherche ou mettre
        courant = *deb;
        while (0==0)
        {
        	if((*courant).suivant==NULL){
        		break;
			}
            courant = (*courant).suivant;
        } 
        (*courant).suivant = temp;
    }
}
// void supprimerClient(Client **deb)
// {
// }
// Affichage des Client
void affichageClient(Client **deb)
{
    Client *courant;
    int i = 0;

    courant = *deb;

        printf(" N  |  Nom                  | Prenom               | Nb de personne | Nb d'enfant | Date de debut | Date de fin \n");
        printf("----+-----------------------+----------------------+----------------+-------------+---------------+-------------\n");
        while (courant != NULL)
        {
            printf("%03d | %-21s | %-21s | %2d             | %2d          | %10s | %10s \n",
                   i++, (*courant).nom,(*courant).prenom,(*courant).nbPersonne,(*courant).nbEnfant,
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
