#include <stdio.h>
#include <string.h>
#include <stdlib.h>

// Creation des structure
typedef struct Client
{
    char nom[50];
    char prenom[50];
    int nbPersonne;
    int nbEnfant;
    char dateDebut[10];
    char dateFin[10];
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
    ajoutClient(&deb, "Vandijstadt", "Nicolas", 4, 0, "24/11/2022", "27/11/2022");

    // Affichage du client
    affichageClient(&deb);
}

//------- A finir (pour ajouter pas pour creer)
// Gestion des Client
void ajoutClient(Client **deb, char nom[], char prenom[], int nbPersonne, int nbEnfant, char dateDebut[], char dateFin[])
{
	// Declaration
    Client *courant, *intercale;
    
    // On verifie si il exist deja un element dans la liste
    if (*deb == NULL)
    {
    	// on alloue de la memoire pour le client
        courant = malloc(sizeof(Client));
        
        // On declarre que c'est le premier element
        *deb=courant;
        
        // Assigne les valeurs
        strcpy((*courant).nom, nom);
        strcpy((*courant).prenom, prenom);
        (*courant).nbPersonne = nbPersonne;
        (*courant).nbEnfant = nbEnfant;
        strcpy((*courant).dateDebut, dateDebut);
        strcpy((*courant).dateFin, dateFin);
        (*courant).suivant = NULL;
    }
    else{
    	
    	// on alloue de la memoire pour le client
        intercale = malloc(sizeof(Client));
        
        // Assigne les valeurs
        strcpy((*intercale).nom, nom);
        strcpy((*intercale).prenom, prenom);
        (*intercale).nbPersonne = nbPersonne;
        (*intercale).nbEnfant = nbEnfant;
        strcpy((*intercale).dateDebut, dateDebut);
        strcpy((*intercale).dateFin, dateFin);
        (*intercale).suivant = NULL;
        
        // Recherche ou mettre
        do{
        	
        	courant = (*courant).suivant;
		}while (courant != NULL);
        courant=intercale;
	}
}
// void supprimerClient(Client **deb)
// {
// }
// Affichage des Client
void affichageClient(Client **deb)
{
    Client *courant;
    int i;

    courant = *deb;
    while (courant != NULL)
    {
        printf("*** %d   %x %-20s %d %x ***\n",
               i, courant, (*courant).nom, (*courant).suivant);
        courant = (*courant).suivant;
    }
}
